/*
 * Tick.h
 *
 *  Created on: Nov 25, 2017
 *      Author: ducky
 */

#ifndef DATETIME_TICK_H_
#define DATETIME_TICK_H_

#include <ducky/Object.h>

namespace ducky {
namespace datetime {

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
