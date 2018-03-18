/*
 * Process.h
 *
 *  Created on: Feb 5, 2017
 *      Author: ducky
 */

#ifndef DUCKY_PROCESS_PROCESS_H_
#define DUCKY_PROCESS_PROCESS_H_

#include <ducky/Object.h>
#include <string>

namespace ducky {
namespace process {

class Process: public Object {
public:
	Process(const std::string& command);
	virtual ~Process();

	int exec(bool wait = true);

public:
	static int GetPid();
	static int GetPPid();
	static int Exec(const std::string& command, bool wait = false);

private:
	std::string command;
};

} /* namespace process */
} /* namespace ducky */

#endif /* DUCKY_PROCESS_PROCESS_H_ */
