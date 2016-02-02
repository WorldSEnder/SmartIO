/*****************************************************************
 * Name: Martin Molzer
 * Project: smartio-build
 * File: /smartio-build/source/main/include/smartio/Supplier.tpp
 *****************************************************************/

#pragma once

#include "smartio/Supplier.hpp"
#include <type_traits>

namespace io {

template<typename T>
void supplier_base<T>::construct(ReadContext& ctx, T* const trgt) const {
	return this->DoConstruct(ctx, trgt);
}

}  // namespace io

