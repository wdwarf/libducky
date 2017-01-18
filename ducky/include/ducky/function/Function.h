/*
 * Function.h
 *
 *  Created on: Nov 5, 2016
 *      Author: ducky
 */

#ifndef DUCKY_FUNCTION_FUNCTION_H_
#define DUCKY_FUNCTION_FUNCTION_H_

#include <iostream>
using namespace std;

namespace ducky {
namespace function {

template<class R>
class IFunction0 {
public:
	IFunction0() {
	}
	virtual ~IFunction0() {
	}

	virtual R operator()() = 0;
};

template<class R, class P1>
class IFunction1 {
public:
	IFunction1() {
	}
	virtual ~IFunction1() {
	}

	virtual R operator()(P1) = 0;
};

template<class R, class P1, class P2>
class IFunction2 {
public:
	IFunction2() {
	}
	virtual ~IFunction2() {
	}

	virtual R operator()(P1, P2) = 0;
};

template<class R, class P1, class P2, class P3>
class IFunction3 {
public:
	IFunction3() {
	}
	virtual ~IFunction3() {
	}

	virtual R operator()(P1, P2, P3) = 0;
};

template<class R, class P1, class P2, class P3, class P4>
class IFunction4 {
public:
	IFunction4() {
	}
	virtual ~IFunction4() {
	}

	virtual R operator()(P1, P2, P3, P4) = 0;
};

template<class R, class P1, class P2, class P3, class P4, class P5>
class IFunction5 {
public:
	IFunction5() {
	}
	virtual ~IFunction5() {
	}

	virtual R operator()(P1, P2, P3, P4, P5) = 0;
};

template<class R, class P1, class P2, class P3, class P4, class P5, class P6>
class IFunction6 {
public:
	IFunction6() {
	}
	virtual ~IFunction6() {
	}

	virtual R operator()(P1, P2, P3, P4, P5, P6) = 0;
};

template<class R, class P1, class P2, class P3, class P4, class P5, class P6,
		class P7>
class IFunction7 {
public:
	IFunction7() {
	}
	virtual ~IFunction7() {
	}

	virtual R operator()(P1, P2, P3, P4, P5, P6, P7) = 0;
};

template<class R, class P1, class P2, class P3, class P4, class P5, class P6,
		class P7, class P8>
class IFunction8 {
public:
	IFunction8() {
	}
	virtual ~IFunction8() {
	}

	virtual R operator()(P1, P2, P3, P4, P5, P6, P7, P8) = 0;
};

template<class R, class P1, class P2, class P3, class P4, class P5, class P6,
		class P7, class P8, class P9>
class IFunction9 {
public:
	IFunction9() {
	}
	virtual ~IFunction9() {
	}

	virtual R operator()(P1, P2, P3, P4, P5, P6, P7, P8, P9) = 0;
};

template<class R>
class FunctionBase0: public IFunction0<R> {
public:
	typedef R (*Func)();

	FunctionBase0(const Func& f) {
		this->f = f;
	}
	virtual ~FunctionBase0() {
	}

	virtual R operator()() {
		return f();
	}

private:
	Func f;
};

template<class R, class P1>
class FunctionBase1: public IFunction1<R, P1> {
public:
	typedef R (*Func)(P1);

	FunctionBase1(const Func& f) {
		this->f = f;
	}
	virtual ~FunctionBase1() {
	}

	virtual R operator()(P1 p1) {
		return f(p1);
	}

private:
	Func f;
};

template<class R, class P1, class P2>
class FunctionBase2: public IFunction2<R, P1, P2> {
public:
	typedef R (*Func)(P1, P2);

	FunctionBase2(const Func& f) {
		this->f = f;
	}
	virtual ~FunctionBase2() {
	}

	virtual R operator()(P1 p1, P2 p2) {
		return f(p1, p2);
	}

private:
	Func f;
};

template<class R, class P1, class P2, class P3>
class FunctionBase3: public IFunction3<R, P1, P2, P3> {
public:
	typedef R (*Func)(P1, P2, P3);

