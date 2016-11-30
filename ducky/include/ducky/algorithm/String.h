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

namespace algorithm {

string& ToLower(string& str);
string ToLowerCopy(const string& str);
string& ToUpper(string& str);
string ToUpperCopy(const string& str);
string& TrimLeft(string& str);
string TrimLeftCopy(const string& str);
string& TrimRight(string& str);
string TrimRightCopy(const string& str);
string& Trim(string& str);
string TrimCopy(const string& str);

} /* namespace string */
} /* namespace ducky */

#endif /* DUCKY_STRIING_STRING_H_ */
