/*
 * Thread.cpp
 *
 *  Created on: 2016-10-17
 *      Author: ducky
 */

#include <ducky/thread/Thread.h>
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <cstring>
#include <cassert>

#ifdef __linux__
#include <sys/syscall.h>
#endif
#include <signal.h>

using namespace std;

namespace ducky {
namespace thread {

static bool IsValidThreadId(const pthread_t& threadId) {
	const char* p = (const char*) &threadId;
	for (size_t i = 0; i < sizeof(threadId); ++i) {
		if (0 != p[i])
			return true;
	}
	return false;
}

Thread::Thread() :
		runnable(this), _canStop(false), freeOnTerminated(false) {
	memset(&this->threadId, 0, sizeof(this->threadId));
}

Thread::Thread(Runnable& r) :
		runnable(&r), _canStop(false), freeOnTerminated(false) {
	memset(&this->threadId, 0, sizeof(this->threadId));
}

Thread::~Thread() {
	try {
		this->stop();
		this->join();

		string className = this->runnable->getClassName();
		if (string::npos != className.find("ThreadFuncWraper")
				|| string::npos != className.find("ThreadMFuncWraper")) {
			delete this->runnable;
		}
	} catch (...) {
	}
}

void* Thread::ThreadFunc(Thread* pThread) {
	assert(pThread);

	cout << "thread " << pThread->threadId << ", " << pThread->getClassName()
			<< " started" << endl;

#ifdef __linux__
	pthread_cleanup_push((void (*)(void*))Thread::ThreadCancelFunc, pThread);
#endif

		try {
			assert(pThread->isInCurrentThread());
			pThread->getRunnable()->run();
		} catch (std::exception& e) {
			cerr << e.what() << endl;
		} catch (...) {
			throw;
		}

#ifdef __linux__
		pthread_cleanup_pop(0);
#endif

	try {
		pThread->onTerminated();
	} catch (std::exception& e) {
		cerr << e.what() << endl;
	} catch (...) {
	}

	cout << "thread " << pThread->threadId << ", " << pThread->getClassName()
			<< " stoped" << endl;

	if (pThread->freeOnTerminated) {
#ifdef __OBJ_DELETE_THIS__
		pThread->deleteThis();
#else
		delete pThread;
#endif
	}

	return NULL;
}

#ifdef __linux__
void Thread::ThreadCancelFunc(Thread* pThread) {
	assert(pThread);

	try {
		pThread->onCanceled();
		pThread->onTerminated();
	} catch (std::exception& e) {
		cerr << e.what() << endl;
	} catch (...) {
	}

	if (pThread->freeOnTerminated) {
#ifdef __OBJ_DELETE_THIS__
		pThread->deleteThis();
#else
		delete pThread;
#endif
	}
}
#endif

bool Thread::start() {
	if (this->isRunning()) {
		THROW_EXCEPTION(ThreadException, "thread is running.", 0);
	}

	this->_canStop = false;

	bool re = (this->beforeStart()
			&& (0
					== pthread_create(&this->threadId, NULL,
							(void* (*)(void*))Thread::ThreadFunc, this)));
	if (!re) {
		THROW_EXCEPTION(ThreadException, "thread create failed..", errno);
	}

	return true;
}

bool Thread::beforeStart() {
	return true;
}

bool Thread::stop() {
	if (this->isRunning()) {
		this->beforeStop();
		this->_canStop = true;
	}

	return true;
}

bool Thread::beforeStop() {
	return true;
}

void Thread::run() {
	cout << "empty thread run method..." << endl;
}

bool Thread::detach() {
	return (IsValidThreadId(this->threadId) && (0 == pthread_detach(this->threadId)));
}

#ifdef __linux__
void Thread::cancel() {
	if (!this->isRunning()) {
		return;
	}

	if (0 != pthread_cancel(this->threadId)) {
		THROW_EXCEPTION(ThreadException, "thread cancel failed..", errno);
	}
}
#endif

pthread_t Thread::getThreadId() {
	return this->threadId;
}

bool Thread::isInCurrentThread() const {
	return pthread_equal(pthread_self(), this->threadId);
}

bool Thread::isRunning() const {
	return (IsValidThreadId(this->threadId) && (0 == pthread_kill(this->threadId, 0)));
}

bool Thread::canStop() const {
	return this->_canStop;
}

bool Thread::join() {
	return (IsValidThreadId(this->threadId)
			&& (0 == pthread_join(this->threadId, NULL)));
}

void Thread::Sleep(unsigned int ms) {
	usleep(ms * 1000);
}

#ifdef __linux__
void Thread::testcancel() {
	pthread_testcancel();
}
#endif

#ifdef __linux__
pid_t Thread::CurrentTid() {
	return syscall(SYS_gettid);
}
#endif

bool Thread::isFreeOnTerminated() const {
	return freeOnTerminated;
}

void Thread::setFreeOnTerminated(bool freeOnTerminated) {
	this->freeOnTerminated = freeOnTerminated;
}

bool Thread::operator==(const Thread& t) const {
	return pthread_equal(this->threadId, t.threadId);
}

Runnable* Thread::getRunnable() {
	return this->runnable;
}

} /* namespace ducky */
} /* namespace thread */
