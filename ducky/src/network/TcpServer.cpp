/*
 * TcpServer.cpp
 *
 *  Created on: 2016-11-15
 *      Author: liyawu
 */

#include <ducky/network/TcpServer.h>
#include <cassert>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <unistd.h>
#include <vector>
#include <iostream>

#include <ducky/thread/Thread.h>
#include <ducky/thread/Semaphore.h>
#include <ducky/thread/Mutex.h>
#include <vector>
#include <netinet/in.h>
#include <list>
#include <ducky/buffer/Buffer.h>
#include "_INetServer.h"
#include "NetServerContext.h"

using namespace std;
using namespace ducky::thread;

namespace ducky {
namespace network {

class _TcpServerWorkThread;
class _TcpServer::_TcpServerImpl: public _INetServer {
public:
	_TcpServerImpl(_TcpServer* tcpServer);
	virtual ~_TcpServerImpl();

	virtual void setIp(const string& ip) throw(NetServerException);
	virtual void setPort(unsigned int port) throw(NetServerException);
	virtual void setWorkThreadCount(int workThreadCount) throw(NetServerException);
	virtual bool start() throw(NetServerException);
	virtual bool stop(bool joinServerThread = false);
	virtual bool isRunning();
	virtual void onStart();
	virtual void onStop();

protected:
	virtual void onCreateSession(IClientSession*& pSession);

private:
	virtual bool bind(unsigned int port, const string& ip);
	virtual bool listen(int n);
	virtual void run();
	bool setNonBlocking(int sock);
	int doAccept();
	_NetServerContext* getContext();
	void addContext(_NetServerContext* context);
	ducky::buffer::Buffer doReceive(_NetServerContext* context);
	void doSend(_NetServerContext* context);
	void addClientFd(int clientFd);
	void removeClientFd(int clientFd);
	int getClientCount();

	string ip;
	unsigned int port;
	int sock;
	int epfd;
	int eventCount;
	int workThreadCount;

	ducky::thread::Mutex mutex;
	ducky::thread::Semaphore semphore;
	list<_NetServerContext*> contexts;
	list<int> clientSockets;
	vector<_TcpServerWorkThread*> workThreads;

	_TcpServer* _tcpServer;

	friend class _TcpServerWorkThread;
};

class _TcpServerWorkThread: public ducky::thread::Thread {
public:
	_TcpServerWorkThread(_TcpServer::_TcpServerImpl* server);
	virtual ~_TcpServerWorkThread();

private:
	void run();

