/*
 * Process.cpp
 *
 *  Created on: Feb 5, 2017
 *      Author: ducky
 */

#include <ducky/process/Process.h>
#include <unistd.h>

namespace ducky {
namespace process {

Process::Process() {
	// TODO Auto-generated constructor stub

}

Process::~Process() {
	// TODO Auto-generated destructor stub
}

int Process::GetPid(){
	return getpid();
}

int Process::GetPPid(){
	return getppid();
}

int Process::Exec(const std::string& command, bool wait){
	if(wait){
		return execlp(command.c_str(), command.c_str(), NULL);
	}else{
		if(0 == fork()){
			execlp(command.c_str(), command.c_str(), NULL);
			exit(1);
		}
	}
	return 0;
}

} /* namespace process */
} /* namespace ducky */
