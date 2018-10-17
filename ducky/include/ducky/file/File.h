/*
 * File.h
 *
 *  Created on: 2018-03-13
 *      Author: liyawu
 */

#ifndef DUCKY_FILE_FILE_H_
#define DUCKY_FILE_FILE_H_

#include <string>
#include <list>
#include <ostream>

#include <ducky/Object.h>
#include <ducky/exception/Exception.h>
#include <ducky/datetime/DateTime.h>

namespace ducky {
namespace file {

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

	bool isDirectory() const;
	bool isRegularFile() const;
	bool isExists() const;
	bool isReadable() const;
	bool isWritable() const;
	bool isExecutable() const;
	void mkdir()const;
	void mkdirs()const;
	void remove(bool recursive = false)const;
	long long getSize() const;
	void rename(const std::string& path) const;
	void copyTo(const std::string& path, bool forceReplace = false) const;
	void moveTo(const std::string& path, bool forceReplace = false) const;

	std::list<File> list() const;
	File cut(int count = 1) const;
	ducky::datetime::DateTime getModifyTime() const;
	ducky::datetime::DateTime getCreateTime() const;

	bool operator==(const std::string& path) const;
	bool operator==(const File& f) const;

	operator std::string() const;
	std::string getSeparater() const;

private:
	std::list<std::string> path;
};

} /* namespace file */
} /* namespace ducky */

std::ostream& operator<<(std::ostream& o, const ducky::file::File& file);

#endif /* SYSTEM_FILE_H_ */
