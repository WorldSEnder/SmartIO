/*
 * traits.hpp
 *
 *  Created on: 27.11.2014
 *      Author: Carbon
 */
#pragma once

#include <functional>
#include <memory>

namespace io
{
// Anonymous helper namespace
  namespace
  {

    template<template<typename > class B, typename Q, typename T, bool = true,
	bool = false>
      struct _base_info : std::true_type
      {
	typedef T type;

	template<typename _>
	  using base_type = B<_>;
	typedef Q actual_type;
      };

    template<template<typename > class B, typename Q, typename T, bool f>
      struct _base_info<B, Q, T, false, f> : std::false_type
      {
	template<typename _>
	  using base_type = B<_>;
	typedef Q actual_type;

	static_assert(f, "Q needs to extend Base<T> for some T");
      };

    template<template<typename > class Base, typename Q, typename T>
      _base_info<Base, Q, T>
      _base_deduction_impl (const Base<T> &);
    template<template<typename > class Base, typename Q>
      _base_info<Base, Q, void, false>
      _base_deduction_impl (...);

    template<typename T, bool = false>
      struct _supply_impl
      {
	using type = std::unique_ptr<T>;
      };

    template<typename T, bool f>
      struct _supply_impl<T&, f>
      {
	static_assert(f, "Supplied type can not be a l-reference.");
	using type = std::unique_ptr<T>;
      };

    template<typename T, bool f>
      struct _supply_impl<T&&, f>
      {
	static_assert(f, "Can not use r-reference type as supplied type.");
	using type = std::unique_ptr<T>;
      };

    template<typename T, bool f>
      struct _supply_impl<T*, f>
      {
	static_assert(f, "Can not use pointer type as supplied type.");
	using type = std::unique_ptr<T*>;
      };

    template<typename T, bool f>
      struct _supply_impl<const T, f>
      {
	static_assert(f, "Can not use cv-qualified type as supplied type.");
	using type = std::unique_ptr<const T>;
      };

    template<typename T, bool f>
      struct _supply_impl<volatile T, f>
      {
	static_assert(f, "Can not use cv-qualified type as supplied type.");
	using type = std::unique_ptr<volatile T>;
      };

    template<typename T, bool = false>
      struct _consume_impl
      {
        typedef T type;
      };

    template<typename T, bool f>
      struct _consume_impl<T&, f>
      {
	static_assert(f, "Can not use l-value reference as consumed type. Use the unqualified type");
	using type = T;
      };

    template<typename T, bool f>
      struct _consume_impl<T&&, f>
      {
	static_assert(f, "Can not use r-value reference as consumed type. Use the unqualified type");
	using type = T;
      };

    template<typename T, bool f>
      struct _consume_impl<T*, f>
      {
	static_assert(f, "Writing pointers is non-sense.");
	using type = T;
      };

    template<typename T, bool f>
      struct _consume_impl<volatile T, f>
      {
	static_assert(f, "Can not use cv-qualified type as consumed type.");
	using type = T;
      };

    template<typename T, bool f>
      struct _consume_impl<const T, f>
      {
	static_assert(f, "Can not use cv-qualified type as consumed type.");
	using type = T;
      };

  } /** End <anonymous> namespace*/

  template<typename T>
    using supply_t = typename _supply_impl<T>::type;

  template<typename T, bool = false>
    using consume_t = typename _consume_impl<T>::type;

  /**
   * Given a templated type Base and a type Q that extends Base<T> for some type
   * T this finds the type T. Fails when Q doesn't extend Base
   */
  template<template<typename > class Base, class Q>
    using base_deduction = decltype(_base_deduction_impl<Base, Q>(std::declval<Q>()));

  template<template<typename > class Base, class Q>
    using base_deduction_t = typename base_deduction<Base, Q>::type;

} /* namespace io */
