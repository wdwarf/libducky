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
namespace string {

String::String() {
	// TODO Auto-generated constructor stub

}

String::~String() {
	// TODO Auto-generated destructor stub
}

String::String(const StdString& str) :
		_str(str) {

}

String::String(const char* str) :
		_str(str) {

}

String::operator StdString() {
	return this->_str;
}

StdString String::toStdString(){
	return this->_str;
}

const char* String::c_str() const{
	return this->_str.c_str();
}

StdString* String::operator->(){
	return &this->_str;
}

String& String::operator=(const StdString& str) {
	this->_str = str;
	return *this;
}

String& String::operator=(const char* str) {
	this->_str = str;
	return *this;
}

String String::trimLeft() {
	StdString s = String::trimLeftCopy(this->_str);
	return String(s);
}

String String::trimRight() {
	StdString s = String::trimRightCopy(this->_str);
	return String(s);
}

String String::trim() {
	StdString s = String::trimCopy(this->_str);
	return String(s);
}

String String::toLower() {
	StdString s = String::toLowerCopy(this->_str);
	return String(s);
}

String String::toUpper() {
	StdString s = String::toUpperCopy(this->_str);
	return String(s);
}




StdString& String::toLower(StdString& str) {
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}

StdString String::toLowerCopy(const StdString& str) {
	StdString re = str;
	String::toLower(re);
	return re;
}

StdString& String::toUpper(StdString& str) {
	std::transform(str.begin(), str.end(), str.begin(), ::toupper);
	return str;
}

StdString String::toUpperCopy(const StdString& str) {
	StdString re = str;
	String::toUpper(re);
	return re;
}

StdString& String::trimLeft(StdString& str) {
	StdString::iterator p = find_if(str.begin(), str.end(),
			not1(ptr_fun<int, int>(isspace)));
	str.erase(str.begin(), p);
	return str;
}

StdString String::trimLeftCopy(const StdString& str) {
	StdString newStr = str;
	return String::trimLeft(newStr);
}

StdString& String::trimRight(StdString& str) {
	StdString::reverse_iterator p = find_if(str.rbegin(), str.rend(),
			not1(ptr_fun<int, int>(isspace)));
	str.erase(p.base(), str.end());
	return str;
}

StdString String::trimRightCopy(const StdString& str) {
	StdString newStr = str;
	return String::trimRight(newStr);
}

StdString& String::trim(StdString& str) {
	return trimRight(trimLeft(str));
}

StdString String::trimCopy(const StdString& str) {
	StdString newStr = str;
	return String::trim(newStr);
}

} /* namespace string */
} /* namespace ducky */

std::ostream& operator<<(std::ostream& o, const ducky::string::String& s){
	o << s.c_str();
	return o;
}

