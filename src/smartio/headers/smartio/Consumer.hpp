/*
 * Consumer.hpp
 *
 *  Created on: 06.12.2014
 *      Author: Carbon
 */
#pragma once

#include <memory>

#include "smartio/traits.hpp"

namespace io {

class WriteContext;

template<typename T>
class consumer_base {
public:
	using item_t = consume_t<T>;

	virtual ~consumer_base();

	void consume(WriteContext&, const item_t&) const;
private:
	virtual void
	DoConsume(WriteContext&, const item_t&) const = 0;
};

template<typename T>
using ConsumerSharedPtr = std::shared_ptr<consumer_base< T >>;
template<typename T>
using ConstConsumerSharedPtr = std::shared_ptr<const consumer_base< T >>;

} /* namespace io */

#include "smartio/Consumer.tpp"
