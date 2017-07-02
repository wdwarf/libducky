/*
 * Function.h
 *
 *  Created on: Nov 5, 2016
 *      Author: ducky
 */

#ifndef DUCKY_FUNCTION_FUNCTION_H_
#define DUCKY_FUNCTION_FUNCTION_H_

#include <ducky/function/FunctionException.h>

namespace ducky {
namespace function {
template<class R>
class FunctionBase0 {
public:
	typedef R (*Func)();
	typedef FunctionBase0<R> ThisType;

	FunctionBase0(const Func& f) {
		memset(this->f, 0, sizeof(this->f));
		this->f[0] = (void*) f;
	}
	virtual ~FunctionBase0() {
	}

	virtual R operator()() {
		return ((Func) this->f[0])();
	}

	virtual ThisType* clone() {
		return new ThisType((Func) this->f[0]);
	}

<<<<<<< HEAD
	bool compare(const ThisType* func) {
		return (0 == memcmp(this->f, func->f, sizeof(this->f)));
	}

protected:
	void* f[3];
	FunctionBase0(const void* f) {
		memcpy(this->f, f, sizeof(this->f));
	}
=======
	virtual bool compare(FunctionBase0* f){
		return (this->f == f->f);
	}

private:
	Func f;
>>>>>>> f4207ded7cfbbe32d619ea7f67ddba451817fc94
};

template<class R, class P1>
class FunctionBase1 {
public:
	typedef R (*Func)(P1);
	typedef FunctionBase1<R, P1> ThisType;

	FunctionBase1(const Func& f) {
		memset(this->f, 0, sizeof(this->f));
		this->f[0] = (void*) f;
	}
	virtual ~FunctionBase1() {
	}

	virtual R operator()(P1 p1) {
		return ((Func) this->f[0])(p1);
	}

	virtual ThisType* clone() {
		return new ThisType((Func) this->f[0]);
	}

	bool compare(const ThisType* func) {
		return (0 == memcmp(this->f, func->f, sizeof(this->f)));
	}

protected:
	void* f[3];
	FunctionBase1(const void* f) {
		memcpy(this->f, f, sizeof(this->f));
	}
};

template<class R, class P1, class P2>
class FunctionBase2 {
public:
	typedef R (*Func)(P1, P2);
	typedef FunctionBase2<R, P1, P2> ThisType;

	FunctionBase2(const Func& f) {
		memset(this->f, 0, sizeof(this->f));
		this->f[0] = (void*) f;
	}
	virtual ~FunctionBase2() {
	}

	virtual R operator()(P1 p1, P2 p2) {
		return ((Func) this->f[0])(p1, p2);
	}

	virtual ThisType* clone() {
		return new ThisType((Func) this->f[0]);
	}

	bool compare(const ThisType* func) {
		return (0 == memcmp(this->f, func->f, sizeof(this->f)));
	}

protected:
	void* f[3];
	FunctionBase2(const void* f) {
		memcpy(this->f, f, sizeof(this->f));
	}
};

template<class R, class P1, class P2, class P3>
class FunctionBase3 {
public:
	typedef R (*Func)(P1, P2, P3);
	typedef FunctionBase3<R, P1, P2, P3> ThisType;

	FunctionBase3(const Func& f) {
		memset(this->f, 0, sizeof(this->f));
		this->f[0] = (void*) f;
	}
	virtual ~FunctionBase3() {
	}

	virtual R operator()(P1 p1, P2 p2, P3 p3) {
		return ((Func) this->f[0])(p1, p2, p3);
	}

	virtual ThisType* clone() {
		return new ThisType((Func) this->f[0]);
	}

	bool compare(const ThisType* func) {
		return (0 == memcmp(this->f, func->f, sizeof(this->f)));
	}

protected:
	void* f[3];
	FunctionBase3(const void* f) {
		memcpy(this->f, f, sizeof(this->f));
	}
};

template<class R, class P1, class P2, class P3, class P4>
class FunctionBase4 {
public:
	typedef R (*Func)(P1, P2, P3, P4);
	typedef FunctionBase4<R, P1, P2, P3, P4> ThisType;

	FunctionBase4(const Func& f) {
		memset(this->f, 0, sizeof(this->f));
		this->f[0] = (void*) f;
	}
	virtual ~FunctionBase4() {
	}

