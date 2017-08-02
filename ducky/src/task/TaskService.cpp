#include <ducky/task/TaskService.h>
#include <sstream>
#include <sys/time.h>

#include <set>
#include <ctime>
#include <iostream>

#include <ducky/thread/Thread.h>
#include <ducky/thread/Mutex.h>
#include <ducky/thread/Semaphore.h>

using namespace ducky::thread;
using namespace std;

namespace ducky {
namespace task {

class ITask::ITaskImpl {
public:
	ITaskImpl() :
			startTime(0), timeout(-1), repeatTask(false), freeAfterExecute(true), canceled(false), taskService(
					NULL) {

	}

	void setTimeout(int timeoutSec) {
		this->timeout = timeoutSec;
	}

	int getTimeout() const {
		return this->timeout;
	}

	void setStartTime(unsigned long long startTime) {
		this->startTime = startTime;
	}

	unsigned long long getStartTime() const {
		return this->startTime;
	}

	void setRepeat(bool repeatTask) {
		this->repeatTask = repeatTask;
	}

	bool isRepeat() const {
		return this->repeatTask;
	}

	void setFreeAfterExecute(bool freeAfterExecute) {
		this->freeAfterExecute = freeAfterExecute;
	}

	bool isFreeAfterExecute() const {
		return freeAfterExecute;
	}

	void cancel() {
		this->canceled = true;
	}

	bool isCanceled() const {
		return this->canceled;
	}

	TaskService* getTaskService() const {
		return this->taskService;
	}

private:
	unsigned long long startTime;
	int timeout;
	bool repeatTask;
	bool freeAfterExecute;
	bool canceled;

	friend class TaskService;
	TaskService* taskService;
};

ITask::ITask() :
		impl(new ITask::ITaskImpl) {
}

ITask::~ITask() {
	delete this->impl;
}

void ITask::setTimeout(int timeoutMSec) {
	this->impl->setTimeout(timeoutMSec);
}

int ITask::getTimeout() const {
	return this->impl->getTimeout();
}

void ITask::setRepeat(bool repeatTask) {
	this->impl->setRepeat(repeatTask);
}

bool ITask::isRepeat() const {
	return this->impl->isRepeat();
}

void ITask::setStartTime(unsigned long long startTime) {
	this->impl->setStartTime(startTime);
}

unsigned long long ITask::getStartTime() const {
	return this->impl->getStartTime();
}

void ITask::setFreeAfterExecute(bool freeAfterExecute) {
	this->impl->setFreeAfterExecute(freeAfterExecute);
}

bool ITask::isFreeAfterExecute() const {
	return this->impl->isFreeAfterExecute();
}

void ITask::cancel() {
	this->impl->cancel();
}

bool ITask::isCanceled() const {
	return this->impl->isCanceled();
}

TaskService* ITask::getTaskService() const {
	return this->impl->getTaskService();
}

//=================================================
//=================================================

class TaskService::TaskServiceImpl: public ducky::thread::Thread {
public:
	TaskServiceImpl(TaskService* taskService);
	virtual ~TaskServiceImpl();

	void addTask(ITask* task, bool removeWorkingTasks = false);
	void cancelTask(ITask* task);
	bool hasTask(ITask* task);
	void removeWorkingTask(ITask* task);
	void setWorkThreadPoolSize(int workThreadPoolSize);
	int getWorkThreadPoolSize() const;
	virtual bool stop();

private:
	void run();

	class TaskServiceWorkThread: public Thread {
	public:
		TaskServiceWorkThread(TaskService::TaskServiceImpl* service) :
				pTaskService(service), task(NULL) {
			this->setFreeOnTerminated(true);
		}

		virtual ~TaskServiceWorkThread() {
		}

		void execute(ITask* task) {
			if (this->task) {
				return;
			}
			this->task = task;
			this->sem.release();
		}

		virtual bool stop() {
			Thread::stop();
			this->sem.release();
			return true;
		}

