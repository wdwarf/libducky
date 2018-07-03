/*
 * SockAddr.h
 *
 *  Created on: 2018年4月28日
 *      Author: liyawu
 */

#ifndef DUCKY_NETWORK_SOCKADDR_H_
#define DUCKY_NETWORK_SOCKADDR_H_

#if defined(WIN32) || defined(__MINGW32__)

#include <winsock2.h>
#include <ws2tcpip.h>

#else

#include <netinet/in.h>

#endif

#include <string>

namespace ducky {
namespace network {

class SockAddr {
public:
	SockAddr();
	SockAddr(const sockaddr_in& addr);
	SockAddr(const sockaddr& addr);
	SockAddr(const std::string& address, unsigned int port);
	virtual ~SockAddr();

	void setFamily(unsigned short family);
	unsigned short getFamily() const;
	void setPort(unsigned short port);
	unsigned short getPort() const;
	void setAddress(const std::string& address);
	std::string getAddress() const;

	operator sockaddr_in&();
	operator const sockaddr_in&() const;
	operator sockaddr_in*();
	operator const sockaddr_in*() const;
	operator sockaddr&();
	operator const sockaddr&() const;
	operator sockaddr*();
	operator const sockaddr*() const;

private:
	sockaddr _addr;
};

} /* namespace network */
} /* namespace ducky */

#endif /* DUCKY_NETWORK_SOCKADDR_H_ */
