/*
 * Environment.h
 *
 *  Created on: Sep 5, 2016
 *      Author: ducky
 */

#ifndef _DUCKY_SYSTEM_ENVIRONMENT_H_
#define _DUCKY_SYSTEM_ENVIRONMENT_H_

#include <ducky/Object.h>
#include <string>
#include <map>

using std::string;
using std::map;

/**
 * 获取系统环境变量
 */

namespace ducky {
namespace system {

class Environment: virtual public Object {
public:
	Environment();
	virtual ~Environment();

	void refresh();
	std::string getEnv(std::string envName);

private:
	map<std::string, std::string> env;
};

} /* namespace system */
} /* namespace ducky */

#endif /* WENV_H_ */
