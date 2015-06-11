/*
 * Supplier.hpp
 *
 *  Created on: 27.11.2014
 *      Author: Carbon
 */
#pragma once

#include <memory>
#include "smartio/traits.hpp"

namespace io
{

// Forward declare Context
  class ReadContext;

  /**
   * A supplier for the type T
   */
  template<typename T>
    class Supplier
    {
    public:
      using item_t = supply_t< T >;

      virtual
      ~Supplier ()
      {
      }

      item_t
      supply (ReadContext& ctx) const;
    private:
      /**
       * Supplies an item of the type
       */
      virtual item_t
      dosupply (ReadContext&) const = 0;
    };

  template<typename T>
    using SupplierPtr = std::shared_ptr<Supplier< T >>;

  template<typename T>
    using ConstSupplierPtr = std::shared_ptr<const Supplier< T >>;

  template<typename T>
    class BoundSupplier
    {
    public:
      using supplier_t = Supplier< T >;
      using typename supplier_t::item_t;
    private:
      // TODO: change this to std::shared_ptr, too?
      SupplierPtr<T> reference;
      ReadContext& ctx;
      BoundSupplier () = delete;
    public:
      /**
       * A bound supplier has a context already applied aswell as a supplier.
       * This enables it to return specific items without a context. The life-time
       * of a BoundSupplier can not exceed the lifetime of the context it is bound
       * to. // FIXME: maybe only allow shared_ptr<Context>'s and enable shared_from_this
       */
      BoundSupplier (SupplierPtr<T> supplier, ReadContext& context) :
	  ctx (context), reference (supplier)
      {
	if (reference == nullptr)
	  {
	    // FIXME: scream as loud as we can
	  }
      }
      BoundSupplier (supplier_t&&, ReadContext&) = delete;

      virtual
      ~BoundSupplier ()
      {
      }
      /**
       * Supplies an item from a previously bound context
       */
      item_t
      supply ()
      {
	return reference->supply (ctx);
      }
    };

} /* namespace io */
