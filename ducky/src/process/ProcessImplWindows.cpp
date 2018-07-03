/*
 * ProcessImplWindows.cpp
 *
 *  Created on: 2018年7月2日
 *      Author: admin
 */
#if defined(WIN32) || defined(__MINGW32__)

#include "ProcessImplWindows.h"
#include <ducky/thread/Thread.h>
#include <cstdlib>
#include <cstdio>
#include <Windows.h>
#include <iostream>

using namespace std;
using namespace ducky::thread;

namespace ducky {
namespace process {

Process::ProcessImpl::ProcessImpl(Process* proc, const std::string& command) :
		_proc(proc), asyncRead(true),
		hRead(INVALID_HANDLE_VALUE), hWrite(INVALID_HANDLE_VALUE) {
	this->command = command;
	memset(&this->pi, 0, sizeof(PROCESS_INFORMATION));
	this->pi.hProcess = INVALID_HANDLE_VALUE;
}

Process::ProcessImpl::~ProcessImpl() {
	try {
		this->stop();
	} catch (...) {
	}
}

void Process::ProcessImpl::start() {
	this->stop();

	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	if (!::CreatePipe(&this->hRead, &this->hWrite, &sa, 0)) {
		THROW_EXCEPTION(ProcessException, "process start failed.",
			GetLastError());
	}

	STARTUPINFO si;
	si.cb = sizeof(STARTUPINFO);
	GetStartupInfo(&si);
	si.hStdError = hWrite;
	si.hStdOutput = hWrite;
	si.wShowWindow = SW_SHOW;
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	if (!::CreateProcess(NULL, (LPSTR) this->command.c_str(),
			NULL, NULL, TRUE, 0, NULL, this->workDir.c_str(), &si, &this->pi)) {
		THROW_EXCEPTION(ProcessException, "process start failed.",
				GetLastError());
	}

	if (this->asyncRead) {
		this->readThread.reset(new Thread(&Process::ProcessImpl::doReadData, this));
		this->readThread->start();
	}

	this->watchThread.reset(new Thread(&Process::ProcessImpl::watchTerminated, this));
	this->watchThread->start();
}

void Process::ProcessImpl::stop() {
	if (INVALID_HANDLE_VALUE == this->pi.hProcess)
		return;

	::TerminateProcess(this->pi.hProcess, 0);

	if (this->watchThread.get()) {
		this->watchThread->stop();
		this->watchThread->join();
		this->watchThread.reset();
	}

	if (this->readThread.get()) {
		this->readThread->stop();
		this->readThread->join();
		this->readThread.reset();
	}

	if(INVALID_HANDLE_VALUE != this->hRead){
		CloseHandle(this->hRead);
	}

	if(INVALID_HANDLE_VALUE != this->hWrite){
		CloseHandle(this->hWrite);
	}
	CloseHandle(this->pi.hProcess);
	memset(&this->pi, 0, sizeof(PROCESS_INFORMATION));
	this->pi.hProcess = INVALID_HANDLE_VALUE;
	this->hRead = INVALID_HANDLE_VALUE;
	this->hWrite = INVALID_HANDLE_VALUE;
}

void Process::ProcessImpl::watchTerminated(){
	this->waitForFinished();
	if(INVALID_HANDLE_VALUE != this->hWrite){
		CloseHandle(this->hWrite);
		this->hWrite = INVALID_HANDLE_VALUE;
	}
}

void Process::ProcessImpl::waitForFinished() {
	if (INVALID_HANDLE_VALUE == this->pi.hProcess)
		return;
	::WaitForSingleObject(this->pi.hProcess, INFINITE);
}

int Process::ProcessImpl::readData(char* buf, int bufLen){
	if (INVALID_HANDLE_VALUE == this->pi.hProcess
			|| INVALID_HANDLE_VALUE == this->hRead
			|| this->asyncRead)
			return -1;

	DWORD readBytes = 0;
	if(ReadFile(this->hRead, buf, bufLen, &readBytes, NULL)){
		return readBytes;
	}
	return -1;
}

void Process::ProcessImpl::doReadData() {
	if (INVALID_HANDLE_VALUE == this->pi.hProcess)
		return;

	const DWORD bufLen = 2048;
	char buf[bufLen];
	DWORD readBytes = 0;
	while (ReadFile(this->hRead, buf, bufLen, &readBytes, NULL)) {
		if(readBytes > 0){
			this->_proc->onReadData(buf, readBytes);
		}else{
			break;
		}
	}
}

int Process::ProcessImpl::GetPid() {
	return ::GetProcessId(NULL);
}

int Process::ProcessImpl::GetPPid() {
	return 0;
}

int Process::ProcessImpl::Exec(const std::string& command, bool wait) {
	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	si.cb = sizeof(STARTUPINFO);
	GetStartupInfo(&si);
	si.hStdError = NULL;
	si.hStdOutput = NULL;
	si.wShowWindow = SW_SHOW;
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	if (!::CreateProcess(NULL, (LPSTR) command.c_str(),
			NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
		THROW_EXCEPTION(ProcessException, "process start failed.",
				GetLastError());
	}

	if(wait){
		::WaitForSingleObject(pi.hProcess, INFINITE);
	}

	return pi.dwProcessId;
}

const std::string& Process::ProcessImpl::getCommand() const {
	return command;
}

void Process::ProcessImpl::setCommand(const std::string& command) {
	this->command = command;
}

bool Process::ProcessImpl::isAsyncRead() const {
	return asyncRead;
}

void Process::ProcessImpl::setAsyncRead(bool asyncRead) {
	if (INVALID_HANDLE_VALUE != this->pi.hProcess){
		THROW_EXCEPTION(ProcessException, "process is running.", -1);
	}
	this->asyncRead = asyncRead;
}

const std::string& Process::ProcessImpl::getWorkDir() const {
	return workDir;
}

void Process::ProcessImpl::setWorkDir(const std::string& workDir) {
	this->workDir = workDir;
}

} /* namespace process */
} /* namespace ducky */

#endif
