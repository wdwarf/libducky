/*
 * TaskService.h
 *
 *  Created On: 2018年8月14日
 *      Author: liyawu
 */

#ifndef DUCKY_TASK_TASKSERVICE_H_
#define DUCKY_TASK_TASKSERVICE_H_

#include <ducky/Object.h>
#include <ducky/thread/Thread.h>
#include <ducky/thread/Mutex.h>
#include <ducky/thread/Semaphore.h>
#include <ducky/function/Function.h>
#include <string>
#include <list>
#include <set>

namespace ducky
{
namespace task
{

class TaskService;

class ITask: virtual public ducky::Object
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

typedef ducky::function::Function0<void> TaskCallbackFunc;

class ITaskService: virtual public ducky::Object
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
};

class TaskService: virtual public ITaskService
{
public:
	TaskService();
	virtual ~TaskService();

	void start();
	void stop();
	void join();

	void addTask(PTask task);
	void addTask(const TaskCallbackFunc& func, const std::string& taskName = "", long timeout = 0, bool repeat = false);
	void cancelTask(PTask task);
	void cancelTask(const std::string& taskName);
	unsigned int getTaskCount() const;
	std::list<std::string> getTaskNames() const;

private:
	typedef std::set<PTask> TaskList;
	TaskList m_tasks;
	mutable ducky::thread::Mutex m_mutex;
	ducky::thread::Semaphore m_sem;

	void notify();
	void handleTask();
	class ServiceThread: public ducky::thread::Thread
	{
	public:
		ServiceThread(TaskService* taskService);

	private:
		void run();
		TaskService* m_taskService;
	};
	ServiceThread m_serviceThread;

	class WorkThread: public ducky::thread::Thread
	{
	public:
		WorkThread(TaskService* taskService);
		virtual ~WorkThread();

		void handleTask(PTask task);
		bool stop();

		static unsigned int GetWorkThreadCount();

	private:
		void run();
		void handleFinished();
		TaskService* m_taskService;
		PTask m_task;
		ducky::thread::Mutex m_mutex;
		ducky::thread::Semaphore m_sem;

		static unsigned int s_WorkThreadCount;
		static ducky::thread::Mutex s_mutex;
	};
	std::list<WorkThread*> m_workThreads;
	unsigned int m_workThreadCount;
	unsigned int m_maxWorkThreadCount;
	ducky::thread::Mutex m_mutexWorkThread;
	WorkThread* getWorkThread();
	void addWorkThread(WorkThread* workThread);
	void onStop();
	void clearWorkThreads();
};

} /* namespace task */
} /* namespace ducky */

#endif /* DUCKY_TASK_TASKSERVICE_H_ */
