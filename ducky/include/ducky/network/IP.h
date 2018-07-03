/*
 * IP.h
 *
 *  Created on: 2018年5月2日
 *      Author: liyawu
 */

#ifndef DUCKY_NETWORK_IP_H_
#define DUCKY_NETWORK_IP_H_

#include <ducky/Object.h>
#include <ducky/exception/Exception.h>
#include <ducky/buffer/Buffer.h>
#include <string>
#include <ostream>

namespace ducky {
namespace network {

class IP: public virtual Object {
public:
	IP();
	IP(const std::string& ip);
	virtual ~IP();

	enum VERSION_TYPE {
		IP_UNKNOWN, IP_V4, IP_V6
	};

	void parse(const std::string& ip);
	bool isValid() const;
	std::string toString() const;
	operator std::string() const;
	VERSION_TYPE getVersion() const;
	bool hasV6Scope() const;
	unsigned int getV6Scope() const;
	void clear();

	buffer::Buffer toBuffer() const;

private:
	static const unsigned int IPV6_LENGTH_NO_SCOPE = 16;
	static const unsigned int IPV6_LENGTH_WITH_SCOPE = 20;
	static const unsigned int BUFSIZE = 32;

	VERSION_TYPE version;
	unsigned char addrBuffer[BUFSIZE];

	bool parseV4(const std::string& ip);
	bool parseV6(const std::string& ip);
};

} /* namespace network */
} /* namespace ducky */

std::ostream& operator<<(std::ostream& o, const ducky::network::IP& ip);

#endif /* DUCKY_NETWORK_IP_H_ */

