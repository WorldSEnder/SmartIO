/*
 * Environement.h
 *
 *  Created on: 27.11.2014
 *      Author: Carbon
 */
#pragma once

#include <memory>

#include "smartio/detail.hpp"
#include "smartio/Supplier.hpp"
#include "smartio/Consumer.hpp"
#include "smartio/Reader.hpp"
#include "smartio/Writer.hpp"

namespace io
{

  using ::std::shared_ptr;
  /**
   * This class serves as a Builder for Readers
   */
  class Environment
  {
  public:
    Environment ();
    template<typename Config>
    Environment (const Config& c);
    virtual
    ~Environment ();
    /**
     * Adds a supplier to the collection of suppliers used by all Readers
     * built by this Environment. Registering a nullptr has no effect.<br>
     *
     * <T> the type to register for
     *
     * \returns A key to retrieve the registered supplier
     */
    template<typename T>
      supplier_key<T>
      addSupplier (SupplierPtr<T> ptr);
    template<typename T>
      consumer_key<T>
      addConsumer (ConsumerPtr<T> ptr);
    /**
     * Adds a supplier to the collection of suppliers. Registering a nullptr
     * has no effect.<br>
     * This method tries to automatically deduce the registered type of supplier
     * even when a more specific one than SupplierPtr is given.
     */
    template<typename T>
      auto
      addSupplier2 (shared_ptr<T> ptr)
      -> supplier_key< base_deduction_t< Supplier, T > >
      {
	// FIXME: (currently) can't be put into .tpp -> "member declaration not found"
	using item_t = base_deduction_t< Supplier, T >;

	SupplierPtr<item_t> new_ptr =
	    std::static_pointer_cast<Supplier<item_t>> (ptr);
	return addSupplier (new_ptr);
      }
    /**
     * Adds a consumer to the collection of consumers. Registering a nullptr
     * has no effect.<br>
     * This method tries to automatically deduce the registered type of consumer
     * even when a more specific one than ConsumerPtr is given.
     */
    template<typename T>
    consumer_key< base_deduction_t< Consumer, T > >
      addConsumer2 (shared_ptr<T> ptr)
      {
	using item_t = base_deduction_t< Consumer, T >;

	ConsumerPtr<item_t> new_ptr =
	    std::static_pointer_cast<Consumer<item_t>> (ptr);
	return addConsumer (new_ptr);
      }
    /**
     * Forwards to addSupplier.
     *
     * <T> the type of the supplier
     * <Args> forwarded arguments
     */
    template<typename T, class ... Args>
      inline auto
      emplaceSupplier (Args ... args)
      -> supplier_key< base_deduction_t< Supplier, T > >
      {
	using item_t = base_deduction_t< Supplier, T >;

	return addSupplier (SupplierPtr<item_t>
	  { new T
	    { ::std::forward<Args>(args)... } });
      }
    /**
     * Forwards to addConsumer.
     *
     * <T> the type of the supplier
     * <Args> forwarded arguments
     */
    template<typename T, class ... Args>
      inline
      supplier_key< base_deduction_t< Consumer, T > >
      emplaceConsumer (Args&& ... args)
      {
	using item_t = base_deduction_t< Consumer, T >;

	return addConsumer (ConsumerPtr<item_t>
	  { new T
	    { ::std::forward<Args>(args)... } });
      }

    template<typename T>
      ConstSupplierPtr<T>
      getSupplier (supplier_key<T> key);

    template<typename T>
      ConstConsumerPtr<T>
      getConsumer (consumer_key<T> key);

    /**
     * Builds a new Reader from all registered suppliers. The Reader will
     * be capable of building objects of all types previously registered in
     * this environment.<br>
     * The returned Reader-object has a lifetime that is limited to this
     * Environment's lifetime and should not be used after the Environment
     * used to create it has been destroyed. This has to do with the nature
     * of the Supplier object as only references to registered suppliers can
     * be kept around. Default suppliers are destroyed when this Environment
     * is destroyed.<br>
     * Only when you are sure that you don't use the default suppliers you
     * may use the returned Reader after this Environment has been destroyed
     * and only if you are sure that all registered Suppliers are alive.
     */
    Reader
    buildReader () const;
    Writer
    buildWriter () const;

  private:
    supplier_map suppliers;
    consumer_map consumers;
  };

} /* namespace io */

#include "Environment.tpp"
