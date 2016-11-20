/*
 * Exception.h
 *
 *  Created on: Sep 6, 2016
 *      Author: ducky
 */

#ifndef WEXCEPTION_H_
#define WEXCEPTION_H_

#include <ducky/Object.h>
#include <exception>
#include <string>

namespace ducky {
namespace exception {

class Exception: public std::exception, public Object {
public:
	Exception(const std::string& msg, int errNo = 0) _GLIBCXX_USE_NOEXCEPT;
	virtual ~Exception() _GLIBCXX_USE_NOEXCEPT;

	virtual const char* what() const _GLIBCXX_USE_NOEXCEPT;
	virtual int getErrNo() const;

private:
	int errNo;
	std::string msg;
};

} /* namespace exception */

#define EXCEPTION_DEF(exceptionName) class exceptionName : public ducky::exception::Exception{\
	public:\
	exceptionName(const std::string& msg, int errNo = 0) : Exception(msg, errNo){}\
};

#define EXCEPTION_DEF2(exceptionName, parentClass) class exceptionName : public parentClass{\
	public:\
	exceptionName(const std::string& msg, int errNo = 0) : parentClass(msg, errNo){}\
};

} /* namespace ducky */

#endif /* WEXCEPTION_H_ */
