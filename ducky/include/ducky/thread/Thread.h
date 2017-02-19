/*
 * Thread.h
 *
 *  Created on: 2016-10-17
 *      Author: ducky
 */

#ifndef DUCKY_THREAD_THREAD_H_
#define DUCKY_THREAD_THREAD_H_

#include <string>
#include <ducky/Object.h>
#include <ducky/exception/Exception.h>
#include <pthread.h>

namespace ducky {
namespace thread {

using std::string;

EXCEPTION_DEF(ThreadException)

typedef enum {
	TS_RUNNING, TS_STOP_REQUIRING, TS_STOPPED
} ThreadState;

string ToString(ThreadState state);

class Thread: virtual public Object {
public:
	Thread();
	virtual ~Thread();

	virtual void start();	//启动线程
	virtual void stop();	//设置停止标志
	virtual void detach();//分离线程
	virtual void cancel();//取消线程
	virtual void join();	//等待线程结束
	virtual bool isRunning() const;	//线程是否正在执行

	virtual ThreadState getState() const;	//线程的状态
	pthread_t getThreadId();
	bool isFreeOnTerminated() const;
	void setFreeOnTerminated(bool freeOnTerminated);

	bool operator==(const Thread& t) const;

	static void Sleep(unsigned int ms);	//睡眠函数，单位为毫秒
	static void testcancel();

protected:
	virtual void run() = 0;	//线程的执行函数，必须实现这个方法。
	virtual void onCanceled() {
	}
	//线程结束时的通知
	virtual void onTerminated() {
	}
	virtual bool canStop();	//判断线程是否可以结束，当stop方法执行后，该方法返回true。

private:
	pthread_t threadId;
	ThreadState threadState;
	bool freeOnTerminated;
	static void* ThreadFunc(Thread* pThread);
	static void ThreadCancelFunc(Thread* pThread);

	Thread(const Thread&);
	Thread& operator=(const Thread&);
};

} /* namespace ducky */
} /* namespace thread */

#endif /* THREAD_H_ */
