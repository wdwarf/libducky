/*
 * ZipEntry.cpp
 *
 *  Created on: Nov 29, 2018
 *      Author: ducky
 */

#include <ducky/compress/ZipEntry.h>

namespace ducky {
namespace compress {

ZipEntry::ZipEntry(const std::string& entry) {
	this->_entry = entry;
}

const std::string& ZipEntry::getEntry() const {
	return _entry;
}

} /* namespace compress */
} /* namespace ducky */
