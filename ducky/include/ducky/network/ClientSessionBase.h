/*
 * ClientSessionBase.h
 *
 *  Created on: 2016-11-15
 *      Author: ducky
 */

#ifndef CLIENTSESSIONBASE_H_
#define CLIENTSESSIONBASE_H_

#include <string>

using std::string;

namespace ducky {
namespace network {

class ClientSessionBase {
public:
	ClientSessionBase();
	virtual ~ClientSessionBase();

	virtual string getLocalIp();
	virtual unsigned int getLocalPort();
	virtual string getRemoteIp();
	virtual unsigned int getRemotePort();
	virtual int send(const char* buf, int len);
	virtual int send(const string& str);

public:
	virtual void init(int sock);

private:
	int sock;
	string localIp;
	unsigned int localPort;
	string remoteIp;
	unsigned int remotePort;
};

} /* namespace network */
} /* namespace ducky */
#endif /* CLIENTSESSIONBASE_H_ */