	FunctionBase3(const Func& f) {
		this->f = f;
	}
	virtual ~FunctionBase3() {
	}

	virtual R operator()(P1 p1, P2 p2, P3 p3) {
		return f(p1, p2, p3);
	}

private:
	Func f;
};

template<class R, class P1, class P2, class P3, class P4>
class FunctionBase4: public IFunction4<R, P1, P2, P3, P4> {
public:
	typedef R (*Func)(P1, P2, P3, P4);

	FunctionBase4(const Func& f) {
		this->f = f;
	}
	virtual ~FunctionBase4() {
	}

	virtual R operator()(P1 p1, P2 p2, P3 p3, P4 p4) {
		return f(p1, p2, p3, p4);
	}

private:
	Func f;
};

template<class R, class P1, class P2, class P3, class P4, class P5>
class FunctionBase5: public IFunction5<R, P1, P2, P3, P4, P5> {
public:
	typedef R (*Func)(P1, P2, P3, P4, P5);

	FunctionBase5(const Func& f) {
		this->f = f;
	}
	virtual ~FunctionBase5() {
	}

	virtual R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5) {
		return f(p1, p2, p3, p4, p5);
	}

private:
	Func f;
};

template<class R, class P1, class P2, class P3, class P4, class P5, class P6>
class FunctionBase6: public IFunction6<R, P1, P2, P3, P4, P5, P6> {
public:
	typedef R (*Func)(P1, P2, P3, P4, P5, P6);

	FunctionBase6(const Func& f) {
		this->f = f;
	}
	virtual ~FunctionBase6() {
	}

	virtual R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6) {
		return f(p1, p2, p3, p4, p5, p6);
	}

private:
	Func f;
};

template<class R, class P1, class P2, class P3, class P4, class P5, class P6,
		class P7>
class FunctionBase7: public IFunction7<R, P1, P2, P3, P4, P5, P6, P7> {
public:
	typedef R (*Func)(P1, P2, P3, P4, P5, P6, P7);

	FunctionBase7(const Func& f) {
		this->f = f;
	}
	virtual ~FunctionBase7() {
	}

	virtual R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7) {
		return f(p1, p2, p3, p4, p5, p6, p7);
	}

private:
	Func f;
};

template<class R, class P1, class P2, class P3, class P4, class P5, class P6,
		class P7, class P8>
class FunctionBase8: public IFunction8<R, P1, P2, P3, P4, P5, P6, P7, P8> {
public:
	typedef R (*Func)(P1, P2, P3, P4, P5, P6, P7, P8);

	FunctionBase8(const Func& f) {
		this->f = f;
	}
	virtual ~FunctionBase8() {
	}

	virtual R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7,
			P8 p8) {
		return f(p1, p2, p3, p4, p5, p6, p7, p8);
	}

private:
	Func f;
};

template<class R, class P1, class P2, class P3, class P4, class P5, class P6,
		class P7, class P8, class P9>
class FunctionBase9: public IFunction9<R, P1, P2, P3, P4, P5, P6, P7, P8, P9> {
public:
	typedef R (*Func)(P1, P2, P3, P4, P5, P6, P7, P8, P9);

	FunctionBase9(const Func& f) {
		this->f = f;
	}
	virtual ~FunctionBase9() {
	}

	virtual R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8,
			P9 p9) {
		return f(p1, p2, p3, p4, p5, p6, p7, p8, p9);
	}

private:
	Func f;
};

template<class R, class C>
class FunctionBaseM0: public IFunction0<R> {
public:
	typedef R (C::*Func)();

	FunctionBaseM0(const Func& f, C* c) {
		this->f = f;
		this->c = c;
	}
	virtual ~FunctionBaseM0() {
	}

	virtual R operator()() {
		return (c->*f)();
	}

private:
	Func f;
	C* c;
};

template<class R, class C, class P1>
class FunctionBaseM1: public IFunction1<R, P1> {
public:
	typedef R (C::*Func)(P1);

	FunctionBaseM1(const Func& f, C* c) {
		this->f = f;
		this->c = c;
	}
	virtual ~FunctionBaseM1() {
	}