	virtual R operator()(P1 p1, P2 p2, P3 p3, P4 p4) {
		return ((Func) this->f[0])(p1, p2, p3, p4);
	}

	virtual ThisType* clone() {
		return new ThisType((Func) this->f[0]);
	}

	bool compare(const ThisType* func) {
		return (0 == memcmp(this->f, func->f, sizeof(this->f)));
	}

protected:
	void* f[3];
	FunctionBase4(const void* f) {
		memcpy(this->f, f, sizeof(this->f));
	}
};

template<class R, class P1, class P2, class P3, class P4, class P5>
class FunctionBase5 {
public:
	typedef R (*Func)(P1, P2, P3, P4, P5);
	typedef FunctionBase5<R, P1, P2, P3, P4, P5> ThisType;

	FunctionBase5(const Func& f) {
		memset(this->f, 0, sizeof(this->f));
		this->f[0] = (void*) f;
	}
	virtual ~FunctionBase5() {
	}

	virtual R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5) {
		return ((Func) this->f[0])(p1, p2, p3, p4, p5);
	}

	virtual ThisType* clone() {
		return new ThisType((Func) this->f[0]);
	}

	bool compare(const ThisType* func) {
		return (0 == memcmp(this->f, func->f, sizeof(this->f)));
	}

protected:
	void* f[3];
	FunctionBase5(const void* f) {
		memcpy(this->f, f, sizeof(this->f));
	}
};

template<class R, class P1, class P2, class P3, class P4, class P5, class P6>
class FunctionBase6 {
public:
	typedef R (*Func)(P1, P2, P3, P4, P5, P6);
	typedef FunctionBase6<R, P1, P2, P3, P4, P5, P6> ThisType;

	FunctionBase6(const Func& f) {
		memset(this->f, 0, sizeof(this->f));
		this->f[0] = (void*) f;
	}
	virtual ~FunctionBase6() {
	}

	virtual R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6) {
		return ((Func) this->f[0])(p1, p2, p3, p4, p5, p6);
	}

	virtual ThisType* clone() {
		return new ThisType((Func) this->f[0]);
	}

	bool compare(const ThisType* func) {
		return (0 == memcmp(this->f, func->f, sizeof(this->f)));
	}

protected:
	void* f[3];
	FunctionBase6(const void* f) {
		memcpy(this->f, f, sizeof(this->f));
	}
};

template<class R, class P1, class P2, class P3, class P4, class P5, class P6,
		class P7>
class FunctionBase7 {
public:
	typedef R (*Func)(P1, P2, P3, P4, P5, P6, P7);
	typedef FunctionBase7<R, P1, P2, P3, P4, P5, P6, P7> ThisType;

	FunctionBase7(const Func& f) {
		memset(this->f, 0, sizeof(this->f));
		this->f[0] = (void*) f;
	}
	virtual ~FunctionBase7() {
	}

	virtual R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7) {
		return ((Func) this->f[0])(p1, p2, p3, p4, p5, p6, p7);
	}

	virtual ThisType* clone() {
		return new ThisType((Func) this->f[0]);
	}

	bool compare(const ThisType* func) {
		return (0 == memcmp(this->f, func->f, sizeof(this->f)));
	}

protected:
	void* f[3];
	FunctionBase7(const void* f) {
		memcpy(this->f, f, sizeof(this->f));
	}
};

template<class R, class P1, class P2, class P3, class P4, class P5, class P6,
		class P7, class P8>
class FunctionBase8 {
public:
	typedef R (*Func)(P1, P2, P3, P4, P5, P6, P7, P8);
	typedef FunctionBase8<R, P1, P2, P3, P4, P5, P6, P7, P8> ThisType;

	FunctionBase8(const Func& f) {
		memset(this->f, 0, sizeof(this->f));
		this->f[0] = (void*) f;
	}
	virtual ~FunctionBase8() {
	}

	virtual R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7,
			P8 p8) {
		return ((Func) this->f[0])(p1, p2, p3, p4, p5, p6, p7, p8);
	}

	virtual ThisType* clone() {
		return new ThisType((Func) this->f[0]);
	}

	bool compare(const ThisType* func) {
		return (0 == memcmp(this->f, func->f, sizeof(this->f)));
	}

