/*
 * Thread.cpp
 *
 *  Created on: 2016-10-17
 *      Author: ducky
 */

#include <ducky/thread/Thread.h>
#include <iostream>
#include <cassert>
#include <cstring>
#include <time.h>
#include <errno.h>
#include <sched.h>

using namespace std;
using ducky::thread::Mutex;

namespace ducky {
namespace thread {

ThreadId::ThreadId() :
		valid(false) {
	memset(&this->id, 0, sizeof(this->id));
}

ThreadId::ThreadId(pthread_t _id) :
		id(_id), valid(true) {
}

ThreadId::operator pthread_t() const {
	return this->id;
}

ThreadId::operator pthread_t*() {
	return &this->id;
}

ThreadId::operator bool() const {
	return this->isValid();
}

pthread_t ThreadId::getId() const {
	return id;
}

void ThreadId::setId(pthread_t id) {
	this->id = id;
}

bool ThreadId::isValid() const {
	return valid;
}

void ThreadId::setValid(bool valid) {
	this->valid = valid;
}

const ThreadId& Thread::getThreadId() const {
	return threadId;
}

bool Thread::isDetached() const {
	return detached;
}

ThreadState Thread::getState() const {
	return state;
}

//=======================================================

void* Thread::_ThreadFunc(void* p) {
	assert(p);

	Thread* thread = (Thread*) p;
	RunnablePtr runnable = thread->getRunnable();
	assert(runnable);

	try {
		runnable->run();
	} catch (...) {
	}

	{
		Mutex::Locker lk(thread->mutex);
		thread->threadId.setValid(false);
		thread->state = TS_STOPED;
	}

	Thread::RemoveThreadInfo(thread->getThreadId());

	if (thread->freeOnTerminated) {
		delete thread;
	}

	return NULL;
}

static void NonDelRunnable(Runnable* r) {
}

static void DelRunnable(Runnable* r) {
	if (r)
		delete r;
}

class FuncRunnable: public Runnable {
public:
	FuncRunnable(ThreadFunc func) :
			_func(func) {
	}

	~FuncRunnable() {
	}

	void run() {
		_func();
	}

private:
	ThreadFunc _func;
};

Thread::Thread(bool _detached) :
		runnable(this, &NonDelRunnable), state(TS_TERMINATED), detached(
				_detached), freeOnTerminated(false), mutex(true) {
}

Thread::Thread(Runnable& r, bool _detached) :
		runnable(&r, &NonDelRunnable), state(TS_TERMINATED), detached(
				_detached), freeOnTerminated(false), mutex(true) {
}

Thread::Thread(ThreadFunc func, bool _detached) :
		runnable(new FuncRunnable(func), &DelRunnable), state(TS_TERMINATED), detached(
				_detached), freeOnTerminated(false), mutex(true) {
}

Thread::~Thread() {
	this->stop();
	this->join();
	while (TS_STOPED != this->state && TS_TERMINATED != this->state) {
		Yield();
	}
}

void Thread::run() {

}

bool Thread::isRunning() const {
	Mutex::Locker lk(this->mutex);
	return (TS_TERMINATED != this->state);
}

bool Thread::isCanStop() const {
	Mutex::Locker lk(this->mutex);
	return (TS_STOP_PENDDING == this->state);
}

bool Thread::isInCurrentThread() const {
	return pthread_equal(pthread_self(), this->threadId);
}

void Thread::Yield() {
	//pthread_yield();
	sched_yield();
}

void Thread::Sleep(unsigned int ms) {
	struct timespec t;
	struct timespec rmt;

	t.tv_sec = ms / 1000;
	t.tv_nsec = (ms % 1000) * 1000000;

	int re = 0;
	while (0 != (re = nanosleep(&t, &rmt))) {
		if (EINVAL == re)
			break;
		t = rmt;
	}
}

bool Thread::start() {
	if (this->isRunning() || this->isInCurrentThread())
		return false;

	Mutex::Locker lk(this->mutex);

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,
			this->detached ? PTHREAD_CREATE_DETACHED : PTHREAD_CREATE_JOINABLE);

	if (0 != pthread_create(this->threadId, &attr, &_ThreadFunc, this)) {
		this->threadId.setValid(false);
		this->state = TS_TERMINATED;
		pthread_attr_destroy(&attr);
		return false;
	}

	pthread_attr_destroy(&attr);
	this->threadId.setValid(true);
	this->state = TS_RUNNING;

	Thread::AddThreadInfo(
			ThreadInfo(this->getThreadId(), runnable->getClassName(), ""));

	return true;
}

bool Thread::stop() {
	Mutex::Locker lk(this->mutex);
	if (TS_RUNNING != this->state)
		return false;
	this->state = TS_STOP_PENDDING;
	return true;
}

void Thread::join() {
	if (this->isInCurrentThread() || !this->isRunning() || this->detached)
		return;

	if (TS_TERMINATED != this->state
			&& 0 == pthread_join(this->threadId, NULL)) {
		this->state = TS_TERMINATED;
		this->threadId.setValid(false);
	}
}

void Thread::exit() {
	if (!this->isInCurrentThread())
		return;

	this->state = TS_STOPED;
	pthread_exit(0);
}

void Thread::detach() {
	if (!this->isRunning() || this->detached)
		return;

	Mutex::Locker lk(this->mutex);
	if (0 == pthread_detach(this->threadId)) {
		this->detached = true;
	}
}

RunnablePtr Thread::getRunnable() {
	return this->runnable;
}

bool Thread::isFreeOnTerminated() const {
	return freeOnTerminated;
}

void Thread::setFreeOnTerminated(bool freeOnTerminated) {
	this->freeOnTerminated = freeOnTerminated;
}

std::list<Thread::ThreadInfo> Thread::threadInfos;
Mutex Thread::sMutex;

std::list<Thread::ThreadInfo> Thread::GetAllThreadInfos() {
	Mutex::Locker lk(sMutex);
	return threadInfos;
}

unsigned int Thread::GetAllThreadCount() {
	Mutex::Locker lk(sMutex);
	return threadInfos.size();
}

void Thread::AddThreadInfo(const ThreadInfo& info) {
	Mutex::Locker lk(sMutex);
	threadInfos.push_back(info);
}

void Thread::RemoveThreadInfo(const ThreadId& id) {
	Mutex::Locker lk(sMutex);
	threadInfos.remove(id);
}

Thread::ThreadInfo::ThreadInfo(ThreadId tid) {
	this->tid = tid;
}

Thread::ThreadInfo::ThreadInfo(ThreadId tid, std::string threadName,
		std::string threadFuncName) {
	this->tid = tid;
	this->threadName = threadName;
	this->threadFuncName = threadFuncName;
}

bool Thread::ThreadInfo::operator==(const ThreadInfo& info) {
	return pthread_equal(this->tid, info.tid);
}

const std::string& Thread::ThreadInfo::getThreadFuncName() const {
	return threadFuncName;
}

void Thread::ThreadInfo::setThreadFuncName(const std::string& threadFuncName) {
	this->threadFuncName = threadFuncName;
}

const std::string& Thread::ThreadInfo::getThreadName() const {
	return threadName;
}

void Thread::ThreadInfo::setThreadName(const std::string& threadName) {
	this->threadName = threadName;
}

const ThreadId& Thread::ThreadInfo::getTid() const {
	return tid;
}

void Thread::ThreadInfo::setTid(const ThreadId& tid) {
	this->tid = tid;
}

} /* namespace ducky */
} /* namespace thread */

