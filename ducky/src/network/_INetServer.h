/*
 * INetServer.h
 *
 *  Created on: 2016-11-15
 *      Author: liyawu
 */

#ifndef __INETSERVER_H_
#define __INETSERVER_H_

#include <ducky/thread/Thread.h>
#include <ducky/string/String.h>

namespace ducky {
namespace network {

using namespace std;

class _INetServer: public ducky::thread::Thread {
public:
	virtual ~_INetServer(){}

	virtual void setIp(const StdString& ip) = 0;
	virtual void setPort(unsigned int port) = 0;
	virtual bool start() = 0;
	virtual bool stop(bool joinServerThread = false) = 0;
	virtual void onStart() = 0;
	virtual void onStop() = 0;
};

}
}

#endif /* INETSERVER_H_ */