protected:
	void* f[3];
	FunctionBase8(const void* f) {
		memcpy(this->f, f, sizeof(this->f));
	}
};

template<class R, class P1, class P2, class P3, class P4, class P5, class P6,
		class P7, class P8, class P9>
class FunctionBase9 {
public:
	typedef R (*Func)(P1, P2, P3, P4, P5, P6, P7, P8, P9);
	typedef FunctionBase9<R, P1, P2, P3, P4, P5, P6, P7, P8, P9> ThisType;

	FunctionBase9(const Func& f) {
		memset(this->f, 0, sizeof(this->f));
		this->f[0] = (void*) f;
	}
	virtual ~FunctionBase9() {
	}

	virtual R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8,
			P9 p9) {
		return ((Func) this->f[0])(p1, p2, p3, p4, p5, p6, p7, p8, p9);
	}

	virtual ThisType* clone() {
		return new ThisType((Func) this->f[0]);
	}

	bool compare(const ThisType* func) {
		return (0 == memcmp(this->f, func->f, sizeof(this->f)));
	}

protected:
	void* f[3];
	FunctionBase9(const void* f) {
		memcpy(this->f, f, sizeof(this->f));
	}
};

template<class R, class C>
class FunctionBaseM0: public FunctionBase0<R> {
public:
	typedef R (C::*Func)();
	typedef FunctionBase0<R> IFuncType;
	typedef FunctionBaseM0<R, C> ThisType;

	FunctionBaseM0(const Func& f, C* c) :
			FunctionBase0<R>((void*) &f) {
		this->f[2] = (void*) c;
	}
	virtual ~FunctionBaseM0() {
	}

	virtual R operator()() {
		return (((C*) this->f[2])->**(Func*) this->f)();
	}

	virtual IFuncType* clone() {
		return new ThisType(*(Func*) this->f, ((C*) this->f[2]));
	}

};

template<class R, class C, class P1>
class FunctionBaseM1: public FunctionBase1<R, P1> {
public:
	typedef R (C::*Func)(P1);
	typedef FunctionBase1<R, P1> IFuncType;
	typedef FunctionBaseM1<R, C, P1> ThisType;

	FunctionBaseM1(const Func& f, C* c) :
			FunctionBase1<R, P1>((void*) &f) {
		this->f[2] = (void*) c;
	}
	virtual ~FunctionBaseM1() {
	}

	virtual R operator()(P1 p1) {
		return (((C*) this->f[2])->**(Func*) this->f)(p1);
	}

	virtual IFuncType* clone() {
		return new ThisType(*(Func*) this->f, ((C*) this->f[2]));
	}

};

template<class R, class C, class P1, class P2>
class FunctionBaseM2: public FunctionBase2<R, P1, P2> {
public:
	typedef R (C::*Func)(P1, P2);
	typedef FunctionBase2<R, P1, P2> IFuncType;
	typedef FunctionBaseM2<R, C, P1, P2> ThisType;

	FunctionBaseM2(const Func& f, C* c) :
			FunctionBase2<R, P1, P2>((void*) &f) {
		this->f[2] = (void*) c;
	}
	virtual ~FunctionBaseM2() {
	}

	virtual R operator()(P1 p1, P2 p2) {
		return (((C*) this->f[2])->**(Func*) this->f)(p1, p2);
	}

	virtual IFuncType* clone() {
		return new ThisType(*(Func*) this->f, ((C*) this->f[2]));
	}

};

template<class R, class C, class P1, class P2, class P3>
class FunctionBaseM3: public FunctionBase3<R, P1, P2, P3> {
public:
	typedef R (C::*Func)(P1, P2, P3);
	typedef FunctionBase3<R, P1, P2, P3> IFuncType;
	typedef FunctionBaseM3<R, C, P1, P2, P3> ThisType;

	FunctionBaseM3(const Func& f, C* c) :
			FunctionBase3<R, P1, P2, P3>((void*) &f) {
		this->f[2] = (void*) c;
	}
	virtual ~FunctionBaseM3() {
	}

	virtual R operator()(P1 p1, P2 p2, P3 p3) {
		return (((C*) this->f[2])->**(Func*) this->f)(p1, p2, p3);
	}

	virtual IFuncType* clone() {
		return new ThisType(*(Func*) this->f, ((C*) this->f[2]));
	}

};

