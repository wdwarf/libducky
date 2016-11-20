/*
 * Environment.cpp
 *
 *  Created on: Sep 5, 2016
 *      Author: ducky
 */

#include <ducky/string/String.h>
#include <ducky/system/Environment.h>
#include <iostream>

using namespace std;

extern char** environ;

namespace ducky {
namespace system{

using ducky::string::String;

Environment::Environment() {
	// TODO Auto-generated constructor stub
	this->refresh();
}

Environment::~Environment() {
	// TODO Auto-generated destructor stub
}

void Environment::refresh() {
	this->env.clear();
	if (environ) {
		char** env = environ;
		while (*env) {
			std::string strEnv = *env;
			int pos = strEnv.find_first_of("=", 0);
			if (pos >= 0) {
				std::string envName = strEnv.substr(0, pos);
				std::string envValue = strEnv.substr(pos + 1);
				String::to_upper(envName);
				this->env.insert(make_pair(envName, envValue));
			}
			++env;
		}
	}
}

std::string Environment::getEnv(std::string envName){
	String::to_upper(envName);
	return this->env[envName];
}

}
} /* namespace ducky */
