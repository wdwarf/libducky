/*
 * Buffer.h
 *
 *  Created on: Oct 14, 2016
 *      Author: ducky
 */

#ifndef DUCKY_BUFFER_BUFFER_H_
#define DUCKY_BUFFER_BUFFER_H_

#include <string>
#include <sstream>
#include <ducky/Object.h>
#include <ducky/exception/Exception.h>

using std::string;
using std::ostream;
using std::istream;

namespace ducky {
namespace buffer {

EXCEPTION_DEF(BufferException)

#define BUF_IN_OPERATOR_DEF(T) ducky::buffer::Buffer& operator<<(const T& t)
#define BUF_OUT_OPERATOR_DEF(T) ducky::buffer::Buffer& operator>>(T& t)

class Buffer: virtual public Object {
public:
	Buffer();
	Buffer(unsigned int initSize);
	Buffer(const char* data, unsigned int size);
	Buffer(const Buffer& buffer);
	virtual ~Buffer();

	Buffer& operator=(const Buffer& buffer);
	Buffer& operator+=(const Buffer& buffer);
	Buffer operator+(const Buffer& buffer) const;
	char& operator[](unsigned index);
	const char& operator[](unsigned index) const;

	void append(const char* data, unsigned int size);
	void append(const Buffer& buffer);

	void setData(const char* data, unsigned int size);
	char* getData() const;
	unsigned int getSize() const;
	void clear();
	bool isEmpty() const;
	Buffer& reverse();
	void alloc(unsigned int size);
	unsigned int capacity() const;
	void zero();

	string toString() const;
	int read(void* buf, unsigned int size) const;
	void resetReadPos() const;

	BUF_IN_OPERATOR_DEF(long long);
	BUF_IN_OPERATOR_DEF(long);
	BUF_IN_OPERATOR_DEF(int);
	BUF_IN_OPERATOR_DEF(short);
	BUF_IN_OPERATOR_DEF(char);
	BUF_IN_OPERATOR_DEF(unsigned long long);
	BUF_IN_OPERATOR_DEF(unsigned long);
	BUF_IN_OPERATOR_DEF(unsigned int);
	BUF_IN_OPERATOR_DEF(unsigned short);
	BUF_IN_OPERATOR_DEF(unsigned char);
	BUF_IN_OPERATOR_DEF(float);
	BUF_IN_OPERATOR_DEF(double);

	BUF_OUT_OPERATOR_DEF(long long);
	BUF_OUT_OPERATOR_DEF(long);
	BUF_OUT_OPERATOR_DEF(int);
	BUF_OUT_OPERATOR_DEF(short);
	BUF_OUT_OPERATOR_DEF(char);
	BUF_OUT_OPERATOR_DEF(unsigned long long);
	BUF_OUT_OPERATOR_DEF(unsigned long);
	BUF_OUT_OPERATOR_DEF(unsigned int);
	BUF_OUT_OPERATOR_DEF(unsigned short);
	BUF_OUT_OPERATOR_DEF(unsigned char);
	BUF_OUT_OPERATOR_DEF(float);
	BUF_OUT_OPERATOR_DEF(double);

	ducky::buffer::Buffer& operator<<(const ducky::buffer::Buffer& in_buffer);
	ducky::buffer::Buffer& operator<<(istream& i);
	ducky::buffer::Buffer& operator<<(const std::string& s);

	static void ReverseBytes(char* buf, int size);
private:
	class BufferImpl;
	BufferImpl* impl;
};
/* class Buffer */

} /* namespace buffer */
} /* namespace ducky */

ostream& operator<<(ostream& o, const ducky::buffer::Buffer& buffer);

#endif /* DUCKY_BUFFER_BUFFER_H_ */
