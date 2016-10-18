/*
 * TcpServer.h
 *
 *  Created on: Oct 18, 2016
 *      Author: ducky
 */

#ifndef DUCKY_NETWORK_TCPSERVER_H_
#define DUCKY_NETWORK_TCPSERVER_H_

#include <ducky/Object.h>
#include <ducky/network/ClientSession.h>
#include <ducky/exception/Exception.h>

EXCEPTION_DEF(TcpServerException);

namespace ducky {
namespace network {

class TcpServer: public Object {
public:
	TcpServer();
	virtual ~TcpServer();

	virtual void onAccept(int sock) {
	}
	virtual void onCreateSession(ClientSession*& refpSession) = 0;
	virtual void setIp(const string& ip);
	virtual void setPort(int port);
	virtual bool start();
	virtual bool stop();

private:
	class TcpServerImpl;
	TcpServerImpl* impl;
};

} /* namespace network */
} /* namespace ducky */

#endif /* DUCKY_NETWORK_TCPSERVER_H_ */
