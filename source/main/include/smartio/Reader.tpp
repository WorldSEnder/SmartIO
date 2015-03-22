#pragma once

#include "smartio/Reader.hpp"

namespace io
{

template<typename T>
SupplierPtr<T> Reader::getSupplier(supplier_key<T> key) const
{
    using _detail::supplier_entry;

    const supplier_entry& entry = _detail::getEntry< T >(this->suppliers, key);
    // That is, after all, a safe cast
    SupplierPtr<T> ptr = _detail::fromEntry< T >(entry);
    return ptr;
}

template<typename T>
T Reader::construct(input& stream, supplier_key<T> key) const
{
    return from(stream).construct< T >(key);
}

}