	_TcpServer::_TcpServerImpl* _server;
};

_TcpServerWorkThread::_TcpServerWorkThread(_TcpServer::_TcpServerImpl* server) :
		_server(server) {

}

_TcpServerWorkThread::~_TcpServerWorkThread() {
	//cout << "work thread destroied..." << endl;
}

void _TcpServerWorkThread::run() {
	//cout << "work thread running..." << endl;
	while (true) {
		_NetServerContext* context = this->_server->getContext();

		if (this->canStop()) {
			if (context) {
				context->session->onDisconnected();

				close(context->sockFd);
				delete context->session;
				delete context;
			}
			break;
		}

		if (context) {
			switch (context->state) {
			case CS_READ: {
				//cout << "do read..." << endl;
				ducky::buffer::Buffer buf = this->_server->doReceive(context);
			}
				break;
			case CS_WRITE:{
				this->_server->doSend(context);
				break;
			}
			case CS_DISCONNECTED: {
				//cout << "do disconnected..." << endl;
				context->session->onDisconnected();
				this->_server->removeClientFd(context->sockFd);
				close(context->sockFd);
				delete context->session;
				delete context;
			}
				break;
			}
		} else {
			break;
		}
	}
	//cout << "work thread end..." << endl;
}

_TcpServer::_TcpServerImpl::_TcpServerImpl(_TcpServer* tcpServer) :
		port(0), sock(0), epfd(0), eventCount(500), workThreadCount(10), _tcpServer(
				tcpServer) {
	// TODO Auto-generated constructor stub
}

_TcpServer::_TcpServerImpl::~_TcpServerImpl() {
	// TODO Auto-generated destructor stub
}

void _TcpServer::_TcpServerImpl::onCreateSession(IClientSession*& pSession) {
	this->_tcpServer->onCreateSession(pSession);
}

bool _TcpServer::_TcpServerImpl::isRunning() {
	return this->sock > 0;
}

void _TcpServer::_TcpServerImpl::setWorkThreadCount(int workThreadCount) throw(NetServerException) {
	if (this->isRunning()) {
		throw NetServerException("Server is running");
	}
	this->workThreadCount = workThreadCount;
}

void _TcpServer::_TcpServerImpl::onStart() {
	this->_tcpServer->onStart();
}

void _TcpServer::_TcpServerImpl::onStop() {
	this->_tcpServer->onStop();
}

void _TcpServer::_TcpServerImpl::setIp(const string& ip) throw(NetServerException) {
	if (this->isRunning()) {
		throw NetServerException("Server is running");
	}
	this->ip = ip;
}

void _TcpServer::_TcpServerImpl::setPort(unsigned int port) throw(NetServerException) {
	if (this->isRunning()) {
		throw NetServerException("Server is running");
	}
	this->port = port;
}

bool _TcpServer::_TcpServerImpl::bind(unsigned int port, const string& ip) {
	sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	if (ip.empty()) {
		addr.sin_addr.s_addr = 0;
	} else {
		inet_aton(ip.c_str(), &addr.sin_addr);
	}
	return (0
			== ::bind(this->sock, (struct sockaddr *) &addr,
					sizeof(sockaddr_in)));
}

bool _TcpServer::_TcpServerImpl::listen(int n) {
	return (0 == ::listen(this->sock, n));
}

bool _TcpServer::_TcpServerImpl::start() throw(NetServerException) {
	if (this->isRunning()) {
		throw NetServerException("Server is running");
	}

	this->sock = socket(AF_INET, SOCK_STREAM, 0);
	if (this->sock <= 0)
		return false;

	this->setNonBlocking(this->sock);
	if (!this->bind(this->port, this->ip) || !this->listen(100)) {
		close(this->sock);
		this->sock = 0;
		return false;
	}

	this->epfd = epoll_create1(0);
	if (this->epfd <= 0) {
		close(this->sock);
		this->sock = 0;
		return false;
	}

	for (int i = 0; i < this->workThreadCount; ++i) {
		_TcpServerWorkThread* workThread = new _TcpServerWorkThread(this);
		this->workThreads.push_back(workThread);
		workThread->start();
	}

	struct epoll_event ev;
	ev.data.fd = this->sock;
	ev.events = EPOLLIN | EPOLLET;
	epoll_ctl(this->epfd, EPOLL_CTL_ADD, this->sock, &ev);

	return Thread::start();
}

bool _TcpServer::_TcpServerImpl::stop(bool joinServerThread) {
	for (list<int>::iterator it = this->clientSockets.begin();
			it != this->clientSockets.end(); ++it) {
		shutdown(*it, SHUT_RDWR);
	}

	while (this->semphore.getValue() > 0) {
		usleep(10 * 1000);
	}

	for (size_t i = 0; i < this->workThreads.size(); ++i) {
		_TcpServerWorkThread* workThread = this->workThreads[i];
		workThread->stop();
	}

	for (size_t i = 0; i < this->workThreads.size(); ++i) {
		this->semphore.release();
	}

	for (size_t i = 0; i < this->workThreads.size(); ++i) {
		_TcpServerWorkThread* workThread = this->workThreads[i];
		workThread->join();
		delete workThread;
	}

	this->clientSockets.clear();
	this->workThreads.clear();

	shutdown(this->sock, SHUT_RDWR);

	int re = Thread::stop();
	if(re && joinServerThread){
		this->join();
	}
	return re;
}

bool _TcpServer::_TcpServerImpl::setNonBlocking(int sock) {
	int opts;
	opts = fcntl(sock, F_GETFL);
	if (opts < 0) {
		//cout << "fcntl(sock, F_GETFL)" << endl;
		return false;
	}

	opts |= O_NONBLOCK;

	if (fcntl(sock, F_SETFL, opts) < 0) {
		//cout << "fcntl(sock, F_SETFL, opts)" << endl;
		return false;
	}

	return true;
}

int _TcpServer::_TcpServerImpl::doAccept() {
	sockaddr_in clientAddr = { 0 };
	socklen_t addrLen = sizeof(clientAddr);
	int clientFd = accept(this->sock, (sockaddr*) &clientAddr, &addrLen);
	if (-1 == clientFd)
		return clientFd;

	this->addClientFd(clientFd);

	this->setNonBlocking(clientFd);
	IClientSession* pSession = NULL;
	this->onCreateSession(pSession);
	assert(pSession);
	pSession->init(clientFd, this->epfd);
	pSession->onConnected();

	//cout << " " << inet_ntoa(clientAddr.sin_addr) << endl;
	//cout << " client " << clientFd << " connected" << endl;

	_NetServerContext* context = new _NetServerContext;
	context->sockFd = clientFd;
	context->session = pSession;
	context->addr = clientAddr;
	context->state = CS_READ;

	struct epoll_event ev;
	ev.data.fd = clientFd;
	ev.events = EPOLLIN | EPOLLET | EPOLLONESHOT;
	ev.data.ptr = context;
	epoll_ctl(this->epfd, EPOLL_CTL_ADD, clientFd, &ev);

	return clientFd;
}

_NetServerContext* _TcpServer::_TcpServerImpl::getContext() {
	this->semphore.wait();
	MutexLocker lk(this->mutex);

	_NetServerContext* context = NULL;

	if (!this->contexts.empty()) {
		context = this->contexts.front();
		this->contexts.pop_front();
	}

	return context;
}

void _TcpServer::_TcpServerImpl::addContext(_NetServerContext* context) {
	MutexLocker lk(this->mutex);

	if (NULL == context)
		return;

	this->contexts.push_back(context);
	this->semphore.release();
}

ducky::buffer::Buffer _TcpServer::_TcpServerImpl::doReceive(
		_NetServerContext* context) {
	ducky::buffer::Buffer buffer;

	int sock = context->sockFd;
	char buf[1024] = { 0 };

	int re = recv(sock, buf, 1023, 0);
	if (re > 0) {
		buffer.setData(buf, re);
		context->session->onRecive(buffer);

		context->state = CS_READ;
		struct epoll_event ev;
		ev.data.fd = sock;
		ev.data.ptr = context;
		ev.events = EPOLLIN | EPOLLET | EPOLLONESHOT;
		epoll_ctl(this->epfd, EPOLL_CTL_MOD, sock, &ev);

	} else {
		struct epoll_event ev;
		ev.data.fd = sock;
		ev.events = EPOLLIN | EPOLLET | EPOLLONESHOT;
		epoll_ctl(this->epfd, EPOLL_CTL_DEL, sock, &ev);

		context->state = CS_DISCONNECTED;
		this->addContext(context);
	}
	return buffer;
}

void _TcpServer::_TcpServerImpl::doSend(_NetServerContext* context){
	::send(context->sockFd, context->dataBuffer.getData(), context->dataBuffer.getSize(), 0);
	context->session->onSend(context->dataBuffer);
	delete context;
}

void _TcpServer::_TcpServerImpl::addClientFd(int clientFd) {
	MutexLocker lk(this->mutex);
	this->clientSockets.push_back(clientFd);
}

void _TcpServer::_TcpServerImpl::removeClientFd(int clientFd) {
	MutexLocker lk(this->mutex);
	this->clientSockets.remove(clientFd);
}

int _TcpServer::_TcpServerImpl::getClientCount() {
	MutexLocker lk(this->mutex);
	return this->clientSockets.size();
}

void _TcpServer::_TcpServerImpl::run() {
	//cout << "_TcpServer::_TcpServerImpl::run begin..." << endl;
	this->onStart();

	vector<struct epoll_event> events(this->eventCount);
	string threadName;
	while (!this->canStop()) {
		int nfds = epoll_wait(epfd, &events[0], this->eventCount, -1);
		for (int i = 0; i < nfds; ++i) {
			if (events[i].data.fd == this->sock) {
				while (this->doAccept() > 0)
					;
				if (EAGAIN != errno) {
					goto server_exit;
				}
			} else if (events[i].events & EPOLLIN) {
				this->addContext((_NetServerContext*) events[i].data.ptr);
			} else if (events[i].events & EPOLLOUT) {
				this->addContext((_NetServerContext*) events[i].data.ptr);
			}
		}

	}

	server_exit: close(this->epfd);
	close(this->sock);
	this->onStop();
	this->sock = 0;
	this->epfd = 0;
}

_TcpServer::_TcpServer() :
		impl(new _TcpServer::_TcpServerImpl(this)) {

}

_TcpServer::~_TcpServer() {
	delete this->impl;
}

void _TcpServer::setIp(const string& ip) throw(NetServerException) {
	this->impl->setIp(ip);
}

void _TcpServer::setPort(unsigned int port) throw(NetServerException) {
	this->impl->setPort(port);
}

bool _TcpServer::start() throw(NetServerException) {
	return this->impl->start();
}

bool _TcpServer::stop(bool joinServerThread) {
	return this->impl->stop(joinServerThread);
}

void _TcpServer::join() {
	this->impl->join();
}

bool _TcpServer::isRunning() {
	return this->impl->isRunning();
}

void _TcpServer::setWorkThreadCount(int workThreadCount) throw(NetServerException) {
	this->impl->setWorkThreadCount(workThreadCount);
}

} /* namespace network */
} /* namespace ducky */
