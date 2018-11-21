/*
 * TaskService.h
 *
 *  Created on: Oct 15, 2016
 *      Author: ducky
 */

#ifndef DUCKY_TASK_TASKSERVICE_H_
#define DUCKY_TASK_TASKSERVICE_H_

#include <ducky/function/Function.h>
#include <ducky/thread/Thread.h>
#include <ducky/thread/Mutex.h>
#include <ducky/thread/Semaphore.h>
#include <ducky/task/ITaskService.h>
#include <ducky/task/ITask.h>
#include <list>
#include <set>
#include <string>

namespace ducky {
namespace task {

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
	unsigned int getActiveWorkThreadCount() const;
	void setActiveWorkThreadCount(unsigned int activeWorkThreadCount);
	unsigned int getMaxWorkThreadCount() const;
	void setMaxWorkThreadCount(unsigned int maxWorkThreadCount);

private:
	typedef std::set<PTask> TaskList;
	TaskList m_tasks;
	mutable ducky::thread::Mutex m_mutex;
	ducky::thread::Semaphore m_sem;

	void notify();
	void handleTask();
	class ServiceThread : public ducky::thread::Thread
	{
	public:
		ServiceThread(TaskService* taskService);

	private:
		void run();
		TaskService* m_taskService;
	};
	ServiceThread m_serviceThread;

	class WorkThread : public ducky::thread::Thread
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
	unsigned int m_activeWorkThreadCount;
	unsigned int m_maxWorkThreadCount;
	ducky::thread::Mutex m_mutexWorkThread;
	WorkThread* getWorkThread();
	void addWorkThread(WorkThread* workThread);
	void onStop();
	void clearWorkThreads();
};

}
}

#endif // DUCKY_TASK_TASKSERVICE_H_
