#pragma once

#include "smartio/ConsumerRegistry.hpp"
#include "smartio/Consumer.hpp"

namespace io {

template<typename T>
consumer_entry consumer_registry::toEntry(
		const ConstConsumerSharedPtr<T>& ptr) {
	return std::static_pointer_cast < _detail::storage_t > (ptr);
}

template<typename T>
ConstConsumerSharedPtr<T> consumer_registry::consumerFromEntry(
		const consumer_entry& entry) {
	return std::template static_pointer_cast<const consumer_base<T>>(entry);
}

template<typename T>
consumer_key<T> consumer_registry::registerConsumer(
		ConstConsumerSharedPtr<T> ptr) {
	return consumers.putEntry < T > (toEntry(ptr));
}

template<typename T>
ConstConsumerSharedPtr<T> consumer_registry::resolveConsumer(
		const consumer_key<T>& key) {
	return consumerFromEntry < T > (consumers.getEntry(key));
}

template<typename T>
bool consumer_registry::makeDefaultEntry(const consumer_key<T>& key) {
	return consumers.makeDefault(key);
}

}
