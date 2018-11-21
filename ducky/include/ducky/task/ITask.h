/*
 * ITask.h
 *
 *  Created on: Oct 15, 2016
 *      Author: ducky
 */

#ifndef DUCKY_TASK_ITASK_H_
#define DUCKY_TASK_ITASK_H_

#include <ducky/Object.h>
#include <string>

namespace ducky {
namespace task {

class TaskService;

class ITask: virtual public Object
{
public:
	ITask(const std::string& taskName = "", bool freeOnFinished = true);
	virtual ~ITask();

	void cancel();
	const std::string& getTaskName() const;
	void setTaskName(const std::string& taskName);
	bool isRepeat() const;
	void setRepeat(bool repeat);
	long getTimeout() const;
	void setTimeout(long timeout);

	bool isFreeOnFinished() const;
	bool isHandling() const;
	bool isCanceled() const;
	bool isFinished() const;

protected:
	virtual void execute() = 0;
	virtual void onCanceled();
	virtual void onFinished();

	TaskService* getTaskService();

private:
	std::string m_taskName;
	bool m_freeOnFinished;
	long m_timeout;
	unsigned long long m_StartTime;
	bool m_repeat;
	bool m_handling;
	bool m_Canceled;
	bool m_finished;

	void setHandling(bool handling);
	void setCanceled(bool Canceled);
	void setFinished(bool finished);
	unsigned long long getStartTime() const;
	void setStartTime(unsigned long long StartTime);

	friend class TaskService;
	TaskService* m_taskService;
	void setTaskService(TaskService* taskService);
};

typedef ITask* PTask;

} /* namespace task */
} /* namespace ducky */

#endif /* DUCKY_TASK_ITASK_H_ */
