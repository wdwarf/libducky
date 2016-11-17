/*
 * TcpServer.h
 *
 *  Created on: 2016-11-15
 *      Author: ducky
 */

#ifndef TCPSERVER_H_
#define TCPSERVER_H_

#include <ducky/network/INetServer.h>
#include <ducky/network/IClientSession.h>

namespace ducky {
namespace network {

class _TcpServer: public INetServer {
public:
	_TcpServer();
	virtual ~_TcpServer();

	virtual void setIp(const string& ip);
	virtual void setPort(unsigned int port);
	virtual bool start();
	virtual bool stop();
	virtual bool isRunning();
	virtual void join();
	virtual void onStart() {
	}
	virtual void onStop() {
	}

protected:
	virtual void onCreateSession(IClientSession*& pSession) = 0;

public:
	class _TcpServerImpl;

private:
	_TcpServerImpl* impl;
	void run(){}

};

template<class T>
class TcpServer: public _TcpServer {

private:
	virtual void onCreateSession(IClientSession*& pSession) {
		pSession = new T;
	}
};

} /* namespace network */
} /* namespace ducky */
#endif /* TCPSERVER_H_ */