	virtual R operator()(P1 p1) {
		return (c->*f)(p1);
	}

private:
	Func f;
	C* c;
};

template<class R, class C, class P1, class P2>
class FunctionBaseM2: public IFunction2<R, P1, P2> {
public:
	typedef R (C::*Func)(P1, P2);

	FunctionBaseM2(const Func& f, C* c) {
		this->f = f;
		this->c = c;
	}
	virtual ~FunctionBaseM2() {
	}

	virtual R operator()(P1 p1, P2 p2) {
		return (c->*f)(p1, p2);
	}

private:
	Func f;
	C* c;
};

template<class R, class C, class P1, class P2, class P3>
class FunctionBaseM3: public IFunction3<R, P1, P2, P3> {
public:
	typedef R (C::*Func)(P1, P2, P3);

	FunctionBaseM3(const Func& f, C* c) {
		this->f = f;
		this->c = c;
	}
	virtual ~FunctionBaseM3() {
	}

	virtual R operator()(P1 p1, P2 p2, P3 p3) {
		return (c->*f)(p1, p2, p3);
	}

private:
	Func f;
	C* c;
};

template<class R, class C, class P1, class P2, class P3, class P4>
class FunctionBaseM4: public IFunction4<R, P1, P2, P3, P4> {
public:
	typedef R (C::*Func)(P1, P2, P3, P4);

	FunctionBaseM4(const Func& f, C* c) {
		this->f = f;
		this->c = c;
	}
	virtual ~FunctionBaseM4() {
	}

	virtual R operator()(P1 p1, P2 p2, P3 p3, P4 p4) {
		return (c->*f)(p1, p2, p3, p4);
	}

private:
	Func f;
	C* c;
};

template<class R, class C, class P1, class P2, class P3, class P4, class P5>
class FunctionBaseM5: public IFunction5<R, P1, P2, P3, P4, P5> {
public:
	typedef R (C::*Func)(P1, P2, P3, P4, P5);

	FunctionBaseM5(const Func& f, C* c) {
		this->f = f;
		this->c = c;
	}
	virtual ~FunctionBaseM5() {
	}

	virtual R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5) {
		return (c->*f)(p1, p2, p3, p4, p5);
	}

private:
	Func f;
	C* c;
};

template<class R, class C, class P1, class P2, class P3, class P4, class P5,
		class P6>
class FunctionBaseM6: public IFunction6<R, P1, P2, P3, P4, P5, P6> {
public:
	typedef R (C::*Func)(P1, P2, P3, P4, P5, P6);

	FunctionBaseM6(const Func& f, C* c) {
		this->f = f;
		this->c = c;
	}
	virtual ~FunctionBaseM6() {
	}

	virtual R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6) {
		return (c->*f)(p1, p2, p3, p4, p5, p6);
	}

private:
	Func f;
	C* c;
};

template<class R, class C, class P1, class P2, class P3, class P4, class P5,
		class P6, class P7>
class FunctionBaseM7: public IFunction7<R, P1, P2, P3, P4, P5, P6, P7> {
public:
	typedef R (C::*Func)(P1, P2, P3, P4, P5, P6, P7);

	FunctionBaseM7(const Func& f, C* c) {
		this->f = f;
		this->c = c;
	}
	virtual ~FunctionBaseM7() {
	}

	virtual R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7) {
		return (c->*f)(p1, p2, p3, p4, p5, p6, p7);
	}

private:
	Func f;
	C* c;
};

template<class R, class C, class P1, class P2, class P3, class P4, class P5,
		class P6, class P7, class P8>
class FunctionBaseM8: public IFunction8<R, P1, P2, P3, P4, P5, P6, P7, P8> {
public:
	typedef R (C::*Func)(P1, P2, P3, P4, P5, P6, P7, P8);

	FunctionBaseM8(const Func& f, C* c) {
		this->f = f;
		this->c = c;
	}
	virtual ~FunctionBaseM8() {
	}

	virtual R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7,
			P8 p8) {
		return (c->*f)(p1, p2, p3, p4, p5, p6, p7, p8);
	}

