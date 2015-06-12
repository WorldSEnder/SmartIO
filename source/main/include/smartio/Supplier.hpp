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

  namespace _detail
  {
    template<typename T>
      struct supplier_base_apply
      {
	virtual
	~supplier_base_apply () = default;
	/**
	 * Given a readcontext and a (non const) target
	 * should fill the target with values read from the
	 * context. If the supplier doesn't support this, it
	 * should return false. Otherwise the target should
	 * be changed accordingly and true is returned.
	 */
	virtual bool
	doapply (ReadContext& ctx, T& trgt) const = 0;
      };

    template<typename T, bool = std::is_default_constructible<T>::value>
      struct supplier_base_supply : public supplier_base_apply<T>
      {
      public:
	using item_t = supply_t< T >;
	virtual
	~supplier_base_supply () = default;
	/**
	 * Supplies an item of the type T. This method allocates
	 * a new T instead of relying on an existant one like #doapply().
	 *
	 * If T is default_constructible there exists a default implementation:
	 * <code>
	 * T* t = new T{};
	 * this->doapply(ctx, *t);
	 * return item_t{ t };
	 * </code>
	 */
	virtual item_t
	dosupply (ReadContext& ctx) const = 0;
      };

    template<typename T>
      struct supplier_base_supply<T, true> : supplier_base_apply<T>
      {
      public:
	using item_t = supply_t< T >;
	virtual
	~supplier_base_supply () = default;
	virtual item_t
	dosupply (ReadContext& ctx) const
	{
	  T* nt = new T; // Default construcible
	  bool success = this->doapply (ctx, *nt);
	  (void) success; // Ignore
	  return item_t
	    { nt };
	}
      };
  }

  /**
   * A supplier for the type T
   */
  template<typename T>
    class Supplier : private _detail::supplier_base_supply<T>
    {
    public:
      using item_t = typename _detail::supplier_base_supply<T>::item_t;

      virtual
      ~Supplier () = default;
      item_t
      supply (ReadContext& ctx) const;
      bool
      apply (ReadContext& ctx, T& trgt) const;
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
      /**
       * Applies the supplier to an element, if possible
       * @ret false if this supplier doesn't support application
       * (e.g. immutable types, UUIDs and what not)
       */
      bool
      apply (T& trgt)
      {
	return reference->apply (trgt);
      }
    };

} /* namespace io */

#include "smartio/Supplier.tpp"
