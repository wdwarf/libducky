/*
 * Socket.h
 *
 *  Created on: Dec 23, 2013
 *      Author: wdwarf
 */

#ifndef DUCKY_NETWORK_SOCKET_H_
#define DUCKY_NETWORK_SOCKET_H_

#ifdef WIN32

#include <winsock2.h>
#include <ws2tcpip.h>
#define SHUT_RDWR 2

#else

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#endif

#include <string>
#include <ducky/Object.h>
#include <ducky/exception/Exception.h>

#ifndef socklen_t

#ifdef __MINGW32__
#define socklen_t int
#else
#define socklen_t unsigned int
#endif

#endif

namespace ducky {
namespace network {

using std::string;

EXCEPTION_DEF(SocketException);
EXCEPTION_DEF2(ConnectException, SocketException);
EXCEPTION_DEF2(SocketBindException, SocketException);

class Socket: virtual public Object {
public:
	Socket();
	Socket(int sockFd);
	virtual ~Socket();

	int create(int af, int style, int protocol = 0);
	int createTcp();
	int createUdp();
	int getHandle();
	int close();
	int shutdown(int type = SHUT_RDWR);
	bool attach(int sockFd);
	int dettach();
	void setBlocking(bool nonBlocking = true);
	bool isNonBlocking() const;
	bool isUseSelect() const;
	void setUseSelect(bool useSelect);

	string getLocalAddress();
	int getLocalPort();
	string getRemoteAddress();
	int getRemotePort();
	int getSocketType();

	int connect(string ip, int port, int msTimeout = 3000);
	bool isConnected();
	void bind(string ip, int port);
	void listen(int n = 10);
	int accept(sockaddr_in& addr);

	int send(const char* buf, socklen_t bufLen);
	int read(char* buf, socklen_t readBytes, int timeoutSec = -1);

	int sendTo(const char* buf, socklen_t bufLen, const sockaddr_in& addr);
	int sendTo(const char* buf, socklen_t bufLen, const string& ip, int port);
	int recvFrom(char* buf, socklen_t readBytes, sockaddr_in& addr,
			int timeoutSec = -1);
	int recvFrom(char* buf, socklen_t readBytes, string& ip, int& port,
			int timeoutSec = -1);

	static bool SetBlocking(int sockFd, bool isNonBlocking = true);
	static bool IsNonBlocking(int sockFd);

private:
	int sockFd;
	bool useSelect;
};

} /* namespace network */
} /* namespace wdwarf */

#endif /* WSOCKET_H_ */
