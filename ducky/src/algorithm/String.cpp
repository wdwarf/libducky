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

inline int _isspace_(int c) {
	int re = isspace(c);
	if (0 == re) {
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

string& Replace(string& src, const string& find, const string& replace,
		bool ignoreCase) {
	string::size_type pos = string::npos;
	if (ignoreCase) {
		string s = src;
		string f = find;
		ToLower(s);
		ToLower(f);
		pos = s.find(f);
	} else {
		pos = src.find(find);
	}

	if (pos != string::npos) {
		src.replace(pos, find.length(), replace);
	}

	return src;
}

string ReplaceCopy(const string& src, const string& find, const string& replace,
		bool ignoreCase) {
	string str = src;
	return Replace(str, find, replace, ignoreCase);
}

string& ReplaceAll(string& src, const string& find, const string& replace,
		bool ignoreCase) {
	string::size_type pos = 0;
	string s = src;
	string f = find;
	if (ignoreCase) {
		ToLower(s);
		ToLower(f);
	}

	do {
		pos = s.find(f, pos);

		if (pos != string::npos) {
			src.replace(pos, find.length(), replace);
			s.replace(pos, find.length(), replace);
		} else {
			break;
		}
		pos += replace.length();
	} while (true);
	return src;
}

string ReplaceAllCopy(const string& src, const string& find,
		const string& replace, bool ignoreCase) {
	string str = src;
	return ReplaceAll(str, find, replace, ignoreCase);
}

int IndexOf(const string& src, const string& find, bool ignoreCase) {
	int re = -1;
	string::size_type pos = string::npos;
	if (ignoreCase) {
		string s = src;
		string f = find;
		ToLower(s);
		ToLower(f);
		pos = s.find(f);
	} else {
		pos = src.find(find);
	}

	if (pos != string::npos) {
		re = pos;
	}

	return re;
}

} /* namespace string */
} /* namespace ducky */

