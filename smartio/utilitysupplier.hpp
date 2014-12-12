/*
 * utilitysupplier.hpp
 *
 *  Created on: 29.11.2014
 *      Author: Carbon
 */
#pragma once

#include <array>
#include <list>
#include <utility>
#include <functional>

#include "Supplier.hpp"

namespace io
{
namespace utility
{
// Used as a capture to capture multiple arguments
template<typename ... Args>
struct __list;

// Used to join multiple lists together
template<typename ... Lists>
struct __join_impl;

template<typename ... Lists>
using __join = typename __join_impl<Lists...>::type;

template<>
struct __join_impl< >
{
    typedef __list < > type;
};

template<typename ... Args>
struct __join_impl< __list < Args... > >
{
    typedef __list < Args... > type;
};

template<typename ... Args1, typename ... Args2, typename ... AddLists>
struct __join_impl< __list < Args1... >, __list < Args2... >, AddLists... >
{
    typedef __join< __list < Args1..., Args2...>, AddLists...> type;
};

// Used to expand recursively
template<typename T, std::size_t = 0>
using __just = T;

// Used to repeat a template argument multiple times
template<typename T, typename Idcs>
struct __repeat_impl;

template<typename T, std::size_t N>
using __repeat =
typename __repeat_impl<T, typename std::_Build_index_tuple<N>::__type >::type;

template<typename T, std::size_t ... idcs>
struct __repeat_impl< T, std::_Index_tuple< idcs... > >
{
    typedef __list< __just < T, idcs> ...> type;
};

template<typename T, std::size_t N, std::size_t ... idcs>
struct __repeat_impl< T[N], std::_Index_tuple< idcs... > >
{
    typedef __join< __just< __repeat< __just < T>, N>, idcs> ...> type;
};
// Flatten it all out
template<typename ... Args>
struct __flatten_impl
{
    // We can just use repeat to apply this recursively
    typedef __join< __repeat < Args, 1>...> type;
};

template<typename ... Args>
using __flatten = typename __flatten_impl<Args...>::type;

template<typename T, typename List>
struct __impl_aggregate;
// Partial specialization to capture list-args
template<typename T, typename ... Args>
struct __impl_aggregate< T, __list < Args... > > : Supplier< T >
{
    using typename Supplier< T >::item_t;
    item_t supply(Context& ctx) const override
    {
        return __impl_aggregate<T, __list<Args...>>::construct(ctx);
    }

    static inline item_t construct(Context& ctx)
    {
        return
        {   ctx.construct<Args>()...};
    }
};

// ------- end of hidden utility
template<typename T>
struct memcpy_supplier : Supplier< T >
{
    using typename Supplier< T >::item_t;
    static constexpr std::size_t size = sizeof(item_t);
    union
    {
        char buffer[size];
        item_t object;
    } mutable converter;

    item_t supply(Context& ctx) const override
    {
        istream& stream = ctx.getStream();
        stream.read(converter.buffer, size);
        return converter.object;
    }
};
/**
 * This supplier can be used when the type to be supplied can be
 * brace-initialized.
 */
template<typename T, typename ... args>
using aggregate_supplier = __impl_aggregate<T, __flatten<args...> >;

/**
 * This supplier can be used when the type to be supplied can be
 * move-constructed.
 */
template<typename T, typename ... args>
struct move_supplier : Supplier< T >
{
    using typename Supplier< T >::item_t;

    item_t supply(Context& ctx) const override
    {
        return move_supplier<T, args...>::construct(ctx);
    }

    static inline item_t construct(Context& ctx)
    {
        return T(std::move(ctx.construct<args>())...);
    }
};

//template<typename T, typename ... Args, Args ... Funcs>
//struct indirect_supplier : Supplier< T >
//{
//    typename Supplier< T >::item_t supply(Context& ctx) const override
//    {
//        return T(std::move(Funcs(ctx)...));
//    }
//};

// TODO: we can generalize PushBack here to any type that has forward iterable
// or random access properties
template<typename T>
void fill_list(std::list<T>& list, Context& ctx, std::size_t c)
{
    while(c --> 0)
        list.push_back( ctx.construct<T>() );
}

template<typename T,
        std::size_t N,
        typename Alloc = std::allocator<T>,
        template<typename, typename> class PushBack=std::list>
PushBack<T, Alloc> constsize_list(Context& ctx)
{
    PushBack<T, Alloc> list;
    fill_list(list, ctx, N);
    return list;
}

template<typename T,
        Context::key_t key,
        typename Alloc = std::allocator<T>,
        template<typename, typename> class PushBack=std::list>
PushBack<T, Alloc> indirectsize_list(Context& ctx)
{
    PushBack<T, Alloc> list;
    fill_list(list, ctx, ctx[key]);
    return list;
}

template<typename T,
        typename Alloc = std::allocator<T>,
        template<typename, typename> class PushBack=std::list>
PushBack<T, Alloc> varsize_list(Context& ctx, std::size_t c)
{
    PushBack<T, Alloc> list;
    fill_list(list, ctx, c);
    return list;
}

} /* namespace utility */
} /* namespace io */
