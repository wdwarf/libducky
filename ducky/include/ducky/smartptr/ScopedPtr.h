/*
 * ScopedPtr.h
 *
 *  Created on: Oct 15, 2016
 *      Author: ducky
 */

#ifndef DUCKY_SMARTPTR_SCOPEDPTR_H_
#define DUCKY_SMARTPTR_SCOPEDPTR_H_

#include "ducky/Object.h"

namespace ducky {
namespace smartptr {

template<class T>
class ScopedPtr: virtual public Object {
public:
	typedef T type;

	ScopedPtr() :
			_ptr(0) {

	}

	ScopedPtr(type* ptr) {
		this->_ptr = ptr;
	}

	virtual ~ScopedPtr() {
		if (this->_ptr) {
			delete this->_ptr;
		}
	}

	type* operator->() const {
		return this->_ptr;
	}

	type* get() const {
		return this->_ptr;
	}

	type* reset(type* ptr = 0) {
		type* oldPtr = this->_ptr;
		this->_ptr = ptr;
		return oldPtr;
	}

	type& operator*() const {
		return *this->_ptr;
	}

	bool operator==(const ScopedPtr& sp) const {
		return this->get() == sp.get();
	}

	bool operator==(const T* p) const {
		return this->get() == p;
	}

	bool operator>(const ScopedPtr& sp) const {
		return this->get() > sp.get();
	}

	bool operator>(const T* p) const {
		return this->get() > p;
	}

	bool operator>=(const ScopedPtr& sp) const {
		return this->get() >= sp.get();
	}

	bool operator>=(const T* p) const {
		return this->get() >= p;
	}

	bool operator<(const ScopedPtr& sp) const {
		return this->get() < sp.get();
	}

	bool operator<(const T* p) const {
		return this->get() < p;
	}

	bool operator<=(const ScopedPtr& sp) const {
		return this->get() <= sp.get();
	}

	bool operator<=(const T* p) const {
		return this->get() <= p;
	}

private:
	type* _ptr;
	ScopedPtr(const ScopedPtr&);
	ScopedPtr& operator=(const ScopedPtr&);
};

} /* namespace smartptr */
} /* namespace ducky */

#endif /* DUCKY_SMARTPTR_SHAREDPTR_H_ */
