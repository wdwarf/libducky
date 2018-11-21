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
#include <algorithm>
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

	virtual void setIp(const string& ip);
	virtual string getIp() const;
	virtual void setPort(unsigned int port);
	virtual unsigned int getPort() const;
	virtual void setWorkThreadCount(int workThreadCount);
	virtual int getWorkThreadCount() const;
	virtual void start();
	virtual void stop(bool joinServerThread = false);
	virtual bool isRunning();
	virtual void onStart() {
		this->server->onStart();
	}
	virtual void onStop() {
		this->server->onStop();
	}

	void send(const string& sessionId, const char* buf, int len);

public:
	static string WrapSessionId(const string& ip, int port);

	typedef list<SharedPtr<IUdpClientSession> > SessionList;
private:
	virtual void run();
	void addSession(IUdpClientSession* pSession);
	SharedPtr<IUdpClientSession> getSession(string sessionId);
	void pushIdelSession(const SharedPtr<IUdpClientSession>& session);
	SharedPtr<IUdpClientSession> popIdelSession();
	void pushReadySession(const SharedPtr<IUdpClientSession>& session);
	SharedPtr<IUdpClientSession> popReadySession();
	void pushBusySession(const SharedPtr<IUdpClientSession>& session);
	SharedPtr<IUdpClientSession> popBusySession();
	void removeSession(const SharedPtr<IUdpClientSession>& session);

	friend class SendThread;
	class SendThread: public Thread {
	public:
		SendThread(UdpServerImpl* parent) {
			this->parent = parent;
		}

		void send(SharedPtr<IUdpClientSession> session, const char* buf,
				int len) {
			Mutex::Locker lk(this->mutex);
			if (session.get() && buf && len > 0) {
				UdpSendContext context(session, buf, len);
				this->constexts.push_back(context);
				this->sem.release();
			}
		}

		void stop() {
			Thread::stop();
			this->sem.release();
		}

	private:
		void run() {
			while (!this->isCanStop()) {
				this->sem.wait();
				if (this->isCanStop())
					break;

				UdpSendContext context;
				{
					Mutex::Locker lk(this->mutex);
					if (constexts.empty())
						continue;

					context = constexts.front();
					constexts.pop_front();
				}

				if (!context.getSession()->isSessionExpired()) {
					int re = this->parent->sock->sendTo(
							context.getData().getData(),
							context.getData().getSize(),
							context.getSession()->getRemoteIp(),
							context.getSession()->getRemotePort());
					if (re > 0) {
						context.getSession()->onSend(
								context.getData().getData(),
								context.getData().getSize());
					}
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
			while (!this->isCanStop()) {
				SharedPtr<IUdpClientSession> session =
						this->parent->popReadySession();
				if (session.get() && !session->isSessionExpired()) {
					session->updateLastCommTime();
					buffer::Buffer buffer = session->getBuffer();
					try {
						session->onReceive(buffer.getData(), buffer.getSize());
					} catch (...) {
					}
					if (session->getBufferSize() > 0) {
						this->parent->pushReadySession(session);
					} else {
						this->parent->pushIdelSession(session);
					}
				}
			}
		}

		UdpServerImpl* parent;
	};

	class TimeoutThread: public Thread {
	public:
		TimeoutThread(UdpServerImpl* parent) {
			this->parent = parent;
		}

		void addSession(SharedPtr<IUdpClientSession> session) {
			if (!session.get())
				return;
			Mutex::Locker lk(this->mutex);
			this->sessions.push_back(session);
		}

		void removeSession(SharedPtr<IUdpClientSession> session) {
			if (!session.get())
				return;

			Mutex::Locker lk(this->mutex);
			session->setSessionExpired(true);
			this->sessions.remove(session);
			this->parent->removeSession(session);
		}
	private:
		void run() {
			while (!this->isCanStop()) {
				UdpServerImpl::SessionList expiredSessions;
				{
					Mutex::Locker lk(this->mutex);
					for (UdpServerImpl::SessionList::iterator it =
							this->sessions.begin(); it != this->sessions.end();
							++it) {
						SharedPtr<IUdpClientSession> session = *it;
						if (session->isSessionExpired()
								|| ((-1 != session->getSessionTimeout())
										&& ((time(0)
												- session->getLastCommTime())
												>= session->getSessionTimeout()))) {
							expiredSessions.push_back(session);
						}
					}
				}
				for (UdpServerImpl::SessionList::iterator it =
						expiredSessions.begin(); it != expiredSessions.end();
						++it) {
					this->removeSession(*it);
				}
				Thread::Sleep(1000);
			}
		}

		Mutex mutex;
		UdpServerImpl::SessionList sessions;
		UdpServerImpl* parent;
	};

	ScopedPtr<SendThread> sendThread;
	list<SharedPtr<WorkThread> > workThreads;
	ScopedPtr<TimeoutThread> timeoutThread;

	int workThreadCount;
	string ip;
	unsigned int listenPort;
	SharedPtr<Socket> sock;
	SessionList idelSessions;
	SessionList readySessions;
	SessionList busySessions;
	Semaphore semWorkThread;
	Semaphore semReadySession;
	Mutex mutex;
	_UdpServer* server;
};

//======================================================
//======================================================

IUdpClientSession::IUdpClientSession() :
		remotePort(0), localPort(0), lastCommTime(time(0)), sessionTimeout(-1), sessionExpired(
				false), server(
		NULL) {
	//
}

IUdpClientSession::~IUdpClientSession() {
	//
}

void IUdpClientSession::setSessionTimeout(int sec) {
	this->sessionTimeout = sec;
}

int IUdpClientSession::getSessionTimeout() const {
	return this->sessionTimeout;
}

void IUdpClientSession::setSessionExpired(bool sessionExpired) {
	this->sessionExpired = sessionExpired;
}

bool IUdpClientSession::isSessionExpired() const {
	return this->sessionExpired;
}

time_t IUdpClientSession::getLastCommTime() const {
	return this->lastCommTime;
}

void IUdpClientSession::updateLastCommTime() {
	this->lastCommTime = time(0);
}

void IUdpClientSession::init(const std::string& remoteIp, int remotePort,
		const std::string& localIp, int localPort, UdpServerImpl* svr) {
	this->remoteIp = remoteIp;
	this->remotePort = remotePort;
	this->localIp = localIp;
	this->localPort = localPort;
	this->server = svr;

	stringstream strId;
	strId << this->remoteIp << ":" << this->remotePort;
	this->clientId = strId.str();
}

const string& IUdpClientSession::getClientId() const {
	return this->clientId;
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
	this->server->send(this->getClientId(), buf, len);
}

void IUdpClientSession::addBuffer(const buffer::Buffer& buf) {
	Mutex::Locker lk(this->mutex);
	this->dataBuffers.push_back(buf);
}

size_t IUdpClientSession::getBufferSize() {
	Mutex::Locker lk(this->mutex);
	return this->dataBuffers.size();
}

Buffer IUdpClientSession::getBuffer() {
	Mutex::Locker lk(this->mutex);
	Buffer buffer;
	if (!this->dataBuffers.empty()) {
		buffer = this->dataBuffers.front();
		this->dataBuffers.pop_front();
	}

	return buffer;
}

//======================================================
//======================================================

UdpServerImpl::UdpServerImpl(_UdpServer* svr) :
		sendThread(new SendThread(this)), timeoutThread(
				new TimeoutThread(this)), workThreadCount(10), listenPort(0), sock(
				new Socket), server(svr) {

}

UdpServerImpl::~UdpServerImpl() {

}

void UdpServerImpl::setIp(const string& ip) {
	this->ip = ip;
}

string UdpServerImpl::getIp() const {
	return this->ip;
}

void UdpServerImpl::setPort(unsigned int port) {
	this->listenPort = port;
}

unsigned int UdpServerImpl::getPort() const {
	return this->listenPort;
}

void UdpServerImpl::setWorkThreadCount(int workThreadCount) {
	this->workThreadCount = workThreadCount;
}

int UdpServerImpl::getWorkThreadCount() const {
	return this->workThreadCount;
}

bool UdpServerImpl::isRunning() {
	return (0 != this->sock->getHandle());
}

string UdpServerImpl::WrapSessionId(const string& ip, int port) {
	stringstream sId;
	sId << ip << ":" << port;
	return sId.str();
}

void UdpServerImpl::removeSession(const SharedPtr<IUdpClientSession>& session) {
	Mutex::Locker lk(this->mutex);
	this->idelSessions.remove(session);
	this->readySessions.remove(session);
	this->busySessions.remove(session);

	session->onDisconnected();
}

void UdpServerImpl::pushIdelSession(
		const SharedPtr<IUdpClientSession>& session) {
	Mutex::Locker lk(this->mutex);

	if (session->isSessionExpired()) {
		return;
	}

	this->idelSessions.push_back(session);
	this->readySessions.remove(session);
	this->busySessions.remove(session);
}

SharedPtr<IUdpClientSession> UdpServerImpl::popIdelSession() {
	SharedPtr<IUdpClientSession> session;
	Mutex::Locker lk(this->mutex);
	if (!this->idelSessions.empty()) {
		session = this->idelSessions.front();
		this->readySessions.push_back(session);
		this->idelSessions.remove(session);
	}
	return session;
}

void UdpServerImpl::pushReadySession(
		const SharedPtr<IUdpClientSession>& session) {
	Mutex::Locker lk(this->mutex);

	if (session->isSessionExpired()) {
		return;
	}

	SessionList::iterator it = find(this->readySessions.begin(),
			this->readySessions.end(), session);
	if (it != this->readySessions.end()) {
		return;
	}

	this->readySessions.push_back(session);
	this->idelSessions.remove(session);
	this->busySessions.remove(session);

	this->semReadySession.release();
}

SharedPtr<IUdpClientSession> UdpServerImpl::popReadySession() {
	this->semReadySession.wait();
	SharedPtr<IUdpClientSession> session;
	Mutex::Locker lk(this->mutex);
	if (!this->readySessions.empty()) {
		session = this->readySessions.front();
		this->busySessions.push_back(session);
		this->readySessions.remove(session);
	}
	return session;
}

void UdpServerImpl::pushBusySession(
		const SharedPtr<IUdpClientSession>& session) {
	Mutex::Locker lk(this->mutex);

	if (session->isSessionExpired()) {
		return;
	}

	this->busySessions.push_back(session);
	this->idelSessions.remove(session);
	this->readySessions.remove(session);
}

SharedPtr<IUdpClientSession> UdpServerImpl::popBusySession() {
	SharedPtr<IUdpClientSession> session;
	Mutex::Locker lk(this->mutex);
	if (!this->busySessions.empty()) {
		session = this->busySessions.front();
		this->busySessions.remove(session);
		this->idelSessions.push_back(session);
	}
	return session;
}

void UdpServerImpl::send(const string& sessionId, const char* buf, int len) {
	SharedPtr<IUdpClientSession> session = getSession(sessionId);
	if (session && !session->isSessionExpired()) {
		this->sendThread->send(session, buf, len);
	}
}

void UdpServerImpl::addSession(IUdpClientSession* pSession) {
	SharedPtr<IUdpClientSession> session(pSession);
	this->pushReadySession(session);
	this->timeoutThread->addSession(session);
}

SharedPtr<IUdpClientSession> UdpServerImpl::getSession(string sessionId) {
	Mutex::Locker lk(this->mutex);
	for (SessionList::iterator it = this->idelSessions.begin();
			it != this->idelSessions.end(); ++it) {
		if ((*it)->getClientId() == sessionId) {
			return *it;
		}
	}

	for (SessionList::iterator it = this->readySessions.begin();
			it != this->readySessions.end(); ++it) {
		if ((*it)->getClientId() == sessionId) {
			return *it;
		}
	}

	for (SessionList::iterator it = this->busySessions.begin();
			it != this->busySessions.end(); ++it) {
		if ((*it)->getClientId() == sessionId) {
			return *it;
		}
	}

	return SharedPtr<IUdpClientSession>();
}

void UdpServerImpl::start() {
	try {
		this->sock->close();
		this->sock->createUdp();
		this->sock->bind(this->ip, this->listenPort);
	} catch (exception::Exception& e) {
		throw UdpServerException(e.what(), errno);
	}

	try {
		this->sendThread->start();
	} catch (...) {
		this->sock->close();
		throw UdpServerException("Send thread start failed.", errno);
	}

	try {
		this->timeoutThread->start();
	} catch (...) {
		this->sock->close();
		throw UdpServerException("Timeout thread start failed.", errno);
	}

	try {
		Thread::start();
	} catch (...) {
		this->sendThread->stop();
		this->sendThread->join();
		throw UdpServerException("Server thread start failed.", errno);
	}

	for (int i = 0; i < this->workThreadCount; ++i) {
		SharedPtr<UdpServerImpl::WorkThread> workThread(new WorkThread(this));
		try {
			workThread->start();
		} catch (...) {
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
}

void UdpServerImpl::stop(bool joinServerThread) {
	this->sendThread->stop();
	this->sendThread->join();

	for (list<SharedPtr<WorkThread> >::iterator it = this->workThreads.begin();
			it != this->workThreads.end(); ++it) {
		(*it)->stop();
	}
	for (list<SharedPtr<WorkThread> >::iterator it = this->workThreads.begin();
			it != this->workThreads.end(); ++it) {
		this->semWorkThread.release();
	}
	for (list<SharedPtr<WorkThread> >::iterator it = this->workThreads.begin();
			it != this->workThreads.end(); ++it) {
		(*it)->join();
	}

	Thread::stop();
	this->sock->shutdown();
}

void UdpServerImpl::run() {
	this->onStart();
	while (!this->isCanStop()) {
		char buf[2048] = { 0 };
		int len = 2048;
		string ip;
		int port = 0;

		int recvBytes = this->sock->recvFrom(buf, len, ip, port);
		if (recvBytes > 0) {
			string sId = this->WrapSessionId(ip, port);
			SharedPtr<IUdpClientSession> session = this->getSession(sId);
			if (session.get()) {
				if (!session->isSessionExpired()) {
					this->mutex.lock();
					session->addBuffer(Buffer(buf, recvBytes));
					SessionList::iterator it = find(this->idelSessions.begin(),
							this->idelSessions.end(), session);
					if (it != this->idelSessions.end()) {
						this->mutex.unlock();
						this->pushReadySession(session);
					} else {
						this->mutex.unlock();
					}
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
					pSession->addBuffer(Buffer(buf, recvBytes));
					this->addSession(pSession);
				}
			}
		} else {
			break;
		}
	}
	this->sock->close();

	for (SessionList::iterator it = this->idelSessions.begin();
			it != this->idelSessions.end(); ++it) {
		(*it)->onDisconnected();
	}

	for (SessionList::iterator it = this->readySessions.begin();
			it != this->readySessions.end(); ++it) {
		(*it)->onDisconnected();
	}

	for (SessionList::iterator it = this->busySessions.begin();
			it != this->busySessions.end(); ++it) {
		(*it)->onDisconnected();
	}

	this->idelSessions.clear();
	this->readySessions.clear();
	this->busySessions.clear();

	this->onStop();
}

//======================================================
//======================================================

_UdpServer::_UdpServer() :
		impl(new UdpServerImpl(this)) {
	

}

_UdpServer::~_UdpServer() {
	
	delete this->impl;
}

void _UdpServer::setIp(const string& ip) {
	this->impl->setIp(ip);
}

string _UdpServer::getIp() const {
	return this->impl->getIp();
}

void _UdpServer::setPort(unsigned int port) {
	this->impl->setPort(port);
}

unsigned int _UdpServer::getPort() const {
	return this->impl->getPort();
}

void _UdpServer::start() {
	this->impl->start();
}

void _UdpServer::stop(bool joinServerThread) {
	this->impl->stop(joinServerThread);
}

void _UdpServer::join() {
	this->impl->join();
}

bool _UdpServer::isRunning() {
	return this->impl->isRunning();
}

void _UdpServer::setWorkThreadCount(int workThreadCount) {
	this->impl->setWorkThreadCount(workThreadCount);
}

int _UdpServer::getWorkThreadCount() const {
	return this->impl->getWorkThreadCount();
}

} /* namespace network */
} /* namespace ducky */
