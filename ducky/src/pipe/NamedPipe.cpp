/*
 * NamedPipe.cpp
 *
 *  Created on: Feb 6, 2017
 *      Author: ducky
 */

#include <ducky/pipe/NamedPipe.h>
#include <ducky/algorithm/String.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <string>

using namespace std;
using namespace ducky::algorithm;

namespace ducky {
namespace pipe {

class NamedPipe::NamedPipeImpl: public Object {
public:
	NamedPipeImpl();
	virtual ~NamedPipeImpl();
	std::string getName() const;
	void open(const std::string& name, PipeType pipeType) throw (PipeException);
	bool isOpen() const;
	void close();
	int read(char* buf, int size, int timeoutMs = -1) throw (PipeException);
	int write(const char* buf, int size, int timeoutMs = -1)
			throw (PipeException);
	int getHandle() const;

private:
	string name;
	PipeType type;
	int pipeFd;
};

NamedPipe::NamedPipeImpl::NamedPipeImpl() :
		type(PT_UNKNOWN), pipeFd(-1) {
	//
}

NamedPipe::NamedPipeImpl::~NamedPipeImpl() {
	this->close();
}

string NamedPipe::NamedPipeImpl::getName() const {
	return this->name;
}

bool NamedPipe::NamedPipeImpl::isOpen() const {
	return (this->pipeFd > 0);
}

int NamedPipe::NamedPipeImpl::getHandle() const {
	return this->pipeFd;
}

void NamedPipe::NamedPipeImpl::open(const string& name, PipeType pipeType)
		throw (PipeException) {
	if (this->isOpen()) {
		throw PipeException("Pipe \"" + name + "\" has opened.");
	}

	if (-1 == access(name.c_str(), F_OK)) {
		if (0 != mkfifo(name.c_str(), 0777)) {
			throw PipeException("Pipe \"" + name + "\" create failed.", errno);
		}
	}

	int openMode = 0;
	switch (pipeType) {
	case PT_READ:
		openMode = O_RDWR | O_NONBLOCK;
		break;
	case PT_WRITE:
		openMode = O_WRONLY;
		break;
	default:
		throw PipeException("Unknown pipe type.");
	}

	this->pipeFd = ::open(name.c_str(), openMode);
	if (this->pipeFd <= 0) {
		throw PipeException("Pipe \"" + name + "\" open failed.", errno);
	}
	this->type = pipeType;
	this->name = name;
}

void NamedPipe::NamedPipeImpl::close() {
	if (this->pipeFd > 0) {
		::close(this->pipeFd);
	}

	this->pipeFd = -1;
	this->name = "";
	this->type = PT_UNKNOWN;
}

int NamedPipe::NamedPipeImpl::read(char* buf, int size, int timeoutMs)
		throw (PipeException) {
	int readBytes = 0;

	if (!this->isOpen()) {
		throw PipeException("Pipe not opened.");
	}

	if (PT_READ != this->type) {
		throw PipeException("Not a read pipe..");
	}

	fd_set fs_read;
	FD_ZERO(&fs_read);
	FD_SET(this->pipeFd, &fs_read);
	if (timeoutMs < 0) {
		if (::select(this->pipeFd + 1, &fs_read, NULL, NULL, NULL) > 0) {
			readBytes = ::read(this->pipeFd, buf, size);
		} else {
			throw PipeException("Pipe read error.", errno);
		}
	} else {
		timeval tv;
		tv.tv_sec = timeoutMs / 1000;
		tv.tv_usec = timeoutMs - (timeoutMs / 1000);
		if (::select(this->pipeFd + 1, &fs_read, NULL, NULL, &tv) > 0) {
			readBytes = ::read(this->pipeFd, buf, size);
		} else {
			throw PipeException("Pipe read timeout.", errno);
		}
	}

	if (readBytes < 0) {
		throw PipeException("Pipe read error.", errno);
	}

	return readBytes;
}

int NamedPipe::NamedPipeImpl::write(const char* buf, int size, int timeoutMs)
		throw (PipeException) {
	int writeBytes = 0;

	if (!this->isOpen()) {
		throw PipeException("Pipe not opened.");
	}

	if (PT_WRITE != this->type) {
		throw PipeException("Not a write pipe..");
	}

	fd_set fs_write;
	FD_ZERO(&fs_write);
	FD_SET(this->pipeFd, &fs_write);
	if (timeoutMs < 0) {
		if (::select(this->pipeFd + 1, NULL, &fs_write, NULL, NULL) > 0) {
			writeBytes = ::write(this->pipeFd, buf, size);
		} else {
			throw PipeException("Pipe write error.", errno);
		}
	} else {
		timeval tv;
		tv.tv_sec = timeoutMs / 1000;
		tv.tv_usec = timeoutMs - (timeoutMs / 1000);
		if (::select(this->pipeFd + 1, NULL, &fs_write, NULL, &tv) > 0) {
			writeBytes = ::write(this->pipeFd, buf, size);
		} else {
			throw PipeException("Pipe write timeout.", errno);
		}
	}

	if (writeBytes < 0) {
		throw PipeException("Pipe write error.", errno);
	}

	return writeBytes;
}

NamedPipe::NamedPipe() :
		impl(new NamedPipeImpl) {
	// TODO Auto-generated constructor stub

}

NamedPipe::~NamedPipe() {
	// TODO Auto-generated destructor stub
	if (this->impl) {
		delete this->impl;
	}
}

string NamedPipe::getName() const {
	return this->impl->getName();
}

int NamedPipe::getHandle() const {
	return this->impl->getHandle();
}

void NamedPipe::open(const std::string& name, PipeType pipeType)
		throw (PipeException) {
	this->impl->open(name, pipeType);
}

void NamedPipe::close() {
	this->impl->close();
}

bool NamedPipe::isOpen() const {
	return this->impl->isOpen();
}

int NamedPipe::read(char* buf, int size, int timeoutMs) throw (PipeException) {
	return this->impl->read(buf, size, timeoutMs);
}

int NamedPipe::write(const char* buf, int size, int timeoutMs)
		throw (PipeException) {
	return this->impl->write(buf, size, timeoutMs);
}

} /* namespace pipe */
} /* namespace ducky */
