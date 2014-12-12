#pragma once

#include "Context.hpp"

#include <stdexcept>

#include "traits.hpp"

namespace io
{
using std::invalid_argument;

using typetoken::token_t;

template<typename T>
const Supplier< supply_t< T > >& Context::retrieveSupplier() const
{
    using supplier_t = Supplier< T >;
    using item_t = typename supplier_t::item_t;
    // Get the registered supplier
    token_t token = typetoken::getToken< item_t >();
    const auto& it = reference.find(token); // Iterator
    // Check if it's there
    if (it == reference.end())
        throw invalid_argument("No supplier registered for given type.");
    // Reinterpret to actual type and get item
    const supplier_t& supp = *std::static_pointer_cast< const supplier_t,
            const SupplierBase >(it->second);
    return supp;
}

template<typename T>
BoundSupplier< supply_t<T> > Context::getSupplier()
{
    return BoundSupplier< supply_t<T> >(this->retrieveSupplier< T >(), *this);
}

template<typename T>
supply_t< T > Context::construct()
{
    using supplier_t = Supplier< T >;
    using item_t = typename supplier_t::item_t;
    const supplier_t& supp = this->retrieveSupplier< item_t >();
    return supp.supply(*this);
}

template<typename T>
Context& Context::operator>>(T& val)
{
    val = construct< T >();
    return *this;
}

template<typename T>
T& Context::operator>>=(T& val)
{
    return val = construct<T>();
}

template<typename T>
Context::operator T()
{
    return construct< T >();
}

template<typename T, std::size_t N>
Context& Context::operator>>(T (&arr)[N])
{
    for (auto& i : arr)
    {
        *this >> i;
    }
    return *this;
}

}
