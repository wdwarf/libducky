/*
 * String.cpp
 *
 *  Created on: Sep 5, 2016
 *      Author: ducky
 */

#include <ducky/string/String.h>
#include <algorithm>

using namespace std;

namespace ducky {
namespace string{

String::String() {
	// TODO Auto-generated constructor stub

}

String::~String() {
	// TODO Auto-generated destructor stub
}

std::string& String::to_lower(std::string& str){
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}

std::string String::to_lower_copy(const std::string& str) {
	std::string re = str;
	String::to_lower(re);
	return re;
}


std::string& String::to_upper(std::string& str) {
	std::transform(str.begin(), str.end(), str.begin(), ::toupper);
	return str;
}

std::string String::to_upper_copy(const std::string& str) {
	std::string re = str;
	String::to_upper(re);
	return re;
}

} /* namespace std::string */
} /* namespace ducky */
