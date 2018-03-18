/*
 * Logger.cpp
 *
 *  Created on: 2018年3月13日
 *      Author: liyawu
 */

#include <ducky/log/Logger.h>
#include <ducky/system/File.h>

#include <iostream>
#include <sstream>

using namespace std;
using namespace ducky::thread;
using namespace ducky::system;

namespace ducky {
namespace log {

Logger::Logger(const std::string& module) :
		logLevel(LL_INFO) {
	this->module = module;
}

Logger::~Logger() {
	this->flush();
	this->stop();
	this->join();
}

void Logger::stop() {
	Thread::stop();
	this->sem.release();
}

void Logger::log(const LogInfo& logInfo) {
	MutexLocker lk(this->mutex);
	this->logInfos.push_back(logInfo);
	this->sem.release();
}

void Logger::flush() {
	MutexLocker lk(this->mutex);
	for(std::list<LogInfo>::iterator it = this->logInfos.begin(); it != this->logInfos.end(); ++it){
		LogInfo& logInfo = *it;
		for (std::list<IAppender*>::iterator it = this->appenders.begin();
				it != this->appenders.end(); ++it) {
			IAppender* appender = *it;
			if (NULL == appender)
				continue;
			appender->log(logInfo);
		}
	}
	this->logInfos.clear();
}

void Logger::run() {
	cout << "logger[" << this->module << "] started" << endl;
	while (!this->canStop()) {
		this->sem.wait();
		if (this->canStop())
			break;
		LogInfo logInfo;

		{
			MutexLocker lk(this->mutex);
			if (this->logInfos.empty())
				continue;

			logInfo = this->logInfos.front();
			this->logInfos.pop_front();
			if (logInfo.getLogLevel() < this->getLogLevel()) {
				continue;
			}
		}

		{
			MutexLocker lk(this->mutex);
			for (std::list<IAppender*>::iterator it = this->appenders.begin();
					it != this->appenders.end(); ++it) {
				IAppender* appender = *it;
				if (NULL == appender)
					continue;
				appender->log(logInfo);
			}
		}
	}
	cout << "logger[" << this->module << "] stoped" << endl;
}

void Logger::addAppender(IAppender* appender) {
	MutexLocker lk(this->mutex);
	for (std::list<IAppender*>::iterator it = this->appenders.begin();
			it != this->appenders.end(); ++it) {
		if (*it == appender)
			return;
	}
	this->appenders.push_back(appender);
}

void Logger::removeAppender(IAppender* appender) {
	MutexLocker lk(this->mutex);
	this->appenders.remove(appender);
	delete appender;
}

const LogLevel& ducky::log::Logger::getLogLevel() const {
	return logLevel;
}

void ducky::log::Logger::setLogLevel(const LogLevel& logLevel) {
	this->logLevel = logLevel;
}

} /* namespace log */
} /* namespace ducky */