	private:
		void run() {
			while (!this->canStop()) {
				sem.wait();
				if (this->canStop()) {
					break;
				}
				if (!this->task) {
					continue;
				}

				try {
					if (!this->task->isCanceled()) {
						this->task->execute();
					}
				} catch (...) {
				}

				if (!this->task->isCanceled() && this->task->isRepeat()) {
					this->pTaskService->addTask(this->task, true);
				} else if (this->task->isFreeAfterExecute()) {
					this->pTaskService->removeWorkingTask(this->task);
					this->task->onDone();
					delete this->task;
				}else{
					this->pTaskService->removeWorkingTask(this->task);
					this->task->onDone();
				}
				this->task = NULL;

				this->pTaskService->recycleWorkThread(this);
			}
		}

	private:
		TaskService::TaskServiceImpl* pTaskService;
		ITask* task;
		ducky::thread::Semaphore sem;
	};

	class TaskServiceWorkThread;
	friend class TaskServiceWorkThread;
	TaskServiceWorkThread* getWorkThread();
	void recycleWorkThread(TaskServiceWorkThread*);

	TaskService* taskService;
	int msecWait;
	int workThreadPoolSize;
	unsigned int currentThreadCount;
	ducky::thread::Mutex mutex;
	ducky::thread::Semaphore semWait;
	std::set<ITask*> taskList;
	std::set<ITask*> workingTaskList;
	std::set<TaskServiceWorkThread*> workThreads;
};

TaskService::TaskServiceImpl::TaskServiceImpl(TaskService* service) :
		taskService(service), msecWait(-1), workThreadPoolSize(5), currentThreadCount(0), mutex(
				true) {

}

TaskService::TaskServiceImpl::~TaskServiceImpl() {
	if (this->isRunning()) {
		this->stop();
	}
}

bool TaskService::TaskServiceImpl::stop() {
	Thread::stop();
	this->semWait.release();
	return true;
}

void TaskService::TaskServiceImpl::setWorkThreadPoolSize(int workThreadPoolSize) {
	if (workThreadPoolSize < 0) {
		stringstream str;
		str << "invalid work thread pool size: " << workThreadPoolSize;
		THROW_EXCEPTION(TaskException, str.str(), workThreadPoolSize);
	}

	MutexLocker lk(this->mutex);
	this->workThreadPoolSize = workThreadPoolSize;
	while (this->workThreads.size() >= this->workThreadPoolSize) {
		TaskServiceWorkThread* workThread = *this->workThreads.begin();
		this->workThreads.erase(this->workThreads.begin());
		workThread->stop();
		--currentThreadCount;
		return;
	}
}

int TaskService::TaskServiceImpl::getWorkThreadPoolSize() const {
	return this->workThreadPoolSize;
}

TaskService::TaskServiceImpl::TaskServiceWorkThread* TaskService::TaskServiceImpl::getWorkThread() {
	MutexLocker lk(this->mutex);
	TaskServiceWorkThread* workThread;
	if (!this->workThreads.empty()) {
		workThread = *this->workThreads.begin();
		this->workThreads.erase(this->workThreads.begin());
	} else {
		workThread = new TaskServiceWorkThread(this);
		try {
			workThread->start();
		} catch (...) {
			delete workThread;
			return NULL;
		}
		++currentThreadCount;
	}

	return workThread;
}

void TaskService::TaskServiceImpl::recycleWorkThread(TaskServiceWorkThread* workThread) {
	if (NULL == workThread)
		return;

	MutexLocker lk(this->mutex);
	if (this->workThreads.size() >= this->workThreadPoolSize) {
		workThread->stop();
		--currentThreadCount;
		return;
	}

	this->workThreads.insert(workThread);
	this->semWait.release();
}

void TaskService::TaskServiceImpl::addTask(ITask* task, bool removeWorkingTasks) {
	if (NULL == task){
		return;
	}
	MutexLocker lk(this->mutex);

	if (this->canStop()) {
		if (task->isFreeAfterExecute()) {
			delete task;
		}
		return;
	}

	if (this->taskList.find(task) != this->taskList.end()) {
		return;
	}

	if (removeWorkingTasks) {
		this->workingTaskList.erase(task);
	} else {
		if (this->workingTaskList.find(task) != this->workingTaskList.end()) {
			return;
		}
	}

	if (task->isCanceled()) {
		if (task->isFreeAfterExecute()){
			task->onDone();
			delete task;
		}
		return;
	}

	timeval tv;
	gettimeofday(&tv, NULL);
	task->setStartTime(tv.tv_sec * 1000 + tv.tv_usec / 1000);
	task->impl->taskService = this->taskService;

	if (-1 == task->getTimeout()) {
		TaskServiceWorkThread* workThread = this->getWorkThread();
		if (workThread) {
			this->workingTaskList.insert(task);
			workThread->execute(task);
			return;
		}
	}

	this->taskList.insert(task);

	int timeout = task->getTimeout();
	unsigned long long t = timeout - (tv.tv_sec * 1000 + tv.tv_usec / 1000 - task->getStartTime());

	if ((-1 == msecWait) || (t < msecWait)) {
		this->semWait.release();
	}
}

void TaskService::TaskServiceImpl::cancelTask(ITask* task) {
	if(!task) return;

	MutexLocker lk(this->mutex);

	if (this->workingTaskList.find(task) != this->workingTaskList.end()) {
		task->cancel();
	} else if (this->taskList.find(task) != this->taskList.end()) {
		task->cancel();
		this->semWait.release();
	}
}

bool TaskService::TaskServiceImpl::hasTask(ITask* task) {
	MutexLocker lk(this->mutex);

	return (this->workingTaskList.find(task) != this->workingTaskList.end())
			|| (this->taskList.find(task) != this->taskList.end());
}

void TaskService::TaskServiceImpl::removeWorkingTask(ITask* task) {
	MutexLocker lk(this->mutex);
	this->workingTaskList.erase(task);
}

void TaskService::TaskServiceImpl::run() {
	while (!this->canStop()) {
		{
			MutexLocker lk(this->mutex);
			msecWait = -1;
			timeval tv;
			gettimeofday(&tv, NULL);
			for (set<ITask*>::iterator it = this->taskList.begin(); it != this->taskList.end();
					++it) {
				ITask* task = *it;

				int timeout = task->getTimeout();
				unsigned long long t = tv.tv_sec * 1000 + tv.tv_usec / 1000 - task->getStartTime();

				if (task->isCanceled() || (timeout <= 0) || (t >= timeout)) {
					set<ITask*>::iterator itPrev = it;
					--itPrev;
					TaskServiceWorkThread* workThread = this->getWorkThread();
					if (workThread) {
						workThread->execute(task);
						this->workingTaskList.insert(task);
						this->taskList.erase(it);
						it = itPrev;
					}
				} else {
					t = timeout - t;
					if (-1 == msecWait) {
						msecWait = t;
					} else {
						msecWait = t < msecWait ? t : msecWait;
					}
				}
			}
		}

		this->semWait.wait(msecWait);
	}

	while (true) {
		MutexLocker lk(this->mutex);
		if (currentThreadCount == this->workThreads.size()) {
			while (!this->workThreads.empty()) {
				TaskServiceWorkThread* workThread = *this->workThreads.begin();
				this->workThreads.erase(this->workThreads.begin());
				workThread->stop();
				//workThread->join();
			}
			Thread::Sleep(500);
			while (!this->taskList.empty()) {
				ITask* task = *this->taskList.begin();
				this->taskList.erase(this->taskList.begin());
				delete task;
			}
			break;
		}
		Thread::Sleep(100);
	}
}

//=================================================
//=================================================

TaskService::TaskService() :
		impl(new TaskService::TaskServiceImpl(this)) {

}

TaskService::~TaskService() {
	delete this->impl;
}

void TaskService::addTask(ITask* task) {
	this->impl->addTask(task);
}

void TaskService::cancelTask(ITask* task) {
	this->impl->cancelTask(task);
}

bool TaskService::hasTask(ITask* task) {
	return this->impl->hasTask(task);
}

void TaskService::setWorkThreadPoolSize(int workThreadPoolSize) {
	this->impl->setWorkThreadPoolSize(workThreadPoolSize);
}

int TaskService::getWorkThreadPoolSize() const {
	return this->impl->getWorkThreadPoolSize();
}

void TaskService::start() {
	this->impl->start();
}

void TaskService::stop() {
	this->impl->stop();
}

void TaskService::join() {
	this->impl->join();
}

}
}

