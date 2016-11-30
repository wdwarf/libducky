#ifndef _DUCKY_Factory_H_
#define _DUCKY_Factory_H_

#include <string>
#include <ducky/Object.h>
#include <map>
#include <ducky/exception/Exception.h>

using std::string;
using std::map;

namespace ducky
{
namespace factory
{

EXCEPTION_DEF(FactoryException);

// 构造类
// Interface 接口，T为具体类
template<typename T>
class ConcreteCreator
{
public:
    static void* createObject()
    {
        return new T();
    }
};

// 工厂类接口
class Factory: virtual public Object
{
public:
	virtual ~Factory(){}

	void* createObject(string className)
	{
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
		map<string, Creator>::iterator it = this->creatorMap.find(className);
		if(it != this->creatorMap.end())
		{
			return (T*)it->second();
		}

		throw FactoryException("Class \"" + className + "\" Not Registered");
	}

	template<typename T>
	void regiesterCreator(string className)
	{
		map<string, Creator>::iterator it = this->creatorMap.find(className);
		if(it == this->creatorMap.end())
		{
			this->creatorMap.insert(make_pair(className, (Creator)ConcreteCreator<T>::createObject));
		}
		else
		{
			it->second = ConcreteCreator<T>::createObject;
		}
	}

	void unregiesterCreator(string className)
	{
		map<string, Creator>::iterator it = this->creatorMap.find(className);
		if(it != this->creatorMap.end())
		{
			this->creatorMap.erase(it);
		}
	}

private:
	typedef void* (*Creator)();
	map<string, Creator> creatorMap;
};

}
}
#endif