template<class R, class C, class P1, class P2, class P3, class P4>
class FunctionBaseM4: public FunctionBase4<R, P1, P2, P3, P4> {
public:
	typedef R (C::*Func)(P1, P2, P3, P4);
	typedef FunctionBase4<R, P1, P2, P3, P4> IFuncType;
	typedef FunctionBaseM4<R, C, P1, P2, P3, P4> ThisType;

	FunctionBaseM4(const Func& f, C* c) :
			FunctionBase4<R, P1, P2, P3, P4>((void*) &f) {
		this->f[2] = (void*) c;
	}
	virtual ~FunctionBaseM4() {
	}

	virtual R operator()(P1 p1, P2 p2, P3 p3, P4 p4) {
		return (((C*) this->f[2])->**(Func*) this->f)(p1, p2, p3, p4);
	}

	virtual IFuncType* clone() {
		return new ThisType(*(Func*) this->f, ((C*) this->f[2]));
	}

};

template<class R, class C, class P1, class P2, class P3, class P4, class P5>
class FunctionBaseM5: public FunctionBase5<R, P1, P2, P3, P4, P5> {
public:
	typedef R (C::*Func)(P1, P2, P3, P4, P5);
	typedef FunctionBase5<R, P1, P2, P3, P4, P5> IFuncType;
	typedef FunctionBaseM5<R, C, P1, P2, P3, P4, P5> ThisType;

	FunctionBaseM5(const Func& f, C* c) :
			FunctionBase5<R, P1, P2, P3, P4, P5>((void*) &f) {
		this->f[2] = (void*) c;
	}
	virtual ~FunctionBaseM5() {
	}

	virtual R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5) {
		return (((C*) this->f[2])->**(Func*) this->f)(p1, p2, p3, p4, p5);
	}

	virtual IFuncType* clone() {
		return new ThisType(*(Func*) this->f, ((C*) this->f[2]));
	}

};

template<class R, class C, class P1, class P2, class P3, class P4, class P5,
		class P6>
class FunctionBaseM6: public FunctionBase6<R, P1, P2, P3, P4, P5, P6> {
public:
	typedef R (C::*Func)(P1, P2, P3, P4, P5, P6);
	typedef FunctionBase6<R, P1, P2, P3, P4, P5, P6> IFuncType;
	typedef FunctionBaseM6<R, C, P1, P2, P3, P4, P5, P6> ThisType;

	FunctionBaseM6(const Func& f, C* c) :
			FunctionBase6<R, P1, P2, P3, P4, P5, P6>((void*) &f) {
		this->f[2] = (void*) c;
	}
	virtual ~FunctionBaseM6() {
	}

	virtual R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6) {
		return (((C*) this->f[2])->**(Func*) this->f)(p1, p2, p3, p4, p5, p6);
	}

	virtual IFuncType* clone() {
		return new ThisType(*(Func*) this->f, ((C*) this->f[2]));
	}

};

template<class R, class C, class P1, class P2, class P3, class P4, class P5,
		class P6, class P7>
class FunctionBaseM7: public FunctionBase7<R, P1, P2, P3, P4, P5, P6, P7> {
public:
	typedef R (C::*Func)(P1, P2, P3, P4, P5, P6, P7);
	typedef FunctionBase7<R, P1, P2, P3, P4, P5, P6, P7> IFuncType;
	typedef FunctionBaseM7<R, C, P1, P2, P3, P4, P5, P6, P7> ThisType;

	FunctionBaseM7(const Func& f, C* c) :
			FunctionBase7<R, P1, P2, P3, P4, P5, P6, P7>((void*) &f) {
		this->f[2] = (void*) c;
	}
	virtual ~FunctionBaseM7() {
	}

	virtual R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7) {
		return (((C*) this->f[2])->**(Func*) this->f)(p1, p2, p3, p4, p5, p6,
				p7);
	}

	virtual IFuncType* clone() {
		return new ThisType(*(Func*) this->f, ((C*) this->f[2]));
	}

};

template<class R, class C, class P1, class P2, class P3, class P4, class P5,
		class P6, class P7, class P8>
class FunctionBaseM8: public FunctionBase8<R, P1, P2, P3, P4, P5, P6, P7, P8> {
public:
	typedef R (C::*Func)(P1, P2, P3, P4, P5, P6, P7, P8);
	typedef FunctionBase8<R, P1, P2, P3, P4, P5, P6, P7, P8> IFuncType;
	typedef FunctionBaseM8<R, C, P1, P2, P3, P4, P5, P6, P7, P8> ThisType;

