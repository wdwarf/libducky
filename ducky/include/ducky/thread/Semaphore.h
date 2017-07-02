/*
 * Semaphore.h
 *
 *  Created on: 2016-10-26
 *      Author: ducky
 */

#ifndef SEMAPHORE_H_
#define SEMAPHORE_H_

#include <string>
#include <ducky/Object.h>
#include <semaphore.h>

namespace ducky {
namespace thread {

using std::string;

class Semaphore: virtual public Object {
public:
	Semaphore();
	Semaphore(const string& name, int flag, ...);

	~Semaphore();

	int wait(int mSec = -1);
	int release();
	int getValue();
	void unlink();

private:
	sem_t* sem;
	string name;
	bool named;
};

} /* namespace thread */
} /* namespace ducky */
#endif /* SEMAPHORE_H_ */
