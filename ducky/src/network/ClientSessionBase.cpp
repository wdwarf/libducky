/*
 * ClientSessionBase.cpp
 *
 *  Created on: 2016-11-15
 *      Author: ducky
 */

#include <ducky/network/ClientSessionBase.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <iostream>
#include "NetServerContext.h"

using namespace std;

namespace ducky {
namespace network {

class IClientSession;
ClientSessionBase::ClientSessionBase() :
		sock(0), epfd(0), localPort(0), remotePort(0) {
	

}

ClientSessionBase::~ClientSessionBase() {
	
}

void ClientSessionBase::init(int sock, int epfd) {
	this->epfd = epfd;
	sockaddr_in svrAddr;
	sockaddr_in clientAddr;
	socklen_t svrLen = sizeof(svrAddr);
	socklen_t clientLen = sizeof(clientAddr);
	::getsockname(sock, (sockaddr*) &svrAddr, &svrLen);
	::getpeername(sock, (sockaddr*) &clientAddr, &clientLen);
	this->localIp = inet_ntoa(svrAddr.sin_addr);
	this->localPort = ntohs(svrAddr.sin_port);
	this->remoteIp = inet_ntoa(clientAddr.sin_addr);
	this->remotePort = ntohs(clientAddr.sin_port);
	this->sock = sock;
}

string ClientSessionBase::getLocalIp() {
	return this->localIp;
}

unsigned int ClientSessionBase::getLocalPort() {
	return this->localPort;
}

string ClientSessionBase::getRemoteIp() {
	return this->remoteIp;
}

unsigned int ClientSessionBase::getRemotePort() {
	return this->remotePort;
}

int ClientSessionBase::send(const char* buf, int len) {
	//return ::send(this->sock, buf, len, 0);

	_NetServerContext* context = new _NetServerContext;
	context->sockFd = this->sock;
	context->dataBuffer.setData(buf, len);
	context->session = (IClientSession*) this;
	context->state = CS_WRITE;

	struct epoll_event ev;
	ev.data.fd = this->sock;
	ev.events = EPOLLOUT | EPOLLET | EPOLLONESHOT;
	ev.data.ptr = context;
	epoll_ctl(this->epfd, EPOLL_CTL_MOD, this->sock, &ev);

	return 0;
}

int ClientSessionBase::send(const string& str) {
	return this->send(str.c_str(), str.length());
}

void ClientSessionBase::close() {
	shutdown(this->sock, 2);
}

} /* namespace network */
} /* namespace ducky */
