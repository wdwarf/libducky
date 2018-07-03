/*
 * UdpServerBase.h
 *
 *  Created on: 2018年4月28日
 *      Author: liyawu
 */

#ifndef DUCKY_NETWORK_UDPSERVERBASE_H_
#define DUCKY_NETWORK_UDPSERVERBASE_H_

#include <ducky/exception/Exception.h>
#include <ducky/thread/Thread.h>
#include <ducky/buffer/Buffer.h>
#include <ducky/network/Socket.h>
#include <ducky/network/SockAddr.h>
#include <ducky/thread/Mutex.h>
#include <ducky/thread/Semaphore.h>
#include <list>

namespace ducky {
namespace network {

EXCEPTION_DEF(UdpServerBaseException);

class UdpServerBase : public virtual Object{
public:
	UdpServerBase();
	virtual ~UdpServerBase();

	/**
	 * 设置IP和端口
	 * 在启动服务之前设置生效
	 */
	const std::string& getServerIp() const;
	void setServerIp(const std::string& serverIp);
	unsigned int getServerPort() const;
	void setServerPort(unsigned int serverPort);

	/**
	 * 启动服务
	 * 失败会抛出UdpServerBaseException
	 */
	void start();
	/**
	 * 停止服务
	 */
	void stop();

	/**
	 * 发送数据
	 */
	void send(const buffer::Buffer& buf, const SockAddr& sockAddr);
	void send(const char* buf, unsigned int size, const SockAddr& sockAddr);

protected:
	/**
	 * 事件回调函数
	 */
	virtual void onStart() {}
	virtual void onStop() {}
	virtual void onReceive(const char* buf, unsigned int size, const SockAddr& sockAddr) = 0;
	virtual void onSend(const char* buf, unsigned int size, const SockAddr& sockAddr) {}

private:
	class UdpServerBaseImpl;
	UdpServerBaseImpl* impl;
};

} /* namespace network */
} /* namespace ducky */

#endif /* UDPSERVERBASE_H_ */
