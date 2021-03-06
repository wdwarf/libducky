/*
 * Buffer.cpp
 *
 *  Created on: Oct 14, 2016
 *      Author: ducky
 */

#include <ducky/buffer/Buffer.h>

#include <iostream>
#include <cstring>
#include <sstream>
#include <vector>

using namespace std;

namespace ducky {
namespace buffer {

const static float BUF_INC_RATIO = 1.5;

#define BUF_IN_OPERATOR_IMPL(T) ducky::buffer::Buffer& ducky::buffer::Buffer::operator<<(const T& t) {\
		this->append((const char*) &t, sizeof(T));\
		return *this;\
}

#define BUF_OUT_OPERATOR_IMPL(T) ducky::buffer::Buffer& ducky::buffer::Buffer::operator>>(T& t) {\
		this->read((void*)&t, sizeof(t));\
		return *this;\
}

/* Buffer::BufferImpl */
class Buffer::BufferImpl {
public:
	BufferImpl();
	BufferImpl(unsigned int initSize);
	BufferImpl(const char* data, unsigned int size);
	BufferImpl(const BufferImpl& buffer);
	virtual ~BufferImpl();

	BufferImpl& operator=(const BufferImpl& buffer);
	BufferImpl operator+(const BufferImpl& buffer) const;
	char& operator[](unsigned index);
	const char& operator[](unsigned index) const;

	void append(const char* data, unsigned int size);
	void append(const BufferImpl& buffer);

	void setData(const char* data, unsigned int size);
	char* getData() const;
	unsigned int getSize() const;
	void resize(unsigned int size);
	void clear();
	bool isEmpty() const;
	void reverse();
	void alloc(unsigned int size);
	unsigned int getCapacity() const;
	void zero();

	string toString();
	int read(void* buf, unsigned int size) const;
	void resetReadPos() const;

private:
	char* data;
	unsigned int size;
	unsigned int capacity;
	mutable unsigned int readPos;
};

Buffer::BufferImpl::BufferImpl() :
		data(NULL), size(0), capacity(0), readPos(0) {

}

Buffer::BufferImpl::BufferImpl(unsigned int initSize) :
		data(NULL), size(0), capacity(0), readPos(0) {
	this->alloc(initSize);
}

Buffer::BufferImpl::BufferImpl(const char* data, unsigned int size) :
		data(NULL), size(0), capacity(0), readPos(0) {
	this->setData(data, size);
}

Buffer::BufferImpl::BufferImpl(const Buffer::BufferImpl& buffer) :
		data(NULL), size(0), capacity(0), readPos(0) {
	this->setData(buffer.getData(), buffer.getSize());
}

int Buffer::BufferImpl::read(void* buf, unsigned int size) const {
	long avaliableSize = this->getSize() - this->readPos;
	if (avaliableSize <= 0)
		return 0;

	unsigned int readSzie = avaliableSize > size ? size : avaliableSize;
	memcpy(buf, this->data + this->readPos, readSzie);
	this->readPos += readSzie;
	return readSzie;
}

void Buffer::BufferImpl::zero() {
	if (this->capacity > 0) {
		memset(this->data, 0, this->capacity);
	}
}

void Buffer::BufferImpl::resetReadPos() const {
	this->readPos = 0;
}

Buffer::BufferImpl& Buffer::BufferImpl::operator=(
		const Buffer::BufferImpl& buffer) {
	this->setData(buffer.getData(), buffer.getSize());
	return *this;
}

Buffer::BufferImpl Buffer::BufferImpl::operator+(
		const Buffer::BufferImpl& buffer) const {
	Buffer::BufferImpl newBuffer;
	newBuffer.append(*this);
	newBuffer.append(buffer);
	return newBuffer;
}

void Buffer::BufferImpl::append(const char* data, unsigned int size) {
	if ((NULL == data) || (size <= 0))
		return;

	unsigned int reserveSize = this->capacity - this->size;
	if (size <= reserveSize) {
		memcpy(this->data + this->size, data, size);
		this->size += size;
		return;
	}

	this->capacity = (this->size + size) * BUF_INC_RATIO;
	char* newData = new char[this->capacity];
	memcpy(newData, this->data, this->size);
	memcpy(newData + this->size, data, size);

	if (NULL != this->data)
		delete[] this->data;
	this->data = newData;
	this->size += size;
}

