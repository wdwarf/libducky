/*
 * Socket.cpp
 *
 *  Created on: Dec 23, 2013
 *      Author: wdwarf
 */

#include <ducky/network/Socket.h>

#ifdef __WINNT__
#include <Mstcpip.h>
#define SIO_UDP_CONNRESET _WSAIOW(IOC_VENDOR, 12)
#else
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/errno.h>
#include <fcntl.h>
#endif

#include <sstream>
#include <cstring>
#include <iostream>

using namespace std;

namespace ducky {
namespace network {

Socket::Socket() :
		sockFd(0) {
#ifdef __WINNT__
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,0), &wsaData);
#endif
}

Socket::Socket(int sockFd) {
	this->sockFd = sockFd;
}

Socket::~Socket() {
	this->close();
}

bool Socket::attach(int sockFd) {
	this->close();
	this->sockFd = sockFd;
	return true;
}

int Socket::dettach() {
	int oldSock = this->sockFd;
	this->sockFd = 0;
	return oldSock;
}

int Socket::create(int af, int style, int protocol) {
	if (this->sockFd > 0) {
		this->close();
	}
	this->sockFd = socket(af, style, protocol);

	if (this->sockFd <= 0) {
		THROW_EXCEPTION(SocketException,
				string("can't create socket.") + strerror(errno), errno);
	}

#ifdef __WINNT__
	if (SOCK_DGRAM == style) {
		BOOL bNewBehavior = FALSE;
		DWORD dwBytesReturned = 0;
		WSAIoctl(iSock, SIO_UDP_CONNRESET, &bNewBehavior, sizeof bNewBehavior,
				NULL, 0, &dwBytesReturned, NULL, NULL);
	}
#endif

	return this->sockFd;
}

int Socket::getHandle() {
	return this->sockFd;
}

int Socket::shutdown(int type) {
	if (this->sockFd > 0) {
		return ::shutdown(this->sockFd, type);
	}
	return 0;
}

int Socket::close() {
	int re = 0;
	if (this->sockFd > 0) {
		this->shutdown();
#if defined(__WINNT__) || defined(__MINGW32__)
		re = ::closesocket(this->sockFd);
#else
		re = ::close(this->sockFd);
#endif
		this->sockFd = 0;
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
	if (this->sockFd <= 0) {
		return -1;
	}

	int re = -1;
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

	//设置为非阻塞模式
#if defined(__WINNT__) || defined(__MINGW32__)
	unsigned long isFIONBIO = 1;
	ioctlsocket(this->sockFd, FIONBIO, &isFIONBIO);
#else
	int opts = fcntl(this->sockFd, F_GETFL);
	opts |= O_NONBLOCK;
	fcntl(this->sockFd, F_SETFL, opts);
#endif

	if (-1 == ::connect(this->sockFd, (sockaddr*) &addr, sizeof(sockaddr))) {
		timeval tm;
		fd_set set;
		int error = -1;
		tm.tv_sec = 3;
		tm.tv_usec = 0;
		FD_ZERO(&set);
		FD_SET(this->sockFd, &set);
		do {
			re = select(this->sockFd + 1, NULL, &set, NULL, &tm);
		} while (re < 0 && EINTR == errno);

		if (1 == re) {
			socklen_t len = sizeof(int);
			getsockopt(this->sockFd, SOL_SOCKET, SO_ERROR, (char *) &error,
					&len);
			if (0 == error) {
				re = 0;
			} else {
				re = -1;
			}
		} else {
			re = -1;
		}
	}

	//设置为阻塞模式
#if defined(__WINNT__) || defined(__MINGW32__)
	isFIONBIO = 0;
	ioctlsocket(this->sockFd, FIONBIO, &isFIONBIO);
#else
	opts = fcntl(this->sockFd, F_GETFL);
	opts &= ~O_NONBLOCK;
	fcntl(this->sockFd, F_SETFL, opts);
#endif

	return re;
}

int Socket::bind(string ip, int port) {
	int re = -1;
	if (this->sockFd > 0) {
		if (port <= 0)
			return false;

		sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		if (!ip.empty()) {
#if defined(__WINNT__) || defined(__MINGW32__)
			addr.sin_addr.s_addr = inet_addr(ip.c_str());
#else
			inet_aton(ip.c_str(), &addr.sin_addr);
#endif
		} else {
			addr.sin_addr.s_addr = INADDR_ANY;
		}

		int flag = 1;
		setsockopt(this->sockFd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag));

		re = ::bind(this->sockFd, (sockaddr*) &addr, sizeof(sockaddr));
		if (re < 0) {
			THROW_EXCEPTION(SocketBindException,
					string("bind socket failed.") + strerror(errno), errno);
		}
	}
	return re;
}

