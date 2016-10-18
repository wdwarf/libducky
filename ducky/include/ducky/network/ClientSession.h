/*
 * ClientSession.h
 *
 *  Created on: Oct 18, 2016
 *      Author: ducky
 */

#ifndef DUCKY_NETWORK_CLIENTSESSION_H_
#define DUCKY_NETWORK_CLIENTSESSION_H_

#include <ducky/Object.h>
#include <string>

using std::string;

namespace ducky {
namespace network {

class ClientSession: public Object {
public:
	ClientSession();
	virtual ~ClientSession();

	virtual void onConnected();
	virtual void onDisconnected();
	virtual void onRecv(const char* buf, unsigned int size);
	virtual void onSend(const char* buf, unsigned int size);
	string getRemoteIp() const;
	int getRemotePort() const;
	string getLocalIp() const;
	int getLocalPort() const;

private:

};

} /* namespace network */
} /* namespace ducky */

#endif /* DUCKY_NETWORK_CLIENTSESSION_H_ */
