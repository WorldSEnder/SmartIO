#pragma once

#include <stdexcept>

#include "smartio/BoundConsumer.hpp"

namespace io {

template<typename T>
BoundConsumer<T>::BoundConsumer(ConstConsumerSharedPtr<T> consumer,
		WriteContext& context) :
		reference(consumer), ctx(context) {
	if (reference == nullptr) {
		throw std::invalid_argument(
				"FIXME: illegal nullptr reference to a consumer");
	}
}

template<typename T>
BoundConsumer<T>::~BoundConsumer() {
}

template<typename T>
void BoundConsumer<T>::consume(const item_t& item) {
	return reference->consume(ctx, item);
}

}
