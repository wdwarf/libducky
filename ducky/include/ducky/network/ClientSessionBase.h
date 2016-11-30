/*
 * ClientSessionBase.h
 *
 *  Created on: 2016-11-15
 *      Author: ducky
 */

#ifndef CLIENTSESSIONBASE_H_
#define CLIENTSESSIONBASE_H_

#include <ducky/Object.h>
#include <ducky/string/String.h>

namespace ducky {
namespace network {

class ClientSessionBase: virtual public Object {
public:
	ClientSessionBase();
	virtual ~ClientSessionBase();

	virtual StdString getLocalIp();
	virtual unsigned int getLocalPort();
	virtual StdString getRemoteIp();
	virtual unsigned int getRemotePort();
	virtual int send(const char* buf, int len);
	virtual int send(const StdString& str);
	virtual void close();

public:
	virtual void init(int sock, int epfd);

private:
	int sock;
	int epfd;
	StdString localIp;
	unsigned int localPort;
	StdString remoteIp;
	unsigned int remotePort;
};

} /* namespace network */
} /* namespace ducky */
#endif /* CLIENTSESSIONBASE_H_ */
