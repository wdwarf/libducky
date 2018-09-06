/*
 * Function.h
 *
 *  Created on: Nov 5, 2016
 *      Author: ducky
 */

#ifndef DUCKY_FUNCTION_FUNCTION_H_
#define DUCKY_FUNCTION_FUNCTION_H_

#include <ducky/function/FunctionException.h>
#include <cassert>
#include <iostream>

using namespace std;

namespace ducky {
namespace function {

template<class R>
struct IFunction0 {
	typedef IFunction0<R> ThisType;
	virtual ~IFunction0() {
	}
	virtual R operator()() = 0;
	virtual bool equals(const ThisType* i) const = 0;
	virtual bool isMemberFunction() const = 0;
	bool operator==(const ThisType& i) const {
		return this->equals(&i);
	}
	virtual ThisType* clone() = 0;
};

template<class R, class P1>
struct IFunction1 {
	typedef IFunction1<R, P1> ThisType;
	virtual ~IFunction1() {
	}
	virtual R operator()(const P1&) = 0;
	virtual bool equals(const ThisType* i) const = 0;
	virtual bool isMemberFunction() const = 0;
	bool operator==(const ThisType& i) const {
		return this->equals(&i);
	}
	virtual ThisType* clone() = 0;
};

template<class R, class P1, class P2>
struct IFunction2 {
	typedef IFunction2<R, P1, P2> ThisType;
	virtual ~IFunction2() {
	}
	virtual R operator()(const P1&, const P2&) = 0;
	virtual bool equals(const ThisType* i) const = 0;
	virtual bool isMemberFunction() const = 0;
	bool operator==(const ThisType& i) const {
		return this->equals(&i);
	}
	virtual ThisType* clone() = 0;
};

template<class R, class P1, class P2, class P3>
struct IFunction3 {
	typedef IFunction3<R, P1, P2, P3> ThisType;
	virtual ~IFunction3() {
	}
	virtual R operator()(const P1&, const P2&, const P3&) = 0;
	virtual bool equals(const ThisType* i) const = 0;
	virtual bool isMemberFunction() const = 0;
	bool operator==(const ThisType& i) const {
		return this->equals(&i);
	}
	virtual ThisType* clone() = 0;
};

template<class R, class P1, class P2, class P3, class P4>
struct IFunction4 {
	typedef IFunction4<R, P1, P2, P3, P4> ThisType;
	virtual ~IFunction4() {
	}
	virtual R operator()(const P1&, const P2&, const P3&, const P4&) = 0;
	virtual bool equals(const ThisType* i) const = 0;
	virtual bool isMemberFunction() const = 0;
	bool operator==(const ThisType& i) const {
		return this->equals(&i);
	}
	virtual ThisType* clone() = 0;
};

template<class R, class P1, class P2, class P3, class P4, class P5>
struct IFunction5 {
	typedef IFunction5<R, P1, P2, P3, P4, P5> ThisType;
	virtual ~IFunction5() {
	}
	virtual R operator()(const P1&, const P2&, const P3&, const P4&, const P5&) = 0;
	virtual bool equals(const ThisType* i) const = 0;
	virtual bool isMemberFunction() const = 0;
	bool operator==(const ThisType& i) const {
		return this->equals(&i);
	}
	virtual ThisType* clone() = 0;
};

template<class R, class P1, class P2, class P3, class P4, class P5, class P6>
struct IFunction6 {
	typedef IFunction6<R, P1, P2, P3, P4, P5, P6> ThisType;
	virtual ~IFunction6() {
	}
	virtual R operator()(const P1&, const P2&, const P3&, const P4&, const P5&, const P6&) = 0;
	virtual bool equals(const ThisType* i) const = 0;
	virtual bool isMemberFunction() const = 0;
	bool operator==(const ThisType& i) const {
		return this->equals(&i);
	}
	virtual ThisType* clone() = 0;
};

template<class R, class P1, class P2, class P3, class P4, class P5, class P6, class P7>
struct IFunction7 {
	typedef IFunction7<R, P1, P2, P3, P4, P5, P6, P7> ThisType;
	virtual ~IFunction7() {
	}
	virtual R operator()(const P1&, const P2&, const P3&, const P4&, const P5&, const P6&,
			const P7&) = 0;
	virtual bool equals(const ThisType* i) const = 0;
	virtual bool isMemberFunction() const = 0;
	bool operator==(const ThisType& i) const {
		return this->equals(&i);
	}
	virtual ThisType* clone() = 0;
};

template<class R, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8>
struct IFunction8 {
	typedef IFunction8<R, P1, P2, P3, P4, P5, P6, P7, P8> ThisType;
	virtual ~IFunction8() {
	}
	virtual R operator()(const P1&, const P2&, const P3&, const P4&, const P5&, const P6&,
			const P7&, const P8&) = 0;
	virtual bool equals(const ThisType* i) const = 0;
	virtual bool isMemberFunction() const = 0;
	bool operator==(const ThisType& i) const {
		return this->equals(&i);
	}
	virtual ThisType* clone() = 0;
};

template<class R, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8,
		class P9>
struct IFunction9 {
	typedef IFunction9<R, P1, P2, P3, P4, P5, P6, P7, P8, P9> ThisType;
	virtual ~IFunction9() {
	}
	virtual R operator()(const P1&, const P2&, const P3&, const P4&, const P5&, const P6&,
			const P7&, const P8&, const P9&) = 0;
	virtual bool equals(const ThisType* i) const = 0;
	virtual bool isMemberFunction() const = 0;
	bool operator==(const ThisType& i) const {
		return this->equals(&i);
	}
	virtual ThisType* clone() = 0;
};

template<class FT>
class IF {
public:
	typedef FT FuncType;
	IF() :
			func(NULL) {
	}
	virtual ~IF() {
	}
	FuncType getFunction() const {
		return this->func;
	}
protected:
	FuncType func;
};

template<class FT, class C>
class IFMem {
public:
	typedef FT FuncType;
	typedef C ClassType;
	IFMem() :
			func(NULL), obj(NULL) {
	}
	virtual ~IFMem() {
	}
	FuncType getFunction() const {
		return this->func;
	}
protected:
	FuncType func;
	ClassType* obj;
};

template<class R>
class F0: public IF<R (*)()>, public IFunction0<R> {
public:
	typedef IF<R (*)()> Parent;
	typedef typename IFunction0<R>::ThisType PThisType;
	typedef F0<R> ThisType;
	F0(const typename Parent::FuncType& f) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
	}

	virtual ~F0() {
	}

	virtual R operator()() {
		return this->func();
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return false;
	}
};

template<class R, class C>
class F0Mem: public IFMem<R (C::*)(), C>, public IFunction0<R> {
public:
	typedef IFMem<R (C::*)(), C> Parent;
	typedef typename IFunction0<R>::ThisType PThisType;
	typedef F0Mem<R, C> ThisType;
	F0Mem(const typename Parent::FuncType& f, C* o) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
		this->obj = o;
	}

	virtual ~F0Mem() {
	}

	virtual R operator()() {
		return (this->obj->*this->func)();
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (!i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return true;
	}
};

template<class R, class C>
class F0MemConst: public IFMem<R (C::*)() const, C>, public IFunction0<R> {
public:
	typedef IFMem<R (C::*)() const, C> Parent;
	typedef typename IFunction0<R>::ThisType PThisType;
	typedef F0MemConst<R, C> ThisType;
	F0MemConst(const typename Parent::FuncType& f, C* o) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
		this->obj = o;
	}

	virtual ~F0MemConst() {
	}

	virtual R operator()() {
		return (this->obj->*this->func)();
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (!i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return true;
	}
};

template<class R, class P1>
class F1: public IF<R (*)(P1)>, public IFunction1<R, P1> {
public:
	typedef IF<R (*)(P1)> Parent;
	typedef typename IFunction1<R, P1>::ThisType PThisType;
	typedef F1<R, P1> ThisType;
	F1(const typename Parent::FuncType& f) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
	}

	virtual ~F1() {
	}

	virtual R operator()(const P1& p1) {
		return this->func(p1);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return false;
	}
};

template<class R, class C, class P1>
class F1Mem: public IFMem<R (C::*)(P1), C>, public IFunction1<R, P1> {
public:
	typedef IFMem<R (C::*)(P1), C> Parent;
	typedef typename IFunction1<R, P1>::ThisType PThisType;
	typedef F1Mem<R, C, P1> ThisType;
	F1Mem(const typename Parent::FuncType& f, C* o) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
		this->obj = o;
	}

	virtual ~F1Mem() {
	}

	virtual R operator()(const P1& p1) {
		return (this->obj->*this->func)(p1);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (!i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return true;
	}
};

