/*
 * detail.hpp
 *
 * Offers some type definitions that should be internal to the library. Also
 * is a book-keeper for information shared by Environment, Reader and Context
 *
 *  Created on: 22.03.2015
 *      Author: Carbon
 */

#pragma once

#include <memory>
#include <vector>
#include <unordered_map>

#include "smartio/Supplier.hpp"
#include "smartio/typetoken.hpp"
// Utility include
#include "smartio/traits.hpp"

namespace io {

template<class T>
using supplier_key = size_t; // The position in the list
/**
 * Retrieves an invalid key object for the type Q. Can be equality compared
 * to other keys of the same type.
 */
template<typename Q>
inline supplier_key<Q> invalidKey()
{
    return -1;
}

namespace _detail {

template<typename Q>
inline supplier_key<Q> fromIndex(size_t listIndex)
{
    return listIndex;
}

using ::typetoken::token_t;
/**
 * The type of shared_ptr that is used internally to store suppliers
 */
using _supplier_storage_t = void;
/**
 * An entry in the supplier list
 */
using supplier_entry = ::std::shared_ptr<_supplier_storage_t>;
/**
 * A list of all suppliers for a given type
 */
using supplier_list = ::std::vector<supplier_entry>;
/**
 * A map of type -> supplier_list
 */
using supplier_map = ::std::unordered_map<token_t, supplier_list>;

/**
 * Casts a supplier to an entry that can be stored in a supplier_list
 */
template<typename T>
inline supplier_entry toEntry(const SupplierPtr<T>& ptr)
{
    return std::static_pointer_cast<_supplier_storage_t>(ptr);
}
/**
 * Reverse of #toEntry().
 * Note: No type-check is performed.
 */
template<typename T>
inline SupplierPtr<T> fromEntry(const supplier_entry& entry)
{
    return std::static_pointer_cast<T>(entry);
}
/**
 * Retrieves a supplier entry from a map, returns an empty shared_ptr
 * when the entry is not found.
 */
template<typename T>
inline const supplier_entry& getEntry(const supplier_map& map, const supplier_key<T>& key)
{
    // Get the registered supplier
    token_t token = typetoken::getToken< T >();
    const auto& it = map.find(token); // Iterator
    // Check if it's there
    if (it == map.end())
        return nullptr;
    // Reinterpret to actual type and get item
    const supplier_list& list = it->second;
    if(invalidKey<T>() == key || list.size() <= key)
        return nullptr;
    return list[key];
}


}  // namespace _detail
}  // namespace io


