/*
 * NamedPipe.h
 *
 *  Created on: Feb 6, 2017
 *      Author: ducky
 */

#ifndef DUCKY_PIPE_NAMEDPIPE_H_
#define DUCKY_PIPE_NAMEDPIPE_H_

#include <ducky/Object.h>
#include <ducky/pipe/PipeType.h>
#include <ducky/pipe/PipeException.h>
#include <string>

namespace ducky {
namespace pipe {

class NamedPipe: public Object {
public:
	NamedPipe();
	virtual ~NamedPipe();

	std::string getName() const;
	void open(const std::string& name, PipeType pipeType) throw (PipeException);
	void close();
	bool isOpen() const;
	int read(char* buf, int size, int timeoutMs = -1) throw (PipeException);
	int write(const char* buf, int size, int timeoutMs = -1)
			throw (PipeException);
	int getHandle() const;

private:
	class NamedPipeImpl;
	NamedPipeImpl* impl;
};

} /* namespace pipe */
} /* namespace ducky */

#endif /* DUCKY_PIPE_NAMEDPIPE_H_ */
