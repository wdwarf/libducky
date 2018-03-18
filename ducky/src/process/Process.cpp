/*
 * Process.cpp
 *
 *  Created on: Feb 5, 2017
 *      Author: ducky
 */

#include <ducky/process/Process.h>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>

using namespace std;

namespace ducky {
namespace process {

Process::Process(const std::string& command) {
	this->command = command;
}

Process::~Process() {
	//
}

int Process::exec(bool wait){
	return Process::Exec(this->command, wait);
}

int Process::GetPid() {
	return getpid();
}

int Process::GetPPid() {
	return getppid();
}

int Process::Exec(const std::string& command, bool wait) {
	int pid = vfork();

	if (0 == pid) {
		int re = execlp(command.c_str(), command.c_str(), NULL);
		exit(re);
	}else{
		if(wait){
			int status = 0;
			waitpid(pid, &status, 0);
		}
	}

	return pid;
}

} /* namespace process */
} /* namespace ducky */
