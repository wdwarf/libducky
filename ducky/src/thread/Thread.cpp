/*
 * Thread.cpp
 *
 *  Created on: 2016-10-17
 *      Author: ducky
 */

#include "ducky/thread/Thread.h"
#include <unistd.h>

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
		threadState(TS_STOPPED) {
}

Thread::~Thread() {
	this->join();
}

void* Thread::ThreadFunc(Thread* pThread) {
	if (NULL == pThread)
		return NULL;

	pThread->threadState = TS_RUNNING;
	try {
		pThread->run();
	} catch (...) {
	}

	try {
		pThread->onTerminated();
	} catch (...) {
	}

	pThread->threadState = TS_STOPPED;

	return NULL;
}

bool Thread::start() {
	if (TS_STOPPED != this->threadState)
		return -1;

	int re = pthread_create(&this->thread, NULL, (void* (*)(void*))Thread::ThreadFunc, this);
	return (-1 != re);
}

bool Thread::stop() {
	if (!this->isRunning())
		return true;

	this->threadState = TS_STOP_REQUIRING;
	//this->join();

	return true;
}

ThreadState Thread::getState() const {
	return this->threadState;
}

bool Thread::isRunning() const {
	return ((TS_RUNNING == this->threadState)
			|| (TS_STOP_REQUIRING == this->threadState));
}

bool Thread::canStop() {
	return (TS_STOP_REQUIRING == this->threadState);
}

void Thread::join() {
	pthread_join(this->thread, NULL);
}

void Thread::sleep(unsigned int ms) {
	usleep(ms * 1000);
}

} /* namespace ducky */
} /* namespace thread */
