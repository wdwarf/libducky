/*
 * Variant.h
 *
 *  Created on: 2016-12-01
 *      Author: liyawu
 */

#ifndef VARIANT_H_
#define VARIANT_H_

#include <ducky/Object.h>
#include <ducky/buffer/Buffer.h>
#include <ducky/exception/Exception.h>
#include <string>

using std::string;

namespace ducky {
namespace variant {

EXCEPTION_DEF(VariantException);

enum VariantType {
	VT_UNKNOWN = 0,
	VT_BOOLEAN,
	VT_UCHAR,
	VT_USHORT,
	VT_UINT,
	VT_ULONG,
	VT_ULONGLONG,
	VT_CHAR,
	VT_SHORT,
	VT_INT,
	VT_LONG,
	VT_LONGLONG,
	VT_FLOAT,
	VT_DOUBLE,
	VT_CARRAY,
	VT_STRING
};

struct VariantTypeInfo: public Object {
	VariantType type;
	long size;

	VariantTypeInfo() :
			type(VT_UNKNOWN), size(0) {
	}
};

class Variant: public Object {
public:
	Variant();
	Variant(const Variant& v);
	Variant& operator=(const Variant& v);
	Variant(bool v);
	Variant(char v);
	Variant(short v);
	Variant(int v);
	Variant(long v);
	Variant(long long v);
	Variant(unsigned char v);
	Variant(unsigned short v);
	Variant(unsigned int v);
	Variant(unsigned long v);
	Variant(unsigned long long v);
	Variant(float v);
	Variant(double v);
	Variant(const char* v);
	Variant(const string& v);
	Variant(const buffer::Buffer& v);
	virtual ~Variant();

	string toString() const;
	buffer::Buffer toBuffer() const;

	Variant& operator=(bool v);
	Variant& operator=(char v);
	Variant& operator=(short v);
	Variant& operator=(int v);
	Variant& operator=(long v);
	Variant& operator=(long long v);
	Variant& operator=(unsigned char v);
	Variant& operator=(unsigned short v);
	Variant& operator=(unsigned int v);
	Variant& operator=(unsigned long v);
	Variant& operator=(unsigned long long v);
	Variant& operator=(float v);
	Variant& operator=(double v);
	Variant& operator=(const char* v);
	Variant& operator=(const string& v);
	Variant& operator=(const buffer::Buffer& v);
	void setValue(const void* v);
	void setValue(const void* v, unsigned long size);
	void setValue(const void* v, VariantType type);
	void setValue(const void* v, const string& typeName);

	operator bool() const;
	operator char() const;
	operator short() const;
	operator int() const;
	operator long() const;
	operator long long() const;
	operator unsigned char() const;
	operator unsigned short() const;
	operator unsigned int() const;
	operator unsigned long() const;
	operator unsigned long long() const;
	operator float() const;
	operator double() const;
	operator string() const;
	operator buffer::Buffer() const;

	void clear();
	void zero();
	unsigned long getSize() const;
	void setSize(unsigned long size);
	VariantType getVt() const;
	void setVt(VariantType vt);
	void setVt(const string& typeName);

	static VariantTypeInfo TypeInfoFromString(const string& typeName);
	static VariantTypeInfo TypeInfo(VariantType type);

	friend bool operator==(const Variant& v1, const Variant& v2);

	Variant operator +(const char* v) const;
	Variant operator +(const std::string& v) const;
	Variant operator ==(const bool& v) const;
	Variant operator !=(const bool& v) const;

	friend std::ostream& operator<<(std::ostream& o,
			const ducky::variant::Variant& v);

#define _VARIANT_OPT_DEF2_(T, OP) Variant operator OP(const T& v);

#define _VARIANT_OPT_DEF2(OP) _VARIANT_OPT_DEF2_(char, OP)\
_VARIANT_OPT_DEF2_(short, OP)\
_VARIANT_OPT_DEF2_(int, OP)\
_VARIANT_OPT_DEF2_(long long, OP)\
_VARIANT_OPT_DEF2_(unsigned char, OP)\
_VARIANT_OPT_DEF2_(unsigned short, OP)\
_VARIANT_OPT_DEF2_(unsigned int, OP)\
_VARIANT_OPT_DEF2_(unsigned long long, OP)

