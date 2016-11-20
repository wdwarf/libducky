#ifndef _DUCKY_Factory_H_
#define _DUCKY_Factory_H_

#include <ducky/Object.h>
#include <string>
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
// Interface 接口，Type为具体类
template<typename Type>
class ConcreteCreator
{
public:
    static void* createObject()
    {
        return new Type();
    }
};

// 工厂类接口
class Factory: public Object
{
public:
	virtual ~Factory(){}

	virtual void* createObject(string className)
	{
		map<string, Creator>::iterator it = this->creatorMap.find(className);
		if(it != this->creatorMap.end())
		{
			return it->second();
		}

		throw FactoryException("Class \"" + className + "\" Not Registered");
	}

	typedef void* (*Creator)();
	template<typename Type>
	void regiesterCreator(string className)
	{
		map<string, Creator>::iterator it = this->creatorMap.find(className);
		if(it == this->creatorMap.end())
		{
			this->creatorMap.insert(make_pair(className, (Creator)ConcreteCreator<Type>::createObject));
		}
		else
		{
			it->second = ConcreteCreator<Type>::createObject;
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
	map<string, Creator> creatorMap;
};

}
}
#endif
