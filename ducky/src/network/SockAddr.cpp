/*
 * SockAddr.cpp
 *
 *  Created on: 2018年4月28日
 *      Author: liyawu
 */

#include <ducky/network/SockAddr.h>
#include <cstring>
#include <sstream>

#if defined(WIN32) || defined(__MINGW32__)
#include <winsock2.h>
#include <ws2tcpip.h>

#else

#include <netdb.h>
#include <arpa/inet.h>

#endif

using namespace std;

namespace ducky {
namespace network {

SockAddr::SockAddr() {
	memset(&this->_addr, 0, sizeof(this->_addr));
}

SockAddr::SockAddr(const sockaddr_in& addr) :
		_addr(*(const sockaddr*) &addr) {
}

SockAddr::SockAddr(const sockaddr& addr) :
		_addr(addr) {
}

SockAddr::SockAddr(const std::string& address, unsigned int port){
	this->setFamily(AF_INET);
	this->setAddress(address);
	this->setPort(port);
}

SockAddr::~SockAddr() {
	//
}

void SockAddr::setFamily(unsigned short family){
	((sockaddr_in*)&this->_addr)->sin_family = family;
}

unsigned short SockAddr::getFamily() const{
	return ((const sockaddr_in*)&this->_addr)->sin_family;
}

void SockAddr::setPort(unsigned short port){
	((sockaddr_in*)&this->_addr)->sin_port = htons(port);
}

unsigned short SockAddr::getPort() const{
	return ntohs(((const sockaddr_in*)&this->_addr)->sin_port);
}

void SockAddr::setAddress(const std::string& address) {
	string ip = address;
	hostent* he = gethostbyname(ip.c_str());
	if (he && (he->h_length > 0)) {
		unsigned char* pAddr = (unsigned char*) he->h_addr_list[0];
		if (pAddr) {
			stringstream str;
			str << (unsigned int) pAddr[0] << "." << (unsigned int) pAddr[1] << "."
					<< (unsigned int) pAddr[2] << "." << (unsigned int) pAddr[3];
			ip = str.str().c_str();
		}
	}

	((sockaddr_in*) &this->_addr)->sin_addr.s_addr = inet_addr(ip.c_str());
}

string SockAddr::getAddress() const{
	return inet_ntoa (((sockaddr_in*) &this->_addr)->sin_addr);
}

SockAddr::operator sockaddr_in&() {
	return *((sockaddr_in*) &this->_addr);
}

SockAddr::operator const sockaddr_in&() const {
	return *((const sockaddr_in*) &this->_addr);
}

SockAddr::operator sockaddr_in*() {
	return (sockaddr_in*) &this->_addr;
}

SockAddr::operator const sockaddr_in*() const {
	return (const sockaddr_in*) &this->_addr;
}

SockAddr::operator sockaddr&() {
	return this->_addr;
}

SockAddr::operator const sockaddr&() const {
	return this->_addr;
}

SockAddr::operator sockaddr*() {
	return &this->_addr;
}

SockAddr::operator const sockaddr*() const {
	return &this->_addr;
}

} /* namespace network */
} /* namespace ducky */
