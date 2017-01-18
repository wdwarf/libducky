/*
 * Bind.h
 *
 *  Created on: Jan 18, 2017
 *      Author: ducky
 */

#ifndef DUCKY_FUNCTION_BIND_H_
#define DUCKY_FUNCTION_BIND_H_

#include <ducky/function/Function.h>

namespace ducky {
namespace function {

template<class R>
Function0<R> Bind(R (*Func)()) {
	return Function0<R>(Func);
}

template<class R, class C>
Function0<R> Bind(R (C::*Func)(), C* c) {
	return Function0<R>(Func, c);
}

template<class R, class P1>
Function1<R, P1> Bind(R (*Func)(P1)) {
	return Function1<R, P1>(Func);
}

template<class R, class C, class P1>
Function1<R, P1> Bind(R (C::*Func)(P1), C* c) {
	return Function1<R, P1>(Func, c);
}

template<class R, class P1, class P2>
Function2<R, P1, P2> Bind(R (*Func)(P1, P2)) {
	return Function2<R, P1, P2>(Func);
}

template<class R, class C, class P1, class P2>
Function2<R, P1, P2> Bind(R (C::*Func)(P1, P2), C* c) {
	return Function2<R, P1, P2>(Func, c);
}

template<class R, class P1, class P2, class P3>
Function3<R, P1, P2, P3> Bind(R (*Func)(P1, P2, P3)) {
	return Function3<R, P1, P2, P3>(Func);
}

template<class R, class C, class P1, class P2, class P3>
Function3<R, P1, P2, P3> Bind(R (C::*Func)(P1, P2, P3), C* c) {
	return Function3<R, P1, P2, P3>(Func, c);
}

template<class R, class P1, class P2, class P3, class P4>
Function4<R, P1, P2, P3, P4> Bind(R (*Func)(P1, P2, P3, P4)) {
	return Function4<R, P1, P2, P3, P4>(Func);
}

template<class R, class C, class P1, class P2, class P3, class P4>
Function4<R, P1, P2, P3, P4> Bind(R (C::*Func)(P1, P2, P3, P4), C* c) {
	return Function4<R, P1, P2, P3, P4>(Func, c);
}

template<class R, class P1, class P2, class P3, class P4, class P5>
Function5<R, P1, P2, P3, P4, P5> Bind(R (*Func)(P1, P2, P3, P4, P5)) {
	return Function5<R, P1, P2, P3, P4, P5>(Func);
}

template<class R, class C, class P1, class P2, class P3, class P4, class P5>
Function5<R, P1, P2, P3, P4, P5> Bind(R (C::*Func)(P1, P2, P3, P4, P5), C* c) {
	return Function5<R, P1, P2, P3, P4, P5>(Func, c);
}

template<class R, class P1, class P2, class P3, class P4, class P5, class P6>
Function6<R, P1, P2, P3, P4, P5, P6> Bind(R (*Func)(P1, P2, P3, P4, P5, P6)) {
	return Function6<R, P1, P2, P3, P4, P5, P6>(Func);
}

template<class R, class C, class P1, class P2, class P3, class P4, class P5,
		class P6>
Function6<R, P1, P2, P3, P4, P5, P6> Bind(R (C::*Func)(P1, P2, P3, P4, P5, P6),
		C* c) {
	return Function6<R, P1, P2, P3, P4, P5, P6>(Func, c);
}

template<class R, class P1, class P2, class P3, class P4, class P5, class P6,
		class P7>
Function7<R, P1, P2, P3, P4, P5, P6, P7> Bind(
		R (*Func)(P1, P2, P3, P4, P5, P6, P7)) {
	return Function7<R, P1, P2, P3, P4, P5, P6, P7>(Func);
}

template<class R, class C, class P1, class P2, class P3, class P4, class P5,
		class P6, class P7>
Function7<R, P1, P2, P3, P4, P5, P6, P7> Bind(
		R (C::*Func)(P1, P2, P3, P4, P5, P6, P7), C* c) {
	return Function7<R, P1, P2, P3, P4, P5, P6, P7>(Func, c);
}

template<class R, class P1, class P2, class P3, class P4, class P5, class P6,
		class P7, class P8>
Function8<R, P1, P2, P3, P4, P5, P6, P7, P8> Bind(
		R (*Func)(P1, P2, P3, P4, P5, P6, P7, P8)) {
	return Function8<R, P1, P2, P3, P4, P5, P6, P7, P8>(Func);
}

template<class R, class C, class P1, class P2, class P3, class P4, class P5,
		class P6, class P7, class P8>
Function8<R, P1, P2, P3, P4, P5, P6, P7, P8> Bind(
		R (C::*Func)(P1, P2, P3, P4, P5, P6, P7, P8), C* c) {
	return Function8<R, P1, P2, P3, P4, P5, P6, P7, P8>(Func, c);
}

template<class R, class P1, class P2, class P3, class P4, class P5, class P6,
		class P7, class P8, class P9>
Function9<R, P1, P2, P3, P4, P5, P6, P7, P8, P9> Bind(
		R (*Func)(P1, P2, P3, P4, P5, P6, P7, P8, P9)) {
	return Function9<R, P1, P2, P3, P4, P5, P6, P7, P8, P9>(Func);
}

template<class R, class C, class P1, class P2, class P3, class P4, class P5,
		class P6, class P7, class P8, class P9>
Function9<R, P1, P2, P3, P4, P5, P6, P7, P8, P9> Bind(
		R (C::*Func)(P1, P2, P3, P4, P5, P6, P7, P8, P9), C* c) {
	return Function9<R, P1, P2, P3, P4, P5, P6, P7, P8, P9>(Func, c);
}

//--------------------------------------------

} /* namespace function */
} /* namespace ducky */

#endif /* DUCKY_FUNCTION_BIND_H_ */
