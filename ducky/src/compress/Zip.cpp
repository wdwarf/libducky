/*
 * Zip::ZipImpl.cpp
 *
 *  Created on: Nov 23, 2018
 *      Author: ducky
 */

#include <ducky/compress/Zip.h>
#include <ducky/file/File.h>
#include <ducky/thread/Mutex.h>
#include <fstream>
#include <iostream>
#include <zlib.h>
#include "minizip/zip.h"

using namespace std;
using namespace ducky::file;
using namespace ducky::thread;

namespace ducky {
namespace compress {

//////////////////////////////////////////////////////////
// class Zip::ZipImpl
//////////////////////////////////////////////////////////

class Zip::ZipImpl: public Object {
public:
	ZipImpl(const std::string& filePath);
	virtual ~ZipImpl();

	void createNew();
	void open();
	void close();
	bool isOpened() const;
	const std::string& getFilePath() const;

	void setCurrentEntry(const ZipEntry& entry);
	void zipFileToCurrEntry(const std::string& file);

	void zip(const std::string& src, const std::string& entry = "",
			const std::string& newFileName = "");

private:
	std::string _filePath;
	std::string _currentEntry;
	void* _zipFile;
	mutable ducky::thread::Mutex mutex;

	void doZipRegFile(const std::string& src, const std::string& entry = "",
			const std::string& newFileName = "");
};

Zip::ZipImpl::ZipImpl(const std::string& filePath) :
		_filePath(filePath), _zipFile(NULL), mutex(true) {
}

Zip::ZipImpl::~ZipImpl() {
	this->close();
}

void Zip::ZipImpl::createNew() {
	this->close();
	this->_zipFile = zipOpen(this->_filePath.c_str(), APPEND_STATUS_CREATE);
	if (NULL == this->_zipFile) {
		THROW_EXCEPTION(ZipException,
				"zip file[" + this->_filePath + "] create failed.", 0);
	}
}

void Zip::ZipImpl::open() {
	if (this->isOpened())
		return;
	this->_zipFile = zipOpen(this->_filePath.c_str(), APPEND_STATUS_ADDINZIP);
	if (NULL == this->_zipFile) {
		THROW_EXCEPTION(ZipException,
				"zip file[" + this->_filePath + "] open failed.", 0);
	}
}

void Zip::ZipImpl::close() {
	Mutex::Locker lk(this->mutex);
	if (this->_zipFile) {
		zipClose(this->_zipFile, NULL);
		this->_zipFile = NULL;
	}
}

bool Zip::ZipImpl::isOpened() const {
	Mutex::Locker lk(this->mutex);
	return (NULL != this->_zipFile);
}

const std::string& Zip::ZipImpl::getFilePath() const {
	return _filePath;
}

void Zip::ZipImpl::zipFileToCurrEntry(const std::string& file) {
	this->zip(file, this->_currentEntry);

	Mutex::Locker lk(this->mutex);
	this->_currentEntry = "";
}

void Zip::ZipImpl::setCurrentEntry(const ZipEntry& entry) {
	Mutex::Locker lk(this->mutex);
	this->_currentEntry = entry.getEntry();
}

void Zip::ZipImpl::zip(const std::string& src, const std::string& entry,
		const std::string& newFileName) {
	Mutex::Locker lk(this->mutex);

	File srcFile(src);

	if(!srcFile.isExists()){
		THROW_EXCEPTION(ZipException, "file[" + src + "] not exists.", 0);
	}

	if (srcFile.isDirectory()) {
		std::list<File> files = srcFile.list();

		for (std::list<File>::iterator it = files.begin(); it != files.end();
				++it) {
			if (it->isDirectory()) {
				string newEntry = it->getName();
				this->zip(*it, File(File(entry, newFileName), newEntry));
				continue;
			}

			doZipRegFile(*it, File(entry, newFileName));
		}
		return;
	}

	this->doZipRegFile(src, entry, newFileName);
}

void Zip::ZipImpl::doZipRegFile(const std::string& src,
		const std::string& entry, const std::string& newFileName) {
	File srcFile(src);
	string zipFileName = (newFileName.empty() ? srcFile.getName() : newFileName);
	File zipFile(entry, zipFileName);

	if (0 != zipOpenNewFileInZip(this->_zipFile, zipFile.getPath().c_str(),
	NULL, NULL, 0,
	NULL, 0,
	NULL, Z_DEFLATED, Z_DEFAULT_COMPRESSION)) {
		THROW_EXCEPTION(ZipException, "file[" + src + "] zip failed.", 0);
	}

	fstream f;
	f.open(srcFile.getPath().c_str(), ios::in | ios::binary);
	const int bufSize = 20480;
	char buf[bufSize];
	while (!f.eof()) {
		f.read(buf, bufSize);
		size_t readBytes = f.gcount();

		if (readBytes <= 0) {
			break;
		}

		if (0 != zipWriteInFileInZip(this->_zipFile, buf, readBytes)) {
			THROW_EXCEPTION(ZipException, "file[" + src + "] zip failed.", 0);
		}
	}

	if (0 != zipCloseFileInZip(this->_zipFile)) {
		THROW_EXCEPTION(ZipException, "file[" + src + "] zip failed.", 0);
	}
}

//////////////////////////////////////////////////////////
// class Zip
//////////////////////////////////////////////////////////

Zip::Zip(const std::string& filePath) :
		impl(new Zip::ZipImpl(filePath)) {

}

Zip::~Zip() {
	delete this->impl;
}

void Zip::createNew() {
	this->impl->createNew();
}

void Zip::open() {
	this->impl->open();
}

void Zip::close() {
	this->impl->close();
}

bool Zip::isOpened() const {
	return this->impl->isOpened();
}

const std::string& Zip::getFilePath() const {
	return this->impl->getFilePath();
}

Zip& Zip::operator <<(const ZipEntry& entry) {
	this->impl->setCurrentEntry(entry);
	return *this;
}

Zip& Zip::operator <<(const std::string& file) {
	this->impl->zipFileToCurrEntry(file);
	return *this;
}

Zip& Zip::zip(const std::string& src, const std::string& entry,
		const std::string& newFileName) {
	this->impl->zip(src, entry, newFileName);
	return *this;
}

} /* namespace compress */
} /* namespace ducky */

