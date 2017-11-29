/*
 * Tick.h
 *
 *  Created on: Nov 25, 2017
 *      Author: ducky
 */

#ifndef DATETIME_TICK_H_
#define DATETIME_TICK_H_

#include <ducky/Object.h>
#include <ducky/exception/Exception.h>

namespace ducky {
namespace datetime {

EXCEPTION_DEF(TickException)

class Tick: public Object {
public:
	Tick();
	virtual ~Tick();

	unsigned long start();
	unsigned long count() const;

	static unsigned long GetTickCount();

private:
	unsigned long tick;
};

} /* namespace datetime */
} /* namespace ducky */

#endif /* DATETIME_TICK_H_ */