template<class R, class C, class P1>
class F1MemConst: public IFMem<R (C::*)(P1) const, C>, public IFunction1<R, P1> {
public:
	typedef IFMem<R (C::*)(P1) const, C> Parent;
	typedef typename IFunction1<R, P1>::ThisType PThisType;
	typedef F1MemConst<R, C, P1> ThisType;
	F1MemConst(const typename Parent::FuncType& f, C* o) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
		this->obj = o;
	}

	virtual ~F1MemConst() {
	}

	virtual R operator()(const P1& p1) {
		return (this->obj->*this->func)(p1);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (!i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return true;
	}
};

template<class R, class P1, class P2>
class F2: public IF<R (*)(P1, P2)>, public IFunction2<R, P1, P2> {
public:
	typedef IF<R (*)(P1, P2)> Parent;
	typedef typename IFunction2<R, P1, P2>::ThisType PThisType;
	typedef F2<R, P1, P2> ThisType;
	F2(const typename Parent::FuncType& f) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
	}

	virtual ~F2() {
	}

	virtual R operator()(const P1& p1, const P2& p2) {
		return this->func(p1, p2);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return false;
	}
};

template<class R, class C, class P1, class P2>
class F2Mem: public IFMem<R (C::*)(P1, P2), C>, public IFunction2<R, P1, P2> {
public:
	typedef IFMem<R (C::*)(P1, P2), C> Parent;
	typedef typename IFunction2<R, P1, P2>::ThisType PThisType;
	typedef F2Mem<R, C, P1, P2> ThisType;
	F2Mem(const typename Parent::FuncType& f, C* o) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
		this->obj = o;
	}

	virtual ~F2Mem() {
	}

	virtual R operator()(const P1& p1, const P2& p2) {
		return (this->obj->*this->func)(p1, p2);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (!i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return true;
	}
};

template<class R, class C, class P1, class P2>
class F2MemConst: public IFMem<R (C::*)(P1, P2) const, C>, public IFunction2<R, P1, P2> {
public:
	typedef IFMem<R (C::*)(P1, P2) const, C> Parent;
	typedef typename IFunction2<R, P1, P2>::ThisType PThisType;
	typedef F2MemConst<R, C, P1, P2> ThisType;
	F2MemConst(const typename Parent::FuncType& f, C* o) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
		this->obj = o;
	}

	virtual ~F2MemConst() {
	}

	virtual R operator()(const P1& p1, const P2& p2) {
		return (this->obj->*this->func)(p1, p2);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (!i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return true;
	}
};

template<class R, class P1, class P2, class P3>
class F3: public IF<R (*)(P1, P2, P3)>, public IFunction3<R, P1, P2, P3> {
public:
	typedef IF<R (*)(P1, P2, P3)> Parent;
	typedef typename IFunction3<R, P1, P2, P3>::ThisType PThisType;
	typedef F3<R, P1, P2, P3> ThisType;
	F3(const typename Parent::FuncType& f) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
	}

	virtual ~F3() {
	}

	virtual R operator()(const P1& p1, const P2& p2, const P3& p3) {
		return this->func(p1, p2, p3);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return false;
	}
};

template<class R, class C, class P1, class P2, class P3>
class F3Mem: public IFMem<R (C::*)(P1, P2, P3), C>, public IFunction3<R, P1, P2, P3> {
public:
	typedef IFMem<R (C::*)(P1, P2, P3), C> Parent;
	typedef typename IFunction3<R, P1, P2, P3>::ThisType PThisType;
	typedef F3Mem<R, C, P1, P2, P3> ThisType;
	F3Mem(const typename Parent::FuncType& f, C* o) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
		this->obj = o;
	}

	virtual ~F3Mem() {
	}

	virtual R operator()(const P1& p1, const P2& p2, const P3& p3) {
		return (this->obj->*this->func)(p1, p2, p3);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (!i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return true;
	}
};

template<class R, class C, class P1, class P2, class P3>
class F3MemConst: public IFMem<R (C::*)(P1, P2, P3) const, C>, public IFunction3<R, P1, P2, P3> {
public:
	typedef IFMem<R (C::*)(P1, P2, P3) const, C> Parent;
	typedef typename IFunction3<R, P1, P2, P3>::ThisType PThisType;
	typedef F3MemConst<R, C, P1, P2, P3> ThisType;
	F3MemConst(const typename Parent::FuncType& f, C* o) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
		this->obj = o;
	}

	virtual ~F3MemConst() {
	}

	virtual R operator()(const P1& p1, const P2& p2, const P3& p3) {
		return (this->obj->*this->func)(p1, p2, p3);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (!i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return true;
	}
};

template<class R, class P1, class P2, class P3, class P4>
class F4: public IF<R (*)(P1, P2, P3, P4)>, public IFunction4<R, P1, P2, P3, P4> {
public:
	typedef IF<R (*)(P1, P2, P3, P4)> Parent;
	typedef typename IFunction4<R, P1, P2, P3, P4>::ThisType PThisType;
	typedef F4<R, P1, P2, P3, P4> ThisType;
	F4(const typename Parent::FuncType& f) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
	}

	virtual ~F4() {
	}

	virtual R operator()(const P1& p1, const P2& p2, const P3& p3, const P4& p4) {
		return this->func(p1, p2, p3, p4);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return false;
	}
};

template<class R, class C, class P1, class P2, class P3, class P4>
class F4Mem: public IFMem<R (C::*)(P1, P2, P3, P4), C>, public IFunction4<R, P1, P2, P3, P4> {
public:
	typedef IFMem<R (C::*)(P1, P2, P3, P4), C> Parent;
	typedef typename IFunction4<R, P1, P2, P3, P4>::ThisType PThisType;
	typedef F4Mem<R, C, P1, P2, P3, P4> ThisType;
	F4Mem(const typename Parent::FuncType& f, C* o) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
		this->obj = o;
	}

	virtual ~F4Mem() {
	}

	virtual R operator()(const P1& p1, const P2& p2, const P3& p3, const P4& p4) {
		return (this->obj->*this->func)(p1, p2, p3, p4);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (!i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return true;
	}
};

template<class R, class C, class P1, class P2, class P3, class P4>
class F4MemConst: public IFMem<R (C::*)(P1, P2, P3, P4) const, C>, public IFunction4<R, P1, P2, P3,
		P4> {
public:
	typedef IFMem<R (C::*)(P1, P2, P3, P4) const, C> Parent;
	typedef typename IFunction4<R, P1, P2, P3, P4>::ThisType PThisType;
	typedef F4MemConst<R, C, P1, P2, P3, P4> ThisType;
	F4MemConst(const typename Parent::FuncType& f, C* o) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
		this->obj = o;
	}

	virtual ~F4MemConst() {
	}

	virtual R operator()(const P1& p1, const P2& p2, const P3& p3, const P4& p4) {
		return (this->obj->*this->func)(p1, p2, p3, p4);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (!i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return true;
	}
};

template<class R, class P1, class P2, class P3, class P4, class P5>
class F5: public IF<R (*)(P1, P2, P3, P4, P5)>, public IFunction5<R, P1, P2, P3, P4, P5> {
public:
	typedef IF<R (*)(P1, P2, P3, P4, P5)> Parent;
	typedef typename IFunction5<R, P1, P2, P3, P4, P5>::ThisType PThisType;
	typedef F5<R, P1, P2, P3, P4, P5> ThisType;
	F5(const typename Parent::FuncType& f) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
	}

	virtual ~F5() {
	}

	virtual R operator()(const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5) {
		return this->func(p1, p2, p3, p4, p5);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return false;
	}
};

template<class R, class C, class P1, class P2, class P3, class P4, class P5>
class F5Mem: public IFMem<R (C::*)(P1, P2, P3, P4, P5), C>, public IFunction5<R, P1, P2, P3, P4, P5> {
public:
	typedef IFMem<R (C::*)(P1, P2, P3, P4, P5), C> Parent;
	typedef typename IFunction5<R, P1, P2, P3, P4, P5>::ThisType PThisType;
	typedef F5Mem<R, C, P1, P2, P3, P4, P5> ThisType;
	F5Mem(const typename Parent::FuncType& f, C* o) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
		this->obj = o;
	}

	virtual ~F5Mem() {
	}

	virtual R operator()(const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5) {
		return (this->obj->*this->func)(p1, p2, p3, p4, p5);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (!i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return true;
	}
};

