/*
 * traits.hpp
 *
 *  Created on: 27.11.2014
 *      Author: Carbon
 */
#pragma once

#include <functional>

namespace io {
// Anonymous helper namespace
namespace {
template<typename T, bool=false>
struct __identity {typedef T type;};
template<bool f>
struct __identity<void, f> { static_assert(f, "Supplier type must extend Supplier<T>"); };

template<template<typename> class Base, typename T>
static __identity<T> __base_deduction(const Base<T> &);
template<template<typename> class>
static __identity<void> __base_deduction(...);
}
template<typename T,
		bool=false>
struct supply_t {
	typedef T type;
};

template<typename T, bool f>
struct supply_t<T&, f> {
	static_assert(f, "Can not use l-reference type as supplied type.");
	typedef T& type;
};

template<typename T, bool f>
struct supply_t<T&&, f> {
	static_assert(f, "Can not use r-reference type as supplied type.");
	typedef T&& type;
};

template<typename T, bool f>
struct supply_t<T*, f> {
	static_assert(f, "Can not use pointer type as supplied type.");
	typedef T* type;
};

template<template<typename> class Base, class Q>
using base_deduction = typename decltype(__base_deduction<Base>(std::declval<Q>()))::type;

} /* namespace io */
