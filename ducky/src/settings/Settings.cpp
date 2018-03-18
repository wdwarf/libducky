/*
 * Settings.cpp
 *
 *  Created on: 2018年3月7日
 *      Author: liyawu
 */

#include <ducky/settings/Settings.h>

using namespace ducky::thread;

namespace ducky {
namespace settings {

Settings::Settings() {
	//

}

Settings::~Settings() {
	//
}

const ducky::variant::Variant& Settings::getValue(const std::string& key) const {
	MutexLocker lk(this->mutex);
	ValueMap::const_iterator it = this->values.find(key);
	if (it == this->values.end()) {
		THROW_EXCEPTION(SettingsException, "[" + key + "] not found.", -1);
	}
	return it->second;
}

void Settings::setValue(const std::string& key, const ducky::variant::Variant& value) {
	MutexLocker lk(this->mutex);
	this->values[key] = value;
}

bool Settings::hasValue(const std::string& key) const {
	MutexLocker lk(this->mutex);
	return (this->values.find(key) != this->values.end());
}

void Settings::removeValue(const std::string& key) {
	MutexLocker lk(this->mutex);
	this->values.erase(key);
}

const ducky::variant::Variant& Settings::operator[](const std::string& key) const {
	return this->getValue(key);
}

void Settings::clear(){
	MutexLocker lk(this->mutex);
	this->values.clear();
}

std::set<std::string> Settings::getKeys() const {
	std::set<std::string> keys;

	MutexLocker lk(this->mutex);
	for (ValueMap::const_iterator it = this->values.begin(); it != this->values.end(); ++it) {
		keys.insert(it->first);
	}

	return keys;
}

} /* namespace settings */
} /* namespace ducky */
