/*
 * Mutex.h
 *
 *  Created on: Oct 15, 2016
 *      Author: ducky
 */

#ifndef DUCKY_THREAD_MUTEX_H_
#define DUCKY_THREAD_MUTEX_H_

#include <ducky/Object.h>
#include <ducky/exception/Exception.h>
#include <pthread.h>

namespace ducky {
namespace thread {

EXCEPTION_DEF(MutexException)

class Mutex: virtual public Object {
public:
	Mutex(bool recursive = false, bool shared = false);
	virtual ~Mutex();

	void lock();
	void unlock();
	bool trylock();
	bool isRecursive() const;
	bool isShared() const;
	operator pthread_mutex_t*();

	class Locker {
	public:
		Locker(Mutex& mutex);
		~Locker();

	private:
		Mutex& _mutex;
	};

	class Condition {
	public:
		Condition(Mutex* mutex = NULL, bool shared = false);
		~Condition();

		void setMutex(Mutex* mutex);
		int wait(int mSec = -1, Mutex* mutex = NULL);
		int lockAndWait(int mSec = -1, Mutex* mutex = NULL);
		int wakeOne();
		int wakeAll();
		bool isShared() const;

		operator pthread_cond_t*();

	private:
		Mutex* _mutex;
		pthread_cond_t cond;
		pthread_condattr_t attr;
	};

private:
	pthread_mutex_t mutex;
	pthread_mutexattr_t attr;
};

} /* namespace thread */
} /* namespace ducky */

#endif /* DUCKY_THREAD_MUTEX_H_ */
