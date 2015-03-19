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

template<typename T, bool = false>
struct __identity
{
    typedef T type;
};

template<bool f>
struct __identity< void, f >
{
    static_assert(f, "Supplier type must extend Supplier<T>");
};

template<template<typename > class Base, typename T>
__identity < T > _base_deduction_impl(const Base< T > &);
template<template<typename > class>
__identity < void > _base_deduction_impl(...);

template<typename T, bool = false>
struct _supply_impl
{
    using type =  std::unique_ptr<T>;
};

template<typename T, bool f>
struct _supply_impl< T&, f >
{
    static_assert(f, "Can not use l-reference type as supplied type.");
    using type = std::unique_ptr<T>;
};

template<typename T, bool f>
struct _supply_impl< T&&, f >
{
    static_assert(f, "Can not use r-reference type as supplied type.");
    using type = std::unique_ptr<T>;
};

template<typename T, bool f>
struct _supply_impl< T*, f >
{
    static_assert(f, "Can not use pointer type as supplied type.");
    using type = std::unique_ptr<T*>;
};

template<typename T, bool f>
struct _supply_impl< const T, f >
{
    static_assert(f, "Can not use cv-qualified type as supplied type.");
    using type = std::unique_ptr<const T>;
};

template<typename T, bool f>
struct _supply_impl< volatile T, f >
{
    static_assert(f, "Can not use cv-qualified type as supplied type.");
    using type = std::unique_ptr<volatile T>;
};

} /** End <anonymous> namespace*/

template<typename T>
using supply_t = typename _supply_impl<T>::type;

template<typename T, bool = false>
struct consume_t
{
    typedef T type;
};

template<template<typename > class Base, class Q>
using base_deduction = typename decltype(_base_deduction_impl<Base>(std::declval<Q>()))::type;

} /* namespace io */
