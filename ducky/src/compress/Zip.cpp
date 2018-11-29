/*
 * Zip.cpp
 *
 *  Created on: Nov 23, 2018
 *      Author: ducky
 */

#include <ducky/compress/Zip.h>
#include <ducky/file/File.h>
#include <fstream>
#include <iostream>
#include <zlib.h>
#include "zip.h"

using namespace std;
using namespace ducky::file;
using namespace ducky::thread;

namespace ducky {
namespace compress {

ZipEntry::ZipEntry(const std::string& entry) {
	this->_entry = entry;
}

const std::string& ZipEntry::getEntry() const {
	return _entry;
}

Zip::Zip(const std::string& filePath) :
		_filePath(filePath), _zipFile(NULL), mutex(true) {
	this->_zipFile = zipOpen64(this->_filePath.c_str(),
			File(this->_filePath).isExists() ?
			APPEND_STATUS_ADDINZIP :
												APPEND_STATUS_CREATE);
	if (NULL == this->_zipFile) {
		THROW_EXCEPTION(ZipException,
				"zip file[" + this->_filePath + "] open failed.", 0);
	}
}

Zip::~Zip() {
	this->close();
}

void Zip::close() {
	Mutex::Locker lk(this->mutex);
	if (this->_zipFile) {
		zipClose(this->_zipFile, NULL);
		this->_zipFile = NULL;
	}
}

const std::string& Zip::getFilePath() const {
	return _filePath;
}

Zip& Zip::operator <<(const std::string& file) {
	this->zipFile(file, this->_currentEntry);

	Mutex::Locker lk(this->mutex);
	this->_currentEntry = "";
	return *this;
}

Zip& Zip::operator <<(const ZipEntry& entry) {
	Mutex::Locker lk(this->mutex);
	this->_currentEntry = entry.getEntry();
	return *this;
}

Zip& Zip::zipFile(const std::string& src, const std::string& entry,
		const std::string& newFileName) {
	Mutex::Locker lk(this->mutex);

	File srcFile(src);

	if (srcFile.isDirectory()) {
		std::list<File> files = srcFile.list();

		for (std::list<File>::iterator it = files.begin(); it != files.end();
				++it) {
			if (it->isDirectory()) {
				string newEntry = it->getName();
				this->zipFile(*it, File(File(entry, newFileName), newEntry));
				continue;
			}

			doZipRegFile(*it, File(entry, newFileName));
		}

		return *this;
	}

	return doZipRegFile(src, entry, newFileName);
}

Zip& Zip::doZipRegFile(const std::string& src, const std::string& entry,
		const std::string& newFileName) {
	File srcFile(src);
	string zipFileName = (newFileName.empty() ? srcFile.getName() : newFileName);
	File zipFile(entry, zipFileName);

	zipOpenNewFileInZip(this->_zipFile, zipFile.getPath().c_str(), NULL, NULL,
			0,
			NULL, 0,
			NULL, Z_DEFLATED, Z_DEFAULT_COMPRESSION);

	fstream f;
	f.open(srcFile.getPath().c_str(), ios::in | ios::binary);
	const int bufSize = 2048;
	char buf[bufSize];
	while (!f.eof()) {
		f.read(buf, bufSize);
		size_t readBytes = f.gcount();
		if (readBytes > 0) {
			zipWriteInFileInZip(this->_zipFile, buf, readBytes);
		}
	}

	zipCloseFileInZip(this->_zipFile);

	return *this;
}

} /* namespace compress */
} /* namespace ducky */

