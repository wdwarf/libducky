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
class ScopedPtr : public Object {
public:
	typedef T type;

	ScopedPtr() :
			_ptr(0) {

	}

	ScopedPtr(type* ptr) {
		this->_ptr = ptr;
	}

	virtual ~ScopedPtr() {
		if(this->_ptr)
		{
			delete this->_ptr;
		}
	}

	type* operator->() {
		return this->_ptr;
	}

	type* get() {
		return this->_ptr;
	}

	type* reset(type* ptr = 0)
	{
		type* oldPtr = this->_ptr;
		this->_ptr = ptr;
		return oldPtr;
	}

	type& operator*()
	{
		return *this->_ptr;
	}

private:
	type* _ptr;
};

} /* namespace smartptr */
} /* namespace ducky */

#endif /* DUCKY_SMARTPTR_SHAREDPTR_H_ */
