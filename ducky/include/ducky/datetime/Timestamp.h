/*
 * Timestamp.h
 *
 *  Created on: Nov 23, 2017
 *      Author: ducky
 */

#ifndef DUCKY_DATETIME_TIMESTAMP_H_
#define DUCKY_DATETIME_TIMESTAMP_H_

#include <ducky/Object.h>
#include <ducky/exception/Exception.h>
#include <ducky/datetime/DateTime.h>

namespace ducky {
namespace datetime {

EXCEPTION_DEF(TimestampException)

class Timestamp: public Object {
public:
	Timestamp();
	Timestamp(const Timestamp& t);
	virtual ~Timestamp();

	Timestamp& operator=(const Timestamp& t);

	DateTime toDateTime() const;

	static Timestamp now();

	bool operator==(const Timestamp& t) const;
	bool operator!=(const Timestamp& t) const;
	bool operator<(const Timestamp& t) const;
	bool operator<=(const Timestamp& t) const;
	bool operator>(const Timestamp& t) const;
	bool operator>=(const Timestamp& t) const;
private:
	class TimestampImpl;
	TimestampImpl* impl;
};

} /* namespace datetime */
} /* namespace ducky */

#endif /* TIMESTAMP_H_ */