void Buffer::BufferImpl::append(const BufferImpl& buffer) {
	this->append(buffer.data, buffer.size);
}

void Buffer::ReverseBytes(char* buf, int size) {
	if (!buf || (size <= 0)) {
		return;
	}

	char* pH = buf;
	char* pE = buf + size - 1;
	while (pH < pE) {
		char c = *pH;
		*pH = *pE;
		*pE = c;
		++pH;
		--pE;
	}
}

void Buffer::BufferImpl::reverse() {
	Buffer::ReverseBytes(this->data, this->size);

	this->resetReadPos();
}

void Buffer::BufferImpl::alloc(unsigned int size) {
	this->clear();

	if (size <= 0) {
		return;
	}

	this->size = size;
	this->capacity = this->size * BUF_INC_RATIO;
	this->data = new char[this->capacity];
	if (!this->data) {
		this->size = 0;
		throw MK_EXCEPTION(BufferException, "Alloc buffer failed", size);
	}
	this->zero();

	this->resetReadPos();
}

unsigned int Buffer::BufferImpl::getCapacity() const {
	return this->capacity;
}

char& Buffer::BufferImpl::operator[](unsigned index) {
	if (index >= this->size) {
		THROW_EXCEPTION(BufferException, "Index out of bound.", this->size);
	}
	return this->data[index];
}

const char& Buffer::BufferImpl::operator[](unsigned index) const {
	if (index >= this->size) {
		THROW_EXCEPTION(BufferException, "Index out of bound.", this->size);
	}
	return this->data[index];
}

void Buffer::BufferImpl::setData(const char* data, unsigned int size) {
	char* oldData = this->data;
	if ((NULL != data) && (size > 0)) {
		this->size = size;
		this->capacity = this->size * BUF_INC_RATIO;
		this->data = new char[this->capacity];
		if (!this->data) {
			this->size = 0;
			throw MK_EXCEPTION(BufferException, "Alloc buffer failed", size);
		}
		memcpy(this->data, data, this->size);
	} else {
		this->size = 0;
		this->data = NULL;
		this->capacity = 0;
	}

	this->resetReadPos();

	if (oldData)
		delete[] oldData;
}

Buffer::BufferImpl::~BufferImpl() {
	this->clear();
}

void Buffer::setData(const char* data, unsigned int size) {
	this->impl->setData(data, size);
}

char* Buffer::BufferImpl::getData() const {
	return this->data;
}

unsigned int Buffer::BufferImpl::getSize() const {
	return this->size;
}

void Buffer::BufferImpl::resize(unsigned int size) {
	if (this->capacity >= size) {
		this->size = size;
		return;
	}

	this->capacity = size * BUF_INC_RATIO;
	char* newData = new char[this->capacity];
	if (!newData) {
		this->size = 0;
		throw MK_EXCEPTION(BufferException, "Alloc buffer failed", size);
	}
	memcpy(newData, this->data, size);

	if (NULL != this->data)
		delete[] this->data;
	this->data = newData;
	this->size = size;
}

void Buffer::BufferImpl::clear() {
	if (NULL != this->data) {
		delete[] this->data;
		this->data = NULL;
		this->size = 0;
		this->capacity = 0;

		this->resetReadPos();
	}
}

bool Buffer::BufferImpl::isEmpty() const {
	return (NULL == this->data);
}

string Buffer::BufferImpl::toString() {
	stringstream strBuf;
	if (!this->isEmpty()) {
		unsigned char* data = (unsigned char*) this->getData();
		unsigned int size = this->getSize();

		strBuf.fill('0');
		for (unsigned int i = 0; i < size; ++i) {
			strBuf.width(2);
			strBuf << hex << (int) data[i] << " ";
		}
	}

	return strBuf.str();
}

/* end of Buffer::BufferImpl */

Buffer::Buffer() :
		impl(new Buffer::BufferImpl()) {

}

Buffer::Buffer(unsigned int initSize) :
		impl(new Buffer::BufferImpl(initSize)) {
}

Buffer::Buffer(const char* data, unsigned int size) :
		impl(new Buffer::BufferImpl(data, size)) {
}

