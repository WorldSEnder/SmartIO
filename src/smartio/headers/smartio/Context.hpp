/*
 * Context.hpp
 *
 *  Created on: 29.11.2014
 *      Author: Carbon
 */

#pragma once

#include <unordered_map>
#include <istream>
#include <ostream>
#include <memory>

#include "smartio/Consumer.hpp"
#include "smartio/ConsumerRegistry.hpp"
#include "smartio/BoundConsumer.hpp"

namespace io {

// Forward declare for friend
class Reader;
class Writer;

using context_key = size_t;
using context_val = size_t;
/**
 * Holds all of context that is shared between Read and Write
 */
class context_base {
public:
	context_base();
	virtual
	~context_base();
	/**
	 * Sets the context variable for key.
	 */
	void
	setValue(context_key, context_val);
	/**
	 * Retrieves the value previously set for the key or default if it hasn't
	 * been set. The context is not changed by this call.
	 */
	context_val
	getValue(context_key, context_val) const;
	/**
	 * Checks if a value for key has been set
	 */
	bool
	hasValue(context_key) const;
	/**
	 * A suitable variant to setValue/getValue.
	 * If the key doesn't yet exist a value of zero is assigned to it. The returned
	 * reference can be used to effectively change the value of the Context-value.
	 */
	context_val&
	operator[](context_key);
private:
	using key_t = context_key;
	using value_t = context_val;

	using var_map = std::unordered_map<context_key, context_val>;

	var_map contextVars;
};

} /* namespace io */
// FIXME: include get() and write() as array operations.

