/*
 * Log.cpp
 *
 *  Created on: 2018年3月13日
 *      Author: liyawu
 */

#include <ducky/log/Log.h>
#include <ducky/log/LogException.h>
#include <ducky/datetime/DateTime.h>

using namespace std;
using namespace ducky::exception;
using namespace ducky::thread;
using namespace ducky::datetime;

namespace ducky {
namespace log {

Log::LoggerMap Log::loggers;
ducky::thread::Mutex Log::mutex;

Log::Log() :
		logLevel(LL_INFO) {
}

Log::Log(const std::string& module) :
		logLevel(LL_INFO) {
	this->module = module;
	this->logger = GetLogger(this->module);
}

Log::~Log() {
	//
}

ducky::smartptr::SharedPtr<Logger> Log::CreateLogger(
		const std::string& module) {
	if (Log::HasLogger(module)) {
		return Log::GetLogger(module);
	}

	MutexLocker lk(Log::mutex);
	ducky::smartptr::SharedPtr<Logger> logger(new Logger(module));
	logger->start();
	Log::loggers.insert(make_pair(module, logger));
	return logger;
}

bool Log::HasLogger(const std::string& module) {
	MutexLocker lk(Log::mutex);
	return (Log::loggers.find(module) != Log::loggers.end());
}

ducky::smartptr::SharedPtr<Logger> Log::GetLogger(const std::string& module) {
	MutexLocker lk(Log::mutex);
	LoggerMap::iterator it = Log::loggers.find(module);
	if (it == Log::loggers.end()) {
		THROW_EXCEPTION(LogException, "logger[" + module + "] not found", -1);
	}

	return it->second;
}

void Log::RemoveLogger(const std::string& module) {
	MutexLocker lk(Log::mutex);
	LoggerMap::iterator it = Log::loggers.find(module);
	if (it != Log::loggers.end()) {
		Log::loggers.erase(it);
	}
}

void Log::log(const LogInfo& logInfo) {
	try {
		ducky::smartptr::SharedPtr<Logger> logger;
		if (module.empty()) {
			logger = Log::GetLogger(logInfo.getLogModule());
		} else {
			logger = this->logger;
		}
		logger->log(logInfo);
	} catch (Exception& e) {
		cout << e.what() << endl;
	}
}

Log& Log::d(const std::string& logMsg, const LogType& type,
		const std::string& fileName, const std::string& functionName,
		unsigned int lineNumber) {
	this->log(
			LogInfo(LL_DEBUG, logMsg, this->module, type, DateTime::now(),
					fileName, functionName, lineNumber));
	return *this;
}

Log& Log::i(const std::string& logMsg, const LogType& type,
		const std::string& fileName, const std::string& functionName,
		unsigned int lineNumber) {
	this->log(
			LogInfo(LL_INFO, logMsg, this->module, type, DateTime::now(),
					fileName, functionName, lineNumber));
	return *this;
}

Log& Log::w(const std::string& logMsg, const LogType& type,
		const std::string& fileName, const std::string& functionName,
		unsigned int lineNumber) {
	this->log(
			LogInfo(LL_WARNING, logMsg, this->module, type, DateTime::now(),
					fileName, functionName, lineNumber));
	return *this;
}

Log& Log::e(const std::string& logMsg, const LogType& type,
		const std::string& fileName, const std::string& functionName,
		unsigned int lineNumber) {
	this->log(
			LogInfo(LL_ERROR, logMsg, this->module, type, DateTime::now(),
					fileName, functionName, lineNumber));
	return *this;
}

Log& Log::put(const ducky::variant::Variant& logMsg) {
	MutexLocker lk(this->_mutex);
	this->logBuffer << logMsg.toString();
	return *this;
}

Log& Log::operator()(const ducky::variant::Variant& logMsg) {
	return this->put(logMsg);
}

Log& Log::done(const LogLevel& logLevel, const LogType& type, const std::string& fileName,
		const std::string& functionName, unsigned int lineNumber) {
	this->log(
			LogInfo(this->logLevel, this->logBuffer.str(), this->module,
					type.getName().empty() ? this->logType : type,
					DateTime::now(), fileName, functionName, lineNumber));
	MutexLocker lk(this->_mutex);
	this->logBuffer.clear();
	this->logBuffer.str("");
	return *this;
}

Log& Log::operator<<(const LogLevel& logLevel) {
	MutexLocker lk(this->_mutex);
	this->logLevel = logLevel;
	return *this;
}

Log& Log::operator<<(const LogType& logType) {
	MutexLocker lk(this->_mutex);
	this->logType = logType;
	return *this;
}

Log& Log::operator<<(const std::string& msg) {
	MutexLocker lk(this->_mutex);
	this->log(
			LogInfo(this->logLevel, msg, this->module, this->logType,
					DateTime::now(), "", "", 0));
	return *this;
}

Log& Log::operator<<(const char* msg) {
	MutexLocker lk(this->_mutex);
	this->log(
			LogInfo(this->logLevel, msg, this->module, this->logType,
					DateTime::now(), "", "", 0));
	return *this;
}

const LogLevel& Log::getLogLevel() const {
	return logLevel;
}

Log& Log::setLogLevel(const LogLevel& logLevel) {
	MutexLocker lk(this->_mutex);
	this->logLevel = logLevel;
	return *this;
}

const LogType& Log::getLogType() const {
	return logType;
}

Log& Log::setLogType(const LogType& logType) {
	MutexLocker lk(this->_mutex);
	this->logType = logType;
	return *this;
}

} /* namespace log */
} /* namespace ducky */