private:
	Func f;
	C* c;
};

template<class R, class C, class P1, class P2, class P3, class P4, class P5,
		class P6, class P7, class P8, class P9>
class FunctionBaseM9: public IFunction9<R, P1, P2, P3, P4, P5, P6, P7, P8, P9> {
public:
	typedef R (C::*Func)(P1, P2, P3, P4, P5, P6, P7, P8, P9);

	FunctionBaseM9(const Func& f, C* c) {
		this->f = f;
		this->c = c;
	}
	virtual ~FunctionBaseM9() {
	}

	virtual R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8,
			P9 p9) {
		return (c->*f)(p1, p2, p3, p4, p5, p6, p7, p8, p9);
	}

private:
	Func f;
	C* c;
};

template<class R>
class Function0 {
public:
	Function0(R (*Func)()) {
		pfunc = new FunctionBase0<R>(Func);
	}
	template<class C> Function0(R (C::*Func)(), C* c) {
		pfunc = new FunctionBaseM0<R, C>(Func, c);
	}
	virtual ~Function0() {
		delete pfunc;
	}

	R operator()() {
		return (*pfunc)();
	}

private:
	IFunction0<R>* pfunc;
};

template<class R, class P1>
class Function1 {
public:
	Function1(R (*Func)(P1)) {
		pfunc = new FunctionBase1<R, P1>(Func);
	}
	template<class C> Function1(R (C::*Func)(P1), C* c) {
		pfunc = new FunctionBaseM1<R, C, P1>(Func, c);
	}
	virtual ~Function1() {
		delete pfunc;
	}

	R operator()(P1 p1) {
		return (*pfunc)(p1);
	}

private:
	IFunction1<R, P1>* pfunc;
};

template<class R, class P1, class P2>
class Function2 {
public:
	Function2(R (*Func)(P1, P2)) {
		pfunc = new FunctionBase2<R, P1, P2>(Func);
	}
	template<class C> Function2(R (C::*Func)(P1, P2), C* c) {
		pfunc = new FunctionBaseM2<R, C, P1, P2>(Func, c);
	}
	virtual ~Function2() {
		delete pfunc;
	}

	R operator()(P1 p1, P2 p2) {
		return (*pfunc)(p1, p2);
	}

private:
	IFunction2<R, P1, P2>* pfunc;
};

template<class R, class P1, class P2, class P3>
class Function3 {
public:
	Function3(R (*Func)(P1, P2, P3)) {
		pfunc = new FunctionBase3<R, P1, P2, P3>(Func);
	}
	template<class C> Function3(R (C::*Func)(P1, P2, P3), C* c) {
		pfunc = new FunctionBaseM3<R, C, P1, P2, P3>(Func, c);
	}
	virtual ~Function3() {
		delete pfunc;
	}

	R operator()(P1 p1, P2 p2, P3 p3) {
		return (*pfunc)(p1, p2, p3);
	}

private:
	IFunction3<R, P1, P2, P3>* pfunc;
};

template<class R, class P1, class P2, class P3, class P4>
class Function4 {
public:
	Function4(R (*Func)(P1, P2, P3, P4)) {
		pfunc = new FunctionBase4<R, P1, P2, P3, P4>(Func);
	}
	template<class C> Function4(R (C::*Func)(P1, P2, P3, P4), C* c) {
		pfunc = new FunctionBaseM4<R, C, P1, P2, P3, P4>(Func, c);
	}
	virtual ~Function4() {
		delete pfunc;
	}

	R operator()(P1 p1, P2 p2, P3 p3, P4 p4) {
		return (*pfunc)(p1, p2, p3, p4);
	}

private:
	IFunction4<R, P1, P2, P3, P4>* pfunc;
};

template<class R, class P1, class P2, class P3, class P4, class P5>
class Function5 {
public:
	Function5(R (*Func)(P1, P2, P3, P4, P5)) {
		pfunc = new FunctionBase5<R, P1, P2, P3, P4, P5>(Func);
	}
	template<class C> Function5(R (C::*Func)(P1, P2, P3, P4, P5), C* c) {
		pfunc = new FunctionBaseM5<R, C, P1, P2, P3, P4, P5>(Func, c);
	}
	virtual ~Function5() {
		delete pfunc;
	}

