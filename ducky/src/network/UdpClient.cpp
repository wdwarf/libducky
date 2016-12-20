/*
 * UdpClient.cpp
 *
 *  Created on: 2016年12月20日
 *      Author: liyawu
 */

#include <ducky/network/UdpClient.h>
#include <errno.h>

using namespace std;
using namespace ducky;
using namespace ducky::thread;

namespace ducky {
namespace network {

UdpClient::UdpClient() :
		serverPort(0), localPort(0), bufferSize(2048), readThread(
				new UdpClientReadThread(this)), sendThread(
				new UdpClientSendThread(this)) {

}

UdpClient::UdpClient(const string& serverIp, int serverPort,
		const string& localIp, int localPort) :
		bufferSize(2048), readThread(new UdpClientReadThread(this)), sendThread(
				new UdpClientSendThread(this)) {
	this->serverIp = serverIp;
	this->serverPort = serverPort;
	this->localIp = localIp;
	this->localPort = localPort;
}

UdpClient::~UdpClient() {
	this->sock.close();
}

const std::string& UdpClient::getServerIp() const {
	return serverIp;
}

void UdpClient::setServerIp(const std::string& serverIp) {
	this->serverIp = serverIp;
}

int UdpClient::getServerPort() const {
	return serverPort;
}

void UdpClient::setServerPort(int serverPort) {
	this->serverPort = serverPort;
}

const Socket& UdpClient::getSock() const {
	return sock;
}

void UdpClient::setSock(const Socket& sock) {
	this->sock = sock;
}

int UdpClient::getBufferSize() const {
	return bufferSize;
}

void UdpClient::setBufferSize(int bufferSize) {
	if (bufferSize <= 0) {
		throw NetworkException("Invalid buffer size.", bufferSize);
	}
	this->bufferSize = bufferSize;
}

bool UdpClient::start() {
	try {
		this->sock.close();
		this->sock.createUdp();

		if (!this->localIp.empty() && (this->localPort > 0)) {
			this->sock.bind(this->localIp, this->localPort);
		}
	} catch (exception::Exception& e) {
		throw UdpClientException(e.what(), errno);
	}

	if (!readThread->start()) {
		this->sock.close();
		throw UdpClientException("Read thread start failed.", errno);
	}

	if (!sendThread->start()) {
		this->sock.close();
		throw UdpClientException("Send thread start failed.", errno);
	}

	if (!Thread::start()) {
		this->sendThread->stop();
		throw UdpClientException("Client thread start failed.", errno);
	}

	return true;
}

bool UdpClient::stop() {
	this->readThread->stop();
	this->sendThread->stop();
	Thread::stop();
	this->sock.shutdown();
	return true;
}

void UdpClient::run() {
	try {
		this->onStart();
	} catch (...) {
	}

	char* buf = new char[this->bufferSize];
	while (!this->canStop()) {
		string ip;
		int port = 0;
		int re = this->sock.recvFrom(buf, this->bufferSize, ip, port);
		if (re > 0) {
			this->readThread->recv(buf, re, ip, port);
		} else {
			break;
		}
	}

	this->sock.close();
	delete[] buf;

	try {
		this->onStop();
	} catch (...) {
	}

}

void UdpClient::send(const char* buf, int len,
		const string& ip, int port) {
	this->sendThread->send(buf, len,
			(ip.empty() ? this->serverIp : ip),
			(port <= 0 ? this->serverPort : port));
}

//=================================================
//=================================================

UdpClientContext::UdpClientContext() :
		port(0) {
}

UdpClientContext::UdpClientContext(const buffer::Buffer& data, const string& ip,
		int port) {
	this->data = data;
	this->ip = ip;
	this->port = port;
}

UdpClientContext::UdpClientContext(const char* data, int dataSize,
		const string& ip, int port) {
	this->data.setData(data, dataSize);
	this->ip = ip;
	this->port = port;
}

UdpClientSendThread::~UdpClientSendThread() {

}

const buffer::Buffer& UdpClientContext::getData() const {
	return data;
}

void UdpClientContext::setData(const buffer::Buffer& data) {
	this->data = data;
}

const std::string& UdpClientContext::getIp() const {
	return ip;
}

void UdpClientContext::setIp(const std::string& ip) {
	this->ip = ip;
}

int UdpClientContext::getPort() const {
	return port;
}

void UdpClientContext::setPort(int port) {
	this->port = port;
}

//=================================================
//=================================================

UdpClientReadThread::UdpClientReadThread(UdpClient* parent) {
	this->parent = parent;
}

void UdpClientReadThread::recv(const UdpClientContext& context) {
	MutexLocker lk(this->mutex);
	if (context.getIp().empty() || (context.getPort() <= 0)) {
		throw NetworkException("Invalid context.", -1);
	}
	this->contexts.push_back(context);
	this->sem.release();
}

void UdpClientReadThread::recv(const buffer::Buffer& data, const string& ip,
		int port) {
	this->recv(UdpClientContext(data, ip, port));
}

void UdpClientReadThread::recv(const char* data, int dataSize, const string& ip,
		int port) {
	this->recv(UdpClientContext(data, dataSize, ip, port));
}

void UdpClientReadThread::run() {
	while (!this->canStop()) {
		this->sem.wait();
		if (this->canStop()) {
			break;
		}

		UdpClientContext ctx;
		{
			MutexLocker lk(this->mutex);
			if (this->contexts.empty()) {
				continue;
			}

			ctx = this->contexts.front();
			this->contexts.pop_front();
		}

		this->parent->onReceive(ctx.getData().getData(),
				ctx.getData().getSize(), ctx.getIp(), ctx.getPort());
	}

	this->contexts.clear();
}

bool UdpClientReadThread::stop() {
	Thread::stop();
	this->sem.release();
	this->join();
	return true;
}

//=================================================
//=================================================

UdpClientSendThread::UdpClientSendThread(UdpClient* parent) {
	this->parent = parent;
}

void UdpClientSendThread::send(const UdpClientContext& context) {
	MutexLocker lk(this->mutex);
	if (context.getIp().empty() || (context.getPort() <= 0)) {
		throw NetworkException("Invalid context.", -1);
	}
	this->contexts.push_back(context);
	this->sem.release();
}

void UdpClientSendThread::send(const buffer::Buffer& data, const string& ip,
		int port) {
	this->send(UdpClientContext(data, ip, port));
}

void UdpClientSendThread::send(const char* data, int dataSize, const string& ip,
		int port) {
	this->send(UdpClientContext(data, dataSize, ip, port));
}

void UdpClientSendThread::run() {
	while (!this->canStop()) {
		this->sem.wait();
		if (this->canStop()) {
			break;
		}

		UdpClientContext ctx;
		{
			MutexLocker lk(this->mutex);
			if (this->contexts.empty()) {
				continue;
			}

			ctx = this->contexts.front();
			this->contexts.pop_front();
		}

		int re = this->parent->sock.sendTo(ctx.getData().getData(),
				ctx.getData().getSize(), ctx.getIp(), ctx.getPort());
		if (re > 0) {
			this->parent->onSend(ctx.getData().getData(),
					ctx.getData().getSize(), ctx.getIp(), ctx.getPort());
		} else {
			break;
		}
	}

	this->contexts.clear();
}

bool UdpClientSendThread::stop() {
	Thread::stop();
	this->sem.release();
	this->join();
	return true;
}

} /* namespace network */
} /* namespace ducky */
