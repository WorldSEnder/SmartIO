#pragma once

#include <limits>

#include "smartio/StorageMap.hpp"

namespace io {

namespace _detail {

template<typename T>
storage_key<T>::storage_key(size_t pos) :
		position(pos) {
}

template<typename T>
inline bool storage_key<T>::operator ==(const storage_key& other) const {
	return position == other.position;
}

template<typename T>
inline bool storage_key<T>::operator !=(const storage_key& other) const {
	return position != other.position;
}

template<typename T>
inline size_t storage_key<T>::asIndex() const {
	return position;
}

template<typename T>
inline storage_key<T> storage_key<T>::invalid() {
	return {std::numeric_limits<size_t>::max()};
}

template<typename T>
inline storage_key<T> storage_key<T>::default_() {
	return {0};
}

template<typename Q>
inline storage_key<Q> storage_key<Q>::fromIndex(size_t listIndex) {
	return {listIndex};
}

template<typename T>
storage_entry storage_map::getEntry(const storage_key<T>& key) const {
	if (key == storage_key < T > ::invalid())
		return {nullptr};
	// Get the registered supplier
	type token = typetoken::getToken<T>();
	const auto& it = find(token); // Iterator
	// Check if it's there
	if (it == end())
		return {nullptr};
	// Reinterpret to actual type and get item
	const storage_list& list = it->second;
	// No range check, result undefined
	return list[key.asIndex()];
}

template<typename T>
storage_key<T> storage_map::putEntry(storage_entry entry) {
	if (entry == nullptr)
		return storage_key < T > ::invalid();
	type token = typetoken::getToken<T>();
	// Default constructs if necessary
	storage_list& list = (*this)[token];
	size_t listsize = list.size();
	if (listsize == 0) {
		list.push_back(entry);
		listsize++;
	}
	list.push_back(entry);
	// NOT THREADSAFE!!
	return storage_key < T > ::fromIndex(listsize);
}

template<typename T>
bool storage_map::makeDefault(const storage_key<T>& key) {
	if (key == storage_key < T > ::invalid())
		return false;
	if (key == storage_key < T > ::default_())
		return true;
	type token = typetoken::getToken<T>();
	auto it = find(token);
	if (it == end())
		return false;
	it->second[0] = it->second[key.asIndex()];
	return true;
}

}

}
