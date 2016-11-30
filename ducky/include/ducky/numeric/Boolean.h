/*
 * 布尔类
 *
 * 用于处理bool类型的值
 */
#ifndef BOOLEAN_H
#define BOOLEAN_H

#include <string>

namespace ducky {
namespace numeric {

using std::string;

class Boolean {
public:
	Boolean();
	Boolean(bool val);
	Boolean(const string& val);

	operator bool();
	operator string();
	Boolean& operator=(bool val);
	Boolean& operator=(const char* val);
	Boolean& operator=(const string& val);

	string toString();
	void fromString(const string& val);

private:
	bool _value;
};

}
}

#endif // BOOLEAN_H
