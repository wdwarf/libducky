#include <ducky/numeric/Boolean.h>
#include <ducky/algorithm/String.h>

namespace ducky {
namespace numeric {

Boolean::Boolean() :
		_value(false) {

}

Boolean::Boolean(bool val) :
		_value(val) {
}

Boolean::Boolean(const string& val) : _value(false) {
	this->fromString(val);
}

string Boolean::toString() {
	if (this->_value)
		return "true";
	return "false";
}

void Boolean::fromString(const string& val) {
	string v = algorithm::ToLowerCopy(val);
	if (v.empty() || ("false" == v) || ("0" == v)) {
		this->_value = false;
	} else {
		this->_value = true;
	}
}

Boolean::operator bool() {
	return this->_value;
}

Boolean::operator string() {
	return this->toString();
}

Boolean& Boolean::operator=(bool val) {
	this->_value = val;
	return *this;
}

Boolean& Boolean::operator=(const char* val) {
	this->fromString(val);
	return *this;
}

Boolean& Boolean::operator=(const string& val) {
	this->fromString(val);
	return *this;
}

}
}
