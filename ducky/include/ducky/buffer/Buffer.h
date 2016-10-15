/*
 * Buffer.h
 *
 *  Created on: Oct 14, 2016
 *      Author: ducky
 */

#ifndef DUCKY_BUFFER_BUFFER_H_
#define DUCKY_BUFFER_BUFFER_H_

#include <string>
#include <ostream>
#include "ducky/Object.h"

using std::string;
using std::ostream;

namespace ducky {
namespace buffer {

class Buffer : public Object {
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

	string toString() const;

private:
	class BufferImpl;
	BufferImpl* impl;
};


} /* namespace buffer */
} /* namespace ducky */

ostream& operator<<(ostream& o, const ducky::buffer::Buffer& buffer);

#endif /* BUFFER_WBUFFER_H_ */
