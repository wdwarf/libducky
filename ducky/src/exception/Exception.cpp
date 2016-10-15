/*
 * Exception.cpp
 *
 *  Created on: Sep 6, 2016
 *      Author: ducky
 */

#include "ducky/exception/Exception.h"

namespace ducky {
namespace exception {

Exception::Exception(const std::string& msg, int errNo) _GLIBCXX_USE_NOEXCEPT {
	// TODO Auto-generated constructor stub
	this->msg = msg;
	this->errNo = errNo;
}

Exception::~Exception() _GLIBCXX_USE_NOEXCEPT {
	// TODO Auto-generated destructor stub
}

const char* Exception::what() const _GLIBCXX_USE_NOEXCEPT {
	return this->msg.c_str();
}

int Exception::getErrNo() const {
	return this->errNo;
}

} /* namespace exception */
} /* namespace ducky */
