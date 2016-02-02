/*****************************************************************
 * Name: Martin Molzer
 * Project: smartio-build
 * File: /smartio-build/source/main/include/smartio/Writer.tpp
 *****************************************************************/

#pragma once

#include "smartio/Writer.hpp"

namespace io {

template<typename T>
ConstConsumerSharedPtr<T> Writer::getSupplier(consumer_key<T> key) const {
	return resolveConsumer(key);
}

template<typename T>
void Writer::consume(output& stream, const T& item, consumer_key<T> key) const {
	return into(stream).write(item, key);
}

}  // namespace io
