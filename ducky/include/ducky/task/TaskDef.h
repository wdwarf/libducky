/*
 * TaskDef.h
 *
 *  Created on: Oct 15, 2016
 *      Author: ducky
 */

#ifndef DUCKY_TASK_TASKDEF_H_
#define DUCKY_TASK_TASKDEF_H_

#include <ducky/exception/Exception.h>
#include <ducky/function/Function.h>

namespace ducky {
namespace task {

EXCEPTION_DEF(TaskException);

typedef ducky::function::Function0<void> TaskCallbackFunc;

}
}

#endif // DUCKY_TASK_TASKDEF_H_
