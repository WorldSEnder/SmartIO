#pragma once

#include "smartio/Environment.hpp"

#include <utility>
#include <type_traits>

namespace io
{

template<typename T>
auto Environment::addSupplier(SupplierPtr< T > supplier)
-> supplier_key<T>
{
    using supplier_t = Supplier< T >;
    using item_t = typename supplier_t::item_t;
    using _detail::supplier_entry;
    using _detail::supplier_list;


    if (supplier == nullptr)
    {
        return invalidKey<T>();
    }
    token_t token = typetoken::getToken< item_t >();
    // List gets default constructed when not present
    supplier_list& list = suppliers[token];
    supplier_key<T> key = list.size();
    list.push_back(_detail::toEntry(supplier));

    return key;
}

}
