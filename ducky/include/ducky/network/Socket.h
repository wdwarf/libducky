/*
 * Socket.h
 *
 *  Created on: Dec 23, 2013
 *      Author: wdwarf
 */
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <ducky/Object.h>
#include <ducky/exception/Exception.h>

#ifndef DUCKY_NETWORK_SOCKET_H_
#define DUCKY_NETWORK_SOCKET_H_

namespace ducky {
namespace network {

using std::string;

EXCEPTION_DEF(SocketException);
EXCEPTION_DEF2(ConnectException, SocketException);
EXCEPTION_DEF2(SocketBindException, SocketException);

class Socket: virtual public Object {
public:
	Socket();
	Socket(int sock_fd);
	virtual ~Socket();

	int create(int af, int style, int protocol = 0);
	int createTcp();
	int createUdp();
	int getHandle();
	int close();
	int shutdown(int type = SHUT_RDWR);
	bool attach(int sock_fd);
	int dettach();

	string getLocalAddress();
	int getLocalPort();
	string getRemoteAddress();
	int getRemotePort();
	int getSocketType();

	int connect(string ip, int port);
	bool isConnected();
	int bind(string ip, int port);
	int listen(int n);
	int accept(sockaddr_in& addr);

	int send(const char* buf, socklen_t bufLen);
	int read(char* buf, socklen_t readBytes, int timeoutSec = -1);

	int sendTo(const char* buf, socklen_t bufLen, const sockaddr_in& addr);
	int sendTo(const char* buf, socklen_t bufLen, const string& ip, int port);
	int recvFrom(char* buf, socklen_t readBytes, sockaddr_in& addr,
			int timeoutSec = -1);
	int recvFrom(char* buf, socklen_t readBytes, string& ip, int& port,
			int timeoutSec = -1);

private:
	int sock_fd;
};

} /* namespace network */
} /* namespace wdwarf */

#endif /* WSOCKET_H_ */
