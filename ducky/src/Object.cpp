/*
 * WObject.cpp
 *
 *  Created on: Oct 14, 2016
 *      Author: ducky
 */

#include "ducky/Object.h"
#include <typeinfo>
#include <sstream>
#include <iostream>
using namespace std;

namespace ducky {

Object::Object() {
	// TODO Auto-generated constructor stub

}

Object::~Object() {
	// TODO Auto-generated destructor stub
}

string Object::getClassName() {
	string className;
	string fullName = typeid(*this).name();

	if ('N' == fullName[0]) {
		fullName = fullName.substr(1, fullName.length());
		int len = 0;
		do {
			stringstream str;
			str << fullName;
			str >> len;
			if (len > 0) {
				stringstream sLen;
				sLen << len;
				int pos = sLen.str().length();
				int partLen = pos + len;

				if(className.empty()){
					className = fullName.substr(pos, len);
				}else{
					className += "::" + fullName.substr(pos, len);
				}
				fullName = fullName.substr(partLen,
						fullName.length() - partLen);
			}
		} while (len > 0);
	} else {
		stringstream str;
		str << fullName;
		int len = 0;
		str >> len;

		if (len > 0)
			className = fullName.substr(fullName.length() - len, len);
	}

	return className;
}

} /* namespace ducky */