int Socket::listen(int n) {
	int re = -1;
	if (this->sockFd > 0) {
		re = ::listen(this->sockFd, n);
	}
	return re;
}

int Socket::accept(sockaddr_in& addr) {
	int s_fd = 0;
	if (this->sockFd > 0) {
		socklen_t addrLen = sizeof(addr);
		s_fd = ::accept(this->sockFd, (sockaddr*) &addr, &addrLen);
	}
	return s_fd;
}

int Socket::send(const char* buf, socklen_t bufLen) {
	int re = -1;
	if (this->sockFd > 0) {
		fd_set fs_send;
		timeval tv;
		tv.tv_sec = 5;
		tv.tv_usec = 0;
		FD_ZERO(&fs_send);
		FD_SET(this->sockFd, &fs_send);
		re = ::select(this->sockFd + 1, 0, &fs_send, 0, &tv);
		if (re > 0) {
			re = ::send(this->sockFd, buf, bufLen, 0);
		}
	}
	return re;
}

int Socket::read(char* buf, socklen_t readBytes, int timeoutSec) {
	int re = -1;
	if (this->sockFd > 0) {
		fd_set fs_read;
		timeval tv;
		tv.tv_sec = timeoutSec;
		tv.tv_usec = 0;
		FD_ZERO(&fs_read);
		FD_SET(this->sockFd, &fs_read);
		re = ::select(this->sockFd + 1, &fs_read, 0, 0,
				(-1 == timeoutSec ? 0 : &tv));
		if (re > 0) {
#if defined(__WINNT__) || defined(__MINGW32__)
			re = ::recv(this->sockFd, buf, readBytes, 0);
#else
			re = ::read(this->sockFd, buf, readBytes);
#endif
		}
	}
	return re;
}

int Socket::sendTo(const char* buf, socklen_t bufLen, const sockaddr_in& addr) {
	return ::sendto(this->sockFd, buf, bufLen, 0, (sockaddr*) &addr,
			sizeof(sockaddr));
}

bool Socket::isConnected() {
	return (this->getRemotePort() > 0);
}

string Socket::getLocalAddress() {
	sockaddr_in addr;
	socklen_t addrLen = sizeof(addr);
	::getsockname(this->sockFd, (sockaddr*) &addr, &addrLen);
	return inet_ntoa(addr.sin_addr);
}

int Socket::getLocalPort() {
	sockaddr_in addr;
	socklen_t addrLen = sizeof(addr);
	::getsockname(this->sockFd, (sockaddr*) &addr, &addrLen);
	return ntohs(addr.sin_port);
}

string Socket::getRemoteAddress() {
	sockaddr_in addr;
	socklen_t addrLen = sizeof(addr);
	::getpeername(this->sockFd, (sockaddr*) &addr, &addrLen);
	return inet_ntoa(addr.sin_addr);
}

int Socket::getRemotePort() {
	sockaddr_in addr;
	socklen_t addrLen = sizeof(addr);
	::getpeername(this->sockFd, (sockaddr*) &addr, &addrLen);
	return ntohs(addr.sin_port);
}

int Socket::getSocketType() {
	if (this->sockFd <= 0) {
		return -1;
	}
#if defined(__WINNT__) || defined(__MINGW32__)
	char type = -1;
#else
	int type = -1;
#endif
	socklen_t len = sizeof(type);
	::getsockopt(this->sockFd, SOL_SOCKET, SO_TYPE, &type, &len);
	return type;
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
	if (this->sockFd > 0) {
		fd_set fs_read;
		timeval tv;
		tv.tv_sec = timeoutSec;
		tv.tv_usec = 0;
		FD_ZERO(&fs_read);
		FD_SET(this->sockFd, &fs_read);
		re = ::select(this->sockFd + 1, &fs_read, 0, 0,
				(-1 == timeoutSec ? 0 : &tv));
		if (re > 0) {
			memset(&addr, 0, sizeof(addr));
			socklen_t addrSize = sizeof(addr);
			re = ::recvfrom(this->sockFd, buf, readBytes, 0, (sockaddr*) &addr,
					&addrSize);
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

} /* namespace network */
} /* namespace wdwarf */

