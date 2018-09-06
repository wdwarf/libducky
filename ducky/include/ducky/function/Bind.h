/*
 * Bind.h
 *
 *  Created on: Nov 5, 2016
 *      Author: ducky
 */

#ifndef DUCKY_FUNCTION_BIND_H_
#define DUCKY_FUNCTION_BIND_H_

#include <ducky/function/Function.h>

namespace ducky {
namespace function {

template<class R>
Function0<R> Bind(R (*f)()) {
	return Function0<R>(new F0<R>(f));
}

template<class R, class C>
Function0<R> Bind(R (C::*f)(), C* o) {
	return Function0<R>(new F0Mem<R, C>(f, o));
}

template<class R, class C>
Function0<R> Bind(R (C::*f)() const, C* o) {
	return Function0<R>(new F0MemConst<R, C>(f, o));
}

template<class R, class P1>
Function1<R, P1> Bind(R (*f)(P1)) {
	return Function1<R, P1>(new F1<R, P1>(f));
}

template<class R, class C, class P1>
Function1<R, P1> Bind(R (C::*f)(P1), C* o) {
	return Function1<R, P1>(new F1Mem<R, C, P1>(f, o));
}

template<class R, class C, class P1>
Function1<R, P1> Bind(R (C::*f)(P1) const, C* o) {
	return Function1<R, P1>(new F1MemConst<R, C, P1>(f, o));
}

template<class R, class P1, class P2>
Function2<R, P1, P2> Bind(R (*f)(P1, P2)) {
	return Function2<R, P1, P2>(new F2<R, P1, P2>(f));
}

template<class R, class C, class P1, class P2>
Function2<R, P1, P2> Bind(R (C::*f)(P1, P2), C* o) {
	return Function2<R, P1, P2>(new F2Mem<R, C, P1, P2>(f, o));
}

template<class R, class C, class P1, class P2>
Function2<R, P1, P2> Bind(R (C::*f)(P1, P2) const, C* o) {
	return Function2<R, P1, P2>(new F2MemConst<R, C, P1, P2>(f, o));
}

template<class R, class P1, class P2, class P3>
Function3<R, P1, P2, P3> Bind(R (*f)(P1, P2, P3)) {
	return Function3<R, P1, P2, P3>(new F3<R, P1, P2, P3>(f));
}

template<class R, class C, class P1, class P2, class P3>
Function3<R, P1, P2, P3> Bind(R (C::*f)(P1, P2, P3), C* o) {
	return Function3<R, P1, P2, P3>(new F3Mem<R, C, P1, P2, P3>(f, o));
}

template<class R, class C, class P1, class P2, class P3>
Function3<R, P1, P2, P3> Bind(R (C::*f)(P1, P2, P3) const, C* o) {
	return Function3<R, P1, P2, P3>(new F3MemConst<R, C, P1, P2, P3>(f, o));
}

template<class R, class P1, class P2, class P3, class P4>
Function4<R, P1, P2, P3, P4> Bind(R (*f)(P1, P2, P3, P4)) {
	return Function4<R, P1, P2, P3, P4>(new F4<R, P1, P2, P3, P4>(f));
}

template<class R, class C, class P1, class P2, class P3, class P4>
Function4<R, P1, P2, P3, P4> Bind(R (C::*f)(P1, P2, P3, P4), C* o) {
	return Function4<R, P1, P2, P3, P4>(new F4Mem<R, C, P1, P2, P3, P4>(f, o));
}

template<class R, class C, class P1, class P2, class P3, class P4>
Function4<R, P1, P2, P3, P4> Bind(R (C::*f)(P1, P2, P3, P4) const, C* o) {
	return Function4<R, P1, P2, P3, P4>(new F4MemConst<R, C, P1, P2, P3, P4>(f, o));
}

template<class R, class P1, class P2, class P3, class P4, class P5>
Function5<R, P1, P2, P3, P4, P5> Bind(R (*f)(P1, P2, P3, P4, P5)) {
	return Function5<R, P1, P2, P3, P4, P5>(new F5<R, P1, P2, P3, P4, P5>(f));
}

template<class R, class C, class P1, class P2, class P3, class P4, class P5>
Function5<R, P1, P2, P3, P4, P5> Bind(R (C::*f)(P1, P2, P3, P4, P5), C* o) {
	return Function5<R, P1, P2, P3, P4, P5>(new F5Mem<R, C, P1, P2, P3, P4, P5>(f, o));
}

template<class R, class C, class P1, class P2, class P3, class P4, class P5>
Function5<R, P1, P2, P3, P4, P5> Bind(R (C::*f)(P1, P2, P3, P4, P5) const, C* o) {
	return Function5<R, P1, P2, P3, P4, P5>(new F5MemConst<R, C, P1, P2, P3, P4, P5>(f, o));
}

template<class R, class P1, class P2, class P3, class P4, class P5, class P6>
Function6<R, P1, P2, P3, P4, P5, P6> Bind(R (*f)(P1, P2, P3, P4, P5, P6)) {
	return Function6<R, P1, P2, P3, P4, P5, P6>(new F6<R, P1, P2, P3, P4, P5, P6>(f));
}

template<class R, class C, class P1, class P2, class P3, class P4, class P5, class P6>
Function6<R, P1, P2, P3, P4, P5, P6> Bind(R (C::*f)(P1, P2, P3, P4, P5, P6), C* o) {
	return Function6<R, P1, P2, P3, P4, P5, P6>(new F6Mem<R, C, P1, P2, P3, P4, P5, P6>(f, o));
}

template<class R, class C, class P1, class P2, class P3, class P4, class P5, class P6>
Function6<R, P1, P2, P3, P4, P5, P6> Bind(R (C::*f)(P1, P2, P3, P4, P5, P6) const, C* o) {
	return Function6<R, P1, P2, P3, P4, P5, P6>(new F6MemConst<R, C, P1, P2, P3, P4, P5, P6>(f, o));
}

template<class R, class P1, class P2, class P3, class P4, class P5, class P6, class P7>
Function7<R, P1, P2, P3, P4, P5, P6, P7> Bind(R (*f)(P1, P2, P3, P4, P5, P6, P7)) {
	return Function7<R, P1, P2, P3, P4, P5, P6, P7>(new F7<R, P1, P2, P3, P4, P5, P6, P7>(f));
}

template<class R, class C, class P1, class P2, class P3, class P4, class P5, class P6, class P7>
Function7<R, P1, P2, P3, P4, P5, P6, P7> Bind(R (C::*f)(P1, P2, P3, P4, P5, P6, P7), C* o) {
	return Function7<R, P1, P2, P3, P4, P5, P6, P7>(
			new F7Mem<R, C, P1, P2, P3, P4, P5, P6, P7>(f, o));
}

template<class R, class C, class P1, class P2, class P3, class P4, class P5, class P6, class P7>
Function7<R, P1, P2, P3, P4, P5, P6, P7> Bind(R (C::*f)(P1, P2, P3, P4, P5, P6, P7) const, C* o) {
	return Function7<R, P1, P2, P3, P4, P5, P6, P7>(
			new F7MemConst<R, C, P1, P2, P3, P4, P5, P6, P7>(f, o));
}

template<class R, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8>
Function8<R, P1, P2, P3, P4, P5, P6, P7, P8> Bind(R (*f)(P1, P2, P3, P4, P5, P6, P7, P8)) {
	return Function8<R, P1, P2, P3, P4, P5, P6, P7, P8>(
			new F8<R, P1, P2, P3, P4, P5, P6, P7, P8>(f));
}

template<class R, class C, class P1, class P2, class P3, class P4, class P5, class P6, class P7,
		class P8>
Function8<R, P1, P2, P3, P4, P5, P6, P7, P8> Bind(R (C::*f)(P1, P2, P3, P4, P5, P6, P7, P8), C* o) {
	return Function8<R, P1, P2, P3, P4, P5, P6, P7, P8>(
			new F8Mem<R, C, P1, P2, P3, P4, P5, P6, P7, P8>(f, o));
}

template<class R, class C, class P1, class P2, class P3, class P4, class P5, class P6, class P7,
		class P8>
Function8<R, P1, P2, P3, P4, P5, P6, P7, P8> Bind(R (C::*f)(P1, P2, P3, P4, P5, P6, P7, P8) const,
		C* o) {
	return Function8<R, P1, P2, P3, P4, P5, P6, P7, P8>(
			new F8MemConst<R, C, P1, P2, P3, P4, P5, P6, P7, P8>(f, o));
}

template<class R, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8,
		class P9>
Function9<R, P1, P2, P3, P4, P5, P6, P7, P8, P9> Bind(R (*f)(P1, P2, P3, P4, P5, P6, P7, P8, P9)) {
	return Function9<R, P1, P2, P3, P4, P5, P6, P7, P8, P9>(
			new F9<R, P1, P2, P3, P4, P5, P6, P7, P8, P9>(f));
}

template<class R, class C, class P1, class P2, class P3, class P4, class P5, class P6, class P7,
		class P8, class P9>
Function9<R, P1, P2, P3, P4, P5, P6, P7, P8, P9> Bind(R (C::*f)(P1, P2, P3, P4, P5, P6, P7, P8, P9),
		C* o) {
	return Function9<R, P1, P2, P3, P4, P5, P6, P7, P8, P9>(
			new F9Mem<R, C, P1, P2, P3, P4, P5, P6, P7, P8, P9>(f, o));
}

template<class R, class C, class P1, class P2, class P3, class P4, class P5, class P6, class P7,
		class P8, class P9>
Function9<R, P1, P2, P3, P4, P5, P6, P7, P8, P9> Bind(
		R (C::*f)(P1, P2, P3, P4, P5, P6, P7, P8, P9) const, C* o) {
	return Function9<R, P1, P2, P3, P4, P5, P6, P7, P8, P9>(
			new F9MemConst<R, C, P1, P2, P3, P4, P5, P6, P7, P8, P9>(f, o));
}

template<class R, class P1, class A1>
Function0<R> Bind(R (*f)(P1), A1 a1) {
	return Function0<R>(new ArgF1<R, P1, A1>(f, a1));
}

template<class R, class C, class P1, class A1>
Function0<R> Bind(R (C::*f)(P1), C* o, A1 a1) {
	return Function0<R>(new ArgF1Mem<R, C, P1, A1>(f, o, a1));
}

template<class R, class C, class P1, class A1>
Function0<R> Bind(R (C::*f)(P1) const, C* o, A1 a1) {
	return Function0<R>(new ArgF1MemConst<R, C, P1, A1>(f, o, a1));
}

template<class R, class P1, class P2, class A1, class A2>
Function0<R> Bind(R (*f)(P1, P2), A1 a1, A2 a2) {
	return Function0<R>(new ArgF2<R, P1, P2, A1, A2>(f, a1, a2));
}

template<class R, class C, class P1, class P2, class A1, class A2>
Function0<R> Bind(R (C::*f)(P1, P2), C* o, A1 a1, A2 a2) {
	return Function0<R>(new ArgF2Mem<R, C, P1, P2, A1, A2>(f, o, a1, a2));
}

template<class R, class C, class P1, class P2, class A1, class A2>
Function0<R> Bind(R (C::*f)(P1, P2) const, C* o, A1 a1, A2 a2) {
	return Function0<R>(new ArgF2MemConst<R, C, P1, P2, A1, A2>(f, o, a1, a2));
}

template<class R, class P1, class P2, class P3, class A1, class A2, class A3>
Function0<R> Bind(R (*f)(P1, P2, P3), A1 a1, A2 a2, A3 a3) {
	return Function0<R>(new ArgF3<R, P1, P2, P3, A1, A2, A3>(f, a1, a2, a3));
}

template<class R, class C, class P1, class P2, class P3, class A1, class A2, class A3>
Function0<R> Bind(R (C::*f)(P1, P2, P3), C* o, A1 a1, A2 a2, A3 a3) {
	return Function0<R>(new ArgF3Mem<R, C, P1, P2, P3, A1, A2, A3>(f, o, a1, a2, a3));
}

template<class R, class C, class P1, class P2, class P3, class A1, class A2, class A3>
Function0<R> Bind(R (C::*f)(P1, P2, P3) const, C* o, A1 a1, A2 a2, A3 a3) {
	return Function0<R>(new ArgF3MemConst<R, C, P1, P2, P3, A1, A2, A3>(f, o, a1, a2, a3));
}

template<class R, class P1, class P2, class P3, class P4, class A1, class A2, class A3, class A4>
Function0<R> Bind(R (*f)(P1, P2, P3, P4), A1 a1, A2 a2, A3 a3, A4 a4) {
	return Function0<R>(new ArgF4<R, P1, P2, P3, P4, A1, A2, A3, A4>(f, a1, a2, a3, a4));
}

template<class R, class C, class P1, class P2, class P3, class P4, class A1, class A2, class A3,
		class A4>
Function0<R> Bind(R (C::*f)(P1, P2, P3, P4), C* o, A1 a1, A2 a2, A3 a3, A4 a4) {
	return Function0<R>(new ArgF4Mem<R, C, P1, P2, P3, P4, A1, A2, A3, A4>(f, o, a1, a2, a3, a4));
}

template<class R, class C, class P1, class P2, class P3, class P4, class A1, class A2, class A3,
		class A4>
Function0<R> Bind(R (C::*f)(P1, P2, P3, P4) const, C* o, A1 a1, A2 a2, A3 a3, A4 a4) {
	return Function0<R>(
			new ArgF4MemConst<R, C, P1, P2, P3, P4, A1, A2, A3, A4>(f, o, a1, a2, a3, a4));
}

template<class R, class P1, class P2, class P3, class P4, class P5, class A1, class A2, class A3,
		class A4, class A5>
Function0<R> Bind(R (*f)(P1, P2, P3, P4, P5), A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) {
	return Function0<R>(new ArgF5<R, P1, P2, P3, P4, P5, A1, A2, A3, A4, A5>(f, a1, a2, a3, a4, a5));
}

template<class R, class C, class P1, class P2, class P3, class P4, class P5, class A1, class A2,
		class A3, class A4, class A5>
Function0<R> Bind(R (C::*f)(P1, P2, P3, P4, P5), C* o, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) {
	return Function0<R>(
			new ArgF5Mem<R, C, P1, P2, P3, P4, P5, A1, A2, A3, A4, A5>(f, o, a1, a2, a3, a4, a5));
}

template<class R, class C, class P1, class P2, class P3, class P4, class P5, class A1, class A2,
		class A3, class A4, class A5>
Function0<R> Bind(R (C::*f)(P1, P2, P3, P4, P5) const, C* o, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) {
	return Function0<R>(
			new ArgF5MemConst<R, C, P1, P2, P3, P4, P5, A1, A2, A3, A4, A5>(f, o, a1, a2, a3, a4,
					a5));
}

template<class R, class P1, class P2, class P3, class P4, class P5, class P6, class A1, class A2,
		class A3, class A4, class A5, class A6>
Function0<R> Bind(R (*f)(P1, P2, P3, P4, P5, P6), A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) {
	return Function0<R>(
			new ArgF6<R, P1, P2, P3, P4, P5, P6, A1, A2, A3, A4, A5, A6>(f, a1, a2, a3, a4, a5, a6));
}

template<class R, class C, class P1, class P2, class P3, class P4, class P5, class P6, class A1,
		class A2, class A3, class A4, class A5, class A6>
Function0<R> Bind(R (C::*f)(P1, P2, P3, P4, P5, P6), C* o, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5,
		A6 a6) {
	return Function0<R>(
			new ArgF6Mem<R, C, P1, P2, P3, P4, P5, P6, A1, A2, A3, A4, A5, A6>(f, o, a1, a2, a3, a4,
					a5, a6));
}

template<class R, class C, class P1, class P2, class P3, class P4, class P5, class P6, class A1,
		class A2, class A3, class A4, class A5, class A6>
Function0<R> Bind(R (C::*f)(P1, P2, P3, P4, P5, P6) const, C* o, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5,
		A6 a6) {
	return Function0<R>(
			new ArgF6MemConst<R, C, P1, P2, P3, P4, P5, P6, A1, A2, A3, A4, A5, A6>(f, o, a1, a2,
					a3, a4, a5, a6));
}

template<class R, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class A1,
		class A2, class A3, class A4, class A5, class A6, class A7>
Function0<R> Bind(R (*f)(P1, P2, P3, P4, P5, P6, P7), A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6,
		A7 a7) {
	return Function0<R>(
			new ArgF7<R, P1, P2, P3, P4, P5, P6, P7, A1, A2, A3, A4, A5, A6, A7>(f, a1, a2, a3, a4,
					a5, a6, a7));
}

template<class R, class C, class P1, class P2, class P3, class P4, class P5, class P6, class P7,
		class A1, class A2, class A3, class A4, class A5, class A6, class A7>
Function0<R> Bind(R (C::*f)(P1, P2, P3, P4, P5, P6, P7), C* o, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5,
		A6 a6, A7 a7) {
	return Function0<R>(
			new ArgF7Mem<R, C, P1, P2, P3, P4, P5, P6, P7, A1, A2, A3, A4, A5, A6, A7>(f, o, a1, a2,
					a3, a4, a5, a6, a7));
}

template<class R, class C, class P1, class P2, class P3, class P4, class P5, class P6, class P7,
		class A1, class A2, class A3, class A4, class A5, class A6, class A7>
Function0<R> Bind(R (C::*f)(P1, P2, P3, P4, P5, P6, P7) const, C* o, A1 a1, A2 a2, A3 a3, A4 a4,
		A5 a5, A6 a6, A7 a7) {
	return Function0<R>(
			new ArgF7MemConst<R, C, P1, P2, P3, P4, P5, P6, P7, A1, A2, A3, A4, A5, A6, A7>(f, o,
					a1, a2, a3, a4, a5, a6, a7));
}

template<class R, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8,
		class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
Function0<R> Bind(R (*f)(P1, P2, P3, P4, P5, P6, P7, P8), A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6,
		A7 a7, A8 a8) {
	return Function0<R>(
			new ArgF8<R, P1, P2, P3, P4, P5, P6, P7, P8, A1, A2, A3, A4, A5, A6, A7, A8>(f, a1, a2,
					a3, a4, a5, a6, a7, a8));
}

template<class R, class C, class P1, class P2, class P3, class P4, class P5, class P6, class P7,
		class P8, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
Function0<R> Bind(R (C::*f)(P1, P2, P3, P4, P5, P6, P7, P8), C* o, A1 a1, A2 a2, A3 a3, A4 a4,
		A5 a5, A6 a6, A7 a7, A8 a8) {
	return Function0<R>(
			new ArgF8Mem<R, C, P1, P2, P3, P4, P5, P6, P7, P8, A1, A2, A3, A4, A5, A6, A7, A8>(f, o,
					a1, a2, a3, a4, a5, a6, a7, a8));
}

template<class R, class C, class P1, class P2, class P3, class P4, class P5, class P6, class P7,
		class P8, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
Function0<R> Bind(R (C::*f)(P1, P2, P3, P4, P5, P6, P7, P8) const, C* o, A1 a1, A2 a2, A3 a3, A4 a4,
		A5 a5, A6 a6, A7 a7, A8 a8) {
	return Function0<R>(
			new ArgF8MemConst<R, C, P1, P2, P3, P4, P5, P6, P7, P8, A1, A2, A3, A4, A5, A6, A7, A8>(
					f, o, a1, a2, a3, a4, a5, a6, a7, a8));
}

template<class R, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8,
		class P9, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8,
		class A9>
Function0<R> Bind(R (*f)(P1, P2, P3, P4, P5, P6, P7, P8, P9), A1 a1, A2 a2, A3 a3, A4 a4, A5 a5,
		A6 a6, A7 a7, A8 a8, A9 a9) {
	return Function0<R>(
			new ArgF9<R, P1, P2, P3, P4, P5, P6, P7, P8, P9, A1, A2, A3, A4, A5, A6, A7, A8, A9>(f,
					a1, a2, a3, a4, a5, a6, a7, a8, a9));
}

template<class R, class C, class P1, class P2, class P3, class P4, class P5, class P6, class P7,
		class P8, class P9, class A1, class A2, class A3, class A4, class A5, class A6, class A7,
		class A8, class A9>
Function0<R> Bind(R (C::*f)(P1, P2, P3, P4, P5, P6, P7, P8, P9), C* o, A1 a1, A2 a2, A3 a3, A4 a4,
		A5 a5, A6 a6, A7 a7, A8 a8, A9 a9) {
	return Function0<R>(
			new ArgF9Mem<R, C, P1, P2, P3, P4, P5, P6, P7, P8, P9, A1, A2, A3, A4, A5, A6, A7, A8,
					A9>(f, o, a1, a2, a3, a4, a5, a6, a7, a8, a9));
}

template<class R, class C, class P1, class P2, class P3, class P4, class P5, class P6, class P7,
		class P8, class P9, class A1, class A2, class A3, class A4, class A5, class A6, class A7,
		class A8, class A9>
Function0<R> Bind(R (C::*f)(P1, P2, P3, P4, P5, P6, P7, P8, P9) const, C* o, A1 a1, A2 a2, A3 a3,
		A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9) {
	return Function0<R>(
			new ArgF9MemConst<R, C, P1, P2, P3, P4, P5, P6, P7, P8, P9, A1, A2, A3, A4, A5, A6, A7,
					A8, A9>(f, o, a1, a2, a3, a4, a5, a6, a7, a8, a9));
}

} /* namespace function */
} /* namespace ducky */

#endif /* DUCKY_FUNCTION_BIND_H_ */
