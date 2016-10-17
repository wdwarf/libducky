/*
 * SharedPtr.h
 *
 *  Created on: Oct 15, 2016
 *      Author: ducky
 */

#ifndef DUCKY_SMARTPTR_SHAREDPTR_H_
#define DUCKY_SMARTPTR_SHAREDPTR_H_

#include <ducky/Object.h>
#include <ducky/thread/Mutex.h>

namespace ducky {
namespace smartptr {

template<class T>
class SPHolder: public Object {
public:
	typedef T type;

	SPHolder(T* p) :
			ptr(p) {
		if (p) {
			refCount = 1;
		}
	}

	T* get() {
		ducky::thread::MutexLocker lk(mutex);
		return this->ptr;
	}

	T* operator->() {
		ducky::thread::MutexLocker lk(mutex);
		return this->ptr;
	}

	void incRef() {
		ducky::thread::MutexLocker lk(mutex);
		refCount += 1;
	}

	void release() {
		ducky::thread::MutexLocker lk(mutex);
		refCount -= 1;
		if (0 == refCount) {
			delete ptr;
			delete this;
		}
	}

	operator bool() {
		ducky::thread::MutexLocker lk(mutex);
		return (0 != this->ptr);
	}

private:
	T* ptr;
	int refCount;
	ducky::thread::Mutex mutex;
};

template<class T>
class SharedPtr: public Object {
public:
	typedef T type;

	SharedPtr() :
			sh(new SPHolder<T>(0)) {
	}

	SharedPtr(T* p) :
			sh(new SPHolder<T>(p)) {

	}

	virtual ~SharedPtr() {
		sh->release();
	}

	SharedPtr(const SharedPtr& sp) :
			sh(sp.sh) {
		sh->incRef();
	}

	SharedPtr& operator=(const SharedPtr& sp) {
		sh = sp.sh;
		sh->incRef();
		return *this;
	}

	void reset(T* p = 0) {
		sh->release();
		sh = new SPHolder<T>(p);
	}

	T* get() {
		return sh->get();
	}

	operator bool() {
		return sh->operator bool();
	}

private:
	SPHolder<T>* sh;
};

} /* namespace smartptr */
} /* namespace ducky */

#endif /* DUCKY_SMARTPTR_SHAREDPTR_H_ */
