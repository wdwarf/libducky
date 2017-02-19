/*
 * Object.h
 *
 *  Created on: Oct 14, 2016
 *      Author: ducky
 */

#ifndef DUCKY_OBJECT_H_
#define DUCKY_OBJECT_H_

#include <ducky/ducky_config.h>
#include <string>

namespace ducky {

class Object {
public:
	virtual std::string getClassName() const;

	virtual bool isOnHeap() const;

	static void* operator new(std::size_t size) throw (std::bad_alloc);
	static void* operator new(std::size_t size,
			const std::nothrow_t&) throw ();
	static void *operator new(std::size_t size, void *ptr) throw ();
	void operator delete(void* ptr);
	void deleteThis();

protected:
	Object();
	virtual ~Object();
};

} /* namespace ducky */

#endif /* WOBJECT_H_ */
