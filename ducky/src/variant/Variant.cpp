/*
 * Variant.cpp
 *
 *  Created on: 2016��12��1��
 *      Author: liyawu
 */

#include <ducky/variant/Variant.h>
#include <ducky/algorithm/String.h>
#include <sstream>
#include <cstring>

using namespace std;

namespace ducky {
namespace variant {

Variant::Variant() :
		vt(VT_UNKNOWN), size(0) {
	// TODO Auto-generated constructor stub
	memset(&this->value, 0, sizeof(this->value));
}

Variant::Variant(bool v) {
	this->vt = VT_BOOLEAN;
	this->size = TypeInfo(this->vt).size;
	this->value.valBool = v;
}

Variant::Variant(char v) {
	this->vt = VT_INT8;
	this->size = TypeInfo(this->vt).size;
	this->value.valInt8 = v;
}

Variant::Variant(short v) {
	this->vt = VT_INT16;
	this->size = TypeInfo(this->vt).size;
	this->value.valInt16 = v;
}

Variant::Variant(int v) {
	this->vt = VT_INT32;
	this->size = TypeInfo(this->vt).size;
	this->value.valInt32 = v;
}

Variant::Variant(long v) {
	this->vt = VT_INT32;
	this->size = TypeInfo(this->vt).size;
	this->value.valInt32 = v;
}

Variant::Variant(long long v) {
	this->vt = VT_INT64;
	this->size = TypeInfo(this->vt).size;
	this->value.valInt64 = v;
}

Variant::Variant(unsigned char v) {
	this->vt = VT_UINT8;
	this->size = TypeInfo(this->vt).size;
	this->value.valUint8 = v;
}

Variant::Variant(unsigned short v) {
	this->vt = VT_UINT16;
	this->size = TypeInfo(this->vt).size;
	this->value.valUint16 = v;
}

Variant::Variant(unsigned int v) {
	this->vt = VT_UINT32;
	this->size = TypeInfo(this->vt).size;
	this->value.valUint32 = v;
}

Variant::Variant(unsigned long v) {
	this->vt = VT_UINT32;
	this->size = TypeInfo(this->vt).size;
	this->value.valUint32 = v;
}

Variant::Variant(unsigned long long v) {
	this->vt = VT_UINT64;
	this->size = TypeInfo(this->vt).size;
	this->value.valUint64 = v;
}

Variant::Variant(const char* v) {
	this->vt = VT_STRING;
	this->size = strlen(v);
	this->value.valPtr = new char[this->size];
	memcpy(this->value.valPtr, v, this->size);
}

Variant::Variant(const string& v) {
	this->vt = VT_STRING;
	this->size = v.length();
	this->value.valPtr = new char[this->size];
	memcpy(this->value.valPtr, v.c_str(), this->size);
}

Variant::Variant(const buffer::Buffer& v) {
	this->vt = VT_CARRAY;
	if (!v.isEmpty()) {
		this->size = v.getSize();
		this->value.valPtr = new char[this->size];
		memcpy(this->value.valPtr, v.getData(), this->size);
	}
}

Variant::~Variant() {
	// TODO Auto-generated destructor stub
	this->clear();
}

Variant::Variant(const Variant& v) {
	this->vt = v.vt;
	this->size = v.size;
	this->value = v.value;
	if (VT_CARRAY == this->vt || VT_STRING == this->vt) {
		this->value.valPtr = new char[this->size];
		memcpy(this->value.valPtr, v.value.valPtr, this->size);
	}
}

Variant& Variant::operator=(const Variant& v) {
	this->vt = v.vt;
	this->size = v.size;
	this->value = v.value;
	if (VT_CARRAY == this->vt || VT_STRING == this->vt) {
		this->value.valPtr = new char[this->size];
		memcpy(this->value.valPtr, v.value.valPtr, this->size);
	}

	return *this;
}

VariantTypeInfo Variant::TypeInfoFromString(const string& typeName) {
	VariantTypeInfo typeInfo;
	string type = typeName;
	algorithm::Trim(type);
	algorithm::ToLower(type);
	if ("boolean" == type || "bool" == type) {
		typeInfo.type = VT_BOOLEAN;
		typeInfo.size = 1;
	} else if ("uint8" == type) {
		typeInfo.type = VT_UINT8;
		typeInfo.size = 1;
	} else if ("uint16" == type) {
		typeInfo.type = VT_UINT16;
		typeInfo.size = 2;
	} else if ("uint32" == type) {
		typeInfo.type = VT_UINT32;
		typeInfo.size = 4;
	} else if ("uint64" == type) {
		typeInfo.type = VT_UINT64;
		typeInfo.size = 8;
	} else if ("int8" == type) {
		typeInfo.type = VT_INT8;
		typeInfo.size = 1;
	} else if ("int16" == type) {
		typeInfo.type = VT_INT16;
		typeInfo.size = 2;
	} else if ("int32" == type) {
		typeInfo.type = VT_INT32;
		typeInfo.size = 4;
	} else if ("int64" == type) {
		typeInfo.type = VT_INT64;
		typeInfo.size = 8;
	} else if ("string" == type) {
		typeInfo.type = VT_STRING;
		typeInfo.size = 0;
	} else if ((0 == type.find("char["))
			&& (']' == type[type.length() - 1])) {
		typeInfo.type = VT_CARRAY;
		stringstream strLen;
		strLen << type.substr(5, type.length() - 6);
		strLen >> typeInfo.size;
	}

	return typeInfo;
}

VariantTypeInfo Variant::TypeInfo(VariantType type) {
	VariantTypeInfo typeInfo;

	typeInfo.type = type;
	switch (type) {
	case VT_BOOLEAN: {
		typeInfo.size = 1;
		break;
	}
	case VT_UINT8: {
		typeInfo.size = 1;
		break;
	}
	case VT_UINT16: {
		typeInfo.size = 2;
		break;
	}
	case VT_UINT32: {
		typeInfo.size = 4;
		break;
	}
	case VT_UINT64: {
		typeInfo.size = 8;
		break;
	}
	case VT_INT8: {
		typeInfo.size = 1;
		break;
	}
	case VT_INT16: {
		typeInfo.size = 2;
		break;
	}
	case VT_INT32: {
		typeInfo.size = 4;
		break;
	}
	case VT_INT64: {
		typeInfo.size = 8;
		break;
	}
	default:
		typeInfo.size = 0;
		break;
	}

	return typeInfo;
}

string Variant::toString() const {
	stringstream val;
	switch (this->vt) {
	case VT_UNKNOWN:
		break;
	case VT_BOOLEAN: {
		val << this->value.valBool;
		break;
	}
	case VT_UINT8: {
		val << (int) this->value.valUint8;
		break;
	}
	case VT_UINT16: {
		val << this->value.valUint16;
		break;
	}
	case VT_UINT32: {
		val << this->value.valUint32;
		break;
	}
	case VT_UINT64: {
		val << this->value.valUint64;
		break;
	}
	case VT_INT8: {
		val << (int) this->value.valInt8;
		break;
	}
	case VT_INT16: {
		val << this->value.valInt16;
		break;
	}
	case VT_INT32: {
		val << this->value.valInt32;
		break;
	}
	case VT_INT64: {
		val << this->value.valInt64;
		break;
	}
	case VT_CARRAY:
	case VT_STRING: {
		val.write((const char*) this->value.valPtr, this->size);
		break;
	}
	}
	return val.str();
}

buffer::Buffer Variant::toBuffer() const {
	buffer::Buffer val;
	switch (this->vt) {
	case VT_UNKNOWN:
		break;
	case VT_BOOLEAN: {
		val << this->value.valBool;
		break;
	}
	case VT_UINT8: {
		val << this->value.valUint8;
		break;
	}
	case VT_UINT16: {
		val << this->value.valUint16;
		break;
	}
	case VT_UINT32: {
		val << this->value.valUint32;
		break;
	}
	case VT_UINT64: {
		val << this->value.valUint64;
		break;
	}
	case VT_INT8: {
		val << this->value.valInt8;
		break;
	}
	case VT_INT16: {
		val << this->value.valInt16;
		break;
	}
	case VT_INT32: {
		val << this->value.valInt32;
		break;
	}
	case VT_INT64: {
		val << this->value.valInt64;
		break;
	}
	case VT_CARRAY:
	case VT_STRING: {
		if (this->size > 0) {
			val.setData((const char*) this->value.valPtr, this->size);
		}
		break;
	}
	}
	return val;
}

void Variant::clear() {
	switch (this->vt) {
	case VT_UNKNOWN:
		break;
	case VT_BOOLEAN: {
		break;
	}
	case VT_UINT8: {
		break;
	}
	case VT_UINT16: {
		break;
	}
	case VT_UINT32: {
		break;
	}
	case VT_UINT64: {
		break;
	}
	case VT_INT8: {
		break;
	}
	case VT_INT16: {
		break;
	}
	case VT_INT32: {
		break;
	}
	case VT_INT64: {
		break;
	}
	case VT_CARRAY:
	case VT_STRING: {
		if (this->value.valPtr) {
			delete[] (char*) this->value.valPtr;
		}
		break;
	}
	}
	this->vt = VT_UNKNOWN;
	this->size = 0;
	memset(&this->value, 0, sizeof(this->value));
}

Variant& Variant::operator=(bool v) {
	this->clear();
	this->vt = VT_BOOLEAN;
	this->size = TypeInfo(this->vt).size;
	this->value.valBool = v;
	return *this;
}

Variant& Variant::operator=(char v) {
	this->clear();
	this->vt = VT_INT8;
	this->size = TypeInfo(this->vt).size;
	this->value.valInt8 = v;
	return *this;
}

Variant& Variant::operator=(short v) {
	this->clear();
	this->vt = VT_INT16;
	this->size = TypeInfo(this->vt).size;
	this->value.valInt16 = v;
	return *this;
}

Variant& Variant::operator=(int v) {
	this->clear();
	this->vt = VT_INT32;
	this->size = TypeInfo(this->vt).size;
	this->value.valInt32 = v;
	return *this;
}

Variant& Variant::operator=(long v) {
	this->operator =((int) v);
	return *this;
}

Variant& Variant::operator=(long long v) {
	this->clear();
	this->vt = VT_INT64;
	this->size = TypeInfo(this->vt).size;
	this->value.valInt64 = v;
	return *this;
}

Variant& Variant::operator=(unsigned char v) {
	this->clear();
	this->vt = VT_UINT8;
	this->size = TypeInfo(this->vt).size;
	this->value.valUint8 = v;
	return *this;
}

Variant& Variant::operator=(unsigned short v) {
	this->clear();
	this->vt = VT_UINT16;
	this->size = TypeInfo(this->vt).size;
	this->value.valUint16 = v;
	return *this;
}

Variant& Variant::operator=(unsigned int v) {
	this->clear();
	this->vt = VT_UINT32;
	this->size = TypeInfo(this->vt).size;
	this->value.valUint32 = v;
	return *this;
}

Variant& Variant::operator=(unsigned long v) {
	this->operator=((unsigned int) v);
	return *this;
}

Variant& Variant::operator=(unsigned long long v) {
	this->clear();
	this->vt = VT_UINT64;
	this->size = TypeInfo(this->vt).size;
	this->value.valUint64 = v;
	return *this;
}

Variant& Variant::operator=(const char* v) {
	this->clear();
	this->vt = VT_STRING;
	this->size = strlen(v);
	this->value.valPtr = new char[this->size];
	memcpy(this->value.valPtr, v, this->size);
	return *this;
}

Variant& Variant::operator=(const string& v) {
	this->operator =(v.c_str());
	return *this;
}

Variant& Variant::operator=(const buffer::Buffer& v) {
	this->clear();
	this->vt = VT_CARRAY;
	if (!v.isEmpty()) {
		this->size = v.getSize();
		this->value.valPtr = new char[this->size];
		memcpy(this->value.valPtr, v.getData(), this->size);
	}
	return *this;
}

unsigned long Variant::getSize() const {
	return size;
}

void Variant::setSize(unsigned long size) {
	if ((VT_CARRAY == this->vt || VT_STRING == this->vt)
			&& (this->size != size)) {
		VariantType t = this->vt;
		this->clear();
		this->vt = t;
		this->size = size;
		this->value.valPtr = new char[this->size];
		memset(this->value.valPtr, 0, this->size);
	}
}

VariantType Variant::getVt() const {
	return vt;
}

void Variant::setVt(VariantType vt) {
	if (this->vt != vt) {
		this->clear();
	}
	this->vt = vt;
	this->size = Variant::TypeInfo(this->vt).size;
}

void Variant::setValue(const void* v) {
	switch (this->vt) {
	case VT_UNKNOWN:
		break;
	case VT_BOOLEAN: {
		memcpy(&this->value.valBool, v, this->size);
		break;
	}
	case VT_UINT8: {
		memcpy(&this->value.valUint8, v, this->size);
		break;
	}
	case VT_UINT16: {
		memcpy(&this->value.valUint16, v, this->size);
		break;
	}
	case VT_UINT32: {
		memcpy(&this->value.valUint32, v, this->size);
		break;
	}
	case VT_UINT64: {
		memcpy(&this->value.valUint64, v, this->size);
		break;
	}
	case VT_INT8: {
		memcpy(&this->value.valInt8, v, this->size);
		break;
	}
	case VT_INT16: {
		memcpy(&this->value.valInt16, v, this->size);
		break;
	}
	case VT_INT32: {
		memcpy(&this->value.valInt32, v, this->size);
		break;
	}
	case VT_INT64: {
		memcpy(&this->value.valInt64, v, this->size);
		break;
	}
	case VT_CARRAY: {
		memcpy(this->value.valPtr, v, this->size);
		break;
	}
	case VT_STRING: {
		if (strlen((const char*) v) != this->size) {
			this->setSize(strlen((const char*) v));
		}
		memcpy(this->value.valPtr, v, this->size);
		break;
	}
	}
}

void Variant::setValue(const void* v, VariantType type) {
	this->setVt(type);
	this->setValue(v);
}

void Variant::setValue(const void* v, const string& typeName) {
	VariantTypeInfo info = TypeInfoFromString(typeName);
	this->setVt(info.type);
	this->setSize(info.size);
	this->setValue(v);
}

template<typename T>
T Variant::toValue() const {
	T val = 0;
	switch (this->vt) {
	case VT_UNKNOWN:
		break;
	case VT_BOOLEAN: {
		val = this->value.valBool;
		break;
	}
	case VT_UINT8: {
		val = this->value.valUint8;
		break;
	}
	case VT_UINT16: {
		val = this->value.valUint16;
		break;
	}
	case VT_UINT32: {
		val = this->value.valUint32;
		break;
	}
	case VT_UINT64: {
		val = this->value.valUint64;
		break;
	}
	case VT_INT8: {
		val = this->value.valInt8;
		break;
	}
	case VT_INT16: {
		val = this->value.valInt16;
		break;
	}
	case VT_INT32: {
		val = this->value.valInt32;
		break;
	}
	case VT_INT64: {
		val = this->value.valInt64;
		break;
	}
	case VT_CARRAY: {
		if (this->size > sizeof(T)) {
			memcpy(&val, this->value.valPtr, sizeof(T));
		}
		break;
	}
	case VT_STRING: {
		stringstream str;
		str.write((const char*) this->value.valPtr, this->size);
		str >> val;
		break;
	}
	}
	return val;
}

Variant::operator bool() const {
	switch (this->vt) {
	case VT_UNKNOWN:
		break;
	case VT_BOOLEAN: {
		return this->value.valBool;
	}
	case VT_UINT8: {
		return (0 != this->value.valUint8);
	}
	case VT_UINT16: {
		return (0 != this->value.valUint16);
	}
	case VT_UINT32: {
		return (0 != this->value.valUint32);
	}
	case VT_UINT64: {
		return (0 != this->value.valUint64);
	}
	case VT_INT8: {
		return (0 != this->value.valInt8);
	}
	case VT_INT16: {
		return (0 != this->value.valInt16);
	}
	case VT_INT32: {
		return (0 != this->value.valInt32);
	}
	case VT_INT64: {
		return (0 != this->value.valInt64);
	}
	case VT_CARRAY:
	case VT_STRING: {
		string val = this->toString();
		if (val.empty() || "0" == val || "false" == val) {
			return false;
		} else {
			return true;
		}
		break;
	}
	}
	return false;
}

Variant::operator char() const {
	return toValue<char>();
}

Variant::operator short() const {
	return toValue<short>();
}

Variant::operator int() const {
	return toValue<int>();
}

Variant::operator long() const {
	return toValue<long>();
}

Variant::operator long long() const {
	return toValue<long long>();
}

Variant::operator unsigned char() const {
	return toValue<unsigned char>();
}

Variant::operator unsigned short() const {
	return toValue<unsigned short>();
}

Variant::operator unsigned int() const {
	return toValue<unsigned int>();
}

Variant::operator unsigned long() const {
	return toValue<unsigned long>();
}

Variant::operator unsigned long long() const {
	return toValue<unsigned long long>();
}

Variant::operator string() const {
	return this->toString();
}

Variant::operator buffer::Buffer() const {
	return this->toBuffer();
}

} /* namespace variant */
} /* namespace ducky */
