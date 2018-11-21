/*
 * ITaskService.h
 *
 *  Created on: Oct 15, 2016
 *      Author: ducky
 */

#ifndef DUCKY_TASK_ITASKSERVICE_H_
#define DUCKY_TASK_ITASKSERVICE_H_

#include <ducky/task/TaskDef.h>
#include <ducky/function/Function.h>
#include <ducky/thread/Thread.h>
#include <ducky/thread/Mutex.h>
#include <ducky/thread/Semaphore.h>
#include <ducky/task/ITask.h>
#include <list>
#include <set>
#include <string>

namespace ducky {
namespace task {

class ITaskService: virtual public Object
{
public:
	ITaskService(){}
	virtual ~ITaskService(){}

	virtual void start() = 0;
	virtual void stop() = 0;
	virtual void join() = 0;

	virtual void addTask(PTask task) = 0;
	virtual void addTask(const TaskCallbackFunc& func, const std::string& taskName = "", long timeout = 0, bool repeat = false) = 0;
	virtual void cancelTask(PTask task) = 0;
	virtual void cancelTask(const std::string& taskName) = 0;
	virtual unsigned int getTaskCount() const = 0;
	virtual std::list<std::string> getTaskNames() const = 0;
	virtual unsigned int getActiveWorkThreadCount() const = 0;
	virtual void setActiveWorkThreadCount(unsigned int activeWorkThreadCount) = 0;
	virtual unsigned int getMaxWorkThreadCount() const = 0;
	virtual void setMaxWorkThreadCount(unsigned int maxWorkThreadCount) = 0;
};

}
}

#endif // DUCKY_TASK_ITASKSERVICE_H_
