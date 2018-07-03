/*
 * Thread.h
 *
 *  Created on: 2016-10-17
 *      Author: ducky
 */

#ifndef DUCKY_THREAD_THREAD_H_
#define DUCKY_THREAD_THREAD_H_

#include <string>
#include <cstring>
#include <ducky/Object.h>
#include <ducky/exception/Exception.h>
#include <ducky/thread/Mutex.h>
#include <ducky/thread/Runnable.h>
#include <pthread.h>

namespace ducky {
namespace thread {

using std::string;

EXCEPTION_DEF(ThreadException)

class Thread: public Runnable {
public:
	Thread();
	Thread(Runnable& r);

	template<typename F>
	class ThreadFuncWraper: public Runnable {
	public:
		ThreadFuncWraper(F f) :
				_f(f) {
		}

		void run() {
			_f();
		}

	private:
		F _f;
	};

	template<typename F, class C>
	class ThreadMFuncWraper: public Runnable {
	public:
		ThreadMFuncWraper(F f, C* c) :
				_f(f), _c(c) {
		}

		void run() {
			(_c->*_f)();
		}

	private:
		F _f;
		C* _c;
	};

	template<typename F>
	Thread(F f) :
			running(false), _canStop(false), freeOnTerminated(false) {
		memset(&this->threadId, 0, sizeof(this->threadId));
		this->runnable = new ThreadFuncWraper<F>(f);
	}

	template<typename F, class C>
	Thread(F f, C* c) :
			running(false), _canStop(false), freeOnTerminated(false) {
		memset(&this->threadId, 0, sizeof(this->threadId));
		this->runnable = new ThreadMFuncWraper<F, C>(f, c);
	}

	virtual ~Thread();

	bool start();	//启动线程
	bool stop();	//设置停止标志
	void detach();	//分离线程
	void join();	//等待线程结束
	bool isRunning() const;	//线程是否正在执行

	pthread_t getThreadId();
	bool isInCurrentThread() const;
	bool isFreeOnTerminated() const;
	void setFreeOnTerminated(bool freeOnTerminated);

	bool operator==(const Thread& t) const;

	static void Sleep(unsigned int ms);	//睡眠函数，单位为毫秒

#ifdef __linux__
	virtual void cancel();	//取消线程

	static void testcancel();
	static pid_t CurrentTid();
#endif

	Runnable* getRunnable();

protected:
	virtual void run();
#ifdef __linux__
	virtual void onCanceled() {
	}
#endif
	//线程结束时的通知
	virtual void onTerminated() {
	}
	virtual bool canStop() const;	//判断线程是否可以结束，当stop方法执行后，该方法返回true。
	virtual bool beforeStart();
	virtual bool beforeStop();

private:
	pthread_t threadId;
	Runnable* runnable;
	bool running;
	bool _canStop;
	bool freeOnTerminated;
	Mutex mutex;
	static void* ThreadFunc(Thread* pThread);

#ifdef __linux__
	static void ThreadCancelFunc(Thread* pThread);
#endif

	Thread(const Thread&);
	Thread& operator=(const Thread&);
};

} /* namespace ducky */
} /* namespace thread */

#endif /* DUCKY_THREAD_THREAD_H_ */
