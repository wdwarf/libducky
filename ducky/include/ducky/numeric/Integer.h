/*
 * Integer.h
 *
 *  Created on: Oct 14, 2016
 *      Author: ducky
 */

#ifndef DUCKY_NUMERIC_INTEGER_H_
#define DUCKY_NUMERIC_INTEGER_H_

#include <string>
#include <ducky/Object.h>
#include <ostream>

namespace ducky {
namespace numeric {

using std::string;

class Integer: virtual public Object {
public:
	Integer();
	Integer(int val);
	Integer(const string& str);
	virtual ~Integer();

	Integer& operator=(const int& val);
	Integer& operator=(const string& val);
	operator int() const;
	int getValue() const;

	string toString(bool toHex = false) const;
	void fromString(const string& str);

private:
	int value;
};

} /* namespace numeric */
} /* namespace ducky */

std::ostream& operator<<(std::ostream& o, const ducky::numeric::Integer& i);

#endif /* NUMERIC_INT_H_ */