Buffer::Buffer(const Buffer& buffer) :
		impl(new Buffer::BufferImpl(*buffer.impl)) {
}

Buffer& Buffer::operator=(const Buffer& buffer) {
	*this->impl = *buffer.impl;
	return *this;
}

Buffer& Buffer::operator+=(const Buffer& buffer) {
	this->append(buffer);
	return *this;
}

Buffer Buffer::operator+(const Buffer& buffer) const {
	Buffer newBuffer;
	newBuffer.append(*this);
	newBuffer.append(buffer);
	return newBuffer;
}

void Buffer::append(const char* data, unsigned int size) {
	this->impl->append(data, size);
}

void Buffer::append(const Buffer& buffer) {
	this->impl->append(*buffer.impl);
}

char& Buffer::operator[](unsigned index) {
	return this->impl->operator [](index);
}

const char& Buffer::operator[](unsigned index) const {
	return this->impl->operator [](index);
}

Buffer::~Buffer() {
	if (NULL != this->impl) {
		delete this->impl;
	}
}

char* Buffer::getData() const {
	return this->impl->getData();
}

unsigned int Buffer::getSize() const {
	return this->impl->getSize();
}

void Buffer::resize(unsigned int size) {
	this->impl->resize(size);
}

void Buffer::clear() {
	this->impl->clear();
}

bool Buffer::isEmpty() const {
	return this->impl->isEmpty();
}

string Buffer::toString() const {
	return this->impl->toString();
}

Buffer& Buffer::reverse() {
	this->impl->reverse();
	return *this;
}

void Buffer::alloc(unsigned int size) {
	this->impl->alloc(size);
}

unsigned int Buffer::getCapacity() const {
	return this->impl->getCapacity();
}

void Buffer::zero() {
	this->impl->zero();
}

int Buffer::read(void* buf, unsigned int size) const {
	return this->impl->read(buf, size);
}

void Buffer::resetReadPos() const {
	this->impl->resetReadPos();
}

Buffer& Buffer::operator<<(const Buffer& in_buffer) {
	this->append(in_buffer);
	return *this;
}

Buffer& Buffer::operator<<(istream& i) {
	istream::pos_type pos = i.tellg();
	i.seekg(0, ios::end);
	istream::pos_type endPos = i.tellg();
	i.seekg(pos, ios::beg);
	istream::pos_type len = endPos - pos;
	vector<char> v(len);
	i.read(&v[0], len);
	this->append(&v[0], len);

	return *this;
}

Buffer& Buffer::operator<<(const string& s) {
	this->append(s.c_str(), s.length());
	return *this;
}

BUF_IN_OPERATOR_IMPL(long long);
BUF_IN_OPERATOR_IMPL(long);
BUF_IN_OPERATOR_IMPL(int);
BUF_IN_OPERATOR_IMPL(short);
BUF_IN_OPERATOR_IMPL(char);
BUF_IN_OPERATOR_IMPL(unsigned long long);
BUF_IN_OPERATOR_IMPL(unsigned long);
BUF_IN_OPERATOR_IMPL(unsigned int);
BUF_IN_OPERATOR_IMPL(unsigned short);
BUF_IN_OPERATOR_IMPL(unsigned char);
BUF_IN_OPERATOR_IMPL(float);
BUF_IN_OPERATOR_IMPL(double);

BUF_OUT_OPERATOR_IMPL(long long);
BUF_OUT_OPERATOR_IMPL(long);
BUF_OUT_OPERATOR_IMPL(int);
BUF_OUT_OPERATOR_IMPL(short);
BUF_OUT_OPERATOR_IMPL(char);
BUF_OUT_OPERATOR_IMPL(unsigned long long);
BUF_OUT_OPERATOR_IMPL(unsigned long);
BUF_OUT_OPERATOR_IMPL(unsigned int);
BUF_OUT_OPERATOR_IMPL(unsigned short);
BUF_OUT_OPERATOR_IMPL(unsigned char);
BUF_OUT_OPERATOR_IMPL(float);
BUF_OUT_OPERATOR_IMPL(double);

} /* namespace buffer */
} /* namespace ducky */

ostream& operator<<(ostream& o, const ducky::buffer::Buffer& buffer) {
	o << buffer.toString();
	return o;
}

