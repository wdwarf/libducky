/*
 * Exception.cpp
 *
 *  Created on: Sep 6, 2016
 *      Author: ducky
 */

#include "ducky/exception/Exception.h"

using namespace std;

namespace ducky {
namespace exception {

Exception::Exception(const std::string& msg, int errNo, int lineNumber,
		const std::string& functionName, const std::string& fileName)
				_GLIBCXX_USE_NOEXCEPT {
	
	this->msg = msg;
	this->errNo = errNo;
	this->lineNumber = lineNumber;
	this->functionName = functionName;
	this->fileName = fileName;
}

Exception::~Exception() _GLIBCXX_USE_NOEXCEPT {
	
}

const char* Exception::what() const _GLIBCXX_USE_NOEXCEPT {
	return this->msg.c_str();
}

int Exception::getErrNo() const {
	return this->errNo;
}

const std::string& Exception::getFileName() const {
	return fileName;
}

const std::string& Exception::getFunctionName() const {
	return functionName;
}

int Exception::getLineNumber() const {
	return lineNumber;
}
} /* namespace exception */
} /* namespace ducky */

