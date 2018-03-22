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
	this->done();
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

Log& Log::put(const ducky::variant::Variant& logMsg) {
	MutexLocker lk(this->_mutex);
	this->logBuffer << logMsg.toString();
	return *this;
}

Log& Log::operator()(const ducky::variant::Variant& logMsg) {
	return this->put(logMsg);
}

Log& Log::operator()(const LogLevel& logLevel){
	this->setLogLevel(logLevel);
	return *this;
}

Log& Log::operator()(const LogType& logType){
	this->setLogType(logType);
	return *this;
}

Log& Log::done(const LogType& type) {
	string logInfo;
	{
		MutexLocker lk(this->_mutex);
		logInfo = this->logBuffer.str();

		if (logInfo.empty())
			return *this;
		this->logBuffer.clear();
		this->logBuffer.str("");
	}

	this->log(
			LogInfo(this->logLevel, logInfo, this->module,
					type.getName().empty() ? this->logType : type,
					DateTime::now(), fileName, this->functionName,
					this->lineNumber));

	return *this;
}

Log& Log::done(const std::string& type){
	return this->done(LogType(type));
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

Log& Log::setLogType(const std::string& logType){
	return this->setLogType(LogType(logType));
}

const std::string& Log::getFileName() const {
	return fileName;
}

void Log::setFileName(const std::string& fileName) {
	this->fileName = fileName;
}

const std::string& Log::getFunctionName() const {
	return functionName;
}

void Log::setFunctionName(const std::string& functionName) {
	this->functionName = functionName;
}

unsigned int Log::getLineNumber() const {
	return lineNumber;
}

void Log::setLineNumber(unsigned int lineNumber) {
	this->lineNumber = lineNumber;
}

} /* namespace log */
} /* namespace ducky */
