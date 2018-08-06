/*
 * Endian.cpp
 *
 *  Created on: 2017年11月14日
 *      Author: liyawu
 */

#include <ducky/endian/Endian.h>

namespace ducky
{
namespace endian
{

Endian Endian::GetHostEndian()
{
	static unsigned short n = 0x1234;
	unsigned char* buf = (unsigned char*) &n;
	if (0x34 == buf[0])
	{
		return Endian(ET_SMALL);
	}
	else
	{
		return Endian(ET_BIG);
	}
}

Endian Endian::GetDefEndian()
{
	switch (Endian::GetHostEndian().getEndianType())
	{
	case ET_SMALL:
		return Endian(ET_BIG);
	case ET_BIG:
		return ET_SMALL;
	}
	return Endian(ET_SMALL);
}

EndianType Endian::getEndianType() const
{
	return endianType;
}

Endian::operator EndianType() const{
	return this->getEndianType();
}

void Endian::setEndianType(EndianType endianType)
{
	this->endianType = endianType;
}

bool Endian::isDifferenceEndian() const{
	return (GetHostEndian() != this->endianType);
}

} /* namespace endian */
} /* namespace ducky */
