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

template<class T> struct is_placeholder {
	enum _vt {
		value = 0
	};
};

template<int I> struct arg {
	arg() {
	}
};

template<class T> struct type {
};

namespace _bi {

template<class T> class value {
public:
	value(T const& t) :
			t_(t) {
	}

	T& get() {
		return t_;
	}

private:
	T t_;
};

template<class F> struct unwrapper {
	static inline F& unwrap(F& f, long) {
		return f;
	}
};

// result_traits
template<class R, class F> struct result_traits {
	typedef R type;
};
struct unspecified {
};
template<class F> struct result_traits<unspecified, F> {
	typedef typename F::result_type type;
};

//1
template<class A1> struct storage1 {
	explicit storage1(A1 a1) :
			a1_(a1) {
	}

	A1 a1_;
};

template<int I> struct storage1<arg<I> > {
	explicit storage1(arg<I>) {
	}

	static arg<I> a1() {
		return arg<I>();
	}
};

template<int I> struct storage1<arg<I> (*)()> {
	explicit storage1(arg<I> (*)()) {
	}

	static arg<I> a1_() {
		return arg<I>();
	}
};

// 2
template<class A1, class A2> struct storage2: public storage1<A1> {
	typedef storage1<A1> inherited;
	storage2(A1 a1, A2 a2) :
			storage1<A1>(a1), a2_(a2) {
		cout << "storage2 storage2(A1 a1, A2 a2)" << endl;
	}
	A2 a2_;
};

template<class A1, int I> struct storage2<A1, arg<I> > : public storage1<A1> {
	typedef storage1<A1> inherited;
	storage2(A1 a1, arg<I>) :
	storage1<A1>(a1) {
		cout<<"storage2 storage2(A1 a1, arg<I>)"<<endl;
	}
	static arg<I> a2_() {
		return arg<I>();
	}
};
template<class A1, int I> struct storage2<A1, arg<I> (*)()> : public storage1<A1> {
	typedef storage1<A1> inherited;
	storage2(A1 a1, arg<I> (*)()) :
			storage1<A1>(a1) {
		cout << "storage2 storage2(A1 a1, arg<I> (*)())" << endl;
	}
	static arg<I> a2_() {
		return arg<I>();
	}
};

//list N
class list0 {
public:
	list0() {
	}

	template<class T> T& operator[](_bi::value<T>& v) const {
		return v.get();
	}

	template<class R, class F, class A> R operator()(type<R>, F& f, A&, long) {
		unwrapper<F>::unwrap(f, 0)();
	}

	template<class F, class A> void operator()(type<void>, F& f, A&, int) {
		unwrapper<F>::unwrap(f, 0)();
	}
};

template<class A1> class list1: private storage1<A1> {
private:
	typedef storage1<A1> base_type;
public:
	explicit list1(A1 a1) :
			base_type(a1) {
	}
	A1 operator[](arg<1>) const {
		return base_type::a1_;
	}
	A1 operator[](arg<1> (*)()) const {
		return base_type::a1_;
	}
	template<class T> T & operator[](_bi::value<T> & v) const {
		return v.get();
	}
	template<class R, class F, class A> R operator()(type<R>, F & f, A & a,
			long) {
		return unwrapper<F>::unwrap(f, 0)(a[base_type::a1_]);
	}
// template<class F, class A> void operator()(type<void>, F & f, A & a, int)
	//{
// unwrapper<F>::unwrap(f, 0)(a[base_type::a1_]);
// }
};

template<class A1, class A2> class list2: private storage2<A1, A2> {
private:
	typedef storage2<A1, A2> base_type;
public:
	list2(A1 a1, A2 a2) :
			base_type(a1, a2) {
	}
	A1 operator[](arg<1>) const {
		cout << "list2 A1 operator[](arg<1>)" << endl;
		return base_type::a1_;
	}
	A2 operator[](arg<2>) const {
		cout << "list2 A1 operator[](arg<2>)" << endl;
		return base_type::a2_;
	}
	A1 operator[](arg<1> (*)()) const {
		cout << "list2 A1 operator[](arg<1> (*)())" << endl;
		return base_type::a1_;
	}
	A2 operator[](arg<2> (*)()) const {
		cout << "list2 A1 operator[](arg<2> (*)())" << endl;
		return base_type::a2_;
	}
	template<class T> T & operator[](_bi::value<T> & v) const {
		cout << "T & operator[](_bi::value<T> & v)" << endl;
		return v.get();
	}
	template<class R, class F, class A> R operator()(type<R>, F & f, A & a,
			long) {
		return f(a[base_type::a1_], a[base_type::a2_]);
	}
};

//bind_t
template<class R, class F, class L> class bind_t {
public:
	typedef bind_t this_type;
	typedef typename result_traits<R, F>::type result_type;

	bind_t(F f, L const& l) :
			f_(f), l_(l) {
	}

	result_type operator()() {
		list0 a;
		return l_(type<result_type>(), f_, a, 0);
	}

	template<class A1> result_type operator()(A1& a1) {
		list1<A1&> a(a1);
		return l_(type<result_type>(), f_, a, 0);
	}

	/*
	 template<class A1, class A2> result_type operator()(A1& a1, A2& a2){
	 list2<A1&, A2&> a(a1, a2);
	 return l_(type<result_type>(), f_, a, 0);
	 }
	 */

private:
	F f_;
	L l_;

};

template<class T, int I> struct add_value_2 {
	typedef arg<I> type;
};
template<class T> struct add_value_2<T, 0> {
	typedef _bi::value<T> type;
};
template<class T> struct add_value {
	typedef typename add_value_2<T, is_placeholder<T>::value>::type type;
};
template<class T> struct add_value<value<T> > {
	typedef _bi::value<T> type;
};
template<int I> struct add_value<arg<I> > {
	typedef arg<I> type;
};

template<class R, class F, class L> struct add_value<bind_t<R, F, L> > {
	typedef bind_t<R, F, L> type;
};
// list_av_N
template<class A1> struct list_av_1 {
	typedef typename add_value<A1>::type B1;
	typedef list1<B1> type;
};
template<class A1, class A2> struct list_av_2 {
	typedef typename add_value<A1>::type B1;
	typedef typename add_value<A2>::type B2;
	typedef list2<B1, B2> type;
};

} /* namespace _bi */

//function pointers
template<class R>
_bi::bind_t<R, R (*)(), _bi::list0> bind(R (*f)()) {
	typedef R (*F)();
	typedef _bi::list0 list_type;

	return _bi::bind_t<R, F, list_type>(f, list_type());
}

template<class R, class B1, class A1>
_bi::bind_t<R, R (*)(B1), typename _bi::list_av_1<A1>::type> bind(R (*f)(B1),
		A1 a1) {
	typedef R(*F)(B1);
	typedef typename _bi::list_av_1<A1>::type list_type;

	cout << "template<class R, class B1, class A1>" << endl;

	return _bi::bind_t<R, F, list_type>(f, list_type(a1));
}

namespace {
arg<1> _1;
arg<2> _2;
}

} /* namespace function */
} /* namespace ducky */

#endif /* DUCKY_FUNCTION_FUNCTION_H_ */
