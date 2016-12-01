/*
 * Variant.h
 *
 *  Created on: 2016��12��1��
 *      Author: liyawu
 */

#ifndef VARIANT_H_
#define VARIANT_H_

#include <ducky/Object.h>
#include <ducky/buffer/Buffer.h>
#include <string>

using std::string;

namespace ducky {
namespace variant {

enum VariantType {
	VT_UNKNOWN = 0,
	VT_BOOLEAN,
	VT_UINT8,
	VT_UINT16,
	VT_UINT32,
	VT_UINT64,
	VT_INT8,
	VT_INT16,
	VT_INT32,
	VT_INT64,
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
	Variant& operator=(const char* v);
	Variant& operator=(const string& v);
	Variant& operator=(const buffer::Buffer& v);
	void setValue(const void* v);
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
	operator string() const;
	operator buffer::Buffer() const;

	static VariantTypeInfo TypeInfoFromString(const string& typeName);
	static VariantTypeInfo TypeInfo(VariantType type);

	void clear();
	unsigned long getSize() const;
	void setSize(unsigned long size);
	VariantType getVt() const;
	void setVt(VariantType vt);

private:
	VariantType vt;
	unsigned long size;
	typedef union {
		void* valPtr;
		bool valBool;
		char valInt8;
		short valInt16;
		int valInt32;
		long long valInt64;
		unsigned char valUint8;
		unsigned short valUint16;
		unsigned int valUint32;
		unsigned long long valUint64;
	} Value;
	Value value;

private:
	template<typename T>
	T toValue() const;
};

} /* namespace variant */
} /* namespace ducky */

#endif /* VARIANT_H_ */
