/*
 * Semaphore.cpp
 *
 *  Created on: 2016-10-26
 *      Author: liyawu
 */

#include <ducky/thread/Semaphore.h>
#include <stdarg.h>
#include <iostream>
using namespace std;

namespace ducky {
namespace thread {

Semaphore::Semaphore() : sem(new sem_t), named(false) {
	// TODO Auto-generated constructor stub
	sem_init(this->sem, 0, 0);
}

Semaphore::Semaphore(const string& name, int flag, ...) : named(true) {
	va_list ap;
	va_start(ap, flag);
	this->sem = sem_open(name.c_str(), flag, ap);
	va_end(ap);
	this->name = name;
}

Semaphore::~Semaphore() {
	// TODO Auto-generated destructor stub
	if(this->named)
	{
		sem_close(this->sem);
	}
	else{
		sem_destroy(this->sem);
		delete this->sem;
	}
}

int Semaphore::wait(int mSec) {
	if (mSec < 0) {
		return sem_wait(this->sem);
	} else {
		timespec ts;
		ts.tv_sec = mSec / 1000;
		ts.tv_nsec = (mSec - ts.tv_sec * 1000) * 1000;
		return sem_timedwait(this->sem, &ts);
	}
}

int Semaphore::release() {
	return sem_post(this->sem);
}

int Semaphore::getValue(){
	int re = 0;
	sem_getvalue(this->sem, &re);
	return re;
}

void Semaphore::unlink(){
	if(this->named){
		sem_unlink(this->name.c_str());
	}
}

} /* namespace thread */
} /* namespace comba */
