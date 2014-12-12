#pragma once

#include "Reader.hpp"

#include <stdexcept>

#include "traits.hpp"

namespace io
{
using std::invalid_argument;

template<typename T>
const Supplier< supply_t< T > >& Reader::getSupplier() const
{
    // TODO: add an option to select different reading modes, BINARY, TEXT, etc.
    using supplier_t = Supplier< T >;
    using item_t = typename supplier_t::item_t;
    // Get the registered supplier
    token_t token = typetoken::getToken< item_t >();
    const auto& it = suppliers.find(token); // Iterator
    // Check if it's there
    if (it == suppliers.end())
        throw invalid_argument("No supplier registered for given type.");
    // Reinterpret to actual type and get item
    const supplier_t& supp = *std::static_pointer_cast< const supplier_t,
            const SupplierBase >(it->second);
    return supp;
}

//Context Reader::createContext(istream& stream) const {
//	return Context(this->suppliers, stream);
//}

template<typename T>
supply_t< T > Reader::construct(istream& f) const
{
    Context ctx = createContext(f);
    return ctx.construct< T >();
}

}