	FunctionBaseM8(const Func& f, C* c) :
			FunctionBase8<R, P1, P2, P3, P4, P5, P6, P7, P8>((void*) &f) {
		this->f[2] = (void*) c;
	}
	virtual ~FunctionBaseM8() {
	}

	virtual R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7,
			P8 p8) {
		return (((C*) this->f[2])->**(Func*) this->f)(p1, p2, p3, p4, p5, p6,
				p7, p8);
	}

	virtual IFuncType* clone() {
		return new ThisType(*(Func*) this->f, ((C*) this->f[2]));
	}

};

template<class R, class C, class P1, class P2, class P3, class P4, class P5,
		class P6, class P7, class P8, class P9>
class FunctionBaseM9: public FunctionBase9<R, P1, P2, P3, P4, P5, P6, P7, P8, P9> {
public:
	typedef R (C::*Func)(P1, P2, P3, P4, P5, P6, P7, P8, P9);
	typedef FunctionBase9<R, P1, P2, P3, P4, P5, P6, P7, P8, P9> IFuncType;
	typedef FunctionBaseM9<R, C, P1, P2, P3, P4, P5, P6, P7, P8, P9> ThisType;

	FunctionBaseM9(const Func& f, C* c) :
			FunctionBase9<R, P1, P2, P3, P4, P5, P6, P7, P8, P9>((void*) &f) {
		this->f[2] = (void*) c;
	}
	virtual ~FunctionBaseM9() {
	}

	virtual R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8,
			P9 p9) {
		return (((C*) this->f[2])->**(Func*) this->f)(p1, p2, p3, p4, p5, p6,
				p7, p8, p9);
	}

	virtual IFuncType* clone() {
		return new ThisType(*(Func*) this->f, ((C*) this->f[2]));
	}

};

template<class R>
class Function0 {
public:
	typedef FunctionBase0<R> IFuncType;
	typedef Function0<R> ThisType;

	Function0() :
			pfunc(0) {
	}

	Function0(const ThisType& f) {
		this->pfunc = f.pfunc->clone();
	}

	Function0(R (*Func)()) {
		pfunc = new FunctionBase0<R>(Func);
	}
	template<class C> Function0(R (C::*Func)(), C* c) {
		pfunc = new FunctionBaseM0<R, C>(Func, c);
	}
	virtual ~Function0() {
		if (pfunc)
			delete pfunc;
	}

	R operator()() {
		if (!pfunc) {
			THROW_EXCEPTION(FunctionException, "function not defined", 0);
		}
		return (*pfunc)();
	}

	ThisType& operator=(const ThisType& f) {
		if (this->pfunc) {
			delete this->pfunc;
		}
		this->pfunc = f.pfunc->clone();
		return *this;
	}

	bool operator==(const ThisType& f) {
		if (!this->pfunc || !f.pfunc) {
			return (this->pfunc == f.pfunc);
		}
		return this->pfunc->compare(f.pfunc);
	}
private:
	IFuncType* pfunc;
};

template<class R, class P1>
class Function1 {
public:
	typedef FunctionBase1<R, P1> IFuncType;
	typedef Function1<R, P1> ThisType;

	Function1() :
			pfunc(0) {
	}

	Function1(const ThisType& f) {
		this->pfunc = f.pfunc->clone();
	}

	Function1(R (*Func)(P1)) {
		pfunc = new FunctionBase1<R, P1>(Func);
	}
	template<class C> Function1(R (C::*Func)(P1), C* c) {
		pfunc = new FunctionBaseM1<R, C, P1>(Func, c);
	}
	virtual ~Function1() {
		if (pfunc)
			delete pfunc;
	}

	R operator()(P1 p1) {
		if (!pfunc) {
			THROW_EXCEPTION(FunctionException, "function not defined", 0);
		}
		return (*pfunc)(p1);
	}

	ThisType& operator=(const ThisType& f) {
		if (this->pfunc) {
			delete this->pfunc;
		}
		this->pfunc = f.pfunc->clone();
		return *this;
	}

