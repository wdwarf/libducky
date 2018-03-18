/*
 * LogInfo.h
 *
 *  Created on: 2018年3月13日
 *      Author: liyawu
 */

#ifndef LOG_LOGINFO_H_
#define LOG_LOGINFO_H_

#include <ctime>
#include <string>

#include <ducky/Object.h>
#include <ducky/log/LogException.h>
#include <ducky/datetime/DateTime.h>

namespace ducky {
namespace log {

enum E_LogLevel {
	LL_DEBUG, LL_INFO, LL_WARNING, LL_ERROR,
};

class LogLevel: virtual public Object {
public:
	LogLevel(E_LogLevel level) :
			_level(level) {

	}

	LogLevel& operator=(E_LogLevel level) {
		this->_level = level;
		return *this;
	}

	operator E_LogLevel() const {
		return this->_level;
	}

	bool operator==(E_LogLevel level) const {
		return (this->_level == level);
	}

	bool operator==(const LogLevel& level) const {
		return (this->_level == (E_LogLevel) level);
	}

	operator std::string() {
		switch (this->_level) {
		case LL_DEBUG: {
			return "D";
		}
		case LL_INFO: {
			return "I";
		}
		case LL_WARNING: {
			return "W";
		}
		case LL_ERROR: {
			return "E";
		}
		}
		return "";
	}

private:
	E_LogLevel _level;
};

class LogType {
public:
	LogType();
	LogType(const std::string& name);
	LogType(const char* name);

	const std::string& getName() const;
	void setName(const std::string& name);

	operator std::string() const;
	LogType& operator=(const std::string& name);
	bool operator==(const std::string& name) const;
	bool operator==(const LogType& logType) const;
private:
	std::string name;
};

class LogInfo: virtual public Object {
public:
	LogInfo();
	LogInfo(const LogLevel& logLevel, const std::string& logMessage, const std::string& logModule,
			const LogType& logType, ducky::datetime::DateTime logTime, const std::string& fileName,
			const std::string& functionName, unsigned int lineNumber);
	virtual ~LogInfo();

	const std::string& getFileName() const;
	void setFileName(const std::string& fileName);
	const std::string& getFunctionName() const;
	void setFunctionName(const std::string& functionName);
	unsigned int getLineNumber() const;
	void setLineNumber(unsigned int lineNumber);
	const std::string& getLogMessage() const;
	void setLogMessage(const std::string& logMessage);
	LogLevel getLogLevel() const;
	void setLogLevel(LogLevel logLevel);
	const std::string& getLogModule() const;
	void setLogModule(const std::string& logModule);
	ducky::datetime::DateTime getLogTime() const;
	void setLogTime(ducky::datetime::DateTime logTime);
	const LogType& getLogType() const;
	void setLogType(const LogType& logType);

	std::string toXml() const;
	void fromXml(const std::string& xml);

private:
	LogLevel logLevel;
	std::string logMessage;
	std::string logModule;
	LogType logType;
	ducky::datetime::DateTime logTime;

	std::string fileName;
	std::string functionName;
	unsigned int lineNumber;
};

#define MK_LOGINFO(logLevel, logMessage, logModule, logType)\
		LogInfo(logLevel, logMessage, logModule, logType, time(0), __FILE__, __FUNCTION__, __LINE__)

} /* namespace log */
} /* namespace ducky */

std::ostream& operator<<(std::ostream& o, const ducky::log::LogType& lt);

#endif /* LOG_LOGINFO_H_ */
