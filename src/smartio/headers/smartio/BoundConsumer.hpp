/*
 * BoundConsumer.hpp
 *
 *  Created on: 01.02.2016
 *      Author: WorldSEnder
 */
#pragma once

#include "smartio/Consumer.hpp"

namespace io {

template<typename T>
class BoundConsumer {
public:
	using item_t = typename consumer_base<T>::item_t;
private:
	ConstConsumerSharedPtr<T> reference;
	WriteContext& ctx;
	BoundConsumer() = delete;
public:
	BoundConsumer(ConstConsumerSharedPtr<T> ref, WriteContext& context);

	virtual ~BoundConsumer();
	/**
	 * Supplies an item from a previously bound context
	 */
	void consume(const item_t& item);
};

}

#include "smartio/BoundConsumer.tpp"