template<class R, class C, class P1, class P2, class P3, class P4, class P5>
class F5MemConst: public IFMem<R (C::*)(P1, P2, P3, P4, P5) const, C>, public IFunction5<R, P1, P2,
		P3, P4, P5> {
public:
	typedef IFMem<R (C::*)(P1, P2, P3, P4, P5) const, C> Parent;
	typedef typename IFunction5<R, P1, P2, P3, P4, P5>::ThisType PThisType;
	typedef F5MemConst<R, C, P1, P2, P3, P4, P5> ThisType;
	F5MemConst(const typename Parent::FuncType& f, C* o) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
		this->obj = o;
	}

	virtual ~F5MemConst() {
	}

	virtual R operator()(const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5) {
		return (this->obj->*this->func)(p1, p2, p3, p4, p5);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (!i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return true;
	}
};

template<class R, class P1, class P2, class P3, class P4, class P5, class P6>
class F6: public IF<R (*)(P1, P2, P3, P4, P5, P6)>, public IFunction6<R, P1, P2, P3, P4, P5, P6> {
public:
	typedef IF<R (*)(P1, P2, P3, P4, P5, P6)> Parent;
	typedef typename IFunction6<R, P1, P2, P3, P4, P5, P6>::ThisType PThisType;
	typedef F6<R, P1, P2, P3, P4, P5, P6> ThisType;
	F6(const typename Parent::FuncType& f) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
	}

	virtual ~F6() {
	}

	virtual R operator()(const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5,
			const P6& p6) {
		return this->func(p1, p2, p3, p4, p5, p6);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return false;
	}
};

template<class R, class C, class P1, class P2, class P3, class P4, class P5, class P6>
class F6Mem: public IFMem<R (C::*)(P1, P2, P3, P4, P5, P6), C>, public IFunction6<R, P1, P2, P3, P4,
		P5, P6> {
public:
	typedef IFMem<R (C::*)(P1, P2, P3, P4, P5, P6), C> Parent;
	typedef typename IFunction6<R, P1, P2, P3, P4, P5, P6>::ThisType PThisType;
	typedef F6Mem<R, C, P1, P2, P3, P4, P5, P6> ThisType;
	F6Mem(const typename Parent::FuncType& f, C* o) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
		this->obj = o;
	}

	virtual ~F6Mem() {
	}

	virtual R operator()(const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5,
			const P6& p6) {
		return (this->obj->*this->func)(p1, p2, p3, p4, p5, p6);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (!i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return true;
	}
};

template<class R, class C, class P1, class P2, class P3, class P4, class P5, class P6>
class F6MemConst: public IFMem<R (C::*)(P1, P2, P3, P4, P5, P6) const, C>, public IFunction6<R, P1,
		P2, P3, P4, P5, P6> {
public:
	typedef IFMem<R (C::*)(P1, P2, P3, P4, P5, P6) const, C> Parent;
	typedef typename IFunction6<R, P1, P2, P3, P4, P5, P6>::ThisType PThisType;
	typedef F6MemConst<R, C, P1, P2, P3, P4, P5, P6> ThisType;
	F6MemConst(const typename Parent::FuncType& f, C* o) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
		this->obj = o;
	}

	virtual ~F6MemConst() {
	}

	virtual R operator()(const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5,
			const P6& p6) {
		return (this->obj->*this->func)(p1, p2, p3, p4, p5, p6);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (!i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return true;
	}
};

template<class R, class P1, class P2, class P3, class P4, class P5, class P6, class P7>
class F7: public IF<R (*)(P1, P2, P3, P4, P5, P6, P7)>, public IFunction7<R, P1, P2, P3, P4, P5, P6,
		P7> {
public:
	typedef IF<R (*)(P1, P2, P3, P4, P5, P6, P7)> Parent;
	typedef typename IFunction7<R, P1, P2, P3, P4, P5, P6, P7>::ThisType PThisType;
	typedef F7<R, P1, P2, P3, P4, P5, P6, P7> ThisType;
	F7(const typename Parent::FuncType& f) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
	}

	virtual ~F7() {
	}

	virtual R operator()(const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5,
			const P6& p6, const P7& p7) {
		return this->func(p1, p2, p3, p4, p5, p6, p7);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return false;
	}
};

template<class R, class C, class P1, class P2, class P3, class P4, class P5, class P6, class P7>
class F7Mem: public IFMem<R (C::*)(P1, P2, P3, P4, P5, P6, P7), C>, public IFunction7<R, P1, P2, P3,
		P4, P5, P6, P7> {
public:
	typedef IFMem<R (C::*)(P1, P2, P3, P4, P5, P6, P7), C> Parent;
	typedef typename IFunction7<R, P1, P2, P3, P4, P5, P6, P7>::ThisType PThisType;
	typedef F7Mem<R, C, P1, P2, P3, P4, P5, P6, P7> ThisType;
	F7Mem(const typename Parent::FuncType& f, C* o) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
		this->obj = o;
	}

	virtual ~F7Mem() {
	}

	virtual R operator()(const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5,
			const P6& p6, const P7& p7) {
		return (this->obj->*this->func)(p1, p2, p3, p4, p5, p6, p7);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (!i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return true;
	}
};

template<class R, class C, class P1, class P2, class P3, class P4, class P5, class P6, class P7>
class F7MemConst: public IFMem<R (C::*)(P1, P2, P3, P4, P5, P6, P7) const, C>, public IFunction7<R,
		P1, P2, P3, P4, P5, P6, P7> {
public:
	typedef IFMem<R (C::*)(P1, P2, P3, P4, P5, P6, P7) const, C> Parent;
	typedef typename IFunction7<R, P1, P2, P3, P4, P5, P6, P7>::ThisType PThisType;
	typedef F7MemConst<R, C, P1, P2, P3, P4, P5, P6, P7> ThisType;
	F7MemConst(const typename Parent::FuncType& f, C* o) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
		this->obj = o;
	}

	virtual ~F7MemConst() {
	}

	virtual R operator()(const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5,
			const P6& p6, const P7& p7) {
		return (this->obj->*this->func)(p1, p2, p3, p4, p5, p6, p7);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (!i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return true;
	}
};

template<class R, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8>
class F8: public IF<R (*)(P1, P2, P3, P4, P5, P6, P7, P8)>, public IFunction8<R, P1, P2, P3, P4, P5,
		P6, P7, P8> {
public:
	typedef IF<R (*)(P1, P2, P3, P4, P5, P6, P7, P8)> Parent;
	typedef typename IFunction8<R, P1, P2, P3, P4, P5, P6, P7, P8>::ThisType PThisType;
	typedef F8<R, P1, P2, P3, P4, P5, P6, P7, P8> ThisType;
	F8(const typename Parent::FuncType& f) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
	}

	virtual ~F8() {
	}

	virtual R operator()(const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5,
			const P6& p6, const P7& p7, const P8& p8) {
		return this->func(p1, p2, p3, p4, p5, p6, p7, p8);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return false;
	}
};

template<class R, class C, class P1, class P2, class P3, class P4, class P5, class P6, class P7,
		class P8>
class F8Mem: public IFMem<R (C::*)(P1, P2, P3, P4, P5, P6, P7, P8), C>, public IFunction8<R, P1, P2,
		P3, P4, P5, P6, P7, P8> {
public:
	typedef IFMem<R (C::*)(P1, P2, P3, P4, P5, P6, P7, P8), C> Parent;
	typedef typename IFunction8<R, P1, P2, P3, P4, P5, P6, P7, P8>::ThisType PThisType;
	typedef F8Mem<R, C, P1, P2, P3, P4, P5, P6, P7, P8> ThisType;
	F8Mem(const typename Parent::FuncType& f, C* o) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
		this->obj = o;
	}

	virtual ~F8Mem() {
	}

	virtual R operator()(const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5,
			const P6& p6, const P7& p7, const P8& p8) {
		return (this->obj->*this->func)(p1, p2, p3, p4, p5, p6, p7, p8);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (!i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return true;
	}
};

template<class R, class C, class P1, class P2, class P3, class P4, class P5, class P6, class P7,
		class P8>
class F8MemConst: public IFMem<R (C::*)(P1, P2, P3, P4, P5, P6, P7, P8) const, C>,
		public IFunction8<R, P1, P2, P3, P4, P5, P6, P7, P8> {
public:
	typedef IFMem<R (C::*)(P1, P2, P3, P4, P5, P6, P7, P8) const, C> Parent;
	typedef typename IFunction8<R, P1, P2, P3, P4, P5, P6, P7, P8>::ThisType PThisType;
	typedef F8MemConst<R, C, P1, P2, P3, P4, P5, P6, P7, P8> ThisType;
	F8MemConst(const typename Parent::FuncType& f, C* o) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
		this->obj = o;
	}

	virtual ~F8MemConst() {
	}

	virtual R operator()(const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5,
			const P6& p6, const P7& p7, const P8& p8) {
		return (this->obj->*this->func)(p1, p2, p3, p4, p5, p6, p7, p8);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (!i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return true;
	}
};

