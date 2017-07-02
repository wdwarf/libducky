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

class _ICreator {
public:
	_ICreator() {
	}
	virtual ~_ICreator() {
	}
	virtual void* createObject() = 0;
	virtual bool IsSingleton() = 0;
};

// 构造类，T为具体类
template<typename T>
class _NewCreator: public _ICreator {
public:
	virtual void* createObject() {
		return new T();
	}

	virtual bool IsSingleton() {
		return false;
	}
};

template<typename T>
class _SingletonCreator: public _ICreator {
public:
	_SingletonCreator() :
			obj(NULL) {
	}

	virtual void* createObject() {
		if (!obj) {
			obj = new T();
		}
		return obj;
	}

	virtual bool IsSingleton() {
		return true;
	}

	~_SingletonCreator() {
		if (this->obj)
			delete this->obj;
	}

private:
	T* obj;
};

// 工厂类接口
class Factory: virtual public Object {
public:
	Factory() {
	}

	virtual ~Factory() {
		thread::MutexLocker lk(this->mutex);
		for (CreatorMap::iterator it = this->creatorMap.begin();
				it != this->creatorMap.end(); ++it) {
			delete it->second;
		}
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
						make_pair(className, new _SingletonCreator<T>()));
			} else {
				this->creatorMap.insert(
						make_pair(className, new _NewCreator<T>()));
			}
		} else {
			_THROW(FactoryException,
					"Class \"" + className + "\" Has Registered", 0);
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

	//创建对象
	void* createObject(string className) {
		thread::MutexLocker lk(this->mutex);
		CreatorMap::iterator it = this->creatorMap.find(className);
		if (it != this->creatorMap.end()) {
			return it->second->createObject();
		}

		_THROW(FactoryException, "Class \"" + className + "\" Not Registered",
				0);
	}

	//创建对象，并强转为T类指针
	template<typename T>
	T* createObject(string className) {
		thread::MutexLocker lk(this->mutex);
		CreatorMap::iterator it = this->creatorMap.find(className);
		if (it != this->creatorMap.end()) {
			return (T*) it->second->createObject();
		}

		_THROW(FactoryException, "Class \"" + className + "\" Not Registered",
				0);
	}

	//查询指定类是否是单例
	bool isSingletonObject(string className) {
		thread::MutexLocker lk(this->mutex);
		CreatorMap::iterator it = this->creatorMap.find(className);
		if (it != this->creatorMap.end()) {
			return it->second->IsSingleton();
		}

		_THROW(FactoryException, "Class \"" + className + "\" Not Registered",
				0);
	}

private:
	typedef map<string, _ICreator*> CreatorMap;
	CreatorMap creatorMap;
	thread::Mutex mutex;
};

}
}
#endif
