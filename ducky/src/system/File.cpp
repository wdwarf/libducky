/*
 * File.cpp
 *
 *  Created on: 2018年3月13日
 *      Author: liyawu
 */

#include <ducky/system/File.h>
#include <ducky/algorithm/String.h>

#include <iostream>
#include <sstream>
#include <cstring>
#include <cstdio>

#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>

using namespace std;
using namespace ducky::algorithm;

namespace ducky {
namespace system {

File::File() {
	//
}

File::File(const std::string& path) {
	this->setPath(path);
}

File::File(const std::string& parent, const std::string& child) {
	this->setPath(File(parent).getPath() + "/" + File(child).getPath());
}

File::File(std::list<std::string> path) {
	this->path = path;
}

File::~File() {
	//
}

void File::setPath(const std::string& path) {
	string p = TrimCopy(path);
	if (p.empty())
		return;

	this->path.clear();

	stringstream nodeStr;
	for (string::iterator it = p.begin(); it != p.end(); ++it) {
		char c = *it;
		if ('/' == c || '\\' == c) {
			string node = nodeStr.str();
			nodeStr.clear();
			nodeStr.str("");
			Trim(node);
			if (!node.empty()) {
				this->path.push_back(node);
			} else if (this->path.empty()) {
				this->path.push_back("/");
			}
		} else {
			nodeStr << c;
		}
	}

	string node = nodeStr.str();
	nodeStr.clear();
	nodeStr.str("");
	Trim(node);
	if (!node.empty()) {
		this->path.push_back(node);
	} else if (this->path.empty()) {
		this->path.push_back("/");
	}
}

string File::getPath() const {
	string path;
	for (std::list<std::string>::const_iterator it = this->path.begin(); it != this->path.end();
			++it) {
		if (path.empty()) {
			path = *it;
		} else {
			if ("/" == path) {
				path += *it;
			} else {
				path += "/" + *it;
			}
		}
	}
	return path;
}

string File::getName() const {
	if (!this->path.empty()) {
		string name = this->path.back();
		if (!name.empty() && "/" != name && ':' != name[name.length() - 1]) {
			return name;
		}
	}
	return "";
}

File File::getParent() const{
	return this->cut();
}

bool File::isDireccory() const {
	string path = this->getPath();
	if (path.empty())
		return false;

	if (':' == path[path.length() - 1]) {
		path += "/";
	}

	struct stat buf;
	int re = stat(path.c_str(), &buf);
	if (0 != re)
		return false;

	return S_ISDIR(buf.st_mode);
}

bool File::isExists() const {
	string path = this->getPath();
	if (path.empty())
		return false;

	if (':' == path[path.length() - 1]) {
		path += "/";
	}

	return (0 == access(path.c_str(), F_OK));
}

long long File::getSize() const {
	string path = this->getPath();
	if (path.empty())
		return false;

	struct stat buf;
	int re = stat(path.c_str(), &buf);

	if (0 != re) {
		THROW_EXCEPTION(FileException, "get file stat failed", errno);
	}

	if (S_ISDIR(buf.st_mode)) {
		THROW_EXCEPTION(FileException, "is a directory", 0);
	}

	return buf.st_size;
}

void File::mkdir() const {
	if (this->isExists())
		return;
	string path = this->getPath();

#if defined(__linux__) || defined(__CYGWIN32__)
	int re = ::mkdir(path.c_str(), S_IRWXU);
#elif defined(__MINGW32__)
	int re = ::mkdir(path.c_str());
#endif

	if (0 != re) {
		THROW_EXCEPTION(FileException, "mkdir[" + path + "] failed, " + strerror(errno), errno);
	}
}

void File::mkdirs() const {
	if (this->isExists())
		return;

	string path;
	for (std::list<std::string>::const_iterator it = this->path.begin(); it != this->path.end();
			++it) {
		if (path.empty()) {
			path = *it;
		} else {
			if ("/" == path) {
				path += *it;
			} else {
				path += "/" + *it;
			}
		}

		File f(path);
		if (!f.isExists()) {
			f.mkdir();
		}
	}
}

void File::remove(bool recursive) const {
	if (!this->isExists())
		return;

	if (recursive && this->isDireccory()) {
		std::list<File> files = this->list();
		if (!files.empty()) {
			for (std::list<File>::iterator it = files.begin(); it != files.end(); ++it) {
				it->remove(true);
			}
		}
	}

	string path = this->getPath();
	int re = ::remove(path.c_str());
	if (0 != re) {
		THROW_EXCEPTION(FileException, "remove[" + path + "] failed, " + strerror(errno), errno);
	}
}

std::list<File> File::list() const {
	std::list<File> files;
	if (this->isDireccory()) {
		string path = this->getPath();

		DIR* dir = opendir(path.c_str());
		if (NULL == dir)
			return files;

		struct dirent* _dirent = NULL;
		while (NULL != (_dirent = readdir(dir))) {
			string name = _dirent->d_name;
			if ("." == name || ".." == name)
				continue;
			files.push_back(File(path + "/" + name));
		}

		closedir(dir);
	}
	return files;
}

File File::cut(int count) const {
	std::list<std::string> p = this->path;
	for (; count > 0 && !p.empty(); --count) {
		p.pop_back();
	}

	return File(p);
}

void File::rename(const std::string& path) const {
	string currentPath = this->getPath();
	int re = ::rename(currentPath.c_str(), path.c_str());
	if (0 != re) {
		THROW_EXCEPTION(FileException,
				"rename[" + currentPath + "] to [" + path + "] failed, " + strerror(errno), errno);
	}
}

void File::rename(const File& path) const {
	this->rename(path.getPath());
}

ducky::datetime::DateTime File::getModifyTime() const {
	if (!this->isExists()) {
		THROW_EXCEPTION(FileException, "file[" + this->getPath() + "] not exists", 0);
	}
	string path = this->getPath();
	struct stat buf;
	int re = stat(path.c_str(), &buf);
	if (0 != re){
		THROW_EXCEPTION(FileException, "file[" + this->getPath() + "] stat failed, " + strerror(errno), errno);
	}

	return ducky::datetime::DateTime(buf.st_mtime);
}

ducky::datetime::DateTime File::getCreateTime() const {
	if (!this->isExists()) {
		THROW_EXCEPTION(FileException, "file[" + this->getPath() + "] not exists", 0);
	}
	string path = this->getPath();
	struct stat buf;
	int re = stat(path.c_str(), &buf);
	if (0 != re){
		THROW_EXCEPTION(FileException, "file[" + this->getPath() + "] stat failed, " + strerror(errno), errno);
	}

	return ducky::datetime::DateTime(buf.st_ctime);
}

bool File::operator==(const std::string& path) const{
	return this->operator ==(File(path));
}

bool File::operator==(const File& f) const{
	return this->path == f.path;
}

} /* namespace system */
} /* namespace ducky */

std::ostream& operator<<(std::ostream& o, const ducky::system::File& file) {
	o << file.getPath();
	return o;
}
