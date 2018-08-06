/*
 * Endian.h
 *
 *  Created on: 2017年11月14日
 *      Author: liyawu
 */

#ifndef DUCKY_ENDIAN_ENDIAN_H_
#define DUCKY_ENDIAN_ENDIAN_H_

#include <ducky/buffer/Buffer.h>

namespace ducky
{
namespace endian
{

enum EndianType
{
	ET_BIG, ET_SMALL
};

#define __REVERSE_T T v = val;\
ducky::buffer::Buffer::ReverseBytes((char*) &v, sizeof(T));\
return v;

class Endian
{
public:
	Endian(EndianType _endianType = GetHostEndian()) :
			endianType(_endianType)
	{
	}

	~Endian()
	{
	}

	EndianType getEndianType() const;
	operator EndianType() const;
	void setEndianType(EndianType endianType);
	bool isDifferenceEndian() const;

	template<typename T> T toBig(const T& val) const
	{
		if (ET_BIG == endianType)
		{
			return val;
		}
		__REVERSE_T
	}

	template<typename T> T toSmall(const T& val) const
	{
		if (ET_SMALL == endianType)
		{
			return val;
		}
		__REVERSE_T
	}

	template<typename T> T toHost(const T& val) const
	{
		if (GetHostEndian() == endianType)
		{
			return val;
		}
		__REVERSE_T
	}

	template<typename T> T to(const T& val, const Endian& e) const
	{
		if (e.endianType == endianType)
		{
			return val;
		}
		__REVERSE_T
	}

	static Endian GetHostEndian();
	static Endian GetDefEndian();

private:
	EndianType endianType;
};

} /* namespace endian */
} /* namespace ducky */

#endif /* DUCKY_ENDIAN_ENDIAN_H_ */
