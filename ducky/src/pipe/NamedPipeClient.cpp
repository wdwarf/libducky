/*
 * NamedPipeClient.cpp
 *
 *  Created on: Feb 7, 2017
 *      Author: ducky
 */

#include <ducky/pipe/NamedPipeClient.h>
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

class NamedPipeClient::NamedPipeClientImpl: public Object {
public:
	NamedPipeClientImpl(NamedPipeClient* parent);
	virtual ~NamedPipeClientImpl();

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
		ReadThread(NamedPipeClientImpl* svr) {
			this->svr = svr;
		}

		void setPipeName(const string& pipeName) {
			this->pipeName = pipeName + "_ducky_pipe_in";
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
		NamedPipeClientImpl* svr;
		string pipeName;
		NamedPipe pipe;
	};

	class SendThread: public Thread {
	public:
		SendThread(NamedPipeClientImpl* svr) {
			this->svr = svr;
		}

		void setPipeName(const string& pipeName) {
			this->pipeName = pipeName + "_ducky_pipe_out";
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
		NamedPipeClientImpl* svr;
		string pipeName;
		NamedPipe pipe;
		list<Buffer> buffers;
		Mutex mutex;
		Semaphore sem;
	};

private:
	NamedPipeClient* parent;
	string pipeName;
	ScopedPtr<ReadThread> readThread;
	ScopedPtr<SendThread> sendThread;
};

NamedPipeClient::NamedPipeClientImpl::NamedPipeClientImpl(
		NamedPipeClient* parent) :
		readThread(new ReadThread(this)), sendThread(new SendThread(this)) {
	this->parent = parent;
}

NamedPipeClient::NamedPipeClientImpl::~NamedPipeClientImpl() {
	//
}

void NamedPipeClient::NamedPipeClientImpl::start(const std::string& name) {
	this->pipeName = name;
	this->readThread->setPipeName(this->pipeName);
	this->sendThread->setPipeName(this->pipeName);
	this->readThread->start();
	this->sendThread->start();
	this->parent->onStart();
}

string NamedPipeClient::NamedPipeClientImpl::getName() const {
	return this->pipeName;
}

void NamedPipeClient::NamedPipeClientImpl::stop() {
	this->readThread->stop();
	this->sendThread->stop();
}

void NamedPipeClient::NamedPipeClientImpl::send(const char* buf, int size) {
	Buffer buffer(buf, size);
	this->sendThread->send(buffer);
}

void NamedPipeClient::NamedPipeClientImpl::join() {
	this->readThread->join();
}

bool NamedPipeClient::NamedPipeClientImpl::isRunning() const {
	return this->readThread->isRunning();
}

void NamedPipeClient::NamedPipeClientImpl::onRead(char* buf, int size) {
	this->parent->onRead(buf, size);
}

void NamedPipeClient::NamedPipeClientImpl::onSend(char* buf, int size) {
	this->parent->onSend(buf, size);
}

NamedPipeClient::NamedPipeClient() :
		impl(new NamedPipeClientImpl(this)) {
// TODO Auto-generated constructor stub

}

NamedPipeClient::~NamedPipeClient() {
// TODO Auto-generated destructor stub
	if (this->impl) {
		delete this->impl;
	}
}
std::string NamedPipeClient::getName() const {
	return this->impl->getName();
}
void NamedPipeClient::start(const std::string& name) throw (PipeException) {
	this->impl->start(name);
}

void NamedPipeClient::stop() {
	this->impl->stop();
}

void NamedPipeClient::join() {
	this->impl->join();
}

bool NamedPipeClient::isRunning() const {
	return this->impl->isRunning();
}

void NamedPipeClient::send(const char* buf, int size) {
	this->impl->send(buf, size);
}

} /* namespace pipe */
} /* namespace ducky */
