/*
 * Socket.cpp
 *
 *  Created on: Dec 23, 2013
 *      Author: wdwarf
 */

#include <ducky/network/Socket.h>
#include <netdb.h>
#include <sys/errno.h>
#include <sstream>
#include <cstring>

using namespace std;

namespace ducky {
namespace network {

Socket::Socket() :
		sock_fd(0) {
	//
}

Socket::Socket(int sock_fd) {
	this->sock_fd = sock_fd;
}

Socket::~Socket() {
	this->close();
}

bool Socket::attach(int sock_fd) {
	this->close();
	this->sock_fd = sock_fd;
	return true;
}

int Socket::dettach() {
	int oldSock = this->sock_fd;
	this->sock_fd = 0;
	return oldSock;
}

int Socket::create(int af, int style, int protocol) {
	if (this->sock_fd > 0) {
		this->close();
	}
	this->sock_fd = socket(af, style, protocol);

	if (this->sock_fd <= 0) {
		throw SocketException("can't create socket.", errno);
	}

	return this->sock_fd;
}

int Socket::getHandle() {
	return this->sock_fd;
}

int Socket::shutdown(int type) {
	if (this->sock_fd > 0) {
		return ::shutdown(this->sock_fd, type);
	}
	return 0;
}

int Socket::close() {
	int re = 0;
	if (this->sock_fd > 0) {
		this->shutdown();
		re = ::close(this->sock_fd);
		this->sock_fd = 0;
	}
	return re;
}

int Socket::createTcp() {
	return this->create(AF_INET, SOCK_STREAM);
}

int Socket::createUdp() {
	return this->create(AF_INET, SOCK_DGRAM);
}

int Socket::connect(string ip, int port) {
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	hostent* he = gethostbyname(ip.c_str());
	if (he && (he->h_length > 0)) {
		unsigned char* pAddr = (unsigned char*) he->h_addr_list[0];
		if (pAddr) {
			stringstream str;
			str << (unsigned int) pAddr[0] << "." << (unsigned int) pAddr[1]
					<< "." << (unsigned int) pAddr[2] << "."
					<< (unsigned int) pAddr[3];
			ip = str.str().c_str();
		}
	}
	addr.sin_addr.s_addr = inet_addr(ip.c_str());
	return ::connect(this->sock_fd, (sockaddr*) &addr, sizeof(sockaddr));
}

int Socket::bind(string ip, int port) {
	int re = -1;
	if (this->sock_fd > 0) {
		sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		if (!ip.empty()) {
			inet_aton(ip.c_str(), &addr.sin_addr);
		} else {
			addr.sin_addr.s_addr = 0;
		}
		re = ::bind(this->sock_fd, (sockaddr*) &addr, sizeof(sockaddr_in));
		if (re < 0) {
			throw SocketBindException("bind socket failed.", errno);
		}
	}
	return re;
}

int Socket::listen(int n) {
	int re = -1;
	if (this->sock_fd > 0) {
		re = ::listen(this->sock_fd, n);
	}
	return re;
}

int Socket::accept(sockaddr_in& addr) {
	int s_fd = 0;
	if (this->sock_fd > 0) {
		socklen_t addrLen = sizeof(addr);
		s_fd = ::accept(this->sock_fd, (sockaddr*) &addr, &addrLen);
	}
	return s_fd;
}

int Socket::send(const char* buf, socklen_t bufLen) {
	int re = -1;
	if (this->sock_fd > 0) {
		fd_set fs_send;
		timeval tv;
		tv.tv_sec = 5;
		tv.tv_usec = 0;
		FD_ZERO(&fs_send);
		FD_SET(this->sock_fd, &fs_send);
		re = ::select(this->sock_fd + 1, 0, &fs_send, 0, &tv);
		if ((re > 0) && (FD_ISSET(this->sock_fd, &fs_send))) {
			re = ::send(this->sock_fd, buf, bufLen, 0);
		}
	}
	return re;
}

int Socket::read(char* buf, socklen_t readBytes, int timeoutSec) {
	int re = -1;
	if (this->sock_fd > 0) {
		if (timeoutSec < 0) {
			re = ::read(this->sock_fd, buf, readBytes);
		} else {
			fd_set fs_read;
			timeval tv;
			tv.tv_sec = timeoutSec;
			tv.tv_usec = 0;
			FD_ZERO(&fs_read);
			FD_SET(this->sock_fd, &fs_read);
			re = ::select(this->sock_fd + 1, &fs_read, 0, 0, &tv);
			if ((re > 0) && FD_ISSET(this->sock_fd, &fs_read)) {
				re = ::read(this->sock_fd, buf, readBytes);
			}
		}
	}
	return re;
}

int Socket::sendTo(const char* buf, socklen_t bufLen, const sockaddr_in& addr) {
	int re = -1;
	if (this->sock_fd > 0) {
		fd_set fs_send;
		timeval tv;
		tv.tv_sec = 5;
		tv.tv_usec = 0;
		FD_ZERO(&fs_send);
		FD_SET(this->sock_fd, &fs_send);
		re = ::select(this->sock_fd + 1, 0, &fs_send, 0, &tv);
		if ((re > 0) && (FD_ISSET(this->sock_fd, &fs_send))) {
			re = ::sendto(this->sock_fd, buf, bufLen, 0, (sockaddr*) &addr,
					sizeof(sockaddr));
		}
	}
	return re;
}

int Socket::sendTo(const char* buf, socklen_t bufLen, const string& ip,
		int port) {
	if (ip.empty() || port <= 0) {
		return -1;
	}

	string realIp;
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	hostent* he = gethostbyname(realIp.c_str());
	if (he && (he->h_length > 0)) {
		unsigned char* pAddr = (unsigned char*) he->h_addr_list[0];
		if (pAddr) {
			stringstream str;
			str << (unsigned int) pAddr[0] << "." << (unsigned int) pAddr[1]
					<< "." << (unsigned int) pAddr[2] << "."
					<< (unsigned int) pAddr[3];
			realIp = str.str();
		}
	}
	addr.sin_addr.s_addr = inet_addr(ip.c_str());

	return this->sendTo(buf, bufLen, addr);
}

int Socket::recvFrom(char* buf, socklen_t readBytes, sockaddr_in& addr,
		int timeoutSec) {
	int re = -1;
	if (this->sock_fd > 0) {
		memset(&addr, 0, sizeof(addr));
		socklen_t addrSize = sizeof(addr);

		if (timeoutSec < 0) {
			re = ::recvfrom(this->sock_fd, buf, readBytes, 0, (sockaddr*) &addr,
					&addrSize);
		} else {
			fd_set fs_read;
			timeval tv;
			tv.tv_sec = timeoutSec;
			tv.tv_usec = 0;
			FD_ZERO(&fs_read);
			FD_SET(this->sock_fd, &fs_read);
			re = ::select(this->sock_fd + 1, &fs_read, 0, 0, &tv);
			if ((re > 0) && FD_ISSET(this->sock_fd, &fs_read)) {
				re = ::recvfrom(this->sock_fd, buf, readBytes, 0,
						(sockaddr*) &addr, &addrSize);
			}
		}
	}
	return re;
}

int Socket::recvFrom(char* buf, socklen_t readBytes, string& ip, int& port,
		int timeoutSec) {
	ip = "";
	port = 0;

	sockaddr_in addr = { 0 };
	int re = this->recvFrom(buf, readBytes, addr, timeoutSec);
	if (re > 0) {
		ip = inet_ntoa(addr.sin_addr);
		port = ntohs(addr.sin_port);
	}

	return re;
}

bool Socket::isConnected() {
	return (this->getRemotePort() > 0);
}

string Socket::getLocalAddress() {
	sockaddr_in addr;
	socklen_t addrLen = sizeof(addr);
	::getsockname(this->sock_fd, (sockaddr*) &addr, &addrLen);
	return inet_ntoa(addr.sin_addr);
}

int Socket::getLocalPort() {
	sockaddr_in addr;
	socklen_t addrLen = sizeof(addr);
	::getsockname(this->sock_fd, (sockaddr*) &addr, &addrLen);
	return ntohs(addr.sin_port);
}

string Socket::getRemoteAddress() {
	sockaddr_in addr;
	socklen_t addrLen = sizeof(addr);
	::getpeername(this->sock_fd, (sockaddr*) &addr, &addrLen);
	return inet_ntoa(addr.sin_addr);
}

int Socket::getRemotePort() {
	sockaddr_in addr;
	socklen_t addrLen = sizeof(addr);
	::getpeername(this->sock_fd, (sockaddr*) &addr, &addrLen);
	return ntohs(addr.sin_port);
}

int Socket::getSocketType() {
	if (this->sock_fd <= 0) {
		return -1;
	}
	int type = -1;
	unsigned int len = sizeof(type);
	::getsockopt(this->sock_fd, SOL_SOCKET, SO_TYPE, &type, &len);
	return type;
}

} /* namespace network */
} /* namespace wdwarf */

