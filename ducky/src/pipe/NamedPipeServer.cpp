/*
 * NamedPipeServer.cpp
 *
 *  Created on: Feb 7, 2017
 *      Author: ducky
 */

#include <ducky/pipe/NamedPipeServer.h>
#include <ducky/pipe/NamedPipe.h>
#include <ducky/thread/Thread.h>
#include <ducky/buffer/Buffer.h>
#include <exception>
#include <iostream>
#include <unistd.h>

using namespace ducky::thread;
using namespace ducky::buffer;
using namespace ducky::exception;
using namespace std;

namespace ducky {
namespace pipe {

class NamedPipeServer::NamedPipeServerImpl: public Thread {
public:
	NamedPipeServerImpl(NamedPipeServer* parent);
	virtual ~NamedPipeServerImpl();

	string getName() const;
	void start(const std::string& name) throw (PipeException);
	virtual bool stop();
	void onRead(char* buf, int size);

private:
	virtual void run();
	NamedPipeServer* parent;
	NamedPipe pipe;
	virtual bool start() {
		return Thread::start();
	}
};

NamedPipeServer::NamedPipeServerImpl::NamedPipeServerImpl(
		NamedPipeServer* parent) {
	this->parent = parent;
}

NamedPipeServer::NamedPipeServerImpl::~NamedPipeServerImpl() {
	this->stop();
	this->join();
}

void NamedPipeServer::NamedPipeServerImpl::start(const std::string& name)
		throw (PipeException) {
	this->pipe.open(name, PT_READ);
	if (!this->start()) {
		throw PipeException("NamePipe client start failed.", -1);
	}
}

string NamedPipeServer::NamedPipeServerImpl::getName() const {
	return this->pipe.getName();
}

bool NamedPipeServer::NamedPipeServerImpl::stop() {
	if(!this->isRunning()){
		return true;
	}

	Thread::stop();
	try{
		NamedPipe p;
		p.open(this->getName(), PT_WRITE);
		p.write("", 1);
		p.close();
	}catch(...){

	}

	return true;
}

void NamedPipeServer::NamedPipeServerImpl::run() {
	int bufSize = 2048;
	Buffer buf;
	buf.alloc(bufSize);
	try {
		while (!this->canStop()) {
			int readBytes = this->pipe.read(buf.getData(), buf.getSize());
			if(this->canStop()){
				break;
			}
			if (readBytes < 0) {
				break;
			} else if (readBytes > 0) {
				try {
					this->onRead(buf.getData(), readBytes);
				} catch (std::exception& e) {
					cout << e.what() << endl;
				}
			}
		}
	} catch (std::exception& e) {
		cout << e.what() << endl;
	}

	this->pipe.close();
}

void NamedPipeServer::NamedPipeServerImpl::onRead(char* buf, int size) {
	this->parent->onRead(buf, size);
}

NamedPipeServer::NamedPipeServer() :
		impl(new NamedPipeServerImpl(this)) {
// TODO Auto-generated constructor stub

}

NamedPipeServer::~NamedPipeServer() {
// TODO Auto-generated destructor stub
	if (this->impl) {
		delete this->impl;
	}
}
std::string NamedPipeServer::getName() const {
	return this->impl->getName();
}
void NamedPipeServer::start(const std::string& name) throw (PipeException) {
	this->impl->start(name);
}

void NamedPipeServer::stop() {
	this->impl->stop();
}

void NamedPipeServer::join() {
	this->impl->join();
}

bool NamedPipeServer::isRunning() const {
	return this->impl->isRunning();
}

} /* namespace pipe */
} /* namespace ducky */
