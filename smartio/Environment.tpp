#pragma once

#include "Environment.hpp"

#include <utility>
#include <type_traits>

#include "traits.hpp"
#include "typetoken.hpp"
#include "Supplier.hpp"

namespace io
{
using typetoken::token_t;

template<typename T, typename Q>
Environment& Environment::addDefaultConstructibleSupplier()
{
    return addSupplier< T, Q >(shared_ptr< T >(new T));
}

template<typename T, typename Q>
Environment& Environment::addSupplier(shared_ptr< T > supplier)
{
    using supplier_t = Supplier< Q >;
    using item_t = typename supplier_t::item_t;
    static_assert(std::is_base_of<supplier_t, T>::value, "T has to extend Supplier<Q>");
    if (supplier != nullptr)
    {
        token_t token = typetoken::getToken< item_t >();
        // We use this instead of map[key] = value because Supplier can't be allocated
        suppliers.insert(
                std::make_pair(token,
                        std::static_pointer_cast< const SupplierBase, T >(
                                supplier)));
    }
    return *this;
}

template<typename T>
Environment& Environment::operator+=(shared_ptr< T > supplier)
{
    return addSupplier(std::move(supplier));
}

}
