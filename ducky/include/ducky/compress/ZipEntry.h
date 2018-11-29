/*
 * ZipEntry.h
 *
 *  Created on: Nov 29, 2018
 *      Author: ducky
 */

#ifndef DUCKY_COMPRESS_ZIPENTRY_H_
#define DUCKY_COMPRESS_ZIPENTRY_H_

#include <ducky/Object.h>
#include <string>

namespace ducky {
namespace compress {

class ZipEntry: public Object {
public:
	explicit ZipEntry(const std::string& entry);
	const std::string& getEntry() const;

private:
	std::string _entry;
};

} /* namespace compress */
} /* namespace ducky */

#endif /* DUCKY_COMPRESS_ZIPENTRY_H_ */
