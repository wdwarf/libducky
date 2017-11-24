/*
 * Tick.cpp
 *
 *  Created on: Nov 25, 2017
 *      Author: ducky
 */

#include <ducky/datetime/Tick.h>
#include <ctime>

namespace ducky {
namespace datetime {

Tick::Tick() : tick(0){
	// TODO Auto-generated constructor stub

}

Tick::~Tick() {
	// TODO Auto-generated destructor stub
}

unsigned long Tick::GetTickCount() {
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

unsigned long Tick::start(){
	this->tick = Tick::GetTickCount();
	return this->tick;
}

unsigned long Tick::count() const{
	return (Tick::GetTickCount() - this->tick);
}

} /* namespace datetime */
} /* namespace ducky */