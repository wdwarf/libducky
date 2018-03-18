/*
 * UdpClient.h
 *
 *  Created on: 2016年12月20日
 *      Author: liyawu
 */

#ifndef DUCKY_NETWORK_UDPCLIENT_H_
#define DUCKY_NETWORK_UDPCLIENT_H_

#include <ducky/thread/Thread.h>
#include <ducky/smartptr/ScopedPtr.h>
#include <ducky/network/Socket.h>
#include <ducky/network/NetworkException.h>
#include <ducky/buffer/Buffer.h>
#include <ducky/thread/Mutex.h>
#include <ducky/thread/Semaphore.h>

#include <string>
#include <list>

namespace ducky {
namespace network {

class UdpClientContext: virtual public Object {
public:
	UdpClientContext();
	UdpClientContext(const buffer::Buffer& data, const string& ip, int port);
	UdpClientContext(const char* data, int dataSize, const string& ip,
			int port);

	const buffer::Buffer& getData() const;
	void setData(const buffer::Buffer& data);
	const std::string& getIp() const;
	void setIp(const std::string& ip);
	int getPort() const;
	void setPort(int port);

private:
	buffer::Buffer data;
	std::string ip;
	int port;
};

class UdpClientReadThread;
class UdpClientSendThread;

class UdpClient: public thread::Thread {
public:
	UdpClient();
	UdpClient(const string& serverIp, int serverPort,
			const string& localIp = "", int localPort = 0);
	virtual ~UdpClient();

	void send(const char* buf, int len, const string& ip = "", int port = 0);

	//must implements these methods
	virtual void onReceive(const char* buf, int len, const string& ip,
			int port) = 0;

	virtual void onSend(const char* buf, int len, const string& ip, int port) {
	}

	virtual void onStart() {
	}
	virtual void onStop() {
	}

	const std::string& getLocalIp() const;
	void setLocalIp(const std::string& localIp);
	int getLocalPort() const;
	void setLocalPort(int localPort);
	const std::string& getServerIp() const;
	void setServerIp(const std::string& serverIp);
	int getServerPort() const;
	void setServerPort(int serverPort);
	const Socket& getSock() const;
	void setSock(const Socket& sock);
	int getBufferSize() const;
	void setBufferSize(int bufferSize);
	void setBroadcast(bool isBroadcast);

	void start();
	void stop();

private:
	void run();

private:
	std::string serverIp;
	int serverPort;
	std::string localIp;
	int localPort;
	unsigned int bufferSize;
	Socket sock;
	smartptr::ScopedPtr<UdpClientReadThread> readThread;
	smartptr::ScopedPtr<UdpClientSendThread> sendThread;

	friend class UdpClientReadThread;
	friend class UdpClientSendThread;
};

class UdpClientReadThread: public thread::Thread {
public:
	UdpClientReadThread(UdpClient* parent);

	void recv(const UdpClientContext& context);
	void recv(const buffer::Buffer& data, const string& ip, int port);
	void recv(const char* data, int dataSize, const string& ip, int port);

	void stop();

private:
	void run();

	UdpClient* parent;
	std::list<UdpClientContext> contexts;
	thread::Mutex mutex;
	thread::Semaphore sem;
};

class UdpClientSendThread: public thread::Thread {
public:
	UdpClientSendThread(UdpClient* parent);
	virtual ~UdpClientSendThread();

	void send(const UdpClientContext& context);
	void send(const buffer::Buffer& data, const string& ip, int port);
	void send(const char* data, int dataSize, const string& ip, int port);

	void stop();

private:
	void run();

	UdpClient* parent;
	std::list<UdpClientContext> contexts;
	thread::Mutex mutex;
	thread::Semaphore sem;
};

} /* namespace network */
} /* namespace ducky */

#endif /* DUCKY_NETWORK_UDPCLIENT_H_ */
