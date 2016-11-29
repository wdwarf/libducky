/*
 * Mutex.h
 *
 *  Created on: Oct 15, 2016
 *      Author: ducky
 */

#ifndef DUCKY_THREAD_MUTEX_H_
#define DUCKY_THREAD_MUTEX_H_

#include <ducky/Object.h>
#include <pthread.h>

namespace ducky {
namespace thread {

class Mutex : virtual public Object {
public:
	Mutex();
	virtual ~Mutex();

	void lock();
	void unlock();
	bool trylock();

private:
	pthread_mutex_t mutex;
};

class MutexLocker
{
public:
	MutexLocker(Mutex& mutex);
	~MutexLocker();

private:
	Mutex& _mutex;
};

#define MUTEX_LOCKER(m) MutexLocker lk(m)

} /* namespace thread */
} /* namespace ducky */

#endif /* DUCKY_THREAD_MUTEX_H_ */
