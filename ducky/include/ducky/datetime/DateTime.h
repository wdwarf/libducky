/*
 * DateTime.h
 *
 *  Created on: Nov 23, 2017
 *      Author: ducky
 */

#ifndef DUCKY_DATETIME_DATETIME_H_
#define DUCKY_DATETIME_DATETIME_H_

#include <ducky/Object.h>
#include <string>
#include <ctime>

using std::string;

namespace ducky {
namespace datetime {

class DateTime: public Object {
public:
	DateTime();
	DateTime(time_t t);
	DateTime(const DateTime& t);
	virtual ~DateTime();
	DateTime& operator=(const DateTime& t);

	int getLocalYear() const;
	int getLocalMonth() const;
	int getLocalMDay() const;
	int getLocalHour() const;
	int getLocalMinute() const;
	int getLocalSecond() const;
	int getLocalWeek() const;
	int getLocalYearDay() const;

	int getYear() const;
	int getMonth() const;
	int getMDay() const;
	int getHour() const;
	int getMinute() const;
	int getSecond() const;
	int getWeek() const;
	int getYearDay() const;

	string toLocalString(const string& format = "") const;
	string toString(const string& format = "") const;
	tm toLocalTm() const;
	tm toTm() const;

	static DateTime now();

	bool operator==(const DateTime& t) const;
	bool operator!=(const DateTime& t) const;
	bool operator<(const DateTime& t) const;
	bool operator<=(const DateTime& t) const;
	bool operator>(const DateTime& t) const;
	bool operator>=(const DateTime& t) const;
	long operator-(const DateTime& t) const;

private:
	time_t t;
};

} /* namespace datetime */
} /* namespace ducky */

#endif /* DATETIME_H_ */
