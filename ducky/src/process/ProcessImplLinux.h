/*
 * ProcessImplLinux.h
 *
 *  Created on: 2018年7月2日
 *      Author: admin
 */

#if defined(__linux__) || defined(__CYGWIN32__)

#ifndef PROCESS_PROCESSIMPLLINUX_H_
#define PROCESS_PROCESSIMPLLINUX_H_

#include <ducky/process/Process.h>
#include <ducky/thread/Thread.h>
#include <ducky/smartptr/ScopedPtr.h>
#include <unistd.h>
#include <errno.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <map>

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
	void addParameter(const std::string& arg);
	const vector<string>& getParameters() const;
	void clearParameter();

	static int GetPid();
	static int GetPPid();
	static int Exec(const std::string& command, bool wait);
	static int GetPidByName(const std::string& processName);
	static bool Kill(int pid, int code = 15);
	static bool Kill(const std::string& processName, int code = 15);
	static std::map<int, std::string> ListProcesses();

private:
	void doReadData();
	Process* _proc;
	string command;
	int pipeFd[2];
	int pid;
	bool asyncRead;
	std::string workDir;
	vector<string> args;

	smartptr::ScopedPtr<Thread> readThread;
};

} /* namespace process */
} /* namespace ducky */

#endif /* PROCESS_PROCESSIMPL_H_ */

#endif
