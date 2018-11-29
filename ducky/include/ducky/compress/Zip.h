/*
 * Zip.h
 *
 *  Created on: Nov 23, 2018
 *      Author: ducky
 */

#ifndef DUCKY_COMPRESS_ZIP_H_
#define DUCKY_COMPRESS_ZIP_H_

#include <ducky/Object.h>
#include <ducky/exception/Exception.h>
#include <ducky/compress/ZipEntry.h>
#include <string>

namespace ducky {
namespace compress {

EXCEPTION_DEF(ZipException);

class Zip: public Object {
public:
	Zip(const std::string& filePath);
	virtual ~Zip();

	void createNew();
	void open();
	void close();
	bool isOpened() const;
	const std::string& getFilePath() const;

	Zip& operator <<(const ZipEntry& entry);
	Zip& operator <<(const std::string& file);

	Zip& zip(const std::string& src, const std::string& entry = "",
			const std::string& newFileName = "");

private:
	class ZipImpl;
	ZipImpl* impl;
};

} /* namespace compress */
} /* namespace ducky */

#endif /* DUCKY_COMPRESS_ZIP_H_ */
