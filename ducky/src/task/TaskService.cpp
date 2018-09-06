/*
 * TaskService.cpp
 *
 *  Created on: 2018年8月14日
 *      Author: liyawu
 */

#include <ducky/task/TaskService.h>
#include <sys/time.h>
#include <ducky/thread/Thread.h>

using namespace ducky::thread;

namespace ducky
{
namespace task
{

//=======================================================
// class FuncTask
//=======================================================
class FuncTask: public ITask
{
public:
	FuncTask(const TaskCallbackFunc& func, const std::string& taskName) :
			ITask(taskName, true), m_func(func)
	{

	}

	void execute()
	{
		try
		{
			this->m_func();
		} catch (...)
		{
		}
	}

private:
	TaskCallbackFunc m_func;
};

//=======================================================
// class ITask
//=======================================================
ITask::ITask(const std::string& taskName, bool freeOnFinished) :
		m_taskName(taskName), m_freeOnFinished(freeOnFinished), m_timeout(0), m_StartTime(0), m_repeat(false), m_handling(false), m_Canceled(false), m_finished(
				false), m_taskService(
		NULL)
{
}

ITask::~ITask()
{
}

const std::string& ITask::getTaskName() const
{
	return m_taskName;
}

void ITask::setTaskName(const std::string& taskName)
{
	this->m_taskName = taskName;
}

bool ITask::isFreeOnFinished() const
{
	return m_freeOnFinished;
}

bool ITask::isRepeat() const
{
	return m_repeat;
}

void ITask::setRepeat(bool repeat)
{
	m_repeat = repeat;
}

long ITask::getTimeout() const
{
	return m_timeout;
}

void ITask::setTimeout(long timeout)
{
	m_timeout = timeout;
}

TaskService* ITask::getTaskService()
{
	return m_taskService;
}

void ITask::cancel()
{
	this->setCanceled(true);
}

void ITask::onCanceled()
{
}

void ITask::onFinished()
{
}

bool ITask::isHandling() const
{
	return m_handling;
}

void ITask::setHandling(bool handling)
{
	m_handling = handling;
}

bool ITask::isCanceled() const
{
	return m_Canceled;
}

void ITask::setCanceled(bool Canceled)
{
	m_Canceled = Canceled;
}

bool ITask::isFinished() const
{
	return m_finished;
}

void ITask::setFinished(bool finished)
{
	m_finished = finished;
}

unsigned long long ITask::getStartTime() const
{
	return m_StartTime;
}

void ITask::setStartTime(unsigned long long StartTime)
{
	m_StartTime = StartTime;
}

void ITask::setTaskService(TaskService* taskService)
{
	m_taskService = taskService;
}

//=======================================================
// class TaskService
//=======================================================
TaskService::TaskService() :
		m_serviceThread(this), m_workThreadCount(10), m_maxWorkThreadCount(1000)
{
	//

}

TaskService::~TaskService()
{
	//
}

void TaskService::start()
{
	this->m_serviceThread.start();
}

void TaskService::stop()
{
	this->m_serviceThread.stop();
	this->notify();
}

void TaskService::join()
{
	this->m_serviceThread.join();
}

unsigned int TaskService::getTaskCount() const
{
	return this->m_tasks.size();
}

std::list<std::string> TaskService::getTaskNames() const
{
	std::list<std::string> taskNames;

	MutexLocker lk(this->m_mutex);
	for (TaskList::const_iterator it = this->m_tasks.begin(); it != this->m_tasks.end(); ++it)
	{
		taskNames.push_back((*it)->getTaskName());
	}
	return taskNames;
}

void TaskService::addTask(PTask task)
{
	MutexLocker lk(this->m_mutex);
	if (this->m_tasks.find(task) != this->m_tasks.end())
		return;

	task->setTaskService(this);
	task->setHandling(false);
	task->setCanceled(false);
	task->setFinished(false);

	timeval tv;
	gettimeofday(&tv, NULL);
	task->setStartTime(tv.tv_sec * 1000 + tv.tv_usec / 1000);
	this->m_tasks.insert(task);

	this->notify();
}

void TaskService::addTask(const TaskCallbackFunc& func, const std::string& taskName, long timeout, bool repeat)
{
	ITask* task = new FuncTask(func, taskName);
	task->setTimeout(timeout);
	task->setRepeat(repeat);
	this->addTask(task);
}

void TaskService::cancelTask(PTask task)
{
	MutexLocker lk(this->m_mutex);
	TaskList::iterator it = this->m_tasks.find(task);
	if (it != this->m_tasks.end())
	{
		task->cancel();
	}
	this->notify();
}

void TaskService::cancelTask(const std::string& taskName)
{
	MutexLocker lk(this->m_mutex);
	for (TaskList::iterator it = this->m_tasks.begin(); it != this->m_tasks.end(); ++it)
	{
		PTask task = *it;
		if (task->getTaskName() == taskName)
		{
			task->cancel();
		}
	}
	this->notify();
}

TaskService::WorkThread* TaskService::getWorkThread()
{
	TaskService::WorkThread* workThread = NULL;

	if (WorkThread::GetWorkThreadCount() > this->m_maxWorkThreadCount)
	{
		return NULL;
	}

	MutexLocker lk(this->m_mutexWorkThread);
	if (!this->m_workThreads.empty())
	{
		workThread = this->m_workThreads.front();
		this->m_workThreads.pop_front();
	}
	else
	{
		workThread = new WorkThread(this);
		try
		{
			workThread->start();
		} catch (...)
		{
			delete workThread;
			workThread = NULL;
		}
	}

	return workThread;
}

void TaskService::addWorkThread(WorkThread* workThread)
{
	MutexLocker lk(this->m_mutexWorkThread);
	if (this->m_workThreads.size() >= m_workThreadCount)
	{
		workThread->stop();
		return;
	}
	this->m_workThreads.push_back(workThread);
}

void TaskService::onStop()
{
	while (WorkThread::GetWorkThreadCount() > 0)
	{
		Thread::Sleep(100);
		this->clearWorkThreads();
	}

	MutexLocker lk(this->m_mutex);
	for (TaskList::iterator it = this->m_tasks.begin(); it != this->m_tasks.end(); ++it)
	{
		PTask task = *it;
		if (task->isFreeOnFinished())
			delete task;
	}
	this->m_tasks.clear();
}

void TaskService::clearWorkThreads()
{
	MutexLocker lk(this->m_mutexWorkThread);
	for (std::list<WorkThread*>::iterator it = this->m_workThreads.begin(); it != this->m_workThreads.end(); ++it)
	{
		(*it)->stop();
	}
	this->m_workThreads.clear();
}

void TaskService::notify()
{
	this->m_sem.release();
}

void TaskService::handleTask()
{
	time_t timeWait = -1;
	timeval tv;
	gettimeofday(&tv, NULL);

	{
		MutexLocker lk(this->m_mutex);
		for (TaskList::iterator it = this->m_tasks.begin(); it != this->m_tasks.end();)
		{
			PTask task = *it;

			if (task->isHandling())
			{
				++it;
				continue;
			}

			if (task->isFinished())
			{
				TaskList::iterator itTmp = it;
				++itTmp;
				this->m_tasks.erase(it);
				it = itTmp;

				if (task->isFreeOnFinished())
					delete task;
				continue;
			}

			long timeout = task->getTimeout();
			time_t t = tv.tv_sec * 1000 + tv.tv_usec / 1000 - task->getStartTime();
			if (task->isCanceled() || (timeout <= 0) || (t >= timeout))
			{
				WorkThread* workThread = this->getWorkThread();
				if (workThread)
				{
					task->setHandling(true);
					workThread->handleTask(task);
				}
				else
				{
					/** 工作线程不够，等待100毫秒 **/
					timeWait = timeWait > 100 ? 100 : timeWait;
				}
				++it;
				continue;
			}
			else
			{
				/** 取最小等待时间 **/
				t = timeout - t;
				if (-1 == timeWait)
				{
					timeWait = t;
				}
				else
				{
					timeWait = t < timeWait ? t : timeWait;
				}
				++it;
			}
		}
	}

	this->m_sem.wait(timeWait);
}

//=======================================================
// class TaskService::ServiceThread
//=======================================================
TaskService::ServiceThread::ServiceThread(TaskService* taskService) :
		m_taskService(taskService)
{
}

void TaskService::ServiceThread::run()
{
	while (!this->canStop())
	{
		this->m_taskService->handleTask();
	}

	this->m_taskService->onStop();
}

//=======================================================
// class TaskService::WorkThread
//=======================================================
unsigned int TaskService::WorkThread::s_WorkThreadCount = 0;
ducky::thread::Mutex TaskService::WorkThread::s_mutex;

TaskService::WorkThread::WorkThread(TaskService* taskService) :
		m_taskService(taskService), m_task(NULL)
{
	MutexLocker lk(TaskService::WorkThread::s_mutex);
	++TaskService::WorkThread::s_WorkThreadCount;
	this->setFreeOnTerminated(true);
}

TaskService::WorkThread::~WorkThread()
{
	//
}

void TaskService::WorkThread::handleTask(PTask task)
{
	MutexLocker lk(this->m_mutex);
	this->m_task = task;
	this->m_sem.release();
}

void TaskService::WorkThread::run()
{
	/** 分离工作线程 **/
	this->detach();

	while (!this->canStop())
	{
		this->m_sem.wait();

		MutexLocker lk(this->m_mutex);
		if (NULL == this->m_task)
			continue;

		if (this->m_task->isCanceled())
		{
			this->m_task->setFinished(true);
			this->m_task->onCanceled();
			this->handleFinished();
			continue;
		}

		this->m_task->execute();
		if (!this->m_task->isRepeat())
		{
			this->m_task->setFinished(true);
			this->m_task->onFinished();
		}

		this->handleFinished();
	}

	MutexLocker lk(TaskService::WorkThread::s_mutex);
	--TaskService::WorkThread::s_WorkThreadCount;
}

void TaskService::WorkThread::handleFinished()
{
	timeval tv;
	gettimeofday(&tv, NULL);

	this->m_task->setStartTime(tv.tv_sec * 1000 + tv.tv_usec / 1000);
	this->m_task->setHandling(false);
	this->m_task = NULL;
	this->m_taskService->addWorkThread(this);
	this->m_taskService->notify();
}

bool TaskService::WorkThread::stop()
{
	Thread::stop();
	this->m_sem.release();
	return true;
}

unsigned int TaskService::WorkThread::GetWorkThreadCount()
{
	MutexLocker lk(TaskService::WorkThread::s_mutex);
	return TaskService::WorkThread::s_WorkThreadCount;
}

} /* namespace Util */
} /* namespace PLib */
