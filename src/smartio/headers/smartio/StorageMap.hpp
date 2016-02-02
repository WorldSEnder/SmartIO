/*
 * StorageMap.hpp
 *
 *  Created on: 01.02.2016
 *      Author: WorldSEnder
 */

#pragma once

#include <memory>
#include <vector>
#include <unordered_map>

#include "smartio/typetoken.hpp"

namespace io {

namespace _detail {
template<typename T>
struct storage_key;

template<typename T>
struct storage_key {
private:
	storage_key() = delete;
	storage_key (size_t);
public:
	inline bool
	operator==(const storage_key& other) const;
	inline bool
	operator!=(const storage_key& other) const;

	inline size_t
	asIndex() const;
	/**
	 * Retrieves an invalid key object for the type Q. Can be equality compared
	 * to other keys of the same type.
	 */
	static inline storage_key
	invalid();
	static inline storage_key
	default_();

	static storage_key<T>
	fromIndex(size_t listIndex);
private:
	size_t position;
};

using type = ::typetoken::token_t;
/**
 * The type of shared_ptr that is used internally to store suppliers
 */
using storage_t = const void;
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
class storage_map: ::std::unordered_map<type, storage_list> {
public:
	storage_map() = default;
	storage_map(const storage_map&) = default;
	virtual ~storage_map() = default;
	/**
	 * Retrieves a supplier entry from a map, returns an empty shared_ptr
	 * when the entry is not found.
	 */
	template<typename T>
	storage_entry
	getEntry(const storage_key<T>& key) const;
	/**
	 * Puts a new entry in the map and returns it's key. If it
	 * is the first entry, it also is the default entry.
	 */
	template<typename T>
	storage_key<T>
	putEntry(storage_entry entry);
	/**
	 * Makes the entry associated with key the default entry in the map
	 */
	template<typename T>
	bool
	makeDefault(const storage_key<T>& key);
};

}

}

#include "smartio/StorageMap.tpp"
