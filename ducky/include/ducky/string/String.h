/*
 * String.h
 *
 *  Created on: Sep 5, 2016
 *      Author: ducky
 */

#ifndef DUCKY_STRIING_STRING_H_
#define DUCKY_STRIING_STRING_H_

#include <ducky/Object.h>
#include <string>
#include <ostream>

using std::string;

namespace ducky {

typedef std::string StdString;

namespace string{

class String: public Object {
public:
	String();
	String(const StdString& str);
	String(const char* str);
	virtual ~String();

	operator StdString();
	StdString toStdString();
	const char* c_str() const;
	StdString* operator->();
	String& operator=(const StdString& str);
	String& operator=(const char* str);
	String trimLeft();
	String trimRight();
	String trim();
	String toLower();
	String toUpper();

	static StdString& toLower(StdString& str);
	static StdString toLowerCopy(const StdString& str);
	static StdString& toUpper(StdString& str);
	static StdString toUpperCopy(const StdString& str);
	static StdString& trimLeft(StdString& str);
	static StdString trimLeftCopy(const StdString& str);
	static StdString& trimRight(StdString& str);
	static StdString trimRightCopy(const StdString& str);
	static StdString& trim(StdString& str);
	static StdString trimCopy(const StdString& str);

private:
	StdString _str;
};

} /* namespace string */
} /* namespace ducky */

std::ostream& operator<<(std::ostream& o, const ducky::string::String& s);

#endif /* WSTRING_H_ */
