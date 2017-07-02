/*
 * Integer.cpp
 *
 *  Created on: Oct 14, 2016
 *      Author: ducky
 */

#include <ducky/numeric/Integer.h>
#include <cstdlib>
#include <sstream>

using namespace std;

namespace ducky {
namespace numeric {

Integer::Integer() :
		value(0) {
	// TODO Auto-generated constructor stub

}

Integer::Integer(int val) :
		value(val) {

}

Integer::Integer(const string& str) {
	this->value = 0;
	this->fromString(str);
}

Integer& Integer::operator=(const int& val) {
	this->value = val;
	return *this;
}

Integer& Integer::operator=(const string& val) {
	this->fromString(val);
	return *this;
}

Integer::operator int() const {
	return this->value;
}

int Integer::getValue() const {
	return this->value;
}

Integer::~Integer() {
	// TODO Auto-generated destructor stub
}

string Integer::toString(bool toHex) const {
	stringstream str;
	if (toHex) {
		str << "0x";
		str.fill('0');
		unsigned char* p = (unsigned char*) &this->value;
		int size = sizeof(this->value);
		for (int i = size; i > 0; --i) {
			str.width(2);
			str << hex << (int) p[i - 1];
		}
	} else {
		str << this->value;
	}
	return str.str();
}

void Integer::fromString(const string& str) {
	this->value = atoi(str.c_str());
}

} /* namespace numeric */
} /* namespace ducky */

std::ostream& operator<<(std::ostream& o, const ducky::numeric::Integer& i) {
	o << (int) i;
	return o;
}
