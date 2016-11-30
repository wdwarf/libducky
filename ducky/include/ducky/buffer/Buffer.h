/*
 * Buffer.h
 *
 *  Created on: Oct 14, 2016
 *      Author: ducky
 */

#ifndef DUCKY_BUFFER_BUFFER_H_
#define DUCKY_BUFFER_BUFFER_H_

#include <sstream>
#include <ducky/Object.h>
#include <ducky/string/String.h>

using std::string;
using std::ostream;
using std::istream;
using std::stringstream;

namespace ducky {
namespace buffer {

class Buffer: virtual public Object {
public:
	Buffer();
	Buffer(unsigned int initSize);
	Buffer(const char* data, unsigned int size);
	Buffer(const Buffer& buffer);
	virtual ~Buffer();

	Buffer& operator=(const Buffer& buffer);
	Buffer operator+(const Buffer& buffer);
	char& operator[](unsigned index);

	void append(const char* data, unsigned int size);
	void append(const Buffer& buffer);

	void setData(const char* data, unsigned int size);
	char* getData() const;
	unsigned int getSize() const;
	void clear();
	bool isEmpty() const;

	StdString toString() const;
	stringstream& getBufferStream();

private:
	class BufferImpl;
	BufferImpl* impl;
}; /* class Buffer */

} /* namespace buffer */
} /* namespace ducky */

ostream& operator<<(ostream& o, ducky::buffer::Buffer& buffer);
ducky::buffer::Buffer& operator<<(ducky::buffer::Buffer& buffer, istream& i);
ducky::buffer::Buffer& operator<<(ducky::buffer::Buffer& buffer, ducky::StdString& str);
ducky::buffer::Buffer& operator<<(ducky::buffer::Buffer& buffer,
		const char* str);

template<class T>
ducky::buffer::Buffer& operator<<(ducky::buffer::Buffer& buffer, T& t) {
	buffer.append((const char*) &t, sizeof(T));
	return buffer;
}

template<class T>
T& operator<<(T& t, ducky::buffer::Buffer& buffer) {
	buffer.getBufferStream() >> t;
	return t;
}

template<class T>
ducky::buffer::Buffer& operator>>(ducky::buffer::Buffer& buffer, T& t) {
	buffer.getBufferStream() >> t;
	return buffer;
}

template<class T>
T& operator>>(T& t, ducky::buffer::Buffer& buffer) {
	buffer.append((const char*) &t, sizeof(T));
	return t;
}

#endif /* BUFFER_WBUFFER_H_ */
