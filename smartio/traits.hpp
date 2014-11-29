/*
 * traits.hpp
 *
 *  Created on: 27.11.2014
 *      Author: Carbon
 */

#pragma once
#ifndef TRAITS_HPP_
#define TRAITS_HPP_

#include <functional>
#include <array>

namespace io {

template<typename T,
		bool=false>
struct supply_t {
	typedef T type;
	typedef T ele_t;
};

template<typename T, bool f>
struct supply_t<T&, f> {
	static_assert(f, "Can not use l-reference type as supplied type.");
	typedef T& type;
	typedef T ele_t;
};

template<typename T, bool f>
struct supply_t<T&&, f> {
	static_assert(f, "Can not use r-reference type as supplied type.");
	typedef T&& type;
	typedef T ele_t;
};

template<typename T, bool f>
struct supply_t<T*, f> {
	static_assert(f, "Can not use pointer type as supplied type.");
	typedef T* type;
	typedef T* ele_t;
};

template<typename T, std::size_t N, bool f>
struct supply_t<T[N], f> {
	typedef typename supply_t<T>::type* type;
	typedef typename supply_t<T>::type ele_t;
};

}

#endif /* TRAITS_HPP_ */
