/*
 * Socket.h
 *
 *  Created on: Dec 23, 2013
 *      Author: wdwarf
 */
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include "ducky/Object.h"
#include "ducky/exception/Exception.h"

using std::string;

#ifndef DUCKY_NETWORK_SOCKET_H_
#define DUCKY_NETWORK_SOCKET_H_

namespace ducky {
namespace network {

EXCEPTION_DEF(SocketException);
EXCEPTION_DEF2(ConnectException, SocketException);

class Socket : public Object {
public:
	Socket();
	Socket(int sock_fd);
	virtual ~Socket();

	int create(int af, int style, int protocol = 0);
	int createTcp();
	int createUdp();
	int getHandle();
	int close();
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

private:
	int sock_fd;
};

} /* namespace network */
} /* namespace wdwarf */

#endif /* WSOCKET_H_ */
