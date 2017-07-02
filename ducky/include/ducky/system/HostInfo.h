/*
 * HostInfo.h
 *
 *  Created on: Sep 6, 2016
 *      Author: ducky
 */

#ifndef DUCKY_SYSTEM_HOSTINFO_H_
#define DUCKY_SYSTEM_HOSTINFO_H_

#include <ducky/Object.h>
#include <string>

/**
 * 获取系统主机信息
 */

namespace ducky {
namespace system {

class HostInfo: virtual public Object {
public:
	HostInfo();
	virtual ~HostInfo();
	long getHostid() const;

	const std::string& getMachine() const;
	const std::string& getNodename() const;
	const std::string& getRelease() const;
	const std::string& getSysname() const;
	const std::string& getVersion() const;
	const std::string& getHostname() const;

private:
	class HostInfoImpl;
	HostInfoImpl* impl;
};

} /* namespace system */
} /* namespace ducky */

#endif /* WHOSTINFO_H_ */