template<class R, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8,
		class P9>
class F9: public IF<R (*)(P1, P2, P3, P4, P5, P6, P7, P8, P9)>, public IFunction9<R, P1, P2, P3, P4,
		P5, P6, P7, P8, P9> {
public:
	typedef IF<R (*)(P1, P2, P3, P4, P5, P6, P7, P8, P9)> Parent;
	typedef typename IFunction9<R, P1, P2, P3, P4, P5, P6, P7, P8, P9>::ThisType PThisType;
	typedef F9<R, P1, P2, P3, P4, P5, P6, P7, P8, P9> ThisType;
	F9(const typename Parent::FuncType& f) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
	}

	virtual ~F9() {
	}

	virtual R operator()(const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5,
			const P6& p6, const P7& p7, const P8& p8, const P9& p9) {
		return this->func(p1, p2, p3, p4, p5, p6, p7, p8, p9);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return false;
	}
};

template<class R, class C, class P1, class P2, class P3, class P4, class P5, class P6, class P7,
		class P8, class P9>
class F9Mem: public IFMem<R (C::*)(P1, P2, P3, P4, P5, P6, P7, P8, P9), C>, public IFunction9<R, P1,
		P2, P3, P4, P5, P6, P7, P8, P9> {
public:
	typedef IFMem<R (C::*)(P1, P2, P3, P4, P5, P6, P7, P8, P9), C> Parent;
	typedef typename IFunction9<R, P1, P2, P3, P4, P5, P6, P7, P8, P9>::ThisType PThisType;
	typedef F9Mem<R, C, P1, P2, P3, P4, P5, P6, P7, P8, P9> ThisType;
	F9Mem(const typename Parent::FuncType& f, C* o) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
		this->obj = o;
	}

	virtual ~F9Mem() {
	}

	virtual R operator()(const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5,
			const P6& p6, const P7& p7, const P8& p8, const P9& p9) {
		return (this->obj->*this->func)(p1, p2, p3, p4, p5, p6, p7, p8, p9);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (!i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return true;
	}
};

template<class R, class C, class P1, class P2, class P3, class P4, class P5, class P6, class P7,
		class P8, class P9>
class F9MemConst: public IFMem<R (C::*)(P1, P2, P3, P4, P5, P6, P7, P8, P9) const, C>,
		public IFunction9<R, P1, P2, P3, P4, P5, P6, P7, P8, P9> {
public:
	typedef IFMem<R (C::*)(P1, P2, P3, P4, P5, P6, P7, P8, P9) const, C> Parent;
	typedef typename IFunction9<R, P1, P2, P3, P4, P5, P6, P7, P8, P9>::ThisType PThisType;
	typedef F9MemConst<R, C, P1, P2, P3, P4, P5, P6, P7, P8, P9> ThisType;
	F9MemConst(const typename Parent::FuncType& f, C* o) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
		this->obj = o;
	}

	virtual ~F9MemConst() {
	}

	virtual R operator()(const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5,
			const P6& p6, const P7& p7, const P8& p8, const P9& p9) {
		return (this->obj->*this->func)(p1, p2, p3, p4, p5, p6, p7, p8, p9);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (!i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return true;
	}
};

template<class R>
class ArgF0: public IF<R (*)()>, public IFunction0<R> {
public:
	typedef IF<R (*)()> Parent;
	typedef typename IFunction0<R>::ThisType PThisType;
	typedef ArgF0<R> ThisType;
	ArgF0(const typename Parent::FuncType& f) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
	}

	virtual ~ArgF0() {
	}

	virtual R operator()() {
		return this->func();
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return false;
	}
private:
};

template<class R, class C>
class ArgF0Mem: public IFMem<R (C::*)(), C>, public IFunction0<R> {
public:
	typedef IFMem<R (C::*)(), C> Parent;
	typedef typename IFunction0<R>::ThisType PThisType;
	typedef ArgF0Mem<R, C> ThisType;
	ArgF0Mem(const typename Parent::FuncType& f, C* o) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
		this->obj = o;
	}

	virtual ~ArgF0Mem() {
	}

	virtual R operator()() {
		return (this->obj->*this->func)();
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (!i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return true;
	}
private:
};

template<class R, class C>
class ArgF0MemConst: public IFMem<R (C::*)() const, C>, public IFunction0<R> {
public:
	typedef IFMem<R (C::*)() const, C> Parent;
	typedef typename IFunction0<R>::ThisType PThisType;
	typedef ArgF0MemConst<R, C> ThisType;
	ArgF0MemConst(const typename Parent::FuncType& f, C* o) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
		this->obj = o;
	}

	virtual ~ArgF0MemConst() {
	}

	virtual R operator()() {
		return (this->obj->*this->func)();
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (!i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return true;
	}
private:
};

template<class R, class P1, class A1>
class ArgF1: public IF<R (*)(P1)>, public IFunction0<R> {
public:
	typedef IF<R (*)(P1)> Parent;
	typedef typename IFunction0<R>::ThisType PThisType;
	typedef ArgF1<R, P1, A1> ThisType;
	ArgF1(const typename Parent::FuncType& f, const A1& a1) :
			_a1(a1) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
	}

	virtual ~ArgF1() {
	}

	virtual R operator()() {
		return this->func(_a1);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return false;
	}
private:
	A1 _a1;
};

template<class R, class C, class P1, class A1>
class ArgF1Mem: public IFMem<R (C::*)(P1), C>, public IFunction0<R> {
public:
	typedef IFMem<R (C::*)(P1), C> Parent;
	typedef typename IFunction0<R>::ThisType PThisType;
	typedef ArgF1Mem<R, C, P1, A1> ThisType;
	ArgF1Mem(const typename Parent::FuncType& f, C* o, const A1& a1) :
			_a1(a1) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
		this->obj = o;
	}

	virtual ~ArgF1Mem() {
	}

	virtual R operator()() {
		return (this->obj->*this->func)(_a1);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (!i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return true;
	}
private:
	A1 _a1;
};

template<class R, class C, class P1, class A1>
class ArgF1MemConst: public IFMem<R (C::*)(P1) const, C>, public IFunction0<R> {
public:
	typedef IFMem<R (C::*)(P1) const, C> Parent;
	typedef typename IFunction0<R>::ThisType PThisType;
	typedef ArgF1MemConst<R, C, P1, A1> ThisType;
	ArgF1MemConst(const typename Parent::FuncType& f, C* o, const A1& a1) :
			_a1(a1) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
		this->obj = o;
	}

	virtual ~ArgF1MemConst() {
	}

	virtual R operator()() {
		return (this->obj->*this->func)(_a1);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (!i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return true;
	}
private:
	A1 _a1;
};

template<class R, class P1, class P2, class A1, class A2>
class ArgF2: public IF<R (*)(P1, P2)>, public IFunction0<R> {
public:
	typedef IF<R (*)(P1, P2)> Parent;
	typedef typename IFunction0<R>::ThisType PThisType;
	typedef ArgF2<R, P1, P2, A1, A2> ThisType;
	ArgF2(const typename Parent::FuncType& f, const A1& a1, const A2& a2) :
			_a1(a1), _a2(a2) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
	}

	virtual ~ArgF2() {
	}

	virtual R operator()() {
		return this->func(_a1, _a2);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return false;
	}
private:
	A1 _a1;
	A2 _a2;
};

template<class R, class C, class P1, class P2, class A1, class A2>
class ArgF2Mem: public IFMem<R (C::*)(P1, P2), C>, public IFunction0<R> {
public:
	typedef IFMem<R (C::*)(P1, P2), C> Parent;
	typedef typename IFunction0<R>::ThisType PThisType;
	typedef ArgF2Mem<R, C, P1, P2, A1, A2> ThisType;
	ArgF2Mem(const typename Parent::FuncType& f, C* o, const A1& a1, const A2& a2) :
			_a1(a1), _a2(a2) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
		this->obj = o;
	}

	virtual ~ArgF2Mem() {
	}

	virtual R operator()() {
		return (this->obj->*this->func)(_a1, _a2);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (!i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return true;
	}
private:
	A1 _a1;
	A2 _a2;
};

template<class R, class C, class P1, class P2, class A1, class A2>
class ArgF2MemConst: public IFMem<R (C::*)(P1, P2) const, C>, public IFunction0<R> {
public:
	typedef IFMem<R (C::*)(P1, P2) const, C> Parent;
	typedef typename IFunction0<R>::ThisType PThisType;
	typedef ArgF2MemConst<R, C, P1, P2, A1, A2> ThisType;
	ArgF2MemConst(const typename Parent::FuncType& f, C* o, const A1& a1, const A2& a2) :
			_a1(a1), _a2(a2) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
		this->obj = o;
	}

	virtual ~ArgF2MemConst() {
	}

	virtual R operator()() {
		return (this->obj->*this->func)(_a1, _a2);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (!i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return true;
	}
private:
	A1 _a1;
	A2 _a2;
};

