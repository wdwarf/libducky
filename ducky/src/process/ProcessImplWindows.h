/*
 * ProcessImplWindows.h
 *
 *  Created on: 2018年7月2日
 *      Author: admin
 */

#if defined(WIN32) || defined(__MINGW32__)
#ifndef PROCESS_PROCESSIMPLWINDOWS_H_
#define PROCESS_PROCESSIMPLWINDOWS_H_

#include <ducky/process/Process.h>
#include <ducky/thread/Thread.h>
#include <ducky/smartptr/ScopedPtr.h>
#include <cstdlib>
#include <iostream>
#include <Windows.h>

using namespace std;
using namespace ducky::thread;

namespace ducky {
namespace process {

class Process::ProcessImpl {
public:

	ProcessImpl(Process* proc, const std::string& command);
	~ProcessImpl();

	void start();
	void stop();
	void waitForFinished();
	int getProcessId() const;
	const std::string& getCommand() const;
	void setCommand(const std::string& command);
	int readData(char* buf, int bufLen);
	bool isAsyncRead() const;
	void setAsyncRead(bool asyncRead);
	const std::string& getWorkDir() const;
	void setWorkDir(const std::string& workDir);

	static int GetPid();
	static int GetPPid();
	static int Exec(const std::string& command, bool wait);

private:
	void doReadData();
	void watchTerminated();
	Process* _proc;
	string command;
	bool asyncRead;
	std::string workDir;
	HANDLE hRead;
	HANDLE hWrite;
	PROCESS_INFORMATION pi;

	smartptr::ScopedPtr<Thread> readThread;
	smartptr::ScopedPtr<Thread> watchThread;
};

} /* namespace process */
} /* namespace ducky */

#endif /* PROCESS_PROCESSIMPL_H_ */

#endif
