/*
 * UserInfo.h
 *
 *  Created on: Sep 6, 2016
 *      Author: ducky
 */

#ifndef DUCKY_SYSTEM_UserInfo_H_
#define DUCKY_SYSTEM_UserInfo_H_

#include <ducky/Object.h>
#include <sys/types.h>
#include <pwd.h>
#include <string>
#include <vector>

using std::string;
using std::vector;

/**
 * 获取系统用户信息
 */

namespace ducky {
namespace system{

class UserInfo: public Object {
public:
	UserInfo();
	UserInfo(uid_t uid);
	UserInfo(passwd* pwd);
	UserInfo(const string& userName);
	virtual ~UserInfo();

	static uid_t getCurrentUID();
	static string getCurrentLogin();
	static vector<UserInfo> listAllUserInfo();

	const string& getDir() const;
	const string& getGecos() const;
	gid_t getGid() const;
	const string& getName() const;
	const string& getShell() const;
	uid_t getUid() const;

private:
	class UserInfoImpl;
	UserInfoImpl* impl;
};

} /* namespace system */
} /* namespace ducky */

#endif /* WUserInfo_H_ */
