/*
 * CompressException.h
 *
 *  Created on: Nov 30, 2018
 *      Author: ducky
 */

#ifndef DUCKY_COMPRESS_COMPRESSEXCEPTION_H_
#define DUCKY_COMPRESS_COMPRESSEXCEPTION_H_


#include <ducky/exception/Exception.h>

namespace ducky {
namespace compress {

EXCEPTION_DEF(CompressException);
EXCEPTION_DEF2(ZipException, CompressException);
EXCEPTION_DEF2(UnzipException, CompressException);

} /* namespace compress */
} /* namespace ducky */

#endif /* DUCKY_COMPRESS_COMPRESSEXCEPTION_H_ */
