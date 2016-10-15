/*
 * Singleton.h
 *
 *  Created on: Oct 15, 2016
 *      Author: ducky
 */

#ifndef DUCKY_SINGLETON_SINGLETON_H_
#define DUCKY_SINGLETON_SINGLETON_H_

#include "ducky/Object.h"

namespace ducky {
namespace singleton {

template<class T>
class Singleton: public Object {
public:
	typedef T type;

	static type* getInstance() {
		if (0 == instance) {
			instance = new type;
		}
		return instance;
	}

private:
	~Singleton() {
	}
	Singleton() {
	}

	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);

	static type* instance;
};

template<class T>
typename Singleton<T>::type* Singleton<T>::instance = 0;

} /* namespace singleton */
} /* namespace ducky */

#endif /* SINGLETON_SINGLETON_H_ */
