/*
 * NamedPipeServer.h
 *
 *  Created on: Feb 7, 2017
 *      Author: ducky
 */

#ifndef DUCKY_PIPE_NAMEDPIPESERVER_H_
#define DUCKY_PIPE_NAMEDPIPESERVER_H_

#include <ducky/Object.h>
#include <ducky/pipe/PipeException.h>
#include <string>

namespace ducky {
namespace pipe {

class NamedPipeServer: public Object {
public:
	NamedPipeServer();
	virtual ~NamedPipeServer();

	std::string getName() const;
	void start(const std::string& name) throw (PipeException);
	void stop();
	void join();
	bool isRunning() const;

	virtual void onRead(char* buf, int size) = 0;
	virtual void onSend(char* buf, int size) = 0;

private:
	class NamedPipeServerImpl;
	NamedPipeServerImpl* impl;
};

} /* namespace pipe */
} /* namespace ducky */

#endif /* DUCKY_PIPE_NAMEDPIPESERVER_H_ */
