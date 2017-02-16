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

#ifndef _GLIBCXX_USE_NOEXCEPT
#define _GLIBCXX_USE_NOEXCEPT throw()
#endif

class Exception: public std::exception, virtual public Object {
public:
	Exception(const std::string& msg, int errNo = 0,
			int lineNumber = 0, const std::string& functionName = "",
			const std::string& fileName = "") _GLIBCXX_USE_NOEXCEPT;
	virtual ~Exception() _GLIBCXX_USE_NOEXCEPT;

	virtual const char* what() const _GLIBCXX_USE_NOEXCEPT;
	virtual int getErrNo() const;
	const std::string& getFileName() const;
	const std::string& getFunctionName() const;
	int getLineNumber() const;

private:
	int errNo;
	int lineNumber;
	std::string functionName;
	std::string fileName;
	std::string msg;
};

} /* namespace exception */

#define EXCEPTION_DEF(exceptionName) class exceptionName : public ducky::exception::Exception{\
	public:\
	exceptionName(const std::string& msg, int errNo = 0, int lineNumber = 0, \
			const std::string& functionName = "", const std::string& fileName = "") _GLIBCXX_USE_NOEXCEPT \
			: Exception(msg, errNo, lineNumber, functionName, fileName){}\
	virtual ~exceptionName() _GLIBCXX_USE_NOEXCEPT{}\
};

#define EXCEPTION_DEF2(exceptionName, parentClass) class exceptionName : public parentClass{\
	public:\
	exceptionName(const std::string& msg, int errNo = 0, int lineNumber = 0, \
			const std::string& functionName = "", const std::string& fileName = "") _GLIBCXX_USE_NOEXCEPT \
			: parentClass(msg, errNo, lineNumber, functionName, fileName){}\
	virtual ~exceptionName() _GLIBCXX_USE_NOEXCEPT{}\
};

#define MK_EXCEPTION(exceptionName, msg, errNo) exceptionName(msg, errNo, __LINE__, __FUNCTION__, __FILE__)
#define _THROW(exceptionName, msg, errNo) throw MK_EXCEPTION(exceptionName, msg, errNo)

} /* namespace ducky */

#endif /* WEXCEPTION_H_ */
