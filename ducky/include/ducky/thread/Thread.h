/*
 * Thread.h
 *
 *  Created on: 2016-10-17
 *      Author: ducky
 */

#ifndef DUCKY_THREAD_THREAD_H_
#define DUCKY_THREAD_THREAD_H_

#include <pthread.h>
#include <string>

using std::string;

namespace ducky {
namespace thread {

typedef enum {
	TS_RUNNING, TS_STOP_REQUIRING, TS_STOPPED
} ThreadState;

string ToString(ThreadState state);

class Thread {
public:
	Thread();
	virtual ~Thread();

	virtual bool start();	//启动线程
	virtual bool stop();	//停止线程
	virtual void join();	//等待线程结束
	virtual bool isRunning() const;	//线程是否正在执行

	//线程结束时的通知
	virtual void onTerminated() {
	}

	virtual ThreadState getState() const;	//线程的状态

	static void sleep(unsigned int ms);	//睡眠函数，单位为毫秒

protected:
	virtual void run() = 0;	//线程的执行函数，必须实现这个方法。
	virtual bool canStop();	//判断线程是否可以结束，当stop方法执行后，该方法返回true。

private:
	pthread_t thread;
	ThreadState threadState;
	static void* ThreadFunc(Thread* pThread);

	Thread(const Thread&);
	Thread& operator=(const Thread&);
};

} /* namespace ducky */
} /* namespace thread */

#endif /* THREAD_H_ */