template<class R, class P1, class P2, class P3, class A1, class A2, class A3>
class ArgF3: public IF<R (*)(P1, P2, P3)>, public IFunction0<R> {
public:
	typedef IF<R (*)(P1, P2, P3)> Parent;
	typedef typename IFunction0<R>::ThisType PThisType;
	typedef ArgF3<R, P1, P2, P3, A1, A2, A3> ThisType;
	ArgF3(const typename Parent::FuncType& f, const A1& a1, const A2& a2, const A3& a3) :
			_a1(a1), _a2(a2), _a3(a3) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
	}

	virtual ~ArgF3() {
	}

	virtual R operator()() {
		return this->func(_a1, _a2, _a3);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return false;
	}
private:
	A1 _a1;
	A2 _a2;
	A3 _a3;
};

template<class R, class C, class P1, class P2, class P3, class A1, class A2, class A3>
class ArgF3Mem: public IFMem<R (C::*)(P1, P2, P3), C>, public IFunction0<R> {
public:
	typedef IFMem<R (C::*)(P1, P2, P3), C> Parent;
	typedef typename IFunction0<R>::ThisType PThisType;
	typedef ArgF3Mem<R, C, P1, P2, P3, A1, A2, A3> ThisType;
	ArgF3Mem(const typename Parent::FuncType& f, C* o, const A1& a1, const A2& a2, const A3& a3) :
			_a1(a1), _a2(a2), _a3(a3) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
		this->obj = o;
	}

	virtual ~ArgF3Mem() {
	}

	virtual R operator()() {
		return (this->obj->*this->func)(_a1, _a2, _a3);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (!i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return true;
	}
private:
	A1 _a1;
	A2 _a2;
	A3 _a3;
};

template<class R, class C, class P1, class P2, class P3, class A1, class A2, class A3>
class ArgF3MemConst: public IFMem<R (C::*)(P1, P2, P3) const, C>, public IFunction0<R> {
public:
	typedef IFMem<R (C::*)(P1, P2, P3) const, C> Parent;
	typedef typename IFunction0<R>::ThisType PThisType;
	typedef ArgF3MemConst<R, C, P1, P2, P3, A1, A2, A3> ThisType;
	ArgF3MemConst(const typename Parent::FuncType& f, C* o, const A1& a1, const A2& a2,
			const A3& a3) :
			_a1(a1), _a2(a2), _a3(a3) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
		this->obj = o;
	}

	virtual ~ArgF3MemConst() {
	}

	virtual R operator()() {
		return (this->obj->*this->func)(_a1, _a2, _a3);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (!i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return true;
	}
private:
	A1 _a1;
	A2 _a2;
	A3 _a3;
};

template<class R, class P1, class P2, class P3, class P4, class A1, class A2, class A3, class A4>
class ArgF4: public IF<R (*)(P1, P2, P3, P4)>, public IFunction0<R> {
public:
	typedef IF<R (*)(P1, P2, P3, P4)> Parent;
	typedef typename IFunction0<R>::ThisType PThisType;
	typedef ArgF4<R, P1, P2, P3, P4, A1, A2, A3, A4> ThisType;
	ArgF4(const typename Parent::FuncType& f, const A1& a1, const A2& a2, const A3& a3,
			const A4& a4) :
			_a1(a1), _a2(a2), _a3(a3), _a4(a4) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
	}

	virtual ~ArgF4() {
	}

	virtual R operator()() {
		return this->func(_a1, _a2, _a3, _a4);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return false;
	}
private:
	A1 _a1;
	A2 _a2;
	A3 _a3;
	A4 _a4;
};

template<class R, class C, class P1, class P2, class P3, class P4, class A1, class A2, class A3,
		class A4>
class ArgF4Mem: public IFMem<R (C::*)(P1, P2, P3, P4), C>, public IFunction0<R> {
public:
	typedef IFMem<R (C::*)(P1, P2, P3, P4), C> Parent;
	typedef typename IFunction0<R>::ThisType PThisType;
	typedef ArgF4Mem<R, C, P1, P2, P3, P4, A1, A2, A3, A4> ThisType;
	ArgF4Mem(const typename Parent::FuncType& f, C* o, const A1& a1, const A2& a2, const A3& a3,
			const A4& a4) :
			_a1(a1), _a2(a2), _a3(a3), _a4(a4) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
		this->obj = o;
	}

	virtual ~ArgF4Mem() {
	}

	virtual R operator()() {
		return (this->obj->*this->func)(_a1, _a2, _a3, _a4);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (!i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return true;
	}
private:
	A1 _a1;
	A2 _a2;
	A3 _a3;
	A4 _a4;
};

template<class R, class C, class P1, class P2, class P3, class P4, class A1, class A2, class A3,
		class A4>
class ArgF4MemConst: public IFMem<R (C::*)(P1, P2, P3, P4) const, C>, public IFunction0<R> {
public:
	typedef IFMem<R (C::*)(P1, P2, P3, P4) const, C> Parent;
	typedef typename IFunction0<R>::ThisType PThisType;
	typedef ArgF4MemConst<R, C, P1, P2, P3, P4, A1, A2, A3, A4> ThisType;
	ArgF4MemConst(const typename Parent::FuncType& f, C* o, const A1& a1, const A2& a2,
			const A3& a3, const A4& a4) :
			_a1(a1), _a2(a2), _a3(a3), _a4(a4) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
		this->obj = o;
	}

	virtual ~ArgF4MemConst() {
	}

	virtual R operator()() {
		return (this->obj->*this->func)(_a1, _a2, _a3, _a4);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (!i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return true;
	}
private:
	A1 _a1;
	A2 _a2;
	A3 _a3;
	A4 _a4;
};

template<class R, class P1, class P2, class P3, class P4, class P5, class A1, class A2, class A3,
		class A4, class A5>
class ArgF5: public IF<R (*)(P1, P2, P3, P4, P5)>, public IFunction0<R> {
public:
	typedef IF<R (*)(P1, P2, P3, P4, P5)> Parent;
	typedef typename IFunction0<R>::ThisType PThisType;
	typedef ArgF5<R, P1, P2, P3, P4, P5, A1, A2, A3, A4, A5> ThisType;
	ArgF5(const typename Parent::FuncType& f, const A1& a1, const A2& a2, const A3& a3,
			const A4& a4, const A5& a5) :
			_a1(a1), _a2(a2), _a3(a3), _a4(a4), _a5(a5) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
	}

	virtual ~ArgF5() {
	}

	virtual R operator()() {
		return this->func(_a1, _a2, _a3, _a4, _a5);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return false;
	}
private:
	A1 _a1;
	A2 _a2;
	A3 _a3;
	A4 _a4;
	A5 _a5;
};

template<class R, class C, class P1, class P2, class P3, class P4, class P5, class A1, class A2,
		class A3, class A4, class A5>
class ArgF5Mem: public IFMem<R (C::*)(P1, P2, P3, P4, P5), C>, public IFunction0<R> {
public:
	typedef IFMem<R (C::*)(P1, P2, P3, P4, P5), C> Parent;
	typedef typename IFunction0<R>::ThisType PThisType;
	typedef ArgF5Mem<R, C, P1, P2, P3, P4, P5, A1, A2, A3, A4, A5> ThisType;
	ArgF5Mem(const typename Parent::FuncType& f, C* o, const A1& a1, const A2& a2, const A3& a3,
			const A4& a4, const A5& a5) :
			_a1(a1), _a2(a2), _a3(a3), _a4(a4), _a5(a5) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
		this->obj = o;
	}

	virtual ~ArgF5Mem() {
	}

	virtual R operator()() {
		return (this->obj->*this->func)(_a1, _a2, _a3, _a4, _a5);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (!i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return true;
	}
private:
	A1 _a1;
	A2 _a2;
	A3 _a3;
	A4 _a4;
	A5 _a5;
};

template<class R, class C, class P1, class P2, class P3, class P4, class P5, class A1, class A2,
		class A3, class A4, class A5>
