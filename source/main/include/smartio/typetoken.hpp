/*
 * typetoken.hpp
 *
 *  Created on: 27.11.2014
 *      Author: Carbon
 */
#pragma once

#include <atomic>
#include <typeinfo>
#include <typeindex>

namespace typetoken
{

using token_t = std::type_index;
using impl_token_t = std::size_t;

//template<typename T> impl_token_t getImplToken(void);

class impltokenbase
{
private:
    impltokenbase(void) = delete;
    ~impltokenbase(void) = delete;
    void *operator new(size_t) = delete;

    static std::atomic< impl_token_t > counter;
};

template<template<typename ...> class T>
struct impl_typetoken : impltokenbase
{
private:
    impl_typetoken(void) = delete;
    ~impl_typetoken(void) = delete;

    static std::atomic<impl_token_t> ID;
public:
    static impl_token_t getToken(void)
    {
        impl_token_t id = impl_typetoken<T>::ID;
        if (!id)
        {
            impl_token_t newID = ++impl_typetoken::counter;
            std::atomic_compare_exchange_strong(&impl_typetoken<T>::ID, &id, newID);
            id = impl_typetoken<T>::ID;
        }
        return id;
    }
};

template<template<typename ...> class T>
std::atomic<impl_token_t> impl_typetoken<T>::ID = ATOMIC_VAR_INIT(0);

/**
 * Gets a typetoken for the given type. The returned token can be
 * used in maps and unordered collections as a key and uniquely
 * identifies the type requested.
 */
template<typename T>
inline token_t getToken(void)
{
    return std::type_index(typeid(T));
}

template<template<typename ...> class T>
inline impl_token_t getImplToken(void)
{
    return impl_typetoken<T>::getToken();
}

}
 // namespace typetoken
