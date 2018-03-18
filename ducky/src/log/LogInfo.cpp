/*
 * LogInfo.cpp
 *
 *  Created on: 2018年3月13日
 *      Author: liyawu
 */

#include <ducky/log/LogInfo.h>

namespace ducky {
namespace log {

LogInfo::LogInfo() :
		logLevel(LL_INFO), logTime(time(0)), lineNumber(0) {
	//
}

LogInfo::LogInfo(const LogLevel& _logLevel, const std::string& logMessage,
		const std::string& logModule, const LogType& logType, ducky::datetime::DateTime logTime,
		const std::string& fileName, const std::string& functionName, unsigned int lineNumber) :
		logLevel(LL_INFO) {
	this->logLevel = _logLevel;
	this->logMessage = logMessage;
	this->logModule = logModule;
	this->logType = logType;
	this->logTime = logTime;
	this->fileName = fileName;
	this->functionName = functionName;
	this->lineNumber = lineNumber;
}

LogInfo::~LogInfo() {
	//
}

const std::string& LogInfo::getFileName() const {
	return fileName;
}

void LogInfo::setFileName(const std::string& fileName) {
	this->fileName = fileName;
}

const std::string& LogInfo::getFunctionName() const {
	return functionName;
}

void LogInfo::setFunctionName(const std::string& functionName) {
	this->functionName = functionName;
}

unsigned int LogInfo::getLineNumber() const {
	return lineNumber;
}

void LogInfo::setLineNumber(unsigned int lineNumber) {
	this->lineNumber = lineNumber;
}

LogLevel LogInfo::getLogLevel() const {
	return logLevel;
}

void LogInfo::setLogLevel(LogLevel logLevel) {
	this->logLevel = logLevel;
}

const std::string& LogInfo::getLogModule() const {
	return logModule;
}

void LogInfo::setLogModule(const std::string& logModule) {
	this->logModule = logModule;
}

ducky::datetime::DateTime LogInfo::getLogTime() const {
	return logTime;
}

void LogInfo::setLogTime(ducky::datetime::DateTime logTime) {
	this->logTime = logTime;
}

const LogType& LogInfo::getLogType() const {
	return logType;
}

void LogInfo::setLogType(const LogType& logType) {
	this->logType = logType;
}

const std::string& LogInfo::getLogMessage() const {
	return logMessage;
}

void LogInfo::setLogMessage(const std::string& logMessage) {
	this->logMessage = logMessage;
}

std::string LogInfo::toXml() const {
	return "";
}

void LogInfo::fromXml(const std::string& xml) {
	//
}

LogType::LogType() {
}

LogType::LogType(const std::string& name) {
	this->name = name;
}

LogType::LogType(const char* name) {
	if(NULL != name) this->name = name;
}

const std::string& LogType::getName() const {
	return name;
}

void LogType::setName(const std::string& name) {
	this->name = name;
}

LogType::operator std::string() const {
	return this->name;
}

LogType& LogType::operator=(const std::string& name) {
	this->name = name;
	return *this;
}

bool LogType::operator==(const std::string& name) const {
	return (this->name == name);
}

bool LogType::operator==(const LogType& logType) const {
	return (this->name == logType.name);
}

} /* namespace log */
} /* namespace ducky */

std::ostream& operator<<(std::ostream& o, const ducky::log::LogType& lt){
	o << lt.getName();
	return o;
}
