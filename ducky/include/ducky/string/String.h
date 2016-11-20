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

using std::string;

namespace ducky {
namespace string{

class String: public Object {
public:
	String();
	virtual ~String();

	static std::string& to_lower(std::string& str);
	static std::string to_lower_copy(const std::string& str);
	static std::string& to_upper(std::string& str);
	static std::string to_upper_copy(const std::string& str);
};

} /* namespace string */
} /* namespace ducky */

#endif /* WSTRING_H_ */
