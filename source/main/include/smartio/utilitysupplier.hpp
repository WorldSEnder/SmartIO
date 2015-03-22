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

#include "smartio/Supplier.hpp"

namespace io
{
namespace utility
{
using ::std::size_t;

// --- Hidden utility
namespace {

// Used as a capture to capture multiple arguments
template<typename ... Args>
struct _list;

// Used to join multiple lists together
template<typename ... Lists>
struct _join_impl;

template<typename ... Lists>
using _join = typename _join_impl<Lists...>::type;

template<>
struct _join_impl< >
{
    typedef _list < > type;
};

template<typename ... Args>
struct _join_impl< _list < Args... > >
{
    typedef _list < Args... > type;
};

template<typename ... Args1, typename ... Args2, typename ... AddLists>
struct _join_impl< _list < Args1... >, _list < Args2... >, AddLists... >
{
    typedef _join< _list < Args1..., Args2...>, AddLists...> type;
};

// Used to expand recursively
template<typename T, size_t = 0>
using _just = T;

// Used to repeat a template argument multiple times
template<typename T, typename Idcs>
struct _repeat_impl;

template<typename T, size_t N>
using _repeat =
typename _repeat_impl<T, typename ::std::_Build_index_tuple<N>::__type >::type;

template<typename T, size_t ... idcs>
struct _repeat_impl< T, std::_Index_tuple< idcs... > >
{
    typedef _list< _just < T, idcs> ...> type;
};

template<typename T, size_t N, size_t ... idcs>
struct _repeat_impl< T[N], std::_Index_tuple< idcs... > >
{
    typedef _join< _just< _repeat< _just < T>, N>, idcs> ...> type;
};
// Flatten it all out
template<typename ... Args>
struct _flatten_impl
{
    // We can just use repeat to apply this recursively
    typedef _join< _repeat < Args, 1>...> type;
};

template<typename ... Args>
using _flatten = typename _flatten_impl<Args...>::type;

template<typename T, typename List>
struct _impl_aggregate;
// Partial specialization to capture list-args
template<typename T, typename ... Args>
struct _impl_aggregate< T, _list < Args... > > : Supplier< T >
{
    using typename Supplier< T >::item_t;

    item_t supply(ReadContext& ctx) const override
    {
        return construct(ctx);
    }

    static inline item_t construct(ReadContext& ctx)
    {
        return { new T{ (ctx.construct<Args>())...} };
    }
};

}

// ------- end of hidden utility
template<typename T>
struct memcpy_supplier : Supplier< T >
{
    using typename Supplier< T >::item_t;
    static constexpr size_t n_size = sizeof(T);

    union
    {
        char buffer[size];
        T *object;
    } mutable converter;

    item_t supply(ReadContext& ctx) const override
    {
        istream& stream = ctx.getStream();
        converter.object = new T;
        stream.read(converter.buffer, size);
        return { converter.object };
    }
};
/**
 * This supplier can be used when the type to be supplied can be
 * brace-initialized.
 */
template<typename T, typename ... args>
using aggregate_supplier = _impl_aggregate<T, _flatten<args...> >;

/**
 * This supplier can be used when the type to be supplied can be
 * move-constructed.
 */
template<typename T, typename ... args>
struct move_supplier : Supplier< T >
{
    using typename Supplier< T >::item_t;

    item_t supply(ReadContext& ctx) const override
    {
        return construct(ctx);
    }

    static inline item_t construct(ReadContext& ctx)
    {
        return { new T{ std::move(ctx.construct<args>())... } };
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

/**
 * Fills a list of type Container with items. The container must support the
 * push_back( T ) method where T an object of type
 * <code>Container::value_type</code>.
 *
 * The value_type must be default-readable by the ctx given.
 */
template<typename Container>
void fill_list(ReadContext& ctx, Container& list, size_t c)
{
    using item_cv_t = typename Container::value_type;
    using item_t = typename ::std::remove_cv< item_cv_t >::type;

    while(c --> 0)
        list.push_back( ctx.construct< item_t >() );
}

template<typename T,
        size_t N,
        typename Alloc = std::allocator<T>,
        template<typename, typename> class List=std::list>
List<T, Alloc> constsize_list(ReadContext& ctx)
{
    List<T, Alloc> list;
    fill_list(list, ctx, N);
    return list;
}

template<typename T,
        ReadContext::key_t key,
        typename Alloc = std::allocator<T>,
        template<typename, typename> class List=std::list>
List<T, Alloc> indirectsize_list(ReadContext& ctx)
{
    List<T, Alloc> list;
    fill_list(list, ctx, ctx[key]);
    return list;
}

template<typename T,
        typename Alloc = std::allocator<T>,
        template<typename, typename> class List=std::list>
List<T, Alloc> varsize_list(ReadContext& ctx, size_t c)
{
    List<T, Alloc> list;
    fill_list(list, ctx, c);
    return list;
}

} /* namespace utility */
} /* namespace io */