class ArgF5MemConst: public IFMem<R (C::*)(P1, P2, P3, P4, P5) const, C>, public IFunction0<R> {
public:
	typedef IFMem<R (C::*)(P1, P2, P3, P4, P5) const, C> Parent;
	typedef typename IFunction0<R>::ThisType PThisType;
	typedef ArgF5MemConst<R, C, P1, P2, P3, P4, P5, A1, A2, A3, A4, A5> ThisType;
	ArgF5MemConst(const typename Parent::FuncType& f, C* o, const A1& a1, const A2& a2,
			const A3& a3, const A4& a4, const A5& a5) :
			_a1(a1), _a2(a2), _a3(a3), _a4(a4), _a5(a5) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
		this->obj = o;
	}

	virtual ~ArgF5MemConst() {
	}

	virtual R operator()() {
		return (this->obj->*this->func)(_a1, _a2, _a3, _a4, _a5);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (!i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return true;
	}
private:
	A1 _a1;
	A2 _a2;
	A3 _a3;
	A4 _a4;
	A5 _a5;
};

template<class R, class P1, class P2, class P3, class P4, class P5, class P6, class A1, class A2,
		class A3, class A4, class A5, class A6>
class ArgF6: public IF<R (*)(P1, P2, P3, P4, P5, P6)>, public IFunction0<R> {
public:
	typedef IF<R (*)(P1, P2, P3, P4, P5, P6)> Parent;
	typedef typename IFunction0<R>::ThisType PThisType;
	typedef ArgF6<R, P1, P2, P3, P4, P5, P6, A1, A2, A3, A4, A5, A6> ThisType;
	ArgF6(const typename Parent::FuncType& f, const A1& a1, const A2& a2, const A3& a3,
			const A4& a4, const A5& a5, const A6& a6) :
			_a1(a1), _a2(a2), _a3(a3), _a4(a4), _a5(a5), _a6(a6) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
	}

	virtual ~ArgF6() {
	}

	virtual R operator()() {
		return this->func(_a1, _a2, _a3, _a4, _a5, _a6);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return false;
	}
private:
	A1 _a1;
	A2 _a2;
	A3 _a3;
	A4 _a4;
	A5 _a5;
	A6 _a6;
};

template<class R, class C, class P1, class P2, class P3, class P4, class P5, class P6, class A1,
		class A2, class A3, class A4, class A5, class A6>
class ArgF6Mem: public IFMem<R (C::*)(P1, P2, P3, P4, P5, P6), C>, public IFunction0<R> {
public:
	typedef IFMem<R (C::*)(P1, P2, P3, P4, P5, P6), C> Parent;
	typedef typename IFunction0<R>::ThisType PThisType;
	typedef ArgF6Mem<R, C, P1, P2, P3, P4, P5, P6, A1, A2, A3, A4, A5, A6> ThisType;
	ArgF6Mem(const typename Parent::FuncType& f, C* o, const A1& a1, const A2& a2, const A3& a3,
			const A4& a4, const A5& a5, const A6& a6) :
			_a1(a1), _a2(a2), _a3(a3), _a4(a4), _a5(a5), _a6(a6) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
		this->obj = o;
	}

	virtual ~ArgF6Mem() {
	}

	virtual R operator()() {
		return (this->obj->*this->func)(_a1, _a2, _a3, _a4, _a5, _a6);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (!i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return true;
	}
private:
	A1 _a1;
	A2 _a2;
	A3 _a3;
	A4 _a4;
	A5 _a5;
	A6 _a6;
};

template<class R, class C, class P1, class P2, class P3, class P4, class P5, class P6, class A1,
		class A2, class A3, class A4, class A5, class A6>
class ArgF6MemConst: public IFMem<R (C::*)(P1, P2, P3, P4, P5, P6) const, C>, public IFunction0<R> {
public:
	typedef IFMem<R (C::*)(P1, P2, P3, P4, P5, P6) const, C> Parent;
	typedef typename IFunction0<R>::ThisType PThisType;
	typedef ArgF6MemConst<R, C, P1, P2, P3, P4, P5, P6, A1, A2, A3, A4, A5, A6> ThisType;
	ArgF6MemConst(const typename Parent::FuncType& f, C* o, const A1& a1, const A2& a2,
			const A3& a3, const A4& a4, const A5& a5, const A6& a6) :
			_a1(a1), _a2(a2), _a3(a3), _a4(a4), _a5(a5), _a6(a6) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
		this->obj = o;
	}

	virtual ~ArgF6MemConst() {
	}

	virtual R operator()() {
		return (this->obj->*this->func)(_a1, _a2, _a3, _a4, _a5, _a6);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (!i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return true;
	}
private:
	A1 _a1;
	A2 _a2;
	A3 _a3;
	A4 _a4;
	A5 _a5;
	A6 _a6;
};

template<class R, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class A1,
		class A2, class A3, class A4, class A5, class A6, class A7>
class ArgF7: public IF<R (*)(P1, P2, P3, P4, P5, P6, P7)>, public IFunction0<R> {
public:
	typedef IF<R (*)(P1, P2, P3, P4, P5, P6, P7)> Parent;
	typedef typename IFunction0<R>::ThisType PThisType;
	typedef ArgF7<R, P1, P2, P3, P4, P5, P6, P7, A1, A2, A3, A4, A5, A6, A7> ThisType;
	ArgF7(const typename Parent::FuncType& f, const A1& a1, const A2& a2, const A3& a3,
			const A4& a4, const A5& a5, const A6& a6, const A7& a7) :
			_a1(a1), _a2(a2), _a3(a3), _a4(a4), _a5(a5), _a6(a6), _a7(a7) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
	}

	virtual ~ArgF7() {
	}

	virtual R operator()() {
		return this->func(_a1, _a2, _a3, _a4, _a5, _a6, _a7);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return false;
	}
private:
	A1 _a1;
	A2 _a2;
	A3 _a3;
	A4 _a4;
	A5 _a5;
	A6 _a6;
	A7 _a7;
};

template<class R, class C, class P1, class P2, class P3, class P4, class P5, class P6, class P7,
		class A1, class A2, class A3, class A4, class A5, class A6, class A7>
class ArgF7Mem: public IFMem<R (C::*)(P1, P2, P3, P4, P5, P6, P7), C>, public IFunction0<R> {
public:
	typedef IFMem<R (C::*)(P1, P2, P3, P4, P5, P6, P7), C> Parent;
	typedef typename IFunction0<R>::ThisType PThisType;
	typedef ArgF7Mem<R, C, P1, P2, P3, P4, P5, P6, P7, A1, A2, A3, A4, A5, A6, A7> ThisType;
	ArgF7Mem(const typename Parent::FuncType& f, C* o, const A1& a1, const A2& a2, const A3& a3,
			const A4& a4, const A5& a5, const A6& a6, const A7& a7) :
			_a1(a1), _a2(a2), _a3(a3), _a4(a4), _a5(a5), _a6(a6), _a7(a7) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
		this->obj = o;
	}

	virtual ~ArgF7Mem() {
	}

	virtual R operator()() {
		return (this->obj->*this->func)(_a1, _a2, _a3, _a4, _a5, _a6, _a7);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (!i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return true;
	}
private:
	A1 _a1;
	A2 _a2;
	A3 _a3;
	A4 _a4;
	A5 _a5;
	A6 _a6;
	A7 _a7;
};

template<class R, class C, class P1, class P2, class P3, class P4, class P5, class P6, class P7,
		class A1, class A2, class A3, class A4, class A5, class A6, class A7>
class ArgF7MemConst: public IFMem<R (C::*)(P1, P2, P3, P4, P5, P6, P7) const, C>, public IFunction0<
		R> {
public:
	typedef IFMem<R (C::*)(P1, P2, P3, P4, P5, P6, P7) const, C> Parent;
	typedef typename IFunction0<R>::ThisType PThisType;
	typedef ArgF7MemConst<R, C, P1, P2, P3, P4, P5, P6, P7, A1, A2, A3, A4, A5, A6, A7> ThisType;
	ArgF7MemConst(const typename Parent::FuncType& f, C* o, const A1& a1, const A2& a2,
			const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7) :
			_a1(a1), _a2(a2), _a3(a3), _a4(a4), _a5(a5), _a6(a6), _a7(a7) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
		this->obj = o;
	}

	virtual ~ArgF7MemConst() {
	}

	virtual R operator()() {
		return (this->obj->*this->func)(_a1, _a2, _a3, _a4, _a5, _a6, _a7);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (!i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return true;
	}
private:
	A1 _a1;
	A2 _a2;
	A3 _a3;
	A4 _a4;
	A5 _a5;
	A6 _a6;
	A7 _a7;
};

template<class R, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8,
		class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
