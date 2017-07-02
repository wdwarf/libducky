/*
 * Thread.cpp
 *
 *  Created on: 2016-10-17
 *      Author: ducky
 */

#include "ducky/thread/Thread.h"
#include <unistd.h>
#include <errno.h>
#include <cstring>

namespace ducky {
namespace thread {

string ToString(ThreadState state) {
	string stateName;
	switch (state) {
	case TS_RUNNING:
		stateName = "TS_RUNNING";
		break;
	case TS_STOP_REQUIRING:
		stateName = "TS_STOP_REQUIRING";
		break;
	case TS_STOPPED:
		stateName = "TS_STOPPED";
		break;
	default:
		break;
	}
	return stateName;
}

Thread::Thread() :
		threadState(TS_STOPPED), freeOnTerminated(false) {
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
	if (NULL == pThread)
		return NULL;

	pThread->threadState = TS_RUNNING;
	pthread_cleanup_push((void (*)(void*))Thread::ThreadCancelFunc, pThread);
		try {
			pThread->run();
		} catch (std::exception& e) {
		} catch (...) {
			throw;
		}
		pthread_cleanup_pop(0);

	try {
		pThread->onTerminated();
	} catch (...) {
	}

	pThread->threadState = TS_STOPPED;
	memset(&pThread->threadId, 0, sizeof(pThread->threadId));
	if (pThread->freeOnTerminated) {
		pThread->deleteThis();
	}

	return NULL;
}

void Thread::ThreadCancelFunc(Thread* pThread) {
	try {
		pThread->onCanceled();
		pThread->onTerminated();
	} catch (...) {
	}

	pThread->threadState = TS_STOPPED;
	memset(&pThread->threadId, 0, sizeof(pThread->threadId));
	if (pThread->freeOnTerminated) {
		pThread->deleteThis();
	}
}

void Thread::start() {
	if (TS_STOPPED != this->threadState) {
		THROW_EXCEPTION(ThreadException, "thread is running.", 0);
	}

	int re = pthread_create(&this->threadId, NULL,
			(void* (*)(void*))Thread::ThreadFunc, this);
	if (0 != re) {
		THROW_EXCEPTION(ThreadException, "thread create failed..", errno);
	}
}

void Thread::stop() {
	if (!this->isRunning())
		return;

	this->threadState = TS_STOP_REQUIRING;
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
		THROW_EXCEPTION(ThreadException, "thread is not running..", 0);
	}

	if (0 != pthread_cancel(this->threadId)) {
		THROW_EXCEPTION(ThreadException, "thread cancel failed..", errno);
	}
}

ThreadState Thread::getState() const {
	return this->threadState;
}

pthread_t Thread::getThreadId() {
	return this->threadId;
}

bool Thread::isRunning() const {
	return ((TS_RUNNING == this->threadState)
			|| (TS_STOP_REQUIRING == this->threadState));
}

bool Thread::canStop() {
	return (TS_STOP_REQUIRING == this->threadState);
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

void Thread::testcancel(){
	pthread_testcancel();
}

bool Thread::isFreeOnTerminated() const {
	return freeOnTerminated;
}

void Thread::setFreeOnTerminated(bool freeOnTerminated) {
	this->freeOnTerminated = freeOnTerminated;
}

bool Thread::operator==(const Thread& t) const{
	return pthread_equal(this->threadId, t.threadId);
}

} /* namespace ducky */
} /* namespace thread */

