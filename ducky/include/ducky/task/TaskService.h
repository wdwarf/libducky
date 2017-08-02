#ifndef TIMER_H
#define TIMER_H

#include <ducky/exception/Exception.h>

namespace ducky {
namespace task {

EXCEPTION_DEF(TaskException);

class TaskService;
class ITask: virtual public Object {
public:
	ITask();
	virtual ~ITask();

	virtual void execute() = 0;
	virtual void onDone(){}

	void setTimeout(int timeoutMSec = -1);
	int getTimeout() const;
	void setFreeAfterExecute(bool freeAfterExecute);
	bool isFreeAfterExecute() const;
	void setRepeat(bool repeatTask);
	bool isRepeat() const;
	void cancel();
	bool isCanceled() const;
	TaskService* getTaskService() const;

private:
	void setStartTime(unsigned long long startTime);
	unsigned long long getStartTime() const;

	class ITaskImpl;
	ITaskImpl* impl;

	friend class TaskService;
};

class TaskService: virtual public Object {
public:
	TaskService();
	virtual ~TaskService();

	void addTask(ITask* task);
	void cancelTask(ITask* task);
	bool hasTask(ITask* task);
	void setWorkThreadPoolSize(int workThreadPoolSize);
	int getWorkThreadPoolSize() const;
	void start();
	void stop();
	void join();

private:
	class TaskServiceImpl;
	TaskServiceImpl* impl;
};

}
}

#endif // TIMER_H
