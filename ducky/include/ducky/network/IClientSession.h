/*
 * IClientSession.h
 *
 *  Created on: 2016-11-15
 *      Author: ducky
 */

#ifndef ICLIENTSESSION_H_
#define ICLIENTSESSION_H_

#include <ducky/network/ClientSessionBase.h>
#include <ducky/buffer/Buffer.h>

namespace ducky {
namespace network {

class IClientSession : public ClientSessionBase {
public:
	virtual ~IClientSession(){}

	virtual void onConnected() = 0;
	virtual void onDisconnected() = 0;
	virtual void onRecive(ducky::buffer::Buffer& buffer) = 0;
	virtual void onSend(ducky::buffer::Buffer& buffer) = 0;
};

}
}

#endif /* ICLIENTSESSION_H_ */
