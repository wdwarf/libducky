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

inline int _isspace_(int c){
	int re = isspace(c);
	if(0 == re){
		re = ('\0' == c);
	}
	return re;
}

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
			not1(ptr_fun<int, int>(_isspace_)));
	str.erase(str.begin(), p);
	return str;
}

string TrimLeftCopy(const string& str) {
	string newStr = str;
	return TrimLeft(newStr);
}

string& TrimRight(string& str) {
	string::reverse_iterator p = find_if(str.rbegin(), str.rend(),
			not1(ptr_fun<int, int>(_isspace_)));
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

string& Replease(string& src, const string& find,
                 const string& replease){
    string::size_type pos = src.find_first_of(find);
    if(pos != string::npos){
        src.replace(pos, find.length(), replease);
    }
    return src;
}

string RepleaseCopy(const string& src, const string& find,
                 const string& replease){
	string str = str;
	return Replease(str, find, replease);
}

string& RepleaseAll(string& src, const string& find,
                 const string& replease){
    string::size_type pos = 0;
    do{
        pos = src.find(find, pos);
        if(pos != string::npos){
            src.replace(pos, find.length(), replease);
        }else{
            break;
        }
        pos += replease.length();
    }while(true);
    return src;
}

string RepleaseAllCopy(const string& src, const string& find,
                 const string& replease){
	string str = src;
	return RepleaseAll(str, find, replease);
}

} /* namespace string */
} /* namespace ducky */

