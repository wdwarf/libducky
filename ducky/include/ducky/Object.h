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

	void* operator new(std::size_t size);
	void operator delete(void* ptr);
	void deleteThis();

protected:
	Object();
	virtual ~Object() = 0;
};

} /* namespace ducky */

#endif /* WOBJECT_H_ */
