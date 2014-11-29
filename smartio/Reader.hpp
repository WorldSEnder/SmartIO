/*
 * Reader.h
 *
 *  Created on: 27.11.2014
 *      Author: Carbon
 */

#pragma once
#ifndef READER_H_
#define READER_H_

#include <unordered_map>
#include <stdexcept>
#include <functional>
#include <istream>

#include "traits.hpp"
#include "Supplier.hpp"
#include "typetoken.hpp"
#include "Context.hpp"

namespace io
{
using std::unordered_map;
using std::istream;
using std::invalid_argument;
using std::reference_wrapper;

using typetoken::token_t;
/**
 * A reader actually reads elements from a given file/stream. When created
 * from an Environment all currently registered Suppliers are copied and
 * can therefore be used in the created Reader. The list of Suppliers is
 * final and can not be altered afterwards.<br>
 *
 */
class Reader
{
	using supplier_map = unordered_map<token_t, reference_wrapper<const SupplierBase>>;
private:
	Reader(void);
	const supplier_map suppliers;
public:
	/**
	 * Constructs a new reader from a map of suppliers
	 */
	Reader(supplier_map);
	virtual ~Reader();
	// TODO: add getSupplier(token_t) for runtime decisions
	/**
	 * Gets a reference to a registered supplier for the given type. If none is
	 * registered invalid_argument is thrown. The reference's lifetime is as long
	 * as the lifetime of the Reader object is was retrieved from.
	 *
	 * <T> the type that should be supplied
	 */
	template<typename T>
	const Supplier<T>& getSupplier() const {
		using item_t = typename supply_t<T>::type;
		using supplier_t = Supplier<item_t>;
		// Get the registered supplier
		token_t token = typetoken::getToken<item_t>();
		const auto& it = suppliers.find(token); // Iterator
		// Check if it's there
		if(it == suppliers.end())
			throw invalid_argument("No supplier registered for given type.");
		// Reinterpret to actual type and get item
		const supplier_t& supp = *reinterpret_cast<const supplier_t*>(&(it->second.get()));
		return supp;
	}
	Context createContext(istream& stream) const {
		return Context(this->suppliers, stream);
	}
	/**
	 * Reads a new object <T> from the file supplied.
	 * If you want to construct multiple objects of the same type rapidly
	 * you may want to use #getSupplier() for better performance. Then
	 * create Context-objects with #createContext(istream&) and call the
	 * suppliers supply method.<br>
	 * Normally the return type is of the requested type (assuming a valid
	 * request), the only exception being an array type with specified
	 * - constexpr - length. In this case a pointer to the created data
	 * is returned and can be used to manipulate the data further.
	 *
	 * <T> the type of object to be created
	 */
	template<typename T>
	typename supply_t<T>::type
	construct(istream& f) const {
		Context ctx = createContext(f);
		return ctx.construct<T>();
	}
};

} /* namespace io */

#endif /* READER_H_ */
