/*
 * Supplier.hpp
 *
 *  Created on: 27.11.2014
 *      Author: Carbon
 */
#pragma once

#include "traits.hpp"

namespace io
{

// Forward declare Context
class Context;
/**
 * Base class for suppliers so we can store them in a list
 */
class SupplierBase
{
};
/**
 * A supplier for the type T
 */
template<typename T>
class Supplier : public SupplierBase
{
public:
    using item_t = supply_t< T >;

    virtual ~Supplier()
    {
    }
    ;
    /**
     * Supplies an item of the type
     */
    virtual item_t supply(Context&) const = 0;
};

template<typename T>
class BoundSupplier
{
public:
    using supplier_t = Supplier< T >;
    using typename supplier_t::item_t;
private:
    // TODO: change this to std::shared_ptr, too?
    const supplier_t& reference;
    Context& ctx;
public:
    BoundSupplier() = delete;
    BoundSupplier(const supplier_t& supplier, Context& context) :
            ctx(context), reference(supplier)
    {
    }
    BoundSupplier(supplier_t&&, Context&) = delete;

    virtual ~BoundSupplier()
    {
    }
    /**
     * Supplies an item from a previously bound context
     */
    item_t supply()
    {
        return reference.supply(ctx);
    }
};

} /* namespace io */
