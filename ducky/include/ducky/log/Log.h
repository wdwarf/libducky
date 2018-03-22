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
#include <sstream>

#include <ducky/Object.h>
#include <ducky/log/LogInfo.h>
#include <ducky/log/Logger.h>
#include <ducky/smartptr/SharedPtr.h>
#include <ducky/thread/Mutex.h>
#include <ducky/variant/Variant.h>

namespace ducky {
namespace log {

class Log: virtual public Object {
public:
	Log();
	Log(const std::string& module);
	virtual ~Log();

	static ducky::smartptr::SharedPtr<Logger> CreateLogger(
			const std::string& module);
	static bool HasLogger(const std::string& module);
	static ducky::smartptr::SharedPtr<Logger> GetLogger(
			const std::string& module);
	static void RemoveLogger(const std::string& module);

	void log(const LogInfo& logInfo);

	Log& put(const ducky::variant::Variant& logMsg);
	Log& operator()(const ducky::variant::Variant& logMsg);
	Log& operator()(const LogLevel& logLevel);
	Log& operator()(const LogType& logType);
	Log& done(const LogType& type);
	Log& done(const std::string& type = "");

	const LogLevel& getLogLevel() const;
	Log& setLogLevel(const LogLevel& logLevel);
	const LogType& getLogType() const;
	Log& setLogType(const LogType& logType);
	Log& setLogType(const std::string& logType);
	const std::string& getFileName() const;
	void setFileName(const std::string& fileName);
	const std::string& getFunctionName() const;
	void setFunctionName(const std::string& functionName);
	unsigned int getLineNumber() const;
	void setLineNumber(unsigned int lineNumber);

private:
	std::string module;
	LogLevel logLevel;
	LogType logType;
	std::string fileName;
	std::string functionName;
	unsigned int lineNumber;
	ducky::thread::Mutex _mutex;
	ducky::smartptr::SharedPtr<Logger> logger;
	std::stringstream logBuffer;

	Log(const Log&);
	Log& operator=(const Log&);

private:
	typedef std::map<std::string, ducky::smartptr::SharedPtr<Logger> > LoggerMap;
	static LoggerMap loggers;
	static ducky::thread::Mutex mutex;
};

} /* namespace log */
} /* namespace ducky */

#endif /* LOG_LOG_H_ */
