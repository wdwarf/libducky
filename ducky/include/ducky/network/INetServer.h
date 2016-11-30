/*
 * INetServer.h
 *
 *  Created on: 2016-11-15
 *      Author: liyawu
 */

#ifndef INETSERVER_H_
#define INETSERVER_H_

#include <string>
#include <ducky/Object.h>
#include <ducky/exception/Exception.h>

namespace ducky {
namespace network {

using namespace std;
using namespace ducky::exception;

EXCEPTION_DEF(NetServerException);

class INetServer: virtual public Object {
public:
	virtual ~INetServer(){}

	virtual void setIp(const string& ip) throw(NetServerException) = 0;
	virtual void setPort(unsigned int port) throw(NetServerException) = 0;
	virtual void setWorkThreadCount(int workThreadCount) throw(NetServerException) = 0;
	virtual bool start() throw(NetServerException) = 0;
	virtual bool stop(bool joinServerThread = false) = 0;
	virtual void join() = 0;
	virtual bool isRunning() = 0;
	virtual void onStart() = 0;
	virtual void onStop() = 0;
};

}
}

#endif /* INETSERVER_H_ */
