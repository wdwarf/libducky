/*
 * DateTime.h
 *
 *  Created on: Nov 23, 2017
 *      Author: ducky
 */

#ifndef DUCKY_DATETIME_DATETIME_H_
#define DUCKY_DATETIME_DATETIME_H_

#include <ducky/Object.h>
#include <ducky/exception/Exception.h>
#include <string>
#include <ctime>

namespace ducky {
namespace datetime {

EXCEPTION_DEF(DateTimeException)

class DateTime: public Object {
public:
	DateTime();
	DateTime(time_t t);
	DateTime(const DateTime& t);
	virtual ~DateTime();

	int getLocalYear() const;
	int getLocalMonth() const;
	int getLocalMDay() const;
	int getLocalHour() const;
	int getLocalMinute() const;
	int getLocalSecond() const;
	int getLocalWeek() const;
	int getLocalYearDay() const;
	std::string getLocalDate() const;
	std::string getLocalTime() const;
	std::string toLocalString(const std::string& format = "") const;
	tm toLocalTm() const;

	int getYear() const;
	int getMonth() const;
	int getMDay() const;
	int getHour() const;
	int getMinute() const;
	int getSecond() const;
	int getWeek() const;
	int getYearDay() const;
	std::string getDate() const;
	std::string getTime() const;
	std::string toString(const std::string& format = "") const;
	tm toTm() const;

	DateTime& operator=(const DateTime& t);
	bool operator==(const DateTime& t) const;
	bool operator!=(const DateTime& t) const;
	bool operator<(const DateTime& t) const;
	bool operator<=(const DateTime& t) const;
	bool operator>(const DateTime& t) const;
	bool operator>=(const DateTime& t) const;
	long operator-(const DateTime& t) const;

	static DateTime now();

private:
	time_t t;
};

} /* namespace datetime */
} /* namespace ducky */

#endif /* DATETIME_H_ */