class ArgF8: public IF<R (*)(P1, P2, P3, P4, P5, P6, P7, P8)>, public IFunction0<R> {
public:
	typedef IF<R (*)(P1, P2, P3, P4, P5, P6, P7, P8)> Parent;
	typedef typename IFunction0<R>::ThisType PThisType;
	typedef ArgF8<R, P1, P2, P3, P4, P5, P6, P7, P8, A1, A2, A3, A4, A5, A6, A7, A8> ThisType;
	ArgF8(const typename Parent::FuncType& f, const A1& a1, const A2& a2, const A3& a3,
			const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8) :
			_a1(a1), _a2(a2), _a3(a3), _a4(a4), _a5(a5), _a6(a6), _a7(a7), _a8(a8) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
	}

	virtual ~ArgF8() {
	}

	virtual R operator()() {
		return this->func(_a1, _a2, _a3, _a4, _a5, _a6, _a7, _a8);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return false;
	}
private:
	A1 _a1;
	A2 _a2;
	A3 _a3;
	A4 _a4;
	A5 _a5;
	A6 _a6;
	A7 _a7;
	A8 _a8;
};

template<class R, class C, class P1, class P2, class P3, class P4, class P5, class P6, class P7,
		class P8, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
class ArgF8Mem: public IFMem<R (C::*)(P1, P2, P3, P4, P5, P6, P7, P8), C>, public IFunction0<R> {
public:
	typedef IFMem<R (C::*)(P1, P2, P3, P4, P5, P6, P7, P8), C> Parent;
	typedef typename IFunction0<R>::ThisType PThisType;
	typedef ArgF8Mem<R, C, P1, P2, P3, P4, P5, P6, P7, P8, A1, A2, A3, A4, A5, A6, A7, A8> ThisType;
	ArgF8Mem(const typename Parent::FuncType& f, C* o, const A1& a1, const A2& a2, const A3& a3,
			const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8) :
			_a1(a1), _a2(a2), _a3(a3), _a4(a4), _a5(a5), _a6(a6), _a7(a7), _a8(a8) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
		this->obj = o;
	}

	virtual ~ArgF8Mem() {
	}

	virtual R operator()() {
		return (this->obj->*this->func)(_a1, _a2, _a3, _a4, _a5, _a6, _a7, _a8);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (!i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return true;
	}
private:
	A1 _a1;
	A2 _a2;
	A3 _a3;
	A4 _a4;
	A5 _a5;
	A6 _a6;
	A7 _a7;
	A8 _a8;
};

template<class R, class C, class P1, class P2, class P3, class P4, class P5, class P6, class P7,
		class P8, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
class ArgF8MemConst: public IFMem<R (C::*)(P1, P2, P3, P4, P5, P6, P7, P8) const, C>,
		public IFunction0<R> {
public:
	typedef IFMem<R (C::*)(P1, P2, P3, P4, P5, P6, P7, P8) const, C> Parent;
	typedef typename IFunction0<R>::ThisType PThisType;
	typedef ArgF8MemConst<R, C, P1, P2, P3, P4, P5, P6, P7, P8, A1, A2, A3, A4, A5, A6, A7, A8> ThisType;
	ArgF8MemConst(const typename Parent::FuncType& f, C* o, const A1& a1, const A2& a2,
			const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8) :
			_a1(a1), _a2(a2), _a3(a3), _a4(a4), _a5(a5), _a6(a6), _a7(a7), _a8(a8) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
		this->obj = o;
	}

	virtual ~ArgF8MemConst() {
	}

	virtual R operator()() {
		return (this->obj->*this->func)(_a1, _a2, _a3, _a4, _a5, _a6, _a7, _a8);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (!i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return true;
	}
private:
	A1 _a1;
	A2 _a2;
	A3 _a3;
	A4 _a4;
	A5 _a5;
	A6 _a6;
	A7 _a7;
	A8 _a8;
};

template<class R, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8,
		class P9, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8,
		class A9>
class ArgF9: public IF<R (*)(P1, P2, P3, P4, P5, P6, P7, P8, P9)>, public IFunction0<R> {
public:
	typedef IF<R (*)(P1, P2, P3, P4, P5, P6, P7, P8, P9)> Parent;
	typedef typename IFunction0<R>::ThisType PThisType;
	typedef ArgF9<R, P1, P2, P3, P4, P5, P6, P7, P8, P9, A1, A2, A3, A4, A5, A6, A7, A8, A9> ThisType;
	ArgF9(const typename Parent::FuncType& f, const A1& a1, const A2& a2, const A3& a3,
			const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9) :
			_a1(a1), _a2(a2), _a3(a3), _a4(a4), _a5(a5), _a6(a6), _a7(a7), _a8(a8), _a9(a9) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
	}

	virtual ~ArgF9() {
	}

	virtual R operator()() {
		return this->func(_a1, _a2, _a3, _a4, _a5, _a6, _a7, _a8, _a9);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return false;
	}
private:
	A1 _a1;
	A2 _a2;
	A3 _a3;
	A4 _a4;
	A5 _a5;
	A6 _a6;
	A7 _a7;
	A8 _a8;
	A9 _a9;
};

template<class R, class C, class P1, class P2, class P3, class P4, class P5, class P6, class P7,
		class P8, class P9, class A1, class A2, class A3, class A4, class A5, class A6, class A7,
		class A8, class A9>
class ArgF9Mem: public IFMem<R (C::*)(P1, P2, P3, P4, P5, P6, P7, P8, P9), C>, public IFunction0<R> {
public:
	typedef IFMem<R (C::*)(P1, P2, P3, P4, P5, P6, P7, P8, P9), C> Parent;
	typedef typename IFunction0<R>::ThisType PThisType;
	typedef ArgF9Mem<R, C, P1, P2, P3, P4, P5, P6, P7, P8, P9, A1, A2, A3, A4, A5, A6, A7, A8, A9> ThisType;
	ArgF9Mem(const typename Parent::FuncType& f, C* o, const A1& a1, const A2& a2, const A3& a3,
			const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9) :
			_a1(a1), _a2(a2), _a3(a3), _a4(a4), _a5(a5), _a6(a6), _a7(a7), _a8(a8), _a9(a9) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
		this->obj = o;
	}

	virtual ~ArgF9Mem() {
	}

	virtual R operator()() {
		return (this->obj->*this->func)(_a1, _a2, _a3, _a4, _a5, _a6, _a7, _a8, _a9);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (!i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return true;
	}
private:
	A1 _a1;
	A2 _a2;
	A3 _a3;
	A4 _a4;
	A5 _a5;
	A6 _a6;
	A7 _a7;
	A8 _a8;
	A9 _a9;
};

template<class R, class C, class P1, class P2, class P3, class P4, class P5, class P6, class P7,
		class P8, class P9, class A1, class A2, class A3, class A4, class A5, class A6, class A7,
		class A8, class A9>
class ArgF9MemConst: public IFMem<R (C::*)(P1, P2, P3, P4, P5, P6, P7, P8, P9) const, C>,
		public IFunction0<R> {
public:
	typedef IFMem<R (C::*)(P1, P2, P3, P4, P5, P6, P7, P8, P9) const, C> Parent;
	typedef typename IFunction0<R>::ThisType PThisType;
	typedef ArgF9MemConst<R, C, P1, P2, P3, P4, P5, P6, P7, P8, P9, A1, A2, A3, A4, A5, A6, A7, A8,
			A9> ThisType;
	ArgF9MemConst(const typename Parent::FuncType& f, C* o, const A1& a1, const A2& a2,
			const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8,
			const A9& a9) :
			_a1(a1), _a2(a2), _a3(a3), _a4(a4), _a5(a5), _a6(a6), _a7(a7), _a8(a8), _a9(a9) {
		assert(f);
		if (NULL == f) {
			THROW_EXCEPTION(FunctionException, "NULL function pointer", 0);
		}
		this->func = f;
		this->obj = o;
	}

	virtual ~ArgF9MemConst() {
	}

	virtual R operator()() {
		return (this->obj->*this->func)(_a1, _a2, _a3, _a4, _a5, _a6, _a7, _a8, _a9);
	}
	virtual PThisType* clone() {
		return new ThisType(*this);
	}
	virtual bool equals(const PThisType* i) const {
		if (!i->isMemberFunction())
			return false;
		const ThisType* ifun = (const ThisType*) i;
		if (NULL == ifun)
			return false;
		return (ifun->getFunction() == this->func);
	}
	virtual bool isMemberFunction() const {
		return true;
	}
private:
	A1 _a1;
	A2 _a2;
	A3 _a3;
	A4 _a4;
	A5 _a5;
	A6 _a6;
	A7 _a7;
	A8 _a8;
	A9 _a9;
};

template<class R>
class Function0 {
public:
	typedef IFunction0<R> FuncType;
	typedef Function0<R> ThisType;

	Function0(FuncType* func) :
			_func(func) {
	}
	~Function0() {
		if (this->_func)
			delete this->_func;
	}

