/*
 * BoundSupplier.hpp
 *
 *  Created on: 01.02.2016
 *      Author: Carbon
 */
#pragma once

#include "smartio/Supplier.hpp"

namespace io {

template<typename T>
class BoundSupplier {
public:
	using typename supplier_base<T>::item_t;
private:
	ConstSupplierSharedPtr<T> reference;
	ReadContext& ctx;
	BoundSupplier() = delete;
public:
	/**
	 * A bound supplier has a context already applied aswell as a supplier.
	 * This enables it to return specific items without a context. The life-time
	 * of a BoundSupplier can not exceed the lifetime of the context it is bound
	 * to. // FIXME: maybe only allow shared_ptr<Context>'s and enable shared_from_this
	 */
	BoundSupplier(ConstSupplierSharedPtr<T> supplier, ReadContext& context);

	virtual ~BoundSupplier();
	/**
	 * Constructs an element in preallocated space.
	 */
	void construct(T const* trgt);
};

}

#include "smartio/BoundSupplier.tpp"
