/*
 * Mutex.cpp
 *
 *  Created on: Oct 15, 2016
 *      Author: ducky
 */

#include <ducky/thread/Mutex.h>

namespace ducky {
namespace thread {

Mutex::Mutex() {
	// TODO Auto-generated constructor stub
	pthread_mutex_init(&this->mutex, NULL);
}

Mutex::~Mutex() {
	// TODO Auto-generated destructor stub
	pthread_mutex_destroy(&this->mutex);
}

void Mutex::lock() {
	pthread_mutex_lock(&this->mutex);
}

void Mutex::unlock(){
	pthread_mutex_unlock(&this->mutex);
}

bool Mutex::trylock()
{
	return pthread_mutex_trylock(&this->mutex);
}

MutexLocker::MutexLocker(Mutex& mutex) : _mutex(mutex)
{
	this->_mutex.lock();
}

MutexLocker::~MutexLocker()
{
	this->_mutex.unlock();
}

} /* namespace thread */
} /* namespace ducky */
