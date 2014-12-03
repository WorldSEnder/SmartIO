/*
 * Supplier.hpp
 *
 *  Created on: 27.11.2014
 *      Author: Carbon
 */
#pragma once

#include <istream>

#include "traits.hpp"

namespace io {

// Forward declare Context
class Context;

using std::istream;
/**
 * Base class for suppliers so we can store them in a list
 */
class SupplierBase {
};
/**
 * A supplier for the type T
 */
template<typename T>
class Supplier : public SupplierBase {
public:
	typedef typename supply_t<T>::type item_t;

	virtual ~Supplier() {};
	/**
	 * Supplies an item of the type
	 */
	virtual item_t supply(Context& reader) const = 0;
};

template<typename T>
class BoundSupplier {
	// TODO: change this to std::shared_ptr, too?
	const Supplier<T>& reference;
	istream& stream;
public:
	BoundSupplier() = delete;
	BoundSupplier(const Supplier<T>&, istream&);
	BoundSupplier(Supplier<T>&&, istream&) = delete;
	typedef typename supply_t<T>::type item_t;

	virtual ~BoundSupplier() {};
	/**
	 * Supplies an item from a previously bound istream
	 */
	item_t supply() const {
		return reference.supply(stream);
	}
};

} /* namespace io */
