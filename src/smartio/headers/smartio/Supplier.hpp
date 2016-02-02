/*
 * Supplier.hpp
 *
 *  Created on: 27.11.2014
 *      Author: Carbon
 */
#pragma once

#include <memory>

#include "smartio/traits.hpp"

namespace io {

class ReadContext;

template<typename T>
class supplier_base {
public:
	using item_t = supply_t<T>;

	virtual ~supplier_base() = default;

	void construct(ReadContext& ctx, T* const trgt) const;
private:
	/**
	 * Given a readcontext and a pointer to a non-const target T the supplier
	 * should construct the object in the preallocated space.
	 *
	 * Should generally not change the state of this supplier.
	 */
	virtual void
	DoConstruct(ReadContext& ctx, T* const trgt) const = 0;
};

template<typename T>
using SupplierSharedPtr = std::shared_ptr<supplier_base<T>>;
template<typename T>
using ConstSupplierSharedPtr = std::shared_ptr<const supplier_base<T>>;

} /* namespace io */

#include "smartio/Supplier.tpp"
