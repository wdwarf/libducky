/*
 * Settings.cpp
 *
 *  Created on: 2018年3月7日
 *      Author: liyawu
 */

#include <ducky/settings/Settings.h>
#include <fstream>
#include <sstream>
#include <iostream>

#include <errno.h>
#include <cstring>

#include <ducky/algorithm/String.h>
#include <ducky/encrypt/Base64.h>

using namespace std;
using namespace ducky::thread;
using namespace ducky::algorithm;
using namespace ducky::encrypt;

namespace ducky {
namespace settings {

Settings::Settings() {
	//

}

Settings::~Settings() {
	//
}

const ducky::variant::Variant& Settings::getValue(const std::string& key) const {
	Mutex::Locker lk(this->mutex);
	ValueMap::const_iterator it = this->values.find(key);
	if (it == this->values.end()) {
		THROW_EXCEPTION(SettingsException, "[" + key + "] not found.", -1);
	}
	return it->second;
}

void Settings::setValue(const std::string& key, const ducky::variant::Variant& value) {
	Mutex::Locker lk(this->mutex);
	this->values[key] = value;
}

bool Settings::hasValue(const std::string& key) const {
	Mutex::Locker lk(this->mutex);
	return (this->values.find(key) != this->values.end());
}

void Settings::removeValue(const std::string& key) {
	Mutex::Locker lk(this->mutex);
	this->values.erase(key);
}

const ducky::variant::Variant& Settings::operator[](const std::string& key) const {
	return this->getValue(key);
}

void Settings::clear() {
	Mutex::Locker lk(this->mutex);
	this->values.clear();
}

std::set<std::string> Settings::getKeys() const {
	std::set<std::string> keys;

	Mutex::Locker lk(this->mutex);
	for (ValueMap::const_iterator it = this->values.begin(); it != this->values.end(); ++it) {
		keys.insert(it->first);
	}

	return keys;
}

void Settings::saveToFile(const std::string& file) {
	Mutex::Locker lk(this->mutex);
	fstream f;
	f.open(file.c_str(), ios::out | ios::trunc);
	if (!f.is_open()) {
		THROW_EXCEPTION(SettingsException, "file[" + file + "] open failed. " + strerror(errno),
				errno);
	}

	for (ValueMap::iterator it = this->values.begin(); it != this->values.end(); ++it) {
		f << Base64::encrypt(it->first) << ":" << Base64::encrypt(it->second.toString()) << endl;
	}

	f.close();
}

void Settings::loadFromFile(const std::string& file) {
	Mutex::Locker lk(this->mutex);
	fstream f;
	f.open(file.c_str(), ios::in);
	if (!f.is_open()) {
		THROW_EXCEPTION(SettingsException, "file[" + file + "] open failed. " + strerror(errno),
				errno);
	}

	while(!f.eof()){
		string line;
		std::getline(f, line);
		Trim(line);
		if(line.empty()) continue;

		string::size_type pos = line.find(":");
		if(pos == string::npos) continue;

		string key = line.substr(0, pos);
		string value = line.substr(pos + 1);
		stringstream strKey;
		stringstream strValue;
		Base64::decrypt(strKey, key);
		Base64::decrypt(strValue, value);

		key = strKey.str();
		value = strValue.str();

		this->values.insert(make_pair(key, value));
	}

	f.close();
}

} /* namespace settings */
} /* namespace ducky */
