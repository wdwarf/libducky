/*
 * UdpServer.h
 *
 *  Created on: 2016年12月19日
 *      Author: liyawu
 */

#ifndef DUCKY_NETWORK_UDPSERVER_H_
#define DUCKY_NETWORK_UDPSERVER_H_

#include <ducky/thread/Thread.h>
#include <ducky/buffer/Buffer.h>
#include <ducky/thread/Mutex.h>
#include <ducky/network/NetworkException.h>
#include <ducky/network/INetServer.h>
#include <string>
#include <list>
#include <ctime>

/**
 * Sample:
 * ================================================
 *
 * //Client Session
 * class MyUdpClientSession : public IUdpClientSession{
 * public:
 * 	virtual void onReceive(const char* buf, int len){
 * 		this->send(buf, len);
 * 	}
 *
 * 	virtual void onSend(const char* buf, int len) {
 * 	}
 *
 * 	virtual void onConnected() {
 * 	}
 *
 * 	virtual void onDisconnected() {
 * 	}
 * }; //class MyUdpClientSession
 *
 *
 * int main(){
 * 	//UDP Server
 * 	typedef UdpServer<MyUdpClientSession> MyUdpServer;
 *
 * 	IUdpServer* myServer = new MyUdpServer;
 * 	myServer->setListenPort(12345);
 * 	myServer->setWorkThreadCount(100);
 * 	myServer->start();
 * 	myServer->join();	//block until the server stopped
 * 	delete myServer;
 * }
 *
 * ================================================
 */

namespace ducky {
namespace network {

class UdpServerImpl;
class IUdpClientSession: virtual public Object {
public:
	IUdpClientSession();
	virtual ~IUdpClientSession();

	//must implements these methods
	virtual void onReceive(const char* buf, int len) = 0;

	virtual void onSend(const char* buf, int len) {
	}
	virtual void onConnected() {
	}
	virtual void onDisconnected() {
	}

	virtual std::string getRemoteIp() const;
	virtual int getRemotePort() const;
	virtual std::string getLocalIp() const;
	virtual int getLocalPort() const;
	virtual void send(const char* buf, int len);

	const string& getClientId() const;
	void setSessionTimeout(int sec);
	int getSessionTimeout() const;
	void setSessionExpired(bool sessionExpired);
	bool isSessionExpired() const;

private:
	std::string remoteIp;
	int remotePort;
	std::string localIp;
	int localPort;
	string clientId;
	time_t lastCommTime;
	int sessionTimeout;
	bool sessionExpired;

	friend class UdpServerImpl;
	UdpServerImpl* server;
	std::list<buffer::Buffer> dataBuffers;
	thread::Mutex mutex;

	void init(const std::string& remoteIp, int remotePort,
			const std::string& localIp, int localPort, UdpServerImpl* svr);

	size_t getBufferSize();
	void addBuffer(const buffer::Buffer& buf);
	buffer::Buffer getBuffer();
	time_t getLastCommTime() const;
	void updateLastCommTime();
};

class _UdpServer: public INetServer {
public:
	_UdpServer();
	virtual ~_UdpServer();

	virtual void setIp(const string& ip);
	virtual string getIp() const;
	virtual void setPort(unsigned int port);
	virtual unsigned int getPort() const;
	virtual void setWorkThreadCount(int workThreadCount);
	virtual int getWorkThreadCount() const;
	virtual void start();
	virtual void stop(bool joinServerThread = false);
	virtual void join();
	virtual bool isRunning();
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
class UdpServer: public _UdpServer {
	void onCreateSession(IUdpClientSession** session) {
		*session = new S;
	}
};

} /* namespace network */
} /* namespace ducky */

#endif /* DUCKY_NETWORK_UDPSERVER_H_ */
