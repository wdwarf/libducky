/*
 * Thread.h
 *
 *  Created on: 2016-10-17
 *      Author: ducky
 */

#ifndef DUCKY_THREAD_THREAD_H_
#define DUCKY_THREAD_THREAD_H_

#include <ducky/thread/Runnable.h>
#include <ducky/thread/Mutex.h>
#include <ducky/function/Function.h>
#include <ducky/smartptr/SharedPtr.h>
#include <pthread.h>
#include <list>

using ducky::thread::Runnable;
using ducky::thread::Mutex;

namespace ducky {
namespace thread {

typedef ducky::function::Function0<void> ThreadFunc;
typedef ducky::smartptr::SharedPtr<ducky::thread::Runnable> RunnablePtr;

class ThreadId {
public:
	ThreadId();
	ThreadId(pthread_t id);

	operator pthread_t() const;
	operator pthread_t*();
	operator bool() const;

	pthread_t getId() const;
	void setId(pthread_t id);
	bool isValid() const;
	void setValid(bool valid);

private:
	pthread_t id;
	bool valid;
};

enum ThreadState {
	TS_TERMINATED, TS_RUNNING, TS_STOP_PENDDING, TS_STOPED
};

class Thread: public thread::Runnable {
public:
	Thread(bool detached = false);
	Thread(Runnable& r, bool detached = false);
	Thread(ThreadFunc func, bool detached = false);
	virtual ~Thread();

	bool start();
	bool stop();
	void join();
	void detach();
	void exit();

	bool isRunning() const;
	bool isCanStop() const;
	virtual void run();
	RunnablePtr getRunnable();
	const ThreadId& getThreadId() const;

	bool isInCurrentThread() const;

	bool isDetached() const;
	ThreadState getState() const;

	static void Sleep(unsigned int ms);
	static void Yield();
	bool isFreeOnTerminated() const;
	void setFreeOnTerminated(bool freeOnTerminated);

private:
	ThreadId threadId;
	RunnablePtr runnable;
	ThreadState state;
	bool detached;
	bool freeOnTerminated;
	mutable Mutex mutex;

	static void* _ThreadFunc(void*);

	Thread(const Thread&);
	Thread& operator=(const Thread&);

	// for debug
public:
	class ThreadInfo {
	public:
		ThreadInfo(ThreadId tid);
		ThreadInfo(ThreadId tid, std::string threadName,
				std::string threadFuncName);

		bool operator==(const ThreadInfo&);

		const std::string& getThreadFuncName() const;
		void setThreadFuncName(const std::string& threadFuncName);
		const std::string& getThreadName() const;
		void setThreadName(const std::string& threadName);
		const ThreadId& getTid() const;
		void setTid(const ThreadId& tid);

	private:
		ThreadId tid;
		std::string threadName;
		std::string threadFuncName;
	};

	static std::list<ThreadInfo> GetAllThreadInfos();
	static unsigned int GetAllThreadCount();

private:
	static std::list<ThreadInfo> threadInfos;
	static Mutex sMutex;

	static void AddThreadInfo(const ThreadInfo&);
	static void RemoveThreadInfo(const ThreadId&);
};

} /* namespace ducky */
} /* namespace thread */

#endif /* DUCKY_THREAD_THREAD_H_ */
