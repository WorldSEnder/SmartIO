#pragma once

#include "Context.hpp"

#include <stdexcept>

#include "traits.hpp"

namespace io
{
using std::invalid_argument;

using typetoken::token_t;

template<typename T>
const Supplier<T>& Context::retrieveSupplier() const {
	using item_t = typename supply_t<T>::type;
	using supplier_t = Supplier<item_t>;
	// Get the registered supplier
	token_t token = typetoken::getToken<item_t>();
	const auto& it = reference.find(token); // Iterator
	// Check if it's there
	if(it == reference.end())
		throw invalid_argument("No supplier registered for given type.");
	// Reinterpret to actual type and get item
	const supplier_t& supp = *std::static_pointer_cast<const Supplier<T>, const SupplierBase>(it->second);
	return supp;
}

template<typename T>
const BoundSupplier<T> Context::getSupplier() const {
	using item_t = typename supply_t<T>::type;
	return BoundSupplier<item_t>(this->retrieveSupplier<T>(), stream);
}

template<typename T>
T Context::construct() {
	using item_t = typename supply_t<T>::type;
	using supplier_t = Supplier<item_t>;
	const supplier_t& supp = this->retrieveSupplier<item_t>();
	return supp.supply(*this);
}

}
