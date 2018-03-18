/*
 * Logger.h
 *
 *  Created on: 2018年3月13日
 *      Author: liyawu
 */

#ifndef LOG_LOGGER_H_
#define LOG_LOGGER_H_

#include <list>
#include <string>

#include <ducky/Object.h>
#include <ducky/thread/Thread.h>
#include <ducky/thread/Mutex.h>
#include <ducky/thread/Semaphore.h>
#include <ducky/log/LogInfo.h>
#include <ducky/log/IAppender.h>

namespace ducky {
namespace log {

class Logger : public ducky::thread::Thread{
public:
	Logger(const std::string& module);
	virtual ~Logger();

	void log(const LogInfo& logInfo);
	const LogLevel& getLogLevel() const;
	void setLogLevel(const LogLevel& logLevel);

	void addAppender(IAppender* appender);
	void removeAppender(IAppender* appender);

	void flush();

private:
	virtual void run();

	virtual void stop();

private:
	std::list<LogInfo> logInfos;
	std::list<IAppender*> appenders;
	ducky::thread::Mutex mutex;
	ducky::thread::Semaphore sem;

	std::string module;
	LogLevel logLevel;
};

} /* namespace log */
} /* namespace ducky */

#endif /* LOG_LOGGER_H_ */
