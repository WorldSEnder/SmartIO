/*****************************************************************
 * Name: Martin Molzer
 * Project: smartio
 * File: /smartio/source/main/include/smartio/detail.tpp
 *****************************************************************/

#pragma once

#include "smartio/detail.hpp"
#include <limits>

namespace io
{

  namespace _detail
  {

    template<typename T>
      storage_key<T>::storage_key (size_t pos) :
	  position (pos)
      {
      }

    template<typename T>
      inline bool
      storage_key<T>::operator == (const storage_key& other) const
      {
	return position == other.position;
      }

    template<typename T>
      inline bool
      storage_key<T>::operator != (const storage_key& other) const
      {
	return position != other.position;
      }

    template<typename T>
      inline size_t
      storage_key<T>::asIndex () const
      {
	return position;
      }

    template<typename T>
      inline storage_key<T>
      storage_key<T>::invalid ()
      {
	return
	  { std::numeric_limits<size_t>::max() };
      }

    template<typename T>
      inline storage_key<T>
      storage_key<T>::default_ ()
      {
	return
	  { 0};
      }

    template<typename Q>
      inline supplier_key<Q>
      fromIndex (size_t listIndex)
      {
	return
	  { listIndex};
      }

    template<typename T>
      inline storage_entry
      toEntry (const SupplierPtr<T>& ptr)
      {
	return std::static_pointer_cast<storage_t> (ptr);
      }
//  template<typename T>
//    inline storage_entry
//    toEntry (const ConsumerPtr<T>& ptr)
//    {
//      return std::static_pointer_cast<storage_t> (ptr);
//    }

    template<typename T>
      inline SupplierPtr<T>
      supplierFromEntry (const storage_entry& entry)
      {
	return std::static_pointer_cast<Supplier<T>> (entry);
      }
//  template<typename T>
//    inline ConsumerPtr<T>
//    consumerFromEntry (const storage_entry& entry)
//    {
//    return std::static_pointer_cast<Consumer<T>> (entry);
//    }

    template<typename T>
      storage_entry
      getEntry (const storage_map& map, const storage_key<T>& key)
      {
	if (key == storage_key<T>::invalid ())
	  return
	    { nullptr};
	// Get the registered supplier
	type token = typetoken::getToken<T> ();
	const auto& it = map.find (token); // Iterator
	// Check if it's there
	if (it == map.end ())
	  return
	    { nullptr};
	// Reinterpret to actual type and get item
	const storage_list& list = it->second;
	// No range check, result undefined
      return list[key.asIndex()];
    }

template<typename T>
  storage_key<T>
  putEntry (storage_map& map, storage_entry entry)
  {
    if(entry == nullptr)
      return storage_key<T>::invalid();
    type token = typetoken::getToken<T>();
    // Default constructs if necessary
    storage_list& list = map[token];
    size_t listsize = list.size();
    if(listsize == 0)
      {
	list.push_back(entry);
	listsize++;
      }
    list.push_back(entry);
    // NOT THREADSAFE!!
    return fromIndex<T> (listsize);
  }

template<typename T>
  bool
  makeDefaultEntry (storage_map& map, const storage_key<T>& key)
  {
    if(key == storage_key<T>::invalid())
      return false;
    if(key == storage_key<T>::default_())
      return true;
    type token = typetoken::getToken<T>();
    auto it = map.find(token);
    if(it == map.end())
      return false;
    it->second[0] = it->second[key.asIndex()];
    return true;
  }

}  // namespace _detail

}  // namespace io
