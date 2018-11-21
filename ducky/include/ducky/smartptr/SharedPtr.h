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
#include <iostream>

using namespace std;

namespace ducky {
namespace smartptr {

template<class T>
class DefaultDeleter: virtual public Object {
public:
	void operator()(T* ptr) {
		if (ptr)
			delete ptr;
	}
};

template<class T>
class ISPHolder: virtual public Object {
public:
	virtual ~ISPHolder() {
	}

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
		refCount = 1;
	}

	virtual ~SPHolder() {
		if (ptr)
			_deleter(ptr);
	}

	T* get() {
		ducky::thread::Mutex::Locker lk(mutex);
		return this->ptr;
	}

	void incRef() {
		ducky::thread::Mutex::Locker lk(mutex);
		refCount += 1;
	}

	void release() {
		ducky::thread::Mutex::Locker lk(mutex);
		refCount -= 1;
		if (0 == refCount) {
			delete this;
		}
	}

	bool isSet() {
		ducky::thread::Mutex::Locker lk(mutex);
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
		if (this == &sp) {
			return *this;
		}
		sh->release();
		sh = sp.sh;
		sh->incRef();
		return *this;
	}

	bool operator==(const SharedPtr& sp) const {
		return this->get() == sp.get();
	}

	bool operator==(const T* p) const {
		return this->get() == p;
	}

	bool operator>(const SharedPtr& sp) const {
		return this->get() > sp.get();
	}

	bool operator>(const T* p) const {
		return this->get() > p;
	}

	bool operator>=(const SharedPtr& sp) const {
		return this->get() >= sp.get();
	}

	bool operator>=(const T* p) const {
		return this->get() >= p;
	}

	bool operator<(const SharedPtr& sp) const {
		return this->get() < sp.get();
	}

	bool operator<(const T* p) const {
		return this->get() < p;
	}

	bool operator<=(const SharedPtr& sp) const {
		return this->get() <= sp.get();
	}

	bool operator<=(const T* p) const {
		return this->get() <= p;
	}

	void reset(T* p = 0) {
		sh->release();
		sh = new SPHolder<T, DefaultDeleter<T> >(p, DefaultDeleter<T>());
	}

	template<typename DT>
	void reset(T* p, DT dt) {
		sh->release();
		sh = new SPHolder<T, DT>(p, dt);
	}

	T* operator->() const {
		return sh->get();
	}

	T* get() const {
		return sh->get();
	}

	operator bool() const {
		return sh->isSet();
	}

private:
	ISPHolder<T>* sh;
};

} /* namespace smartptr */
} /* namespace ducky */

#endif /* DUCKY_SMARTPTR_SHAREDPTR_H_ */