	R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5) {
		return (*pfunc)(p1, p2, p3, p4, p5);
	}

private:
	IFunction5<R, P1, P2, P3, P4, P5>* pfunc;
};

template<class R, class P1, class P2, class P3, class P4, class P5, class P6>
class Function6 {
public:
	Function6(R (*Func)(P1, P2, P3, P4, P5, P6)) {
		pfunc = new FunctionBase6<R, P1, P2, P3, P4, P5, P6>(Func);
	}
	template<class C> Function6(R (C::*Func)(P1, P2, P3, P4, P5, P6), C* c) {
		pfunc = new FunctionBaseM6<R, C, P1, P2, P3, P4, P5, P6>(Func, c);
	}
	virtual ~Function6() {
		delete pfunc;
	}

	R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6) {
		return (*pfunc)(p1, p2, p3, p4, p5, p6);
	}

private:
	IFunction6<R, P1, P2, P3, P4, P5, P6>* pfunc;
};

template<class R, class P1, class P2, class P3, class P4, class P5, class P6,
		class P7>
class Function7 {
public:
	Function7(R (*Func)(P1, P2, P3, P4, P5, P6, P7)) {
		pfunc = new FunctionBase7<R, P1, P2, P3, P4, P5, P6, P7>(Func);
	}
	template<class C> Function7(R (C::*Func)(P1, P2, P3, P4, P5, P6, P7),
			C* c) {
		pfunc = new FunctionBaseM7<R, C, P1, P2, P3, P4, P5, P6, P7>(Func, c);
	}
	virtual ~Function7() {
		delete pfunc;
	}

	R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7) {
		return (*pfunc)(p1, p2, p3, p4, p5, p6, p7);
	}

private:
	IFunction7<R, P1, P2, P3, P4, P5, P6, P7>* pfunc;
};

template<class R, class P1, class P2, class P3, class P4, class P5, class P6,
		class P7, class P8>
class Function8 {
public:
	Function8(R (*Func)(P1, P2, P3, P4, P5, P6, P7, P8)) {
		pfunc = new FunctionBase8<R, P1, P2, P3, P4, P5, P6, P7, P8>(Func);
	}
	template<class C> Function8(R (C::*Func)(P1, P2, P3, P4, P5, P6, P7, P8),
			C* c) {
		pfunc = new FunctionBaseM8<R, C, P1, P2, P3, P4, P5, P6, P7, P8>(Func,
				c);
	}
	virtual ~Function8() {
		delete pfunc;
	}

	R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8) {
		return (*pfunc)(p1, p2, p3, p4, p5, p6, p7, p8);
	}

private:
	IFunction8<R, P1, P2, P3, P4, P5, P6, P7, P8>* pfunc;
};

template<class R, class P1, class P2, class P3, class P4, class P5, class P6,
		class P7, class P8, class P9>
class Function9 {
public:
	Function9(R (*Func)(P1, P2, P3, P4, P5, P6, P7, P8, P9)) {
		pfunc = new FunctionBase9<R, P1, P2, P3, P4, P5, P6, P7, P8, P9>(Func);
	}
	template<class C> Function9(
			R (C::*Func)(P1, P2, P3, P4, P5, P6, P7, P8, P9), C* c) {
		pfunc = new FunctionBaseM9<R, C, P1, P2, P3, P4, P5, P6, P7, P8, P9>(
				Func, c);
	}
	virtual ~Function9() {
		delete pfunc;
	}

	R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8,
			P9 p9) {
		return (*pfunc)(p1, p2, p3, p4, p5, p6, p7, p8, p9);
	}

private:
	IFunction9<R, P1, P2, P3, P4, P5, P6, P7, P8, P9>* pfunc;
};

} /* namespace function */
} /* namespace ducky */

#endif /* DUCKY_FUNCTION_FUNCTION_H_ */
