/*
 * UdpServer.cpp
 *
 *  Created on: 2016年12月19日
 *      Author: liyawu
 */

#include <ducky/network/UdpServer.h>
#include <ducky/smartptr/SharedPtr.h>
#include <ducky/smartptr/ScopedPtr.h>
#include <ducky/network/Socket.h>
#include <ducky/thread/Mutex.h>
#include <errno.h>
#include <map>
#include <list>
#include <memory>
#include <sstream>
#include <iostream>
#include <ducky/thread/Semaphore.h>
#include <ducky/buffer/Buffer.h>

using namespace std;
using namespace ducky::smartptr;
using namespace ducky::thread;
using namespace ducky::buffer;

namespace ducky {
namespace network {

class UdpSendContext {
public:
	UdpSendContext() {
	}
	UdpSendContext(SharedPtr<IUdpClientSession> session, const char* buf,
			int len) {
		this->session = session;
		this->data.setData(buf, len);
	}

	const Buffer& getData() const {
		return data;
	}

	void setData(const Buffer& data) {
		this->data = data;
	}

	const SharedPtr<IUdpClientSession>& getSession() const {
		return session;
	}

	void setSession(const SharedPtr<IUdpClientSession>& session) {
		this->session = session;
	}

private:
	SharedPtr<IUdpClientSession> session;
	Buffer data;
};

class UdpServerImpl: public thread::Thread {
public:
	UdpServerImpl(_UdpServer* svr);
	virtual ~UdpServerImpl();

	virtual void setListenPort(int port);
	virtual bool start();
	virtual bool stop();
	virtual void onStart() {
		this->server->onStart();
	}
	virtual void onStop() {
		this->server->onStop();
	}

	void send(const string& sessionId, const char* buf, int len);

public:
	static string WrapSessionId(const string& ip, int port);

private:
	virtual void run();
	void addSession(IUdpClientSession* pSession);
	SharedPtr<IUdpClientSession> getSession(string sessionId);

	friend class SendThread;
	class SendThread: public Thread {
	public:
		SendThread(UdpServerImpl* parent) {
			this->parent = parent;
		}

		void send(SharedPtr<IUdpClientSession> session, const char* buf,
				int len) {
			MutexLocker lk(this->mutex);
			if (session.get() && buf && len > 0) {
				UdpSendContext context(session, buf, len);
				this->constexts.push_back(context);
				this->sem.release();
			}
		}

		bool stop() {
			Thread::stop();
			this->sem.release();
			return true;
		}

	private:
		void run() {
			while (!this->canStop()) {
				this->sem.wait();
				if (this->canStop())
					break;

				UdpSendContext context;
				{
					MutexLocker lk(this->mutex);
					if (constexts.empty())
						continue;

					context = constexts.front();
					constexts.pop_front();
				}

				int re = this->parent->sock->sendTo(context.getData().getData(),
						context.getData().getSize(),
						context.getSession()->getRemoteIp(),
						context.getSession()->getRemotePort());
				if (re > 0) {
					context.getSession()->onSend(context.getData().getData(),
							context.getData().getSize());
				}
			}
			this->constexts.clear();
		}

		Semaphore sem;
		Mutex mutex;
		list<UdpSendContext> constexts;
		UdpServerImpl* parent;
	};

	ScopedPtr<SendThread> sendThread;

