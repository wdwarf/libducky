/*
 * UdpServerBase.cpp
 *
 *  Created on: 2018年4月28日
 *      Author: liyawu
 */

#include <ducky/network/UdpServerBase.h>
#include <ducky/thread/Runnable.h>
#include <ducky/buffer/Buffer.h>
#include <ducky/network/SockAddr.h>

#include <iostream>

using namespace std;
using namespace ducky::thread;
using namespace ducky::buffer;

namespace ducky {
namespace network {

//==============================================
// class UdpServerBase::UdpServerBaseImpl
//==============================================
class UdpServerBase::UdpServerBaseImpl {
public:
	UdpServerBaseImpl(UdpServerBase* serverBase);
	virtual ~UdpServerBaseImpl();

	const std::string& getServerIp() const;
	void setServerIp(const std::string& serverIp);
	unsigned int getServerPort() const;
	void setServerPort(unsigned int serverPort);

	void start();
	void stop();

	void send(const buffer::Buffer& buf, const SockAddr& sockAddr);
	void send(const char* buf, unsigned int size, const SockAddr& sockAddr);

	void onStart();
	void onStop();
private:
	UdpServerBase* _serverBase;
	thread::Thread* readThread;
	thread::Thread* sendThread;
	std::string serverIp;
	unsigned int serverPort;
	Socket sock;
	unsigned int bufferSize;

	struct SendContext {
		buffer::Buffer buf;
		SockAddr addr;
	};
	std::list<SendContext> sendContexts;
	thread::Mutex mutexSend;
	thread::Semaphore semSend;

	friend class UdpReadThread;
	friend class UdpSendThread;
	bool doRecv();
	bool doSend();

private:
	class UdpReadThread: public Thread {
	public:
		UdpReadThread(UdpServerBase::UdpServerBaseImpl* server) :
				_server(server) {

		}

	private:
		void run() {
			this->_server->onStart();
			while (!this->isCanStop() && this->_server->doRecv()) {
				//
			}
			this->_server->onStop();
		}

		UdpServerBase::UdpServerBaseImpl* _server;
	};

	class UdpSendThread: public Thread {
	public:
		UdpSendThread(UdpServerBase::UdpServerBaseImpl* server) :
				_server(server) {

		}

	private:
		void run() {
			while (!this->isCanStop() && this->_server->doSend()) {
				//
			}
		}

		UdpServerBase::UdpServerBaseImpl* _server;
	};

};

UdpServerBase::UdpServerBaseImpl::UdpServerBaseImpl(UdpServerBase* serverBase) :
		_serverBase(serverBase), readThread(new UdpReadThread(this)), sendThread(
				new UdpSendThread(this)), serverPort(0), bufferSize(2048) {

}

UdpServerBase::UdpServerBaseImpl::~UdpServerBaseImpl() {
	this->stop();
	delete this->readThread;
	delete this->sendThread;
}

void UdpServerBase::UdpServerBaseImpl::start() {
	if (this->sock.createUdp() <= 0) {
		THROW_EXCEPTION(UdpServerBaseException, "Failed to create UDP socket", -1);
	}
	this->sock.bind(this->serverIp, this->serverPort);

	this->readThread->start();
	this->sendThread->start();
}

void UdpServerBase::UdpServerBaseImpl::stop() {
	this->readThread->stop();
	this->sendThread->stop();
	this->sock.close();
	this->semSend.release();
	this->readThread->join();
	this->sendThread->join();
}

void UdpServerBase::UdpServerBaseImpl::onStart(){
	this->_serverBase->onStart();
}

void UdpServerBase::UdpServerBaseImpl::onStop(){
	this->_serverBase->onStop();
}

void UdpServerBase::UdpServerBaseImpl::send(const buffer::Buffer& buf, const SockAddr& sockAddr) {
	Mutex::Locker lk(this->mutexSend);
	SendContext context;
	context.buf = buf;
	context.addr = sockAddr;
	this->sendContexts.push_back(context);
	this->semSend.release();
}

void UdpServerBase::UdpServerBaseImpl::send(const char* buf, unsigned int size,
		const SockAddr& sockAddr) {
	this->send(Buffer(buf, size), sockAddr);
}

const std::string& UdpServerBase::UdpServerBaseImpl::getServerIp() const {
	return serverIp;
}

void UdpServerBase::UdpServerBaseImpl::setServerIp(const std::string& serverIp) {
	this->serverIp = serverIp;
}

unsigned int UdpServerBase::UdpServerBaseImpl::getServerPort() const {
	return serverPort;
}

void UdpServerBase::UdpServerBaseImpl::setServerPort(unsigned int serverPort) {
	this->serverPort = serverPort;
}

bool UdpServerBase::UdpServerBaseImpl::doRecv() {
	SockAddr sockAddr;
	Buffer buf(this->bufferSize);
	int readBytes = this->sock.recvFrom(buf.getData(), buf.getSize(), sockAddr);
	if (readBytes <= 0)
		return false;

	this->_serverBase->onReceive(buf.getData(), readBytes, sockAddr);

	return true;
}

bool UdpServerBase::UdpServerBaseImpl::doSend() {
	this->semSend.wait();

	SendContext context;
	{
		Mutex::Locker lk(this->mutexSend);
		if (this->sendContexts.empty())
			return false;

		context = this->sendContexts.front();
		this->sendContexts.pop_front();
	}

	int sendBytes = this->sock.sendTo(context.buf.getData(), context.buf.getSize(), context.addr);
	if (sendBytes <= 0)
		return false;

	this->_serverBase->onSend(context.buf.getData(), context.buf.getSize(), context.addr);

	return true;
}

//==============================================
// class UdpServerBase
//==============================================
UdpServerBase::UdpServerBase() :
		impl(new UdpServerBase::UdpServerBaseImpl(this)) {

}

UdpServerBase::~UdpServerBase() {
	delete this->impl;
}

const std::string& UdpServerBase::getServerIp() const {
	return this->impl->getServerIp();
}

void UdpServerBase::setServerIp(const std::string& serverIp) {
	this->impl->setServerIp(serverIp);
}

unsigned int UdpServerBase::getServerPort() const {
	return this->impl->getServerPort();
}

void UdpServerBase::setServerPort(unsigned int serverPort) {
	this->impl->setServerPort(serverPort);
}

void UdpServerBase::start() {
	this->impl->start();
}

void UdpServerBase::stop() {
	this->impl->stop();
}

void UdpServerBase::send(const buffer::Buffer& buf, const SockAddr& sockAddr) {
	this->impl->send(buf, sockAddr);
}

void UdpServerBase::send(const char* buf, unsigned int size, const SockAddr& sockAddr) {
	this->impl->send(buf, size, sockAddr);
}

} /* namespace network */
} /* namespace ducky */
