#include <ducky/task/TaskService.h>
#include <sstream>
#include <sys/time.h>

using namespace ducky::thread;
using namespace std;

namespace ducky {
namespace task {

class ITask::ITaskImpl {
public:
	ITaskImpl() :
			startTime(0), timeout(-1), freeAfterExecute(true) {

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

	void setFreeAfterExecute(bool freeAfterExecute){
		this->freeAfterExecute = freeAfterExecute;
	}

	bool isFreeAfterExecute() const{
		return freeAfterExecute;
	}

private:
	unsigned long long startTime;
	int timeout;
	bool freeAfterExecute;
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

void ITask::setStartTime(unsigned long long startTime) {
	this->impl->setStartTime(startTime);
}

unsigned long long ITask::getStartTime() const {
	return this->impl->getStartTime();
}

void ITask::setFreeAfterExecute(bool freeAfterExecute){
	this->impl->setFreeAfterExecute(freeAfterExecute);
}

bool ITask::isFreeAfterExecute() const{
	return this->impl->isFreeAfterExecute();
}

//=================================================
//=================================================

class TaskService::TaskServiceImpl : public ducky::thread::Thread {
public:
	TaskServiceImpl();
	virtual ~TaskServiceImpl();

	void addTask(ITask* task);
	void setWorkThreadPoolSize(int workThreadPoolSize) throw (TaskException);
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
					this->task->execute();
				} catch (...) {
				}

				if(this->task->isFreeAfterExecute()){
					delete this->task;
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

	int msecWait;
	int workThreadPoolSize;
	unsigned int currentThreadCount;
	ducky::thread::Mutex mutex;
	ducky::thread::Semaphore semWait;
	std::list<ITask*> taskList;
	std::list<TaskServiceWorkThread*> workThreads;
};



TaskService::TaskServiceImpl::TaskServiceImpl() :
		msecWait(-1), workThreadPoolSize(5), currentThreadCount(0), mutex(true) {

}

TaskService::TaskServiceImpl::~TaskServiceImpl() {
	if(this->isRunning()){
		this->stop();
	}
}

bool TaskService::TaskServiceImpl::stop() {
	Thread::stop();
	this->semWait.release();
	return true;
}

void TaskService::TaskServiceImpl::setWorkThreadPoolSize(int workThreadPoolSize) throw (TaskException) {
	if (workThreadPoolSize < 0) {
		stringstream str;
		str << "invalid work thread pool size: " << workThreadPoolSize;
		THROW_EXCEPTION(TaskException, str.str(), workThreadPoolSize);
	}

	MutexLocker lk(this->mutex);
	this->workThreadPoolSize = workThreadPoolSize;
	while (this->workThreads.size() >= this->workThreadPoolSize) {
		TaskServiceWorkThread* workThread = this->workThreads.front();
		this->workThreads.pop_front();
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
		workThread = this->workThreads.front();
		this->workThreads.pop_front();
	} else {
		workThread = new TaskServiceWorkThread(this);
		if (!workThread->start()) {
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

	this->workThreads.push_back(workThread);
	this->semWait.release();
}

void TaskService::TaskServiceImpl::addTask(ITask* task) {
	if (NULL == task)
		return;
	MutexLocker lk(this->mutex);

	if (-1 == task->getTimeout()) {
		TaskServiceWorkThread* workThread = this->getWorkThread();
		if (workThread) {
			workThread->execute(task);
			return;
		}
	}

	timeval tv;
	gettimeofday(&tv, NULL);
	task->setStartTime(tv.tv_sec * 1000 + tv.tv_usec / 1000);
	this->taskList.push_back(task);

	if (-1 == msecWait) {
		this->semWait.release();
	}
}

void TaskService::TaskServiceImpl::run() {
	while (!this->canStop()) {
		{
			MutexLocker lk(this->mutex);
			msecWait = -1;
			for (list<ITask*>::iterator it = this->taskList.begin(); it != this->taskList.end();
					++it) {
				ITask* task = *it;

				int timeout = task->getTimeout();
				timeval tv;
				gettimeofday(&tv, NULL);
				unsigned long long t = tv.tv_sec * 1000 + tv.tv_usec / 1000 - task->getStartTime();

				if ((timeout <= 0) || (t >= timeout)) {
					list<ITask*>::iterator itPrev = it;
					--itPrev;
					TaskServiceWorkThread* workThread = this->getWorkThread();
					if (workThread) {
						workThread->execute(task);
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
				TaskServiceWorkThread* workThread = this->workThreads.front();
				this->workThreads.pop_front();
				workThread->stop();
				workThread->join();
			}
			break;
		}
		Thread::Sleep(100);
	}
}

//=================================================
//=================================================

TaskService::TaskService() : impl(new TaskService::TaskServiceImpl){

}

TaskService::~TaskService(){
	delete this->impl;
}

void TaskService::addTask(ITask* task){
	this->impl->addTask(task);
}

void TaskService::setWorkThreadPoolSize(int workThreadPoolSize) throw (TaskException){
	this->impl->setWorkThreadPoolSize(workThreadPoolSize);
}

int TaskService::getWorkThreadPoolSize() const{
	return this->impl->getWorkThreadPoolSize();
}

void TaskService::start(){
	this->impl->start();
}

void TaskService::stop(){
	this->impl->stop();
}

void TaskService::join(){
	this->impl->join();
}


}
}

