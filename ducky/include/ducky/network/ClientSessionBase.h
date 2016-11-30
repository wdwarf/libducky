/*
 * ClientSessionBase.h
 *
 *  Created on: 2016-11-15
 *      Author: ducky
 */

#ifndef CLIENTSESSIONBASE_H_
#define CLIENTSESSIONBASE_H_

#include <string>
#include <ducky/Object.h>

namespace ducky {
namespace network {

using std::string;

class ClientSessionBase: virtual public Object {
public:
	ClientSessionBase();
	virtual ~ClientSessionBase();

	virtual string getLocalIp();
	virtual unsigned int getLocalPort();
	virtual string getRemoteIp();
	virtual unsigned int getRemotePort();
	virtual int send(const char* buf, int len);
	virtual int send(const string& str);
	virtual void close();

public:
	virtual void init(int sock, int epfd);

private:
	int sock;
	int epfd;
	string localIp;
	unsigned int localPort;
	string remoteIp;
	unsigned int remotePort;
};

} /* namespace network */
} /* namespace ducky */
#endif /* CLIENTSESSIONBASE_H_ */
