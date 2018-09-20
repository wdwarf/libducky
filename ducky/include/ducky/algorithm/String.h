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
#include <vector>
#include <ostream>

using std::string;

namespace ducky {

namespace algorithm {

std::string& ToLower(std::string& str);
std::string ToLowerCopy(const std::string& str);
std::string& ToUpper(std::string& str);
std::string ToUpperCopy(const std::string& str);
std::string& TrimLeft(std::string& str);
std::string TrimLeftCopy(const std::string& str);
std::string& TrimRight(std::string& str);
std::string TrimRightCopy(const std::string& str);
std::string& Trim(std::string& str);
std::string TrimCopy(const std::string& str);

std::string& Replace(std::string& src, const std::string& find, const std::string& replace,
		bool ignoreCase = false);
std::string ReplaceCopy(const std::string& src, const std::string& find, const std::string& replace,
		bool ignoreCase = false);
std::string& ReplaceAll(std::string& src, const std::string& find, const std::string& replace,
		bool ignoreCase = false);
std::string ReplaceAllCopy(const std::string& src, const std::string& find,
		const std::string& replace, bool ignoreCase = false);

int IndexOf(const std::string& src, const std::string& find, bool ignoreCase = false);

template<class T>
void SplitTo(const std::string& src, const std::string& find, T& t){
	std::string s;
	for(std::string::size_type i = 0; i < src.length(); ++i){
		const char c = src[i];
		if(find.find(c) != std::string::npos){
			t.insert(t.end(), s);
			s = "";
		}else{
			s.push_back(c);
		}
	}
	if(!s.empty() || (find.find(src[src.length() - 1]) != std::string::npos)){
		t.insert(t.end(), s);
	}
}

std::vector<std::string> Split(const std::string& src, const std::string& find){
	std::vector<std::string> v;
	SplitTo(src, find, v);
	return v;
}

//十六进制字符转数字
unsigned int HexAToI(char x);
char IToHexA(unsigned int x);

} /* namespace string */
} /* namespace ducky */

#endif /* DUCKY_STRIING_STRING_H_ */
