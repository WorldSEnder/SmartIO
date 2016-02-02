#pragma once

#include <stdexcept>

#include "smartio/BoundSupplier.hpp"

namespace io {

template<typename T>
BoundSupplier<T>::BoundSupplier(ConstSupplierSharedPtr<T> supplier,
		ReadContext& context) :
		reference(supplier), ctx(context) {
	if (reference == nullptr) {
		throw std::invalid_argument(
				"FIXME: illegal nullptr reference to a supplier");
	}
}

template<typename T>
BoundSupplier<T>::~BoundSupplier() {
}

template<typename T>
void BoundSupplier<T>::construct(T const* trgt) {
	return reference->apply(trgt);
}

}
