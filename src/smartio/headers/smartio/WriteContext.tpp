#pragma once

#include "smartio/WriteContext.hpp"
#include "smartio/Consumer.hpp"

namespace io {

template<typename T>
BoundConsumer<T> WriteContext::getConsumer(consumer_key<T> key) {
	return {resolveConsumer(key), stream};
}

template<typename T>
void WriteContext::write(const T& object, consumer_key<T> key) {
	ConstConsumerSharedPtr < T > writer = resolveConsumer(key);
	writer->consume(*this, object);
}

template<typename T>
WriteContext&
WriteContext::operator<<(const T& object) {
	this->write(object);
	return *this;
}

template<typename T, size_t N>
WriteContext&
WriteContext::operator<<(arr_ref<T, N> in) {
	for (size_t i = 0; i < N; ++i) {
		(*this) << in[i];
	}
	return *this;
}

}
