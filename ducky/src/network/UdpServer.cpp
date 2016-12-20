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

//======================================================
//======================================================

class UdpServerImpl: public thread::Thread {
public:
	UdpServerImpl(_UdpServer* svr);
	virtual ~UdpServerImpl();

	virtual void setListenPort(int port);
	virtual void setWorkThreadCount(int workThreadCount);
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
	SharedPtr<IUdpClientSession> getBusySession();

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

	friend class WorkThread;
	class WorkThread: public Thread {
	public:
		WorkThread(UdpServerImpl* parent) {
			this->parent = parent;
		}
	private:
		void run() {
			while (!this->canStop()) {
				SharedPtr<IUdpClientSession> session =
						this->parent->getBusySession();
				if (session.get()) {
					buffer::Buffer buffer = session->getBuffer();
					session->onReceive(buffer.getData(), buffer.getSize());
					session->setHandling(false);
				}
			}
		}

		UdpServerImpl* parent;
	};

	ScopedPtr<SendThread> sendThread;
	list<SharedPtr<WorkThread> > workThreads;

	typedef map<string, SharedPtr<IUdpClientSession> > SessionsMap;
	int workThreadCount;
	int listenPort;
	SharedPtr<Socket> sock;
	SessionsMap sessions;
	Semaphore semWorkThread;
	Mutex mutex;
	_UdpServer* server;
};

//======================================================
//======================================================
IUdpClientSession::IUdpClientSession() : handling(false) {
}

IUdpClientSession::~IUdpClientSession() {
}

bool IUdpClientSession::isHandling() const {
	return handling;
}

void IUdpClientSession::setHandling(bool handling) {
	this->handling = handling;
}

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

void IUdpClientSession::addBuffer(const buffer::Buffer& buf) {
	MutexLocker lk(this->mutex);
	this->dataBuffers.push_back(buf);
}

size_t IUdpClientSession::getBufferSize(){
	MutexLocker lk(this->mutex);
	return this->dataBuffers.size();
}

Buffer IUdpClientSession::getBuffer() {
	MutexLocker lk(this->mutex);
	Buffer buffer;
	if(!this->dataBuffers.empty()){
		buffer = this->dataBuffers.front();
		this->dataBuffers.pop_front();
	}

	return buffer;
}

//======================================================
//======================================================

UdpServerImpl::UdpServerImpl(_UdpServer* svr) :
		workThreadCount(10), sendThread(new SendThread(this)), listenPort(0), sock(
				new Socket), server(svr) {

}

UdpServerImpl::~UdpServerImpl() {

}

void UdpServerImpl::setListenPort(int port) {
	this->listenPort = port;
}

void UdpServerImpl::setWorkThreadCount(int workThreadCount) {
	this->workThreadCount = workThreadCount;
}

string UdpServerImpl::WrapSessionId(const string& ip, int port) {
	stringstream sId;
	sId << ip << ":" << port;
	return sId.str();
}

SharedPtr<IUdpClientSession> UdpServerImpl::getBusySession() {
	this->semWorkThread.wait();
	MutexLocker lk(this->mutex);
	SharedPtr<IUdpClientSession> session;
	if (!this->sessions.empty()) {
		for(SessionsMap::iterator it = this->sessions.begin(); it != this->sessions.end(); ++it){
			if(!it->second->isHandling() && (it->second->getBufferSize() > 0)){
				session = it->second;
				session->setHandling(true);
				break;
			}
		}
	}

	return session;
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
		this->sock->close();
		throw UdpServerException("Send thread start failed.", errno);
	}

	if (!Thread::start()) {
		this->sendThread->stop();
		this->sendThread->join();
		throw UdpServerException("Server thread start failed.", errno);
	}

	for (int i = 0; i < this->workThreadCount; ++i) {
		SharedPtr<UdpServerImpl::WorkThread> workThread(new WorkThread(this));
		if (!workThread->start()) {
			for (list<SharedPtr<UdpServerImpl::WorkThread> >::iterator it =
					this->workThreads.begin(); it != this->workThreads.end();
					++it) {
				(*it)->stop();
				this->semWorkThread.release();
				(*it)->join();
			}
			throw UdpServerException("work thread start failed.", errno);
		}
		this->workThreads.push_back(workThread);
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

		int recvBytes = this->sock->recvFrom(buf, len, ip, port);
		if (recvBytes > 0) {
			string sId = this->WrapSessionId(ip, port);
			SharedPtr<IUdpClientSession> session = this->getSession(sId);
			if (session.get()) {
				MutexLocker lk(this->mutex);
				session->addBuffer(Buffer(buf, recvBytes));
				this->semWorkThread.release();
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
					pSession->addBuffer(Buffer(buf, recvBytes));
					this->semWorkThread.release();
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

//======================================================
//======================================================

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

void _UdpServer::setWorkThreadCount(int workThreadCount) {
	this->impl->setWorkThreadCount(workThreadCount);
}

} /* namespace network */
} /* namespace ducky */
