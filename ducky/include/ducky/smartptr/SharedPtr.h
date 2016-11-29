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
class DefaultDeleter : virtual public Object{
public:
	void operator()(T* ptr){ delete ptr; }
};

template<class T>
class ISPHolder: virtual public Object {
public:
	typedef T type;

	virtual T* get() = 0;

	virtual void incRef() = 0;

	virtual void release() = 0;

	virtual bool isSet() = 0;
};

template<class T, class DT>
class SPHolder: public ISPHolder<T> {
public:
	typedef T type;
	typedef DT deleter;

	SPHolder(T* p, deleter dt) :
			ptr(p), _deleter(dt) {
		if (p) {
			refCount = 1;
		}
	}

	T* get() {
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
			_deleter(ptr);
			delete this;
		}
	}

	bool isSet() {
		ducky::thread::MutexLocker lk(mutex);
		return (0 != this->ptr);
	}

private:
	T* ptr;
	deleter _deleter;
	int refCount;
	ducky::thread::Mutex mutex;
};

template<class T>
class SharedPtr: virtual public Object {
public:
	typedef T type;

	SharedPtr() :
			sh(new SPHolder<T, DefaultDeleter<T> >(0, DefaultDeleter<T>())) {
	}

	SharedPtr(T* p) :
			sh(new SPHolder<T, DefaultDeleter<T> >(p, DefaultDeleter<T>())) {
	}

	template<typename DT>
	SharedPtr(T* p, DT dt) :
			sh(new SPHolder<T, DT>(p, dt)) {
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
		sh = new SPHolder<T, DefaultDeleter<T> >(p, DefaultDeleter<T>());
	}

	template<typename DT>
	void reset(T* p, DT dt) {
		sh->release();
		sh = new SPHolder<T, DT >(p, dt);
	}

	T* operator->(){
		return sh->get();
	}

	T* get() {
		return sh->get();
	}

	operator bool() {
		return sh->isSet();
	}

private:
	ISPHolder<T>* sh;
};

} /* namespace smartptr */
} /* namespace ducky */

#endif /* DUCKY_SMARTPTR_SHAREDPTR_H_ */
