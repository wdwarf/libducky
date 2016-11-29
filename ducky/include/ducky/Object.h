/*
 * Object.h
 *
 *  Created on: Oct 14, 2016
 *      Author: ducky
 */

#ifndef DUCKY_OBJECT_H_
#define DUCKY_OBJECT_H_

#include <string>

namespace ducky {

class Object {
public:
	virtual std::string getClassName();

protected:
	Object();
	virtual ~Object();
};

} /* namespace ducky */

#endif /* WOBJECT_H_ */