	R operator()() {
		return (*this->_func)();
	}

	Function0(const Function0& f) {
		this->_func = f._func->clone();
	}

	ThisType operator=(const Function0& f) {
		this->_func = f._func->clone();
		return *this;
	}

	bool operator==(const ThisType& f) {
		return this->_func->equals(f._func);
	}

	bool operator!=(const ThisType& f) {
		return !this->operator==(f);
	}

private:
	FuncType* _func;
};

template<class R, class P1>
class Function1 {
public:
	typedef IFunction1<R, P1> FuncType;
	typedef Function1<R, P1> ThisType;

	Function1(FuncType* func) :
			_func(func) {
	}
	~Function1() {
		if (this->_func)
			delete this->_func;
	}

	R operator()(const P1& p1) {
		return (*this->_func)(p1);
	}

	Function1(const Function1& f) {
		this->_func = f._func->clone();
	}

	ThisType operator=(const Function1& f) {
		this->_func = f._func->clone();
		return *this;
	}

	bool operator==(const ThisType& f) {
		return this->_func->equals(f._func);
	}

	bool operator!=(const ThisType& f) {
		return !this->operator==(f);
	}

private:
	FuncType* _func;
};

template<class R, class P1, class P2>
class Function2 {
public:
	typedef IFunction2<R, P1, P2> FuncType;
	typedef Function2<R, P1, P2> ThisType;

	Function2(FuncType* func) :
			_func(func) {
	}
	~Function2() {
		if (this->_func)
			delete this->_func;
	}

	R operator()(const P1& p1, const P2& p2) {
		return (*this->_func)(p1, p2);
	}

	Function2(const Function2& f) {
		this->_func = f._func->clone();
	}

	ThisType operator=(const Function2& f) {
		this->_func = f._func->clone();
		return *this;
	}

	bool operator==(const ThisType& f) {
		return this->_func->equals(f._func);
	}

	bool operator!=(const ThisType& f) {
		return !this->operator==(f);
	}

private:
	FuncType* _func;
};

template<class R, class P1, class P2, class P3>
class Function3 {
public:
	typedef IFunction3<R, P1, P2, P3> FuncType;
	typedef Function3<R, P1, P2, P3> ThisType;

	Function3(FuncType* func) :
			_func(func) {
	}
	~Function3() {
		if (this->_func)
			delete this->_func;
	}

	R operator()(const P1& p1, const P2& p2, const P3& p3) {
		return (*this->_func)(p1, p2, p3);
	}

	Function3(const Function3& f) {
		this->_func = f._func->clone();
	}

	ThisType operator=(const Function3& f) {
		this->_func = f._func->clone();
		return *this;
	}

	bool operator==(const ThisType& f) {
		return this->_func->equals(f._func);
	}

	bool operator!=(const ThisType& f) {
		return !this->operator==(f);
	}

private:
	FuncType* _func;
};

template<class R, class P1, class P2, class P3, class P4>
class Function4 {
public:
	typedef IFunction4<R, P1, P2, P3, P4> FuncType;
	typedef Function4<R, P1, P2, P3, P4> ThisType;

	Function4(FuncType* func) :
			_func(func) {
	}
	~Function4() {
		if (this->_func)
			delete this->_func;
	}

	R operator()(const P1& p1, const P2& p2, const P3& p3, const P4& p4) {
		return (*this->_func)(p1, p2, p3, p4);
	}

	Function4(const Function4& f) {
		this->_func = f._func->clone();
	}

	ThisType operator=(const Function4& f) {
		this->_func = f._func->clone();
		return *this;
	}

	bool operator==(const ThisType& f) {
		return this->_func->equals(f._func);
	}

	bool operator!=(const ThisType& f) {
		return !this->operator==(f);
	}

private:
	FuncType* _func;
};

template<class R, class P1, class P2, class P3, class P4, class P5>
class Function5 {
public:
	typedef IFunction5<R, P1, P2, P3, P4, P5> FuncType;
	typedef Function5<R, P1, P2, P3, P4, P5> ThisType;

	Function5(FuncType* func) :
			_func(func) {
	}
	~Function5() {
		if (this->_func)
			delete this->_func;
	}

	R operator()(const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5) {
		return (*this->_func)(p1, p2, p3, p4, p5);
	}

	Function5(const Function5& f) {
		this->_func = f._func->clone();
	}

	ThisType operator=(const Function5& f) {
		this->_func = f._func->clone();
		return *this;
	}

	bool operator==(const ThisType& f) {
		return this->_func->equals(f._func);
	}

	bool operator!=(const ThisType& f) {
		return !this->operator==(f);
	}

private:
	FuncType* _func;
};

template<class R, class P1, class P2, class P3, class P4, class P5, class P6>
class Function6 {
public:
	typedef IFunction6<R, P1, P2, P3, P4, P5, P6> FuncType;
	typedef Function6<R, P1, P2, P3, P4, P5, P6> ThisType;

	Function6(FuncType* func) :
			_func(func) {
	}
	~Function6() {
		if (this->_func)
			delete this->_func;
	}

	R operator()(const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5,
			const P6& p6) {
		return (*this->_func)(p1, p2, p3, p4, p5, p6);
	}

	Function6(const Function6& f) {
		this->_func = f._func->clone();
	}

	ThisType operator=(const Function6& f) {
		this->_func = f._func->clone();
		return *this;
	}

	bool operator==(const ThisType& f) {
		return this->_func->equals(f._func);
	}

	bool operator!=(const ThisType& f) {
		return !this->operator==(f);
	}

private:
	FuncType* _func;
};

template<class R, class P1, class P2, class P3, class P4, class P5, class P6, class P7>
class Function7 {
public:
	typedef IFunction7<R, P1, P2, P3, P4, P5, P6, P7> FuncType;
	typedef Function7<R, P1, P2, P3, P4, P5, P6, P7> ThisType;

	Function7(FuncType* func) :
			_func(func) {
	}
	~Function7() {
		if (this->_func)
			delete this->_func;
	}

	R operator()(const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5, const P6& p6,
			const P7& p7) {
		return (*this->_func)(p1, p2, p3, p4, p5, p6, p7);
	}

	Function7(const Function7& f) {
		this->_func = f._func->clone();
	}

	ThisType operator=(const Function7& f) {
		this->_func = f._func->clone();
		return *this;
	}

	bool operator==(const ThisType& f) {
		return this->_func->equals(f._func);
	}

	bool operator!=(const ThisType& f) {
		return !this->operator==(f);
	}

private:
	FuncType* _func;
};

template<class R, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8>
class Function8 {
public:
	typedef IFunction8<R, P1, P2, P3, P4, P5, P6, P7, P8> FuncType;
	typedef Function8<R, P1, P2, P3, P4, P5, P6, P7, P8> ThisType;

	Function8(FuncType* func) :
			_func(func) {
	}
	~Function8() {
		if (this->_func)
			delete this->_func;
	}

	R operator()(const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5, const P6& p6,
			const P7& p7, const P8& p8) {
		return (*this->_func)(p1, p2, p3, p4, p5, p6, p7, p8);
	}

	Function8(const Function8& f) {
		this->_func = f._func->clone();
	}

	ThisType operator=(const Function8& f) {
		this->_func = f._func->clone();
		return *this;
	}

	bool operator==(const ThisType& f) {
		return this->_func->equals(f._func);
	}

	bool operator!=(const ThisType& f) {
		return !this->operator==(f);
	}

private:
	FuncType* _func;
};

template<class R, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8,
		class P9>
class Function9 {
public:
	typedef IFunction9<R, P1, P2, P3, P4, P5, P6, P7, P8, P9> FuncType;
	typedef Function9<R, P1, P2, P3, P4, P5, P6, P7, P8, P9> ThisType;

	Function9(FuncType* func) :
			_func(func) {
	}
	~Function9() {
		if (this->_func)
			delete this->_func;
	}

	R operator()(const P1& p1, const P2& p2, const P3& p3, const P4& p4, const P5& p5, const P6& p6,
			const P7& p7, const P8& p8, const P9& p9) {
		return (*this->_func)(p1, p2, p3, p4, p5, p6, p7, p8, p9);
	}

	Function9(const Function9& f) {
		this->_func = f._func->clone();
	}

	ThisType operator=(const Function9& f) {
		this->_func = f._func->clone();
		return *this;
	}

	bool operator==(const ThisType& f) {
		return this->_func->equals(f._func);
	}

	bool operator!=(const ThisType& f) {
		return !this->operator==(f);
	}

private:
	FuncType* _func;
};

} /* namespace function */
} /* namespace ducky */

#endif /* DUCKY_FUNCTION_FUNCTION_H_ */
