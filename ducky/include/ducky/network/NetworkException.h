/*
 * NetworkException.h
 *
 *  Created on: 2016年12月19日
 *      Author: liyawu
 */

#ifndef DUCKY_NETWORK_NETWORKEXCEPTION_H_
#define DUCKY_NETWORK_NETWORKEXCEPTION_H_



#include <ducky/exception/Exception.h>

EXCEPTION_DEF(NetworkException);
EXCEPTION_DEF2(TcpServerException, NetworkException);
EXCEPTION_DEF2(UdpServerException, NetworkException);


#endif /* DUCKY_NETWORK_NETWORKEXCEPTION_H_ */
