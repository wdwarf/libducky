/*
 * TcpServer.cpp
 *
 *  Created on: Oct 18, 2016
 *      Author: ducky
 */

#include <ducky/network/TcpServer.h>
#include <ducky/thread/Thread.h>
#include <ducky/thread/Mutex.h>
#include <sys/epoll.h>
#include <ducky/network/Socket.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <iostream>

using namespace std;
using namespace ducky::thread;

namespace ducky {
namespace network {

class TcpServer::TcpServerImpl: public Thread {
public:
	TcpServerImpl(TcpServer* svr);
	virtual ~TcpServerImpl();

	virtual void setIp(const string& ip);
	virtual void setPort(int port);
	virtual void onAccept(int sock);
	virtual void onCreateSession(ClientSession*& refpSession);
	virtual bool start();
	virtual bool stop();
	virtual void run();

private:
	int epfd;
	Socket svrSock;
	TcpServer* server;
	int pollSize;
	int port;
	string ip;
};

TcpServer::TcpServerImpl::TcpServerImpl(TcpServer* svr) :
		epfd(0), server(svr), pollSize(1000), port(0) {
}

TcpServer::TcpServerImpl::~TcpServerImpl() {

}

void TcpServer::TcpServerImpl::setIp(const string& ip) {
	this->ip = ip;
}

void TcpServer::TcpServerImpl::setPort(int port) {
	this->port = port;
}

bool TcpServer::TcpServerImpl::start() {
	try {
		this->epfd = epoll_create(pollSize);

		cout << port << endl;
		svrSock.createTcp();
		svrSock.bind(ip, port);
		svrSock.listen(50);

		struct epoll_event evt;
		evt.events = EPOLLIN | EPOLLET | EPOLLERR;
		evt.data.fd = svrSock.getHandle();
		epoll_ctl(this->epfd, EPOLL_CTL_ADD, svrSock.getHandle(), &evt);
		cout << "start good" << endl;
	} catch (std::exception& e) {
		cout << e.what() << endl;
		return false;
	} catch (...) {
		cout << "start error" << endl;
		return false;
	}

	return Thread::start();
}

bool TcpServer::TcpServerImpl::stop() {
	Thread::stop();
	if (this->epfd > 0) {
		close(this->epfd);
	}
	return true;
}

void TcpServer::TcpServerImpl::run() {

	cout << "running..." << endl;
	const int MAX_EVENT = 10000;
	const int BUF_SIZE = 10240;
	char* buf = new char[BUF_SIZE];
	struct epoll_event* evts = new struct epoll_event[MAX_EVENT];
	while (!this->canStop()) {
		cout << "waitting..." << endl;
		int evtCount = epoll_wait(this->epfd, evts, MAX_EVENT, -1);
		cout << "got signal..." << endl;

		if (evtCount > 0) {
			int clientSock = 0;
			for (int i = 0; i < evtCount; ++i) {
				if (evts[i].data.fd == this->svrSock.getHandle()) {
					cout << "accept" << endl;
					sockaddr_in addr = { 0 };
					socklen_t len = sizeof(addr);
					clientSock = accept(this->svrSock.getHandle(),
							(sockaddr*) &addr, &len);

					struct epoll_event evt;
					evt.events = EPOLLIN | EPOLLET | EPOLLONESHOT;
					evt.data.fd = clientSock;
					epoll_ctl(this->epfd, EPOLL_CTL_ADD, clientSock, &evt);
				} else if (evts[i].events & EPOLLIN) {
					if (evts[i].events & EPOLLERR) {
						cout << "got EPOLLERR" << endl;
					}
					clientSock = evts[i].data.fd;
					int readBytes = read(clientSock, buf, BUF_SIZE);
					if (readBytes > 0) {
						struct epoll_event evt;
						evt.events =
						EPOLLIN | EPOLLET | EPOLLONESHOT;
						evt.data.fd = clientSock;
						epoll_ctl(this->epfd, EPOLL_CTL_MOD, clientSock, &evt);
					} else {
						cout << "disconnected" << endl;
						struct epoll_event evt;
						evt.events =
						EPOLLIN | EPOLLET | EPOLLONESHOT;
						evt.data.fd = clientSock;
						epoll_ctl(this->epfd, EPOLL_CTL_DEL, clientSock, &evt);
						close(clientSock);
					}
				} else if (evts[i].events & EPOLLOUT) {
					cout << "EPOLLOUT" << endl;

					clientSock = evts[i].data.fd;
					struct epoll_event evt;
					evt.events =
					EPOLLIN | EPOLLOUT | EPOLLET | EPOLLONESHOT;
					evt.data.fd = clientSock;
					epoll_ctl(this->epfd, EPOLL_CTL_MOD, clientSock, &evt);
				}
			}
		} else {
			//
		}
	}

	cout << "end running..." << endl;
	delete[] evts;
}

void TcpServer::TcpServerImpl::onAccept(int sock) {
	this->server->onAccept(sock);
}

void TcpServer::TcpServerImpl::onCreateSession(ClientSession*& refpSession) {
	this->server->onCreateSession(refpSession);
}

TcpServer::TcpServer() {
	// TODO Auto-generated constructor stub
	this->impl = new TcpServerImpl(this);
}

TcpServer::~TcpServer() {
	// TODO Auto-generated destructor stub
	this->stop();
	if (NULL != this->impl) {
		delete this->impl;
	}
}

void TcpServer::setIp(const string& ip) {
	this->impl->setIp(ip);
}
void TcpServer::setPort(int port) {
	this->impl->setPort(port);
}

bool TcpServer::start() {
	return this->impl->start();
}

bool TcpServer::stop() {
	return this->impl->stop();
}

} /* namespace network */
} /* namespace ducky */
