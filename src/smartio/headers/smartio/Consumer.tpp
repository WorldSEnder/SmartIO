/*****************************************************************
 * Name: Martin Molzer
 * Project: smartio-build
 * File: /smartio-build/source/main/include/smartio/Consumer.tpp
 *****************************************************************/

#pragma once

#include "smartio/Consumer.hpp"

namespace io {

template<typename T>
consumer_base<T>::~consumer_base() {
}

template<typename T>
void consumer_base<T>::consume(WriteContext& ctx, const item_t& item) const {
	this->DoConsume(ctx, item);
}

}
// namespace io
