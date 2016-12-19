/*
 * UdpServer.h
 *
 *  Created on: 2016年12月19日
 *      Author: liyawu
 */

#ifndef DUCKY_NETWORK_UDPSERVER_H_
#define DUCKY_NETWORK_UDPSERVER_H_

#include <ducky/thread/Thread.h>
#include <ducky/network/NetworkException.h>
#include <string>

namespace ducky {
namespace network {

class UdpServerImpl;
class IUdpClientSession: virtual public Object {
public:
	IUdpClientSession() {
	}
	virtual ~IUdpClientSession() {
	}

	//must implements these methods
	virtual void onReceive(const char* buf, int len) = 0;
	virtual void onSend(const char* buf, int len) = 0;
	virtual void onConnected(){};
	virtual void onDisconnected(){};


	virtual std::string getRemoteIp() const;
	virtual int getRemotePort() const;
	virtual std::string getLocalIp() const;
	virtual int getLocalPort() const;
	virtual void send(const char* buf, int len);

private:
	std::string remoteIp;
	int remotePort;
	std::string localIp;
	int localPort;

	friend class UdpServerImpl;
	UdpServerImpl* server;
	void init(const std::string& remoteIp, int remotePort,
			const std::string& localIp, int localPort, UdpServerImpl* svr);
};

class IUdpServer: virtual public Object {
public:
	virtual void setListenPort(int port) = 0;
	virtual void start() = 0;
	virtual void stop() = 0;
	virtual void join() = 0;
};

class _UdpServer: public IUdpServer {
public:
	_UdpServer();
	virtual ~_UdpServer();

	virtual void setListenPort(int port);
	virtual void start();
	virtual void stop();
	virtual void join();
	virtual void onStart() {
	}
	virtual void onStop() {
	}

protected:
	virtual void onCreateSession(IUdpClientSession** session) = 0;

private:
	UdpServerImpl* impl;
	friend class UdpServerImpl;
};

template<class S>
class UdpServer : public _UdpServer{
	void onCreateSession(IUdpClientSession** session){
		*session = new S;
	}
};

} /* namespace network */
} /* namespace ducky */

#endif /* DUCKY_NETWORK_UDPSERVER_H_ */
