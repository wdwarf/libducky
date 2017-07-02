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

Process::Process() {
	// TODO Auto-generated constructor stub

}

Process::~Process() {
	// TODO Auto-generated destructor stub
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
		execlp(command.c_str(), command.c_str(), NULL);
		exit(0);
	}else{
		if(wait){
			int status = 0;
			waitpid(pid, &status, 0);
		}
	}
	return 0;
}

} /* namespace process */
} /* namespace ducky */
