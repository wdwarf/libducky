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

#include <iostream>

using namespace std;

namespace ducky {
namespace network {

ClientSessionBase::ClientSessionBase() :
		sock(0), localPort(0), remotePort(0) {
	// TODO Auto-generated constructor stub

}

ClientSessionBase::~ClientSessionBase() {
	// TODO Auto-generated destructor stub
}

void ClientSessionBase::init(int sock) {
	//inet_ntoa(clientAddr.sin_addr)
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
	return ::send(this->sock, buf, len, 0);
}

int ClientSessionBase::send(const string& str) {
	return this->send(str.c_str(), str.length());
}

void ClientSessionBase::close() {
	shutdown(this->sock, 2);
}

} /* namespace network */
} /* namespace ducky */
