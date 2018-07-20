/*
 * Application.h
 *
 *  Created on: 2018年7月18日
 *      Author: liyawu
 */

#ifndef APP_APPLICATION_H_
#define APP_APPLICATION_H_

#include <ducky/Object.h>
#include <ducky/exception/Exception.h>
#include <ducky/variant/Variant.h>
#include <vector>
#include <string>
#include <set>

namespace ducky {
namespace app {

EXCEPTION_DEF(ApplicationException);

class Application: public ducky::Object {
public:
	Application(int argc, char** argv);
	virtual ~Application();

	int run();
	void exit(int code = 0);
	int getExitCode() const;
	virtual void onInitialize(){}
	virtual void onRun() = 0;
	virtual void onUninitialize(){}

	const std::vector<std::string>& getCommandLines() const;
	int getCommandLineCount() const;

	const ducky::variant::Variant& getValue(const std::string& key) const;
	void setValue(const std::string& key, const ducky::variant::Variant& value);
	bool hasValue(const std::string& key) const;
	void removeValue(const std::string& key);
	std::set<std::string> getKeys() const;
	void saveSettings(const std::string& file);
	void loadSettings(const std::string& file);

private:
	class ApplicationImpl;
	ApplicationImpl* impl;
};

Application* GetApplication();

} /* namespace app */
} /* namespace ducky */

#endif /* APP_APPLICATION_H_ */
