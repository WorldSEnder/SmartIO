#pragma once

#include "smartio/Context.hpp"

#include <stdexcept>

#include "smartio/defaultsuppliers.hpp"
#include "smartio/typetoken.hpp"

namespace io
{
using std::invalid_argument;

using typetoken::token_t;

template<typename T>
SupplierPtr< T > ReadContext::retrieveSupplier(supplier_key<T> key) const
{
    using _detail::supplier_entry;

    const supplier_entry& entry = _detail::getEntry< T >(reference, key);
    // Reinterpret to actual type and get item
    SupplierPtr< T > ptr = _detail::fromEntry< T >(entry);
    return ptr;
}

template<typename T>
SupplierPtr< T > ReadContext::retrieveSupplier() const
{
    using _detail::supplier_entry;
    using _detail::supplier_list;
    using typetoken::token_t;

    token_t token = typetoken::getToken< T >();

    const auto& entry = reference.find(token);
    if(entry == reference.end())
        return {nullptr};
    const supplier_list& list = entry->second;
    if(list.size() == 0)
        return {nullptr};
    SupplierPtr< T > ptr = _detail::fromEntry< T >(list[0]);
    // Reinterpret to actual type and get item
    return ptr;
}

template<typename T>
BoundSupplier< T > ReadContext::getSupplier(supplier_key<T> key)
{
    return BoundSupplier< supply_t<T> >(this->retrieveSupplier< T >(key), *this);
}

template<typename T>
supply_t< T > ReadContext::get(supplier_key< T > key)
{
    SupplierPtr< T > ptr = this->retrieveSupplier< T >(key);
    if(ptr == nullptr)
        return {nullptr};
    return ptr->supply(*this);
}
template<typename T>
T ReadContext::construct(supplier_key< T > key)
{
    T *ptr = this->get< T >(key).release();
    // IDEA: add missing item policy
    // if(ptr == nullptr) return T{};
    return *ptr;
}
template<typename T>
supply_t< T > ReadContext::get()
{
    SupplierPtr< T > ptr = this->retrieveSupplier< T >();
    if(ptr == nullptr)
        return {nullptr};
    return ptr->supply(*this);
}
template<typename T>
T ReadContext::construct()
{
    T *ptr = this->get< T >().release();
    // IDEA: add missing item policy
    // if(ptr == nullptr) return T{};
    return *ptr;
}

template<typename T>
inline ReadContext& ReadContext::operator>>(T& out)
{
    (*this) >> out;
    return *this;
}

template<typename T>
inline T& ReadContext::operator>>=(T& out)
{
    using cv_item_t = typename ::std::remove_reference<T>::type;
    using item_t = typename ::std::remove_cv< cv_item_t >::type;

    out = this->construct< item_t >();
    return out;
}

template<typename T, size_t N>
inline auto ReadContext::operator>>=(arr_ref<T, N> out)
-> arr_ref<T, N>
{
    using item_t = typename ::std::remove_cv< T >::type;

    for(size_t i = 0; i < N; ++i)
    {
        (*this) >> out[i];
    }
    return out;

}

template<typename T, size_t N>
inline ReadContext& ReadContext::operator>>(arr_ref<T, N> out)
{
    (*this) >> out;
    return *this;
}

}
