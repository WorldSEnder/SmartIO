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

namespace io
{

  namespace _detail
  {
    template<typename T>
      struct storage_key;

    template<typename T>
      inline storage_key<T>
      fromIndex (size_t listIndex);

    template<typename T>
      struct storage_key
      {
      private:
	storage_key () = delete;
	storage_key (size_t);
      public:
	inline bool
	operator== (const storage_key& other) const;
	inline bool
	operator!= (const storage_key& other) const;

	inline size_t
	asIndex () const;
	/**
	 * Retrieves an invalid key object for the type Q. Can be equality compared
	 * to other keys of the same type.
	 */
	static inline storage_key
	invalid ();
	static inline storage_key
	default_ ();
      private:
	size_t position;

	template<typename Q>
	  friend storage_key<Q>
	  fromIndex (size_t listIndex);
      };

    using type = ::typetoken::token_t;
    /**
     * The type of shared_ptr that is used internally to store suppliers
     */
    using storage_t = void;
    /**
     * An entry in the supplier list
     */
    using storage_entry = ::std::shared_ptr<storage_t>;
    /**
     * A list of all suppliers for a given type
     */
    using storage_list = ::std::vector<storage_entry>;
    /**
     * A map of type -> supplier_list
     */
    using storage_map = ::std::unordered_map<type, storage_list>;

    /**
     * Casts a supplier to an entry that can be stored in a supplier_list
     */
    template<typename T>
      inline storage_entry
      toEntry (const SupplierPtr<T>& ptr);
//    template<typename T>
//      inline storage_entry
//      toEntry (const ConsumerPtr<T>& ptr)
//      {
//	return std::static_pointer_cast<storage_t> (ptr);
//      }
    /**
     * Reverse of #toEntry().
     * Note: No type-check is performed.
     */
    template<typename T>
      inline SupplierPtr<T>
      supplierFromEntry (const storage_entry& entry);
//    template<typename T>
//      inline ConsumerPtr<T>
//      consumerFromEntry (const storage_entry& entry);

    /**
     * Retrieves a supplier entry from a map, returns an empty shared_ptr
     * when the entry is not found.
     */
    template<typename T>
      const storage_entry&
      getEntry (const storage_map& map, const storage_key<T>& key);
    /**
     * Puts a new entry in the map and returns it's key. If it
     * is the first entry, it also is the default entry.
     */
    template<typename T>
      const storage_key<T>
      putEntry (storage_map& map, storage_entry entry);
    /**
     * Makes the entry associated with key the default entry in the map
     */
    template<typename T>
      bool
      makeDefaultEntry (storage_map& map, const storage_key<T>& key);
  }  // namespace _detail

  template<class T>
    using supplier_key = _detail::storage_key<T>;
  template<class T>
    using consumer_key = _detail::storage_key<T>;

  using supplier_map = _detail::storage_map;
  using consumer_map = _detail::storage_map;

  /**
   * Retrieves a supplier entry from a map, returns an empty shared_ptr
   * when the entry is not found.
   */
  template<typename T>
    inline const SupplierPtr<T>&
    getSupplier (const supplier_map& map, const supplier_key<T>& key)
    {
      return _detail::supplierFromEntry<T> (_detail::getEntry (map, key));
    }
//  template<typename T>
//    inline const ConsumerPtr<T>&
//    getConsumer (const consumer_map& map, const consumer_key<T>& key)
//    {
//      return _detail::consumerFromEntry<T> (_detail::getEntry (map, key));
//    }
  template<typename T>
    inline supplier_key<T>
    putSupplier (supplier_map& map, SupplierPtr<T> ptr)
    {
      return _detail::putEntry<T> (map, _detail::toEntry (ptr));
    }
//  template<typename T>
//    inline const ConsumerPtr<T>&
//    putConsumer (consumer_map& map, ConsumerPtr<T> ptr)
//    {
//      return _detail::putEntry<T> (map, _detail::toEntry (ptr));
//    }
  template<typename T>
    inline bool
    makeDefaultSupplier (supplier_map& map, const supplier_key<T>& key)
    {
      return _detail::makeDefaultEntry (map, key);
    }
//  template<typename T>
//    inline bool
//    makeDefaultConsumer (consumer_map& map, const consumer_key<T>& key)
//    {
//      return _detail::makeDefaultEntry (map, key);
//    }

}// namespace io

#include "smartio/detail.tpp"