	_VARIANT_OPT_DEF2(+)
	_VARIANT_OPT_DEF2(-)
	_VARIANT_OPT_DEF2(*)
	_VARIANT_OPT_DEF2(/)
	_VARIANT_OPT_DEF2(%)
	_VARIANT_OPT_DEF2(==)
	_VARIANT_OPT_DEF2(!=)
	_VARIANT_OPT_DEF2(|)
	_VARIANT_OPT_DEF2(&)

#define _VARIANT_OPT_DEF_FLOAT2(OP) _VARIANT_OPT_DEF2_(float, OP)\
_VARIANT_OPT_DEF2_(double, OP)

	_VARIANT_OPT_DEF_FLOAT2(+)
	_VARIANT_OPT_DEF_FLOAT2(-)
	_VARIANT_OPT_DEF_FLOAT2(*)
	_VARIANT_OPT_DEF_FLOAT2(/)
	_VARIANT_OPT_DEF_FLOAT2(==)
	_VARIANT_OPT_DEF_FLOAT2(!=)

	friend Variant operator +(const char* p1, const Variant& p2);
	friend Variant operator +(const std::string& p1, const Variant& p2);

	friend Variant operator ==(const bool& p1, const Variant& p2);
	friend Variant operator !=(const bool& p1, const Variant& p2);

#define _VARIANT_OPT_DEF_(T, OP) friend  Variant operator OP(const T& p1, const Variant& p2);

#define _VARIANT_OPT_DEF(OP) _VARIANT_OPT_DEF_(char, OP)\
_VARIANT_OPT_DEF_(short, OP)\
_VARIANT_OPT_DEF_(int, OP)\
_VARIANT_OPT_DEF_(long long, OP)\
_VARIANT_OPT_DEF_(unsigned char, OP)\
_VARIANT_OPT_DEF_(unsigned short, OP)\
_VARIANT_OPT_DEF_(unsigned int, OP)\
_VARIANT_OPT_DEF_(unsigned long long, OP)

	_VARIANT_OPT_DEF(+)
	_VARIANT_OPT_DEF(-)
	_VARIANT_OPT_DEF(*)
	_VARIANT_OPT_DEF(/)
	_VARIANT_OPT_DEF(%)
	_VARIANT_OPT_DEF(==)
	_VARIANT_OPT_DEF(!=)
	_VARIANT_OPT_DEF(|)
	_VARIANT_OPT_DEF(&)

#define _VARIANT_OPT_DEF_FLOAT(OP) _VARIANT_OPT_DEF_(float, OP)\
_VARIANT_OPT_DEF_(double, OP)

	_VARIANT_OPT_DEF_FLOAT(+)
	_VARIANT_OPT_DEF_FLOAT(-)
	_VARIANT_OPT_DEF_FLOAT(*)
	_VARIANT_OPT_DEF_FLOAT(/)
	_VARIANT_OPT_DEF_FLOAT(==)
	_VARIANT_OPT_DEF_FLOAT(!=)

private:
	VariantType vt;
	unsigned long size;
	typedef union {
		void* valPtr;
		bool valBool;
		char valChar;
		short valShort;
		int valInt;
		long valLong;
		long long valLongLong;
		unsigned char valUChar;
		unsigned short valUShort;
		unsigned int valUInt;
		unsigned long valULong;
		unsigned long long valULongLong;
		float valFloat;
		double valDouble;
	} Value;
	Value value;

private:
	template<typename T>
	T toValue() const;
};

} /* namespace variant */
} /* namespace ducky */

#endif /* VARIANT_H_ */