	bool operator==(const ThisType& f) {
		if (!this->pfunc || !f.pfunc) {
			return (this->pfunc == f.pfunc);
		}
		return this->pfunc->compare(f.pfunc);
	}
private:
	IFuncType* pfunc;
};

template<class R, class P1, class P2>
class Function2 {
public:
	typedef FunctionBase2<R, P1, P2> IFuncType;
	typedef Function2<R, P1, P2> ThisType;

	Function2() :
			pfunc(0) {
	}

	Function2(const ThisType& f) {
		this->pfunc = f.pfunc->clone();
	}

	Function2(R (*Func)(P1, P2)) {
		pfunc = new FunctionBase2<R, P1, P2>(Func);
	}
	template<class C> Function2(R (C::*Func)(P1, P2), C* c) {
		pfunc = new FunctionBaseM2<R, C, P1, P2>(Func, c);
	}
	virtual ~Function2() {
		if (pfunc)
			delete pfunc;
	}

	R operator()(P1 p1, P2 p2) {
		if (!pfunc) {
			THROW_EXCEPTION(FunctionException, "function not defined", 0);
		}
		return (*pfunc)(p1, p2);
	}

	ThisType& operator=(const ThisType& f) {
		if (this->pfunc) {
			delete this->pfunc;
		}
		this->pfunc = f.pfunc->clone();
		return *this;
	}

	bool operator==(const ThisType& f) {
		if (!this->pfunc || !f.pfunc) {
			return (this->pfunc == f.pfunc);
		}
		return this->pfunc->compare(f.pfunc);
	}
private:
	IFuncType* pfunc;
};

template<class R, class P1, class P2, class P3>
class Function3 {
public:
	typedef FunctionBase3<R, P1, P2, P3> IFuncType;
	typedef Function3<R, P1, P2, P3> ThisType;

	Function3() :
			pfunc(0) {
	}

	Function3(const ThisType& f) {
		this->pfunc = f.pfunc->clone();
	}

	Function3(R (*Func)(P1, P2, P3)) {
		pfunc = new FunctionBase3<R, P1, P2, P3>(Func);
	}
	template<class C> Function3(R (C::*Func)(P1, P2, P3), C* c) {
		pfunc = new FunctionBaseM3<R, C, P1, P2, P3>(Func, c);
	}
	virtual ~Function3() {
		if (pfunc)
			delete pfunc;
	}

	R operator()(P1 p1, P2 p2, P3 p3) {
		if (!pfunc) {
			THROW_EXCEPTION(FunctionException, "function not defined", 0);
		}
		return (*pfunc)(p1, p2, p3);
	}

	ThisType& operator=(const ThisType& f) {
		if (this->pfunc) {
			delete this->pfunc;
		}
		this->pfunc = f.pfunc->clone();
		return *this;
	}

	bool operator==(const ThisType& f) {
		if (!this->pfunc || !f.pfunc) {
			return (this->pfunc == f.pfunc);
		}
		return this->pfunc->compare(f.pfunc);
	}
private:
	IFuncType* pfunc;
};

template<class R, class P1, class P2, class P3, class P4>
class Function4 {
public:
	typedef FunctionBase4<R, P1, P2, P3, P4> IFuncType;
	typedef Function4<R, P1, P2, P3, P4> ThisType;

	Function4() :
			pfunc(0) {
	}

	Function4(const ThisType& f) {
		this->pfunc = f.pfunc->clone();
	}

	Function4(R (*Func)(P1, P2, P3, P4)) {
		pfunc = new FunctionBase4<R, P1, P2, P3, P4>(Func);
	}
	template<class C> Function4(R (C::*Func)(P1, P2, P3, P4), C* c) {
		pfunc = new FunctionBaseM4<R, C, P1, P2, P3, P4>(Func, c);
	}
	virtual ~Function4() {
		if (pfunc)
			delete pfunc;
	}

	R operator()(P1 p1, P2 p2, P3 p3, P4 p4) {
		if (!pfunc) {
			THROW_EXCEPTION(FunctionException, "function not defined", 0);
		}
		return (*pfunc)(p1, p2, p3, p4);
	}

	ThisType& operator=(const ThisType& f) {
		if (this->pfunc) {
			delete this->pfunc;
		}
		this->pfunc = f.pfunc->clone();
		return *this;
	}

