/*
 * Runnable.h
 *
 *  Created on: 2018年4月9日
 *      Author: liyawu
 */

#ifndef DUCKY_THREAD_RUNNABLE_H_
#define DUCKY_THREAD_RUNNABLE_H_

#include <ducky/Object.h>

namespace ducky {
namespace thread {

class Runnable: public virtual Object {
public:
	Runnable(){}
	virtual ~Runnable(){}

	virtual void run() = 0;	//线程的执行函数，必须实现这个方法。
};

} /* namespace thread */
} /* namespace ducky */

#endif /* DUCKY_THREAD_RUNNABLE_H_ */
