/*
 * INetServer.h
 *
 *  Created on: 2016-11-15
 *      Author: liyawu
 */

#ifndef INETSERVER_H_
#define INETSERVER_H_

#include <ducky/thread/Thread.h>
#include <string>

namespace ducky {
namespace network {

using namespace std;

class INetServer: public ducky::thread::Thread {
public:
	virtual ~INetServer(){}

	virtual void setIp(const string& ip) = 0;
	virtual void setPort(unsigned int port) = 0;
	virtual bool start() = 0;
	virtual bool stop() = 0;
	virtual void onStart() = 0;
	virtual void onStop() = 0;
};

}
}

#endif /* INETSERVER_H_ */
