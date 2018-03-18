/*
 * Log.h
 *
 *  Created on: 2018年3月13日
 *      Author: liyawu
 */

#ifndef LOG_LOG_H_
#define LOG_LOG_H_

#include <map>
#include <string>

#include <ducky/Object.h>
#include <ducky/log/LogInfo.h>
#include <ducky/log/Logger.h>
#include <ducky/smartptr/SharedPtr.h>
#include <ducky/thread/Mutex.h>

namespace ducky {
namespace log {

class Log: virtual public Object {
public:
	Log();
	Log(const std::string& module);
	virtual ~Log();

	static ducky::smartptr::SharedPtr<Logger> CreateLogger(const std::string& module);
	static bool HasLogger(const std::string& module);
	static ducky::smartptr::SharedPtr<Logger> GetLogger(const std::string& module);

	void log(const LogInfo& logInfo);
	Log& d(const std::string& logMsg, const LogType& type, const std::string& fileName = "",
			const std::string& functionName = "", unsigned int lineNumber = 0);
	Log& i(const std::string& logMsg, const LogType& type, const std::string& fileName = "",
			const std::string& functionName = "", unsigned int lineNumber = 0);
	Log& w(const std::string& logMsg, const LogType& type, const std::string& fileName = "",
			const std::string& functionName = "", unsigned int lineNumber = 0);
	Log& e(const std::string& logMsg, const LogType& type, const std::string& fileName = "",
			const std::string& functionName = "", unsigned int lineNumber = 0);

	Log& operator<<(const LogLevel& logLevel);
	Log& operator<<(const LogType& logType);
	Log& operator<<(const std::string& msg);
	Log& operator<<(const char* msg);
private:
	std::string module;
	LogLevel logLevel;
	LogType logType;
	ducky::thread::Mutex _mutex;

private:
	typedef std::map<std::string, ducky::smartptr::SharedPtr<Logger> > LoggerMap;
	static LoggerMap loggers;
	static ducky::thread::Mutex mutex;
};

} /* namespace log */
} /* namespace ducky */

#endif /* LOG_LOG_H_ */
