/*
 * String.cpp
 *
 *  Created on: Sep 5, 2016
 *      Author: ducky
 */

#include <string>
#include <algorithm>

using namespace std;

namespace ducky {
namespace algorithm {

string& ToLower(string& str) {
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}

string ToLowerCopy(const string& str) {
	string re = str;
	ToLower(re);
	return re;
}

string& ToUpper(string& str) {
	std::transform(str.begin(), str.end(), str.begin(), ::toupper);
	return str;
}

string ToUpperCopy(const string& str) {
	string re = str;
	ToUpper(re);
	return re;
}

string& TrimLeft(string& str) {
	string::iterator p = find_if(str.begin(), str.end(),
			not1(ptr_fun<int, int>(isspace)));
	str.erase(str.begin(), p);
	return str;
}

string TrimLeftCopy(const string& str) {
	string newStr = str;
	return TrimLeft(newStr);
}

string& TrimRight(string& str) {
	string::reverse_iterator p = find_if(str.rbegin(), str.rend(),
			not1(ptr_fun<int, int>(isspace)));
	str.erase(p.base(), str.end());
	return str;
}

string TrimRightCopy(const string& str) {
	string newStr = str;
	return TrimRight(newStr);
}

string& Trim(string& str) {
	return TrimRight(TrimLeft(str));
}

string TrimCopy(const string& str) {
	string newStr = str;
	return Trim(newStr);
}

} /* namespace string */
} /* namespace ducky */

