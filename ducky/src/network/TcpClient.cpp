#include <ducky/network/TcpClient.h>
#include <ducky/thread/Thread.h>
#include <ducky/network/Socket.h>
#include <ducky/thread/Mutex.h>
#include <ducky/thread/Semaphore.h>
#include <ducky/buffer/Buffer.h>
#include <list>

using namespace std;
using namespace ducky::buffer;
using namespace ducky::thread;

namespace ducky {
namespace network {

class TcpClient::TcpClientImpl: public Object {
public:
	TcpClientImpl(TcpClient* client);
	virtual ~TcpClientImpl();

	/*发送数据*/
	virtual void send(const char* buf, size_t len);
	virtual void send(const string& str);

	/*设置服务器地址*/
	virtual void setServerAddress(const string& serverAddress);
	virtual const string& getServerAddress() const;
	/*设置服务器端口*/
	virtual void setServerPort(int serverPort);
	virtual int getServerPort() const;
	/*启动\停止*/
	virtual bool start();
	virtual void stop();

private:
	Socket sock;
	string serverAddress;
	int serverPort;

	/*接收线程*/
	class TcpClientReadThread;
	/*发送线程*/
	class TcpClientSendThread;
	TcpClientReadThread* readThread;
	TcpClientSendThread* sendThread;
	friend class TcpClientReadThread;
	friend class TcpClientSendThread;

	void doConnected();
	void doDisconnected();
	void doReceive(const char* buf, size_t len);
	void doSend(const char* buf, size_t len);

	TcpClient* client;
};

class TcpClient::TcpClientImpl::TcpClientReadThread: public Thread {
public:
	TcpClientReadThread(TcpClientImpl* client) {
		this->client = client;
	}

private:
	void run() {
		try {
			this->client->doConnected();
		} catch (...) {
		}

		while (!this->canStop()) {
			try {
				const int bufLen = 20480;
				char* buf = new char[bufLen];
				int size = this->client->sock.read(buf, bufLen);
				if (size > 0) {
					this->client->doReceive(buf, size);
				} else {
					delete[] buf;
					break;
				}
				delete[] buf;
			} catch (...) {
				break;
			}
		}

		try {
			this->client->doDisconnected();
		} catch (...) {
		}
	}

	TcpClientImpl* client;
};

class TcpClient::TcpClientImpl::TcpClientSendThread: public Thread {
public:
	TcpClientSendThread(TcpClientImpl* client) {
		this->client = client;
	}

	void send(const Buffer& buf) {
		MutexLocker lk(this->mutex);
		buffers.push_back(buf);
		this->sem.release();
	}

	bool stop() {
		Thread::stop();
		this->sem.release();
		return true;
	}

private:
	void run() {
		while (!this->canStop()) {
			try {
				this->sem.wait();
				if (this->canStop()) {
					break;
				}

				Buffer buf;
				{
					MutexLocker lk(this->mutex);
					if (this->buffers.empty()) {
						continue;
					}
					buf = this->buffers.front();
					this->buffers.pop_front();
				}
				int size = this->client->sock.send(buf.getData(),
						buf.getSize());
				if (size > 0) {
					this->client->doSend(buf.getData(), size);
				} else {
					break;
				}
			} catch (...) {
				break;
			}
		}
	}

	list<Buffer> buffers;
	TcpClientImpl* client;
	Mutex mutex;
	Semaphore sem;
};

TcpClient::TcpClientImpl::TcpClientImpl(TcpClient* client) :
		readThread(new TcpClientReadThread(this)), sendThread(
				new TcpClientSendThread(this)) {
	this->client = client;
}

TcpClient::TcpClientImpl::~TcpClientImpl() {
	this->stop();
	delete readThread;
	delete sendThread;
}

void TcpClient::TcpClientImpl::send(const char* buf, size_t len) {
	this->sendThread->send(Buffer(buf, len));
}

void TcpClient::TcpClientImpl::send(const string& str) {
	this->send(str.c_str(), str.length());
}

bool TcpClient::TcpClientImpl::start() {
	this->sock.close();
	try {
		this->sock.createTcp();
	} catch (ducky::network::SocketException& e) {
		return false;
	}

	catch (...) {
		return false;
	}

	if (0 == this->sock.connect(this->serverAddress, this->serverPort)) {
		readThread->start();
		sendThread->start();
		return true;
	}
	return false;
}

void TcpClient::TcpClientImpl::stop() {
	this->sock.shutdown();
	readThread->stop();
	sendThread->stop();

	readThread->join();
	sendThread->join();
}

void TcpClient::TcpClientImpl::setServerAddress(const string& serverAddress) {
	this->serverAddress = serverAddress;
}

const string& TcpClient::TcpClientImpl::getServerAddress() const {
	return this->serverAddress;
}

void TcpClient::TcpClientImpl::setServerPort(int serverPort) {
	this->serverPort = serverPort;
}

int TcpClient::TcpClientImpl::getServerPort() const {
	return this->serverPort;
}

void TcpClient::TcpClientImpl::doConnected() {
	try {
		this->client->onConnected();
	} catch (...) {
	}
}

void TcpClient::TcpClientImpl::doDisconnected() {
	this->sock.close();

	sendThread->stop();
	sendThread->join();

	try {
		this->client->onDisconnected();
	} catch (...) {
	}
}

void TcpClient::TcpClientImpl::doReceive(const char* buf, size_t len) {
	try {
		this->client->onReceive(buf, len);
	} catch (...) {
	}
}

void TcpClient::TcpClientImpl::doSend(const char* buf, size_t len) {
	try {
		this->client->onSend(buf, len);
	} catch (...) {
	}
}

TcpClient::TcpClient() : impl(new TcpClientImpl(this)){

}

TcpClient::~TcpClient(){
	delete this->impl;
}

/*发送数据*/
void TcpClient::send(const char* buf, size_t len){
	this->impl->send(buf, len);
}

void TcpClient::send(const string& str){
	this->impl->send(str);
}

/*设置服务器地址*/
void TcpClient::setServerAddress(const string& serverAddress){
	this->impl->setServerAddress(serverAddress);
}

const string& TcpClient::getServerAddress() const{
	return this->impl->getServerAddress();
}

/*设置服务器端口*/
void TcpClient::setServerPort(int serverPort){
	this->impl->setServerPort(serverPort);
}

int TcpClient::getServerPort() const{
	return this->impl->getServerPort();
}

/*启动\停止*/
bool TcpClient::start(){
	return this->impl->start();
}

void TcpClient::stop(){
	return this->impl->stop();
}


} //namespace network
} //namespace ducky
