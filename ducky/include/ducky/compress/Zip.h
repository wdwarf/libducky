/*
 * Zip.h
 *
 *  Created on: Nov 23, 2018
 *      Author: ducky
 */

#ifndef DUCKY_COMPRESS_ZIP_H_
#define DUCKY_COMPRESS_ZIP_H_

#include <ducky/Object.h>
#include <ducky/thread/Mutex.h>
#include <ducky/exception/Exception.h>
#include <string>

namespace ducky {
namespace compress {

EXCEPTION_DEF(ZipException);

class ZipEntry: public Object
{
public:
	explicit ZipEntry(const std::string& entry);
	const std::string& getEntry() const;

private:
	std::string _entry;
};

class Zip: public Object {
public:
	Zip(const std::string& filePath);
	virtual ~Zip();

	void close();
	const std::string& getFilePath() const;

	Zip& operator <<(const ZipEntry& entry);
	Zip& operator <<(const std::string& file);

	Zip& zipFile(const std::string& src, const std::string& entry = "",
			const std::string& newFileName = "");

private:
	std::string _filePath;
	std::string _currentEntry;
	void* _zipFile;
	ducky::thread::Mutex mutex;

	Zip& doZipRegFile(const std::string& src, const std::string& entry = "",
			const std::string& newFileName = "");
};

} /* namespace compress */
} /* namespace ducky */

#endif /* COMPRESS_ZIP_H_ */
