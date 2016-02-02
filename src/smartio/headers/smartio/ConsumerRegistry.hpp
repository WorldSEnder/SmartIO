#pragma once

#include "smartio/StorageMap.hpp"
#include "smartio/Consumer.hpp"

namespace io {

template<class T>
using consumer_key = _detail::storage_key<T>;
using consumer_entry = _detail::storage_entry;
using consumer_map = _detail::storage_map;

class consumer_registry {
public:
	consumer_registry() = default;
	consumer_registry(const consumer_registry&) = default;
	consumer_registry(consumer_registry&&) = default;
	virtual ~consumer_registry() = default;

protected:
	template<typename T>
	consumer_key<T>
	registerConsumer(ConstConsumerSharedPtr<T> ptr);

	template<typename T>
	ConstConsumerSharedPtr<T>
	resolveConsumer(const consumer_key<T>& key = consumer_key<T>::default_());

	template<typename T>
	bool
	makeDefaultEntry(const consumer_key<T>& key);
private:
	consumer_map consumers;
	/**
	 * Casts a supplier to an entry that can be stored in a supplier_list
	 */
	template<typename T>
	inline consumer_entry
	toEntry(const ConstConsumerSharedPtr<T>& ptr);
	/**
	 * Reverse of #toEntry().
	 * Note: No type-check is performed.
	 */
	template<typename T>
	ConstConsumerSharedPtr<T>
	consumerFromEntry(const consumer_entry& entry);
};

}

#include "smartio/ConsumerRegistry.tpp"
