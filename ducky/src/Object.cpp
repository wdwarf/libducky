/*
 * WObject.cpp
 *
 *  Created on: Oct 14, 2016
 *      Author: ducky
 */

#include "ducky/Object.h"
#include <typeinfo>
#include <sstream>
#include <iostream>
#include <cstring>
#include <set>
#include <pthread.h>

using namespace std;

namespace ducky {

static set<const void*> __heabObjs__;
static pthread_mutex_t __obj_onheap_mutex__;
static bool __obj_onheap_mutex_inited__ = false;

Object::Object() {
	// TODO Auto-generated constructor stub
	if (!__obj_onheap_mutex_inited__) {
		__obj_onheap_mutex_inited__ = true;
		pthread_mutex_init(&__obj_onheap_mutex__, NULL);
	}
}

Object::~Object() {
	// TODO Auto-generated destructor stub
}

std::string Object::getClassName() const {
	std::string className;
	std::string fullName = typeid(*this).name();

	if ('N' == fullName[0]) {
		fullName = fullName.substr(1, fullName.length());
		int len = 0;
		do {
			stringstream str;
			str << fullName;
			str >> len;
			if (len > 0) {
				stringstream sLen;
				sLen << len;
				int pos = sLen.str().length();
				int partLen = pos + len;

				if (className.empty()) {
					className = fullName.substr(pos, len);
				} else {
					className += "::" + fullName.substr(pos, len);
				}
				fullName = fullName.substr(partLen,
						fullName.length() - partLen);
			}
		} while (len > 0);
	} else {
		stringstream str;
		str << fullName;
		int len = 0;
		str >> len;

		str.clear();
		str.str("");
		str << len;

		if (len > 0)
			className = fullName.substr(str.str().length(), len);
	}

	return className;
}

bool Object::isOnHeap() const {
	bool isOnHeap = false;
	pthread_mutex_lock(&__obj_onheap_mutex__);
	const void* rawThisAddr = dynamic_cast<const void*>(this);
	if (__heabObjs__.find(rawThisAddr) != __heabObjs__.end()) {
		isOnHeap = true;
	}
	pthread_mutex_unlock(&__obj_onheap_mutex__);
	return isOnHeap;
}

void* Object::operator new(std::size_t size) throw (std::bad_alloc) {
	if (!__obj_onheap_mutex_inited__) {
		__obj_onheap_mutex_inited__ = true;
		pthread_mutex_init(&__obj_onheap_mutex__, NULL);
	}

	void* p = ::operator new(size);
	pthread_mutex_lock(&__obj_onheap_mutex__);
	__heabObjs__.insert(p);
	pthread_mutex_unlock(&__obj_onheap_mutex__);
	return p;
}

void* Object::operator new(size_t size, const std::nothrow_t&) throw () {
	if (!__obj_onheap_mutex_inited__) {
		__obj_onheap_mutex_inited__ = true;
		pthread_mutex_init(&__obj_onheap_mutex__, NULL);
	}

	void* p = ::operator new(size);
	pthread_mutex_lock(&__obj_onheap_mutex__);
	__heabObjs__.insert(p);
	pthread_mutex_unlock(&__obj_onheap_mutex__);
	return p;
}

void* Object::operator new(std::size_t size, void *ptr) throw () {
	if (!__obj_onheap_mutex_inited__) {
		__obj_onheap_mutex_inited__ = true;
		pthread_mutex_init(&__obj_onheap_mutex__, NULL);
	}

	void* p = ::operator new(size);
	pthread_mutex_lock(&__obj_onheap_mutex__);
	__heabObjs__.insert(p);
	pthread_mutex_unlock(&__obj_onheap_mutex__);
	return p;
}

void Object::operator delete(void* ptr) {
	if (0 == ptr)
		return;

	pthread_mutex_lock(&__obj_onheap_mutex__);
	if (__heabObjs__.find(ptr) != __heabObjs__.end()) {
		__heabObjs__.erase(ptr);
	}
	pthread_mutex_unlock(&__obj_onheap_mutex__);
	::operator delete(ptr);
}

void Object::deleteThis() {
	if (!this->isOnHeap()) {
		return;
	}

	delete this;
}

} /* namespace ducky */
