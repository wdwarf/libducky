/*
 * UserInfo.cpp
 *
 *  Created on: Sep 6, 2016
 *      Author: ducky
 */

#include <ducky/system/UserInfo.h>
#include <unistd.h>
#include <pwd.h>

namespace ducky {
namespace system {

class UserInfo::UserInfoImpl {
public:
	UserInfoImpl();
	UserInfoImpl(uid_t uid);
	UserInfoImpl(passwd* pwd);
	UserInfoImpl(const string& userName);
	virtual ~UserInfoImpl();

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
	string name;
	uid_t uid;
	gid_t gid;
	string dir;
	string gecos;
	string shell;

	void loadUserInfo(uid_t uid);
	void loadUserInfo(const string& userName);
	void clear();
	void setValues(passwd* pwd);
};

UserInfo::UserInfoImpl::UserInfoImpl() {
	this->loadUserInfo(UserInfo::UserInfoImpl::getCurrentUID());
}

UserInfo::UserInfoImpl::UserInfoImpl(uid_t uid) :
		uid(0), gid(0) {
	this->loadUserInfo(uid);
}

UserInfo::UserInfoImpl::UserInfoImpl(passwd* pwd) :
		uid(0), gid(0) {
	this->clear();
	this->setValues(pwd);
}

UserInfo::UserInfoImpl::UserInfoImpl(const string& userName) :
		uid(0), gid(0) {
	this->loadUserInfo(userName);
}

UserInfo::UserInfoImpl::~UserInfoImpl() {
	// TODO Auto-generated destructor stub
}

void UserInfo::UserInfoImpl::loadUserInfo(uid_t uid) {
	this->clear();
	this->setValues(getpwuid(uid));
}

void UserInfo::UserInfoImpl::loadUserInfo(const string& userName) {
	this->clear();
	this->setValues(getpwnam(userName.c_str()));
}

uid_t UserInfo::UserInfoImpl::getCurrentUID() {
	return getuid();
}

string UserInfo::UserInfoImpl::getCurrentLogin() {
	char* user = getlogin();
	if (user)
		return user;
	else
		return "";
}

vector<UserInfo> UserInfo::UserInfoImpl::listAllUserInfo() {
	vector<UserInfo> re;
	passwd* pwd = NULL;
	while ((pwd = getpwent())) {
		re.push_back(UserInfo(pwd));
	}
	return re;
}

const string& UserInfo::UserInfoImpl::getDir() const {
	return dir;
}

const string& UserInfo::UserInfoImpl::getGecos() const {
	return gecos;
}

gid_t UserInfo::UserInfoImpl::getGid() const {
	return gid;
}

const string& UserInfo::UserInfoImpl::getName() const {
	return name;
}

const string& UserInfo::UserInfoImpl::getShell() const {
	return shell;
}

uid_t UserInfo::UserInfoImpl::getUid() const {
	return uid;
}

void UserInfo::UserInfoImpl::setValues(passwd* pwd) {
	if (pwd) {
		this->name = pwd->pw_name;
		this->uid = pwd->pw_uid;
		this->gid = pwd->pw_gid;
		this->dir = pwd->pw_dir;
		this->gecos = pwd->pw_gecos;
		this->shell = pwd->pw_shell;
	}
}

void UserInfo::UserInfoImpl::clear() {
	this->uid = 0;
	this->gid = 0;
	this->name = "";
	this->dir = "";
	this->gecos = "";
	this->shell = "";
}

UserInfo::UserInfo() :
		impl(new UserInfoImpl) {
}

UserInfo::UserInfo(uid_t uid) :
		impl(new UserInfoImpl(uid)) {
	//
}

UserInfo::UserInfo(passwd* pwd) :
		impl(new UserInfoImpl(pwd)) {
	//
}

UserInfo::UserInfo(const string& userName) :
		impl(new UserInfoImpl(userName)) {
	//
}

UserInfo::~UserInfo() {
	// TODO Auto-generated destructor stub
}

uid_t UserInfo::getCurrentUID() {
	return UserInfoImpl::getCurrentUID();
}

string UserInfo::getCurrentLogin() {
	return UserInfoImpl::getCurrentLogin();
}

vector<UserInfo> UserInfo::listAllUserInfo() {
	return UserInfoImpl::listAllUserInfo();
}

const string& UserInfo::getDir() const {
	return this->impl->getDir();
}

const string& UserInfo::getGecos() const {
	return this->impl->getGecos();
}

gid_t UserInfo::getGid() const {
	return this->impl->getGid();
}

const string& UserInfo::getName() const {
	return this->impl->getName();
}

const string& UserInfo::getShell() const {
	return this->impl->getShell();
}

uid_t UserInfo::getUid() const {
	return this->impl->getUid();
}

} /* namespace system */
} /* namespace ducky */
