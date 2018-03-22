/*
 * Thread.cpp
 *
 *  Created on: 2016-10-17
 *      Author: ducky
 */

#include "ducky/thread/Thread.h"
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <cstring>
#include <cassert>
#include <sys/syscall.h>
#include <signal.h>

using namespace std;

namespace ducky {
namespace thread {

Thread::Thread() :
		running(false), canStop(false), freeOnTerminated(false) {
	memset(&this->threadId, 0, sizeof(this->threadId));
}

Thread::~Thread() {
	try {
		this->cancel();
		this->join();
	} catch (...) {
	}
}

void* Thread::ThreadFunc(Thread* pThread) {
	assert(pThread);

	pthread_cleanup_push((void (*)(void*))Thread::ThreadCancelFunc, pThread);
		try {
			assert(pThread->isInCurrentThread());
			pThread->run();
		} catch (std::exception& e) {
			cerr << e.what() << endl;
		} catch (...) {
			throw;
		}
		pthread_cleanup_pop(0);

	try {
		pThread->onTerminated();
	} catch (std::exception& e) {
		cerr << e.what() << endl;
	} catch (...) {
	}

	{
		MutexLocker lk(pThread->mutex);
		pThread->running = false;
	}
	if (pThread->freeOnTerminated) {
#ifdef __OBJ_DELETE_THIS__
		pThread->deleteThis();
#else
		delete pThread;
#endif
	}

	return NULL;
}

void Thread::ThreadCancelFunc(Thread* pThread) {
	assert(pThread);

	try {
		pThread->onCanceled();
		pThread->onTerminated();
	} catch (std::exception& e) {
		cerr << e.what() << endl;
	} catch (...) {
	}

	{
		MutexLocker lk(pThread->mutex);
		pThread->running = false;
	}
	if (pThread->freeOnTerminated) {
#ifdef __OBJ_DELETE_THIS__
		pThread->deleteThis();
#else
		delete pThread;
#endif
	}
}

void Thread::start() {
	if (this->isRunning()) {
		THROW_EXCEPTION(ThreadException, "thread is running.", 0);
	}

	this->canStop = false;
	int re = pthread_create(&this->threadId, NULL,
			(void* (*)(void*))Thread::ThreadFunc, this);
	if (0 != re) {
		THROW_EXCEPTION(ThreadException, "thread create failed..", errno);
	}

	{
		MutexLocker lk(this->mutex);
		this->running = true;
	}
}

void Thread::stop() {
	if (this->isRunning()) {
		this->canStop = true;
	}
}

void Thread::detach() {
	if (!this->isRunning()) {
		THROW_EXCEPTION(ThreadException, "thread is not running..", 0);
	}

	if (0 != pthread_detach(this->threadId)) {
		THROW_EXCEPTION(ThreadException, "thread detach failed..", errno);
	}
}

void Thread::cancel() {
	if (!this->isRunning()) {
		return;
	}

	if (0 != pthread_cancel(this->threadId)) {
		THROW_EXCEPTION(ThreadException, "thread cancel failed..", errno);
	}
}

pthread_t Thread::getThreadId() {
	return this->threadId;
}

bool Thread::isInCurrentThread() const {
	return pthread_equal(pthread_self(), this->threadId);
}

bool Thread::isRunning() const {
	return (this->running && (0 == pthread_kill(this->threadId, 0)));
}

bool Thread::isCanStop() const {
	return this->canStop;
}

void Thread::join() {
	if (!this->isRunning()) {
		return;
	}

	if (0 != pthread_join(this->threadId, NULL)) {
		THROW_EXCEPTION(ThreadException, "thread join failed..", errno);
	}
}

void Thread::Sleep(unsigned int ms) {
	usleep(ms * 1000);
}

void Thread::testcancel() {
	pthread_testcancel();
}

pid_t Thread::CurrentTid() {
	return syscall(SYS_gettid);
}

bool Thread::isFreeOnTerminated() const {
	return freeOnTerminated;
}

void Thread::setFreeOnTerminated(bool freeOnTerminated) {
	this->freeOnTerminated = freeOnTerminated;
}

bool Thread::operator==(const Thread& t) const {
	return pthread_equal(this->threadId, t.threadId);
}

} /* namespace ducky */
} /* namespace thread */