	bool operator==(const ThisType& f) {
		if (!this->pfunc || !f.pfunc) {
			return (this->pfunc == f.pfunc);
		}
		return this->pfunc->compare(f.pfunc);
	}
private:
	IFuncType* pfunc;
};

template<class R, class P1, class P2, class P3, class P4, class P5>
class Function5 {
public:
	typedef FunctionBase5<R, P1, P2, P3, P4, P5> IFuncType;
	typedef Function5<R, P1, P2, P3, P4, P5> ThisType;

	Function5() :
			pfunc(0) {
	}

	Function5(const ThisType& f) {
		this->pfunc = f.pfunc->clone();
	}

	Function5(R (*Func)(P1, P2, P3, P4, P5)) {
		pfunc = new FunctionBase5<R, P1, P2, P3, P4, P5>(Func);
	}
	template<class C> Function5(R (C::*Func)(P1, P2, P3, P4, P5), C* c) {
		pfunc = new FunctionBaseM5<R, C, P1, P2, P3, P4, P5>(Func, c);
	}
	virtual ~Function5() {
		if (pfunc)
			delete pfunc;
	}

	R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5) {
		if (!pfunc) {
			THROW_EXCEPTION(FunctionException, "function not defined", 0);
		}
		return (*pfunc)(p1, p2, p3, p4, p5);
	}

	ThisType& operator=(const ThisType& f) {
		if (this->pfunc) {
			delete this->pfunc;
		}
		this->pfunc = f.pfunc->clone();
		return *this;
	}

	bool operator==(const ThisType& f) {
		if (!this->pfunc || !f.pfunc) {
			return (this->pfunc == f.pfunc);
		}
		return this->pfunc->compare(f.pfunc);
	}
private:
	IFuncType* pfunc;
};

template<class R, class P1, class P2, class P3, class P4, class P5, class P6>
class Function6 {
public:
	typedef FunctionBase6<R, P1, P2, P3, P4, P5, P6> IFuncType;
	typedef Function6<R, P1, P2, P3, P4, P5, P6> ThisType;

	Function6() :
			pfunc(0) {
	}

	Function6(const ThisType& f) {
		this->pfunc = f.pfunc->clone();
	}

	Function6(R (*Func)(P1, P2, P3, P4, P5, P6)) {
		pfunc = new FunctionBase6<R, P1, P2, P3, P4, P5, P6>(Func);
	}
	template<class C> Function6(R (C::*Func)(P1, P2, P3, P4, P5, P6), C* c) {
		pfunc = new FunctionBaseM6<R, C, P1, P2, P3, P4, P5, P6>(Func, c);
	}
	virtual ~Function6() {
		if (pfunc)
			delete pfunc;
	}

	R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6) {
		if (!pfunc) {
			THROW_EXCEPTION(FunctionException, "function not defined", 0);
		}
		return (*pfunc)(p1, p2, p3, p4, p5, p6);
	}

	ThisType& operator=(const ThisType& f) {
		if (this->pfunc) {
			delete this->pfunc;
		}
		this->pfunc = f.pfunc->clone();
		return *this;
	}

	bool operator==(const ThisType& f) {
		if (!this->pfunc || !f.pfunc) {
			return (this->pfunc == f.pfunc);
		}
		return this->pfunc->compare(f.pfunc);
	}
private:
	IFuncType* pfunc;
};

template<class R, class P1, class P2, class P3, class P4, class P5, class P6,
		class P7>
class Function7 {
public:
	typedef FunctionBase7<R, P1, P2, P3, P4, P5, P6, P7> IFuncType;
	typedef Function7<R, P1, P2, P3, P4, P5, P6, P7> ThisType;

	Function7() :
			pfunc(0) {
	}

	Function7(const ThisType& f) {
		this->pfunc = f.pfunc->clone();
	}

	Function7(R (*Func)(P1, P2, P3, P4, P5, P6, P7)) {
		pfunc = new FunctionBase7<R, P1, P2, P3, P4, P5, P6, P7>(Func);
	}
	template<class C> Function7(R (C::*Func)(P1, P2, P3, P4, P5, P6, P7),
			C* c) {
		pfunc = new FunctionBaseM7<R, C, P1, P2, P3, P4, P5, P6, P7>(Func, c);
	}
	virtual ~Function7() {
		if (pfunc)
			delete pfunc;
	}

