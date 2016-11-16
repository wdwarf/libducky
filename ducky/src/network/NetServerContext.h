/*
 * NetServerContext.h
 *
 *  Created on: Nov 16, 2016
 *      Author: ducky
 */

#ifndef DUCKY_NETWORK_NETSERVERCONTEXT_H_
#define DUCKY_NETWORK_NETSERVERCONTEXT_H_

#include <ducky/buffer/Buffer.h>
#include <ducky/network/IClientSession.h>

namespace ducky {
namespace network {

enum _ContextState{
	CS_READ,
	CS_WRITE,
	CS_DISCONNECTED
};

struct _NetServerContext{
	int sockFd;
	sockaddr_in addr;
	IClientSession* session;
	_ContextState state;
	ducky::buffer::Buffer dataBuffer;
};

} /* namespace network */
} /* namespace ducky */

#endif /* DUCKY_NETWORK_NETSERVERCONTEXT_H_ */
