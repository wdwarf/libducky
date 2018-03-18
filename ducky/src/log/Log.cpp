/*
 * Log.cpp
 *
 *  Created on: 2018年3月13日
 *      Author: liyawu
 */

#include <ducky/log/Log.h>
#include <ducky/log/LogException.h>

using namespace std;
using namespace ducky::exception;
using namespace ducky::thread;

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
}

Log::~Log() {
	//
}

ducky::smartptr::SharedPtr<Logger> Log::CreateLogger(const std::string& module) {
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

void Log::log(const LogInfo& logInfo) {
	string module = this->module;
	if (module.empty()) {
		module = logInfo.getLogModule();
	}

	try {
		ducky::smartptr::SharedPtr<Logger> logger = Log::GetLogger(module);
		logger->log(logInfo);
	} catch (Exception& e) {
		cout << e.what() << endl;
	}
}

Log& Log::d(const std::string& logMsg, const LogType& type, const std::string& fileName,
		const std::string& functionName, unsigned int lineNumber) {
	this->log(
			LogInfo(LL_DEBUG, logMsg, this->module, type, time(0), fileName, functionName,
					lineNumber));
	return *this;
}

Log& Log::i(const std::string& logMsg, const LogType& type, const std::string& fileName,
		const std::string& functionName, unsigned int lineNumber) {
	this->log(
			LogInfo(LL_INFO, logMsg, this->module, type, time(0), fileName, functionName,
					lineNumber));
	return *this;
}

Log& Log::w(const std::string& logMsg, const LogType& type, const std::string& fileName,
		const std::string& functionName, unsigned int lineNumber) {
	this->log(
			LogInfo(LL_WARNING, logMsg, this->module, type, time(0), fileName, functionName,
					lineNumber));
	return *this;
}

Log& Log::e(const std::string& logMsg, const LogType& type, const std::string& fileName,
		const std::string& functionName, unsigned int lineNumber) {
	this->log(
			LogInfo(LL_ERROR, logMsg, this->module, type, time(0), fileName, functionName,
					lineNumber));
	return *this;
}

Log& Log::operator<<(const LogLevel& logLevel){
	MutexLocker lk(this->_mutex);
	this->logLevel = logLevel;
	return *this;
}

Log& Log::operator<<(const LogType& logType){
	MutexLocker lk(this->_mutex);
	this->logType = logType;
	return *this;
}

Log& Log::operator<<(const std::string& msg){
	MutexLocker lk(this->_mutex);
	this->log(LogInfo(this->logLevel, msg, this->module, this->logType, time(0), "", "", 0));
	return *this;
}

Log& Log::operator<<(const char* msg){
	MutexLocker lk(this->_mutex);
	this->log(LogInfo(this->logLevel, msg, this->module, this->logType, time(0), "", "", 0));
	return *this;
}

} /* namespace log */
} /* namespace ducky */
