#pragma once

#include "smartio/Reader.hpp"

namespace io {

template<typename T>
ConstSupplierSharedPtr<T> Reader::getSupplier(supplier_key<T> key) const {
	return resolveSupplier(key);
}

template<typename T>
T Reader::construct(input& stream, supplier_key<T> key) const {
	return from(stream).construct(T { }, key);
}

}
