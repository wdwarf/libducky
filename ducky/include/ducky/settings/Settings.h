/*
 * Settings.h
 *
 *  Created on: 2018年3月7日
 *      Author: liyawu
 */

#ifndef SETTINGS_SETTINGS_H_
#define SETTINGS_SETTINGS_H_

#include <ducky/Object.h>
#include <ducky/exception/Exception.h>
#include <ducky/variant/Variant.h>
#include <ducky/thread/Mutex.h>
#include <string>
#include <map>
#include <set>

namespace ducky {
namespace settings {

EXCEPTION_DEF(SettingsException);

class Settings: virtual public Object {
public:
	Settings();
	virtual ~Settings();

	const ducky::variant::Variant& getValue(const std::string& key) const;
	void setValue(const std::string& key, const ducky::variant::Variant& value);
	bool hasValue(const std::string& key) const;
	void removeValue(const std::string& key);
	const ducky::variant::Variant& operator[](const std::string& key) const;
	void clear();

	std::set<std::string> getKeys() const;
private:
	typedef std::map<string, ducky::variant::Variant> ValueMap;
	ValueMap values;
	mutable ducky::thread::Mutex mutex;
};

} /* namespace settings */
} /* namespace ducky */

#endif /* SETTINGS_SETTINGS_H_ */
