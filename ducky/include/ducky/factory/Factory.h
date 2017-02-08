#ifndef _DUCKY_Factory_H_
#define _DUCKY_Factory_H_

#include <string>
#include <ducky/Object.h>
#include <map>
#include <ducky/exception/Exception.h>
#include <ducky/thread/Mutex.h>

using std::string;
using std::map;

namespace ducky {
namespace factory {

/*
 * Sample:
 *
 * Factory objFactory;
 * objFactory.regiesterCreator<string>("string");
 * string* str = (string*)objFactory.createObject("string");
 * string* str2 = objFactory.createObject<string>("string");
 *
 * delete str;
 * delete str2;
 */

EXCEPTION_DEF(FactoryException);

class _IConcreateCreator {
public:
	_IConcreateCreator() {
	}
	virtual ~_IConcreateCreator() {
	}
	virtual void* createObject() = 0;
	virtual bool IsSingleton() = 0;
};

// 构造类，T为具体类
template<typename T, bool PSingleton = false>
class _ConcreteCreator: public _IConcreateCreator {
public:
	virtual void* createObject() {
		if (singleton) {
			static T* obj = 0;
			if (!obj) {
				obj = new T();
			}
			return obj;
		} else {
			return new T();
		}
	}

	virtual bool IsSingleton() {
		return singleton;
	}

private:
	static const bool singleton = PSingleton;
};

// 工厂类接口
class Factory: virtual public Object {
public:
	Factory() {
	}
	virtual ~Factory() {
	}

	//创建对象
	void* createObject(string className) {
		thread::MutexLocker lk(this->mutex);
		CreatorMap::iterator it = this->creatorMap.find(className);
		if (it != this->creatorMap.end()) {
			return it->second->createObject();
		}

		throw FactoryException("Class \"" + className + "\" Not Registered");
	}

	//创建对象，并强转为T类指针
	template<typename T>
	T* createObject(string className) {
		thread::MutexLocker lk(this->mutex);
		CreatorMap::iterator it = this->creatorMap.find(className);
		if (it != this->creatorMap.end()) {
			return (T*) it->second->createObject();
		}

		throw MK_EXCEPTION(FactoryException, "Class \"" + className + "\" Not Registered", 0);
	}

	//查询指定类是否是单例
	bool isSingletonObject(string className) {
		thread::MutexLocker lk(this->mutex);
		CreatorMap::iterator it = this->creatorMap.find(className);
		if (it != this->creatorMap.end()) {
			return it->second->IsSingleton();
		}

		throw MK_EXCEPTION(FactoryException, "Class \"" + className + "\" Not Registered", 0);
	}

	/*
	 * 注册构造类
	 * 注册后便可调用createObject方法构造类T的对象。
	 */
	template<typename T>
	void regiesterCreator(string className, bool isSingleton = false) {
		thread::MutexLocker lk(this->mutex);
		CreatorMap::iterator it = this->creatorMap.find(className);
		if (it == this->creatorMap.end()) {
			if (isSingleton) {
				this->creatorMap.insert(
						make_pair(className, new _ConcreteCreator<T, true>()));
			} else {
				this->creatorMap.insert(
						make_pair(className, new _ConcreteCreator<T, false>()));
			}
		} else {
			delete it->second;
			if (isSingleton) {
				it->second = new _ConcreteCreator<T, true>();
			} else {
				it->second = new _ConcreteCreator<T, false>();
			}
		}
	}

	/*
	 * 反注册指定类
	 */
	void unregiesterCreator(string className) {
		thread::MutexLocker lk(this->mutex);
		CreatorMap::iterator it = this->creatorMap.find(className);
		if (it != this->creatorMap.end()) {
			delete it->second;
			this->creatorMap.erase(it);
		}
	}

private:
	typedef map<string, _IConcreateCreator*> CreatorMap;
	CreatorMap creatorMap;
	thread::Mutex mutex;
};

}
}
#endif
