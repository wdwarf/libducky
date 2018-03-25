#ifndef DUCKY_NETWORK_TCPCLIENT_H_
#define DUCKY_NETWORK_TCPCLIENT_H_

#include <ducky/Object.h>
#include <string>

using std::string;

namespace ducky {
namespace network {

class TcpClient: public Object {
public:
	TcpClient();
	virtual ~TcpClient();

	/*当已连接与失连接时，这两个函数分别被调用*/
	virtual void onConnected() = 0;
	virtual void onDisconnected() = 0;
	/*接收到数据时，这个函数被调用*/
	virtual void onReceive(const char* buf, size_t len) = 0;
	/*发送了数据时,这个函数被调用*/
	virtual void onSend(const char* buf, size_t len) = 0;

	/*发送数据*/
	virtual void send(const char* buf, size_t len);
	virtual void send(const string& str);

	virtual void setLocalAddress(const string& localAddr);
	virtual const string& getLocalAddress() const;
	virtual void setLocalPort(int port);
	virtual int getLocalPort() const;

	/*设置服务器地址*/
	virtual void setServerAddress(const string& serverAddress);
	virtual const string& getServerAddress() const;
	/*设置服务器端口*/
	virtual void setServerPort(int serverPort);
	virtual int getServerPort() const;
	/*启动\停止*/
	virtual void start();
	virtual void stop();

private:
	class TcpClientImpl;
	TcpClientImpl* impl;
};

} //namespace network
} //namespace ducky

#endif // TCPWORKTHREAD_H
