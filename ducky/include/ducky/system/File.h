/*
 * File.h
 *
 *  Created on: 2018年3月13日
 *      Author: liyawu
 */

#ifndef SYSTEM_FILE_H_
#define SYSTEM_FILE_H_

#include <string>
#include <list>
#include <ostream>

#include <ducky/Object.h>
#include <ducky/exception/Exception.h>
#include <ducky/datetime/DateTime.h>

namespace ducky {
namespace system {

EXCEPTION_DEF(FileException);

class File : virtual public Object {
public:
	File();
	File(const std::string& path);
	File(const std::string& parent, const std::string& child);
	File(std::list<std::string> path);
	virtual ~File();

	void setPath(const std::string& path);
	std::string getPath() const;
	std::string getName() const;
	File getParent() const;

	bool isDireccory() const;
	bool isExists() const;
	void mkdir()const;
	void mkdirs()const;
	void remove(bool recursive = false)const;
	long long getSize() const;
	void rename(const std::string& path) const;
	void rename(const File& path) const;
	std::list<File> list() const;
	File cut(int count = 1) const;
	ducky::datetime::DateTime getModifyTime() const;
	ducky::datetime::DateTime getCreateTime() const;

	bool operator==(const std::string& path) const;
	bool operator==(const File& f) const;
private:
	std::list<std::string> path;
};

} /* namespace system */
} /* namespace ducky */

std::ostream& operator<<(std::ostream& o, const ducky::system::File& file);

#endif /* SYSTEM_FILE_H_ */
