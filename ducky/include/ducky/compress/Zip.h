/*
 * Zip.h
 *
 *  Created on: Nov 23, 2018
 *      Author: ducky
 */

#ifndef DUCKY_COMPRESS_ZIP_H_
#define DUCKY_COMPRESS_ZIP_H_

#include <ducky/Object.h>
#include <ducky/compress/CompressException.h>
#include <ducky/compress/ZipEntry.h>
#include <string>

namespace ducky {
namespace compress {

class Zip: public Object {
public:
	Zip(const std::string& filePath);
	virtual ~Zip();

	void createNew();
	void open();
	void close();
	bool isOpened() const;
	Zip& operator <<(const ZipEntry& entry);
	Zip& operator <<(const std::string& file);

	Zip& zip(const std::string& src, const std::string& entry = "",
			const std::string& newFileName = "");

	const std::string& getFilePath() const;

private:
	class ZipImpl;
	ZipImpl* impl;
};

} /* namespace compress */
} /* namespace ducky */

#endif /* DUCKY_COMPRESS_ZIP_H_ */