	typedef map<string, SharedPtr<IUdpClientSession> > SessionsMap;
	int listenPort;
	SharedPtr<Socket> sock;
	SessionsMap sessions;
	Mutex mutex;
	_UdpServer* server;
};

//======================================================
//======================================================

void IUdpClientSession::init(const std::string& remoteIp, int remotePort,
		const std::string& localIp, int localPort, UdpServerImpl* svr) {
	this->remoteIp = remoteIp;
	this->remotePort = remotePort;
	this->localIp = localIp;
	this->localPort = localPort;
	this->server = svr;
}

std::string IUdpClientSession::getRemoteIp() const {
	return this->remoteIp;
}

int IUdpClientSession::getRemotePort() const {
	return this->remotePort;
}

std::string IUdpClientSession::getLocalIp() const {
	return this->localIp;
}

int IUdpClientSession::getLocalPort() const {
	return this->localPort;
}

void IUdpClientSession::send(const char* buf, int len) {
	this->server->send(
			UdpServerImpl::WrapSessionId(this->remoteIp, this->remotePort), buf,
			len);
}

//======================================================
//======================================================

UdpServerImpl::UdpServerImpl(_UdpServer* svr) :
		sendThread(new SendThread(this)), listenPort(0), sock(new Socket), server(
				svr) {

}

UdpServerImpl::~UdpServerImpl() {

}

void UdpServerImpl::setListenPort(int port) {
	this->listenPort = port;
	cout << this->listenPort << endl;
}

string UdpServerImpl::WrapSessionId(const string& ip, int port) {
	stringstream sId;
	sId << ip << ":" << port;
	return sId.str();
}

void UdpServerImpl::send(const string& sessionId, const char* buf, int len) {
	SharedPtr<IUdpClientSession> session = getSession(sessionId);
	if (session) {
		/*this->sock->sendTo(buf, len, session->getRemoteIp(),
		 session->getRemotePort());
		 session->onSend(buf, len);*/
		this->sendThread->send(session, buf, len);
	}
}

void UdpServerImpl::addSession(IUdpClientSession* pSession) {
	MutexLocker lk(this->mutex);
	SharedPtr<IUdpClientSession> session(pSession);
	this->sessions.insert(
			make_pair(
					this->WrapSessionId(pSession->getRemoteIp(),
							pSession->getRemotePort()), session));
}

SharedPtr<IUdpClientSession> UdpServerImpl::getSession(string sessionId) {
	MutexLocker lk(this->mutex);
	SessionsMap::iterator it = this->sessions.find(sessionId);
	if (it != this->sessions.end()) {
		return it->second;
	}
	return SharedPtr<IUdpClientSession>();
}

bool UdpServerImpl::start() {
	try {
		this->sock->close();
		this->sock->createUdp();
		this->sock->bind("", this->listenPort);
	} catch (exception::Exception& e) {
		throw UdpServerException(e.what(), errno);
	}

	if (!this->sendThread->start()) {
		throw UdpServerException("Send thread start failed.", errno);
	}

	if (!Thread::start()) {
		this->sendThread->stop();
		this->sendThread->join();
		throw UdpServerException("Server thread start failed.", errno);
	}

	return true;
}

bool UdpServerImpl::stop() {
	this->sendThread->stop();
	this->sendThread->join();

	Thread::stop();
	this->sock->shutdown();

	return true;
}

void UdpServerImpl::run() {
	this->onStart();
	while (!this->canStop()) {
		char buf[2048] = { 0 };
		int len = 2048;
		string ip;
		int port = 0;

		if (this->sock->recvFrom(buf, len, ip, port) > 0) {
			string sId = this->WrapSessionId(ip, port);
			SharedPtr<IUdpClientSession> session = this->getSession(sId);
			if (session.get()) {
				try {
					session->onReceive(buf, len);
				} catch (...) {
				}
			} else {
				IUdpClientSession* pSession = NULL;
				this->server->onCreateSession(&pSession);
				if (NULL != pSession) {
					pSession->init(ip, port, this->sock->getLocalAddress(),
							this->sock->getLocalPort(), this);
					try {
						pSession->onConnected();
					} catch (...) {
					}
					this->addSession(pSession);
					try {
						pSession->onReceive(buf, len);
					} catch (...) {
					}
				}
			}
		} else {
			break;
		}
	}
	this->sock->close();

	for (SessionsMap::iterator it = this->sessions.begin();
			it != this->sessions.end(); ++it) {
		it->second->onDisconnected();
	}

	this->onStop();
}

_UdpServer::_UdpServer() :
		impl(new UdpServerImpl(this)) {
	// TODO Auto-generated constructor stub

}

_UdpServer::~_UdpServer() {
	// TODO Auto-generated destructor stub
	delete this->impl;
}
void _UdpServer::setListenPort(int port) {
	this->impl->setListenPort(port);
}

void _UdpServer::start() {
	this->impl->start();
}

void _UdpServer::stop() {
	this->impl->stop();
}

void _UdpServer::join() {
	this->impl->join();
}

} /* namespace network */
} /* namespace ducky */