	R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7) {
		if (!pfunc) {
			THROW_EXCEPTION(FunctionException, "function not defined", 0);
		}
		return (*pfunc)(p1, p2, p3, p4, p5, p6, p7);
	}

	ThisType& operator=(const ThisType& f) {
		if (this->pfunc) {
			delete this->pfunc;
		}
		this->pfunc = f.pfunc->clone();
		return *this;
	}

	bool operator==(const ThisType& f) {
		if (!this->pfunc || !f.pfunc) {
			return (this->pfunc == f.pfunc);
		}
		return this->pfunc->compare(f.pfunc);
	}
private:
	IFuncType* pfunc;
};

template<class R, class P1, class P2, class P3, class P4, class P5, class P6,
		class P7, class P8>
class Function8 {
public:
	typedef FunctionBase8<R, P1, P2, P3, P4, P5, P6, P7, P8> IFuncType;
	typedef Function8<R, P1, P2, P3, P4, P5, P6, P7, P8> ThisType;

	Function8() :
			pfunc(0) {
	}

	Function8(const ThisType& f) {
		this->pfunc = f.pfunc->clone();
	}

	Function8(R (*Func)(P1, P2, P3, P4, P5, P6, P7, P8)) {
		pfunc = new FunctionBase8<R, P1, P2, P3, P4, P5, P6, P7, P8>(Func);
	}
	template<class C> Function8(R (C::*Func)(P1, P2, P3, P4, P5, P6, P7, P8),
			C* c) {
		pfunc = new FunctionBaseM8<R, C, P1, P2, P3, P4, P5, P6, P7, P8>(Func,
				c);
	}
	virtual ~Function8() {
		if (pfunc)
			delete pfunc;
	}

	R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8) {
		if (!pfunc) {
			THROW_EXCEPTION(FunctionException, "function not defined", 0);
		}
		return (*pfunc)(p1, p2, p3, p4, p5, p6, p7, p8);
	}

	ThisType& operator=(const ThisType& f) {
		if (this->pfunc) {
			delete this->pfunc;
		}
		this->pfunc = f.pfunc->clone();
		return *this;
	}

	bool operator==(const ThisType& f) {
		if (!this->pfunc || !f.pfunc) {
			return (this->pfunc == f.pfunc);
		}
		return this->pfunc->compare(f.pfunc);
	}
private:
	IFuncType* pfunc;
};

template<class R, class P1, class P2, class P3, class P4, class P5, class P6,
		class P7, class P8, class P9>
class Function9 {
public:
	typedef FunctionBase9<R, P1, P2, P3, P4, P5, P6, P7, P8, P9> IFuncType;
	typedef Function9<R, P1, P2, P3, P4, P5, P6, P7, P8, P9> ThisType;

	Function9() :
			pfunc(0) {
	}

	Function9(const ThisType& f) {
		this->pfunc = f.pfunc->clone();
	}

	Function9(R (*Func)(P1, P2, P3, P4, P5, P6, P7, P8, P9)) {
		pfunc = new FunctionBase9<R, P1, P2, P3, P4, P5, P6, P7, P8, P9>(Func);
	}
	template<class C> Function9(
			R (C::*Func)(P1, P2, P3, P4, P5, P6, P7, P8, P9), C* c) {
		pfunc = new FunctionBaseM9<R, C, P1, P2, P3, P4, P5, P6, P7, P8, P9>(
				Func, c);
	}
	virtual ~Function9() {
		if (pfunc)
			delete pfunc;
	}

	R operator()(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8,
			P9 p9) {
		if (!pfunc) {
			THROW_EXCEPTION(FunctionException, "function not defined", 0);
		}
		return (*pfunc)(p1, p2, p3, p4, p5, p6, p7, p8, p9);
	}

	ThisType& operator=(const ThisType& f) {
		if (this->pfunc) {
			delete this->pfunc;
		}
		this->pfunc = f.pfunc->clone();
		return *this;
	}

	bool operator==(const ThisType& f) {
		if (!this->pfunc || !f.pfunc) {
			return (this->pfunc == f.pfunc);
		}
		return this->pfunc->compare(f.pfunc);
	}
private:
	IFuncType* pfunc;
};

} /* namespace function */
} /* namespace ducky */

#endif /* DUCKY_FUNCTION_FUNCTION_H_ */
