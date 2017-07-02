/*
 * NamedPipeServer.cpp
 *
 *  Created on: Feb 7, 2017
 *      Author: ducky
 */

#include <ducky/pipe/NamedPipeServer.h>
#include <ducky/pipe/NamedPipe.h>
#include <ducky/thread/Thread.h>
#include <ducky/thread/Mutex.h>
#include <ducky/thread/Semaphore.h>
#include <ducky/buffer/Buffer.h>
#include <exception>
#include <iostream>
#include <unistd.h>
#include <list>
#include <ducky/smartptr/ScopedPtr.h>

using namespace ducky::thread;
using namespace ducky::buffer;
using namespace ducky::exception;
using namespace ducky::smartptr;
using namespace std;

namespace ducky {
namespace pipe {

class NamedPipeServer::NamedPipeServerImpl: public Object {
public:
	NamedPipeServerImpl(NamedPipeServer* parent);
	virtual ~NamedPipeServerImpl();

	string getName() const;
	void start(const std::string& name);
	virtual void stop();
	void join();
	bool isRunning() const;
	void send(const char* buf, int size);
	void onRead(char* buf, int size);
	void onSend(char* buf, int size);

private:
	class ReadThread: public Thread {
	public:
		ReadThread(NamedPipeServerImpl* svr) {
			this->svr = svr;
		}

		void setPipeName(const string& pipeName) {
			this->pipeName = pipeName + "_ducky_pipe_out";
		}

		void run() {
			try {
				this->pipe.open(this->pipeName, PT_READ);
				int bufSize = 2048;
				Buffer buf;
				buf.alloc(bufSize);
				while (!this->canStop()) {
					int readBytes = this->pipe.read(buf.getData(),
							buf.getSize());
					if (this->canStop()) {
						break;
					}
					if (readBytes < 0) {
						break;
					} else if (readBytes > 0) {
						try {
							this->svr->onRead(buf.getData(), readBytes);
						} catch (std::exception& e) {
							cout << e.what() << endl;
						}
					}
				}
			} catch (...) {
			}
		}

	private:
		NamedPipeServerImpl* svr;
		string pipeName;
		NamedPipe pipe;
	};

	class SendThread: public Thread {
	public:
		SendThread(NamedPipeServerImpl* svr) {
			this->svr = svr;
		}

		void setPipeName(const string& pipeName) {
			this->pipeName = pipeName + "_ducky_pipe_in";
		}

		void run() {
			try {
				this->pipe.open(this->pipeName, PT_WRITE);
				while (!this->canStop()) {
					this->sem.wait();
					if (this->canStop()) {
						break;
					}

					Buffer buf;
					{
						buf = this->buffers.front();
						this->buffers.pop_front();
					}

					int readBytes = this->pipe.write(buf.getData(),
							buf.getSize());
					if (this->canStop()) {
						break;
					}
					if (readBytes < 0) {
						break;
					} else if (readBytes > 0) {
						try {
							this->svr->onSend(buf.getData(), readBytes);
						} catch (std::exception& e) {
							cout << e.what() << endl;
						}
					}
				}
			} catch (...) {
			}
		}

		void send(const Buffer& buf) {
			MutexLocker lk(this->mutex);
			this->buffers.push_back(buf);
			this->sem.release();
		}

	private:
		NamedPipeServerImpl* svr;
		string pipeName;
		NamedPipe pipe;
		list<Buffer> buffers;
		Mutex mutex;
		Semaphore sem;
	};

private:
	NamedPipeServer* parent;
	string pipeName;
	ScopedPtr<ReadThread> readThread;
	ScopedPtr<SendThread> sendThread;
};

NamedPipeServer::NamedPipeServerImpl::NamedPipeServerImpl(
		NamedPipeServer* parent) :
		readThread(new ReadThread(this)), sendThread(new SendThread(this)) {
	this->parent = parent;
}

NamedPipeServer::NamedPipeServerImpl::~NamedPipeServerImpl() {
	//
}

void NamedPipeServer::NamedPipeServerImpl::start(const std::string& name) {
	this->pipeName = name;
	this->readThread->setPipeName(this->pipeName);
	this->sendThread->setPipeName(this->pipeName);
	this->readThread->start();
	this->sendThread->start();
}

string NamedPipeServer::NamedPipeServerImpl::getName() const {
	return this->pipeName;
}

void NamedPipeServer::NamedPipeServerImpl::stop() {
	this->readThread->stop();
	this->sendThread->stop();
}

void NamedPipeServer::NamedPipeServerImpl::send(const char* buf, int size) {
	Buffer buffer(buf, size);
	this->sendThread->send(buffer);
}

void NamedPipeServer::NamedPipeServerImpl::join() {
	this->readThread->join();
}

bool NamedPipeServer::NamedPipeServerImpl::isRunning() const {
	return this->readThread->isRunning();
}

void NamedPipeServer::NamedPipeServerImpl::onRead(char* buf, int size) {
	this->parent->onRead(buf, size);
}

void NamedPipeServer::NamedPipeServerImpl::onSend(char* buf, int size) {
	this->parent->onSend(buf, size);
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

void NamedPipeServer::send(const char* buf, int size) {
	this->impl->send(buf, size);
}

} /* namespace pipe */
} /* namespace ducky */
