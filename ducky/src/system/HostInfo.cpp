/*
 * HostInfo.cpp
 *
 *  Created on: Sep 6, 2016
 *      Author: ducky
 */

#include <ducky/system/HostInfo.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <errno.h>
#include <ducky/exception/Exception.h>

namespace ducky {
namespace system {

using ducky::exception::Exception;

class HostInfo::HostInfoImpl{
public:
	HostInfoImpl();
	virtual ~HostInfoImpl();
	long getHostid() const;

	const std::string& getMachine() const;
	const std::string& getNodename() const;
	const std::string& getRelease() const;
	const std::string& getSysname() const;
	const std::string& getVersion() const;
	const std::string& getHostname() const;

private:
	std::string hostname;
	std::string sysname;
	std::string nodename;
	std::string release;
	std::string version;
	std::string machine;
	long hostid;
};

HostInfo::HostInfoImpl::HostInfoImpl() {
	// TODO Auto-generated constructor stub
	char bufHostName[256] = { 0 };
	struct utsname uts = { 0 };

	this->hostid = gethostid();

	if (0 != gethostname(bufHostName, 255) || uname(&uts) < 0) {
		throw Exception("", errno);
	} else {
		this->hostname = bufHostName;
		this->sysname = uts.sysname;
		this->nodename = uts.nodename;
		this->release = uts.release;
		this->version = uts.version;
		this->machine = uts.machine;
	}
}

HostInfo::HostInfoImpl::~HostInfoImpl() {
	// TODO Auto-generated destructor stub
}

long HostInfo::HostInfoImpl::getHostid() const {
	return hostid;
}

const std::string& HostInfo::HostInfoImpl::getMachine() const {
	return machine;
}

const std::string& HostInfo::HostInfoImpl::getNodename() const {
	return nodename;
}

const std::string& HostInfo::HostInfoImpl::getRelease() const {
	return release;
}

const std::string& HostInfo::HostInfoImpl::getSysname() const {
	return sysname;
}

const std::string& HostInfo::HostInfoImpl::getVersion() const {
	return version;
}

const std::string& HostInfo::HostInfoImpl::getHostname() const {
	return hostname;
}



HostInfo::HostInfo() : impl(new HostInfoImpl){
	//
}

HostInfo::~HostInfo() {
	// TODO Auto-generated destructor stub
}

long HostInfo::getHostid() const {
	return this->impl->getHostid();
}

const std::string& HostInfo::getMachine() const {
	return this->impl->getMachine();
}

const std::string& HostInfo::getNodename() const {
	return this->impl->getNodename();
}

const std::string& HostInfo::getRelease() const {
	return this->impl->getRelease();
}

const std::string& HostInfo::getSysname() const {
	return this->impl->getSysname();
}

const std::string& HostInfo::getVersion() const {
	return this->impl->getVersion();
}

const std::string& HostInfo::getHostname() const {
	return this->impl->getHostname();
}

} /* namespace system */
} /* namespace ducky */
