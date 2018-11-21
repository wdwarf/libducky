/*
 * ITask.cpp
 *
 *  Created on: Oct 15, 2016
 *      Author: ducky
 */

#include <ducky/task/ITask.h>

namespace ducky {
namespace task {

//=======================================================
// class ITask
//=======================================================
ITask::ITask(const std::string& taskName, bool freeOnFinished) :
		m_taskName(taskName), m_freeOnFinished(freeOnFinished), m_timeout(0), m_StartTime(
				0), m_repeat(false), m_handling(false), m_Canceled(false), m_finished(
				false), m_taskService(NULL) {
}

ITask::~ITask() {
}

const std::string& ITask::getTaskName() const {
	return m_taskName;
}

void ITask::setTaskName(const std::string& taskName) {
	this->m_taskName = taskName;
}

bool ITask::isFreeOnFinished() const {
	return m_freeOnFinished;
}

bool ITask::isRepeat() const {
	return m_repeat;
}

void ITask::setRepeat(bool repeat) {
	m_repeat = repeat;
}

long ITask::getTimeout() const {
	return m_timeout;
}

void ITask::setTimeout(long timeout) {
	m_timeout = timeout;
}

TaskService* ITask::getTaskService() {
	return m_taskService;
}

void ITask::cancel() {
	this->setCanceled(true);
}

void ITask::onCanceled() {
}

void ITask::onFinished() {
}

bool ITask::isHandling() const {
	return m_handling;
}

void ITask::setHandling(bool handling) {
	m_handling = handling;
}

bool ITask::isCanceled() const {
	return m_Canceled;
}

void ITask::setCanceled(bool Canceled) {
	m_Canceled = Canceled;
}

bool ITask::isFinished() const {
	return m_finished;
}

void ITask::setFinished(bool finished) {
	m_finished = finished;
}

unsigned long long ITask::getStartTime() const {
	return m_StartTime;
}

void ITask::setStartTime(unsigned long long StartTime) {
	m_StartTime = StartTime;
}

void ITask::setTaskService(TaskService* taskService) {
	m_taskService = taskService;
}

} /* namespace task2 */
} /* namespace ducky */
