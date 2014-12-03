#pragma once

#include "Environment.hpp"

#include <utility>

#include "traits.hpp"
#include "typetoken.hpp"
#include "Supplier.hpp"

namespace io {
using typetoken::token_t;

template<typename T, typename Q>
Environment& Environment::addDefaultConstructibleSupplier() {
	return addSupplier<T, Q>(shared_ptr<T>(new T));
}

template<typename T, typename Q>
Environment& Environment::addSupplier(shared_ptr<T> supplier) {
	using item_t = typename supply_t<Q>::type;
	if(supplier == nullptr)
		return *this;
	token_t token = typetoken::getToken<item_t>();
	// We use this instead of map[key] = value because Supplier is abstract
	suppliers.insert(
			std::make_pair(token,
					std::static_pointer_cast<const SupplierBase, T>(supplier)));
	return *this;
}

}
