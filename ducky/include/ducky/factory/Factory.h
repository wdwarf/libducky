#ifndef _DUCKY_Factory_H_
#define _DUCKY_Factory_H_

#include <string>
#include <ducky/Object.h>
#include <map>
#include <ducky/exception/Exception.h>
#include <ducky/thread/Mutex.h>

using std::string;
using std::map;

namespace ducky
{
namespace factory
{

EXCEPTION_DEF(FactoryException);

// 构造类
// Interface 接口，T为具体类
template<typename T, bool IsSingleton = false>
class ConcreteCreator
{
public:
    static void* createObject()
    {
    	if(singleton){
    		static T* obj = 0;
    		if(!obj){
    			obj = new T();
    		}
    		return obj;
    	}
    	else{
    		return new T();
    	}
    }

private:
    static const bool singleton = IsSingleton;
};

// 工厂类接口
class Factory: virtual public Object
{
public:
	virtual ~Factory(){}

	void* createObject(string className)
	{
		thread::MutexLocker lk(this->mutex);
		map<string, Creator>::iterator it = this->creatorMap.find(className);
		if(it != this->creatorMap.end())
		{
			return it->second();
		}

		throw FactoryException("Class \"" + className + "\" Not Registered");
	}

	template<typename T>
	T* createObject(string className)
	{
		thread::MutexLocker lk(this->mutex);
		map<string, Creator>::iterator it = this->creatorMap.find(className);
		if(it != this->creatorMap.end())
		{
			return (T*)it->second();
		}

		throw FactoryException("Class \"" + className + "\" Not Registered");
	}

	template<typename T>
	void regiesterCreator(string className, bool isSingleton = false)
	{
		thread::MutexLocker lk(this->mutex);
		map<string, Creator>::iterator it = this->creatorMap.find(className);
		if(it == this->creatorMap.end())
		{
			if(isSingleton){
				this->creatorMap.insert(make_pair(className, (Creator)ConcreteCreator<T, true>::createObject));
			}
			else{
				this->creatorMap.insert(make_pair(className, (Creator)ConcreteCreator<T, false>::createObject));
			}
		}
		else
		{
			if(isSingleton){
				it->second = ConcreteCreator<T, true>::createObject;
			}else{
				it->second = ConcreteCreator<T, false>::createObject;
			}
		}
	}

	void unregiesterCreator(string className)
	{
		thread::MutexLocker lk(this->mutex);
		map<string, Creator>::iterator it = this->creatorMap.find(className);
		if(it != this->creatorMap.end())
		{
			this->creatorMap.erase(it);
		}
	}

private:
	typedef void* (*Creator)();
	map<string, Creator> creatorMap;
	thread::Mutex mutex;
};

}
}
#endif
