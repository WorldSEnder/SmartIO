#pragma once

#include "Reader.hpp"

#include <stdexcept>

#include "traits.hpp"

namespace io {
using std::invalid_argument;

template<typename T>
const Supplier<T>& Reader::getSupplier() const {
	// TODO: add an option to select different reading modes, BINARY, TEXT, etc.
	using item_t = typename supply_t<T>::type;
	using supplier_t = Supplier<item_t>;
	// Get the registered supplier
	token_t token = typetoken::getToken<item_t>();
	const auto& it = suppliers.find(token); // Iterator
	// Check if it's there
	if(it == suppliers.end())
		throw invalid_argument("No supplier registered for given type.");
	// Reinterpret to actual type and get item
	const supplier_t& supp = *std::static_pointer_cast<const Supplier<T>, const SupplierBase>(it->second);
	return supp;
}

//Context Reader::createContext(istream& stream) const {
//	return Context(this->suppliers, stream);
//}

template<typename T>
T Reader::construct(istream& f) const {
	// Check the type
	__attribute__((unused))
	typedef typename supply_t<T>::type item_t;
	Context ctx = createContext(f);
	return ctx.construct<T>();
}

}
