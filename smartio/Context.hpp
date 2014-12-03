/*
 * Context.hpp
 *
 *  Created on: 29.11.2014
 *      Author: Carbon
 */

#pragma once

#include <unordered_map>
#include <stdexcept>
#include <memory>
#include <istream>

#include "typetoken.hpp"
#include "traits.hpp"
#include "Supplier.hpp"

namespace io
{
using std::unordered_map;
using std::istream;
using std::invalid_argument;
using std::shared_ptr;

using typetoken::token_t;

// Forward declare for friend
class Reader;

/**
 * Works as a temporary context for Suppliers and thus is dependent
 * on a previously created Reader to create objects from. This reader
 * is kept by reference so the Context's lifetime should be at most as
 * long as the Reader's.<br>
 * The difference to Reader is that also the input stream is already set
 * and also kept as a reference - introducing another lifetime dependence.
 */
class Context
{
	// Suppliers
	using supplier_map = unordered_map<token_t, shared_ptr<const SupplierBase>>;
	// Context variables
	using key_t = unsigned int;
	using value_t = signed int;
	using var_map = unordered_map<key_t, value_t>;
private:
	const supplier_map reference;
	istream& stream;
	var_map contextVars;
	Context() = delete;
	/**
	 * Constructs a Context from a reference to a (non-temporary) map of
	 * suppliers and a given i-stream to read objects from. We can never be
	 * sure that supplier_map contains actual suppliers when handed over by
	 * user so we have to friend Reader for this
	 */
	Context(const supplier_map, istream&);
	// Helper function to find supplier in map
	template<typename T>
	const Supplier<T>& retrieveSupplier() const {
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
public:
	virtual ~Context();
	/**
	 * Gets a reference to a registered supplier for the given type. If none is
	 * registered invalid_argument is thrown. The reference's lifetime is as long
	 * as the lifetime of the Reader object is was retrieved from.
	 *
	 * <T> the type that should be supplied
	 */
	template<typename T>
	const BoundSupplier<T> getSupplier() const {
		using item_t = typename supply_t<T>::type;
		return BoundSupplier<item_t>(this->retrieveSupplier<T>(), stream);
	}
	/**
	 * Constructs a new object from this context using the stream that was
	 * supplied in the context's constructor. Altering the stream
	 * effectively changes the context thus this method can't be called from
	 * a constant Context object.<br>
	 * Normally the return type is the requested type (assuming a valid
	 * request), the only exception being an array type with specified
	 * - constexpr - length. In this case a pointer to the created data
	 * is returned and can be used to manipulate the data further.
	 */
	template<typename T>
	typename supply_t<T>::type
	construct() {
		using item_t = typename supply_t<T>::type;
		using supplier_t = Supplier<item_t>;
		const supplier_t& supp = this->retrieveSupplier<item_t>();
		return supp.supply(*this);
	}
	/**
	 * Returns the i-stream this Context is bound to. Altering the stream
	 * effectively changes the context thus this method can't be called from
	 * a constant Context object.
	 */
	istream& getStream();
	/**
	 * Sets the context variable for key.
	 */
	void setValue(key_t, value_t);
	/**
	 * Retrieves the value previously set for the key or default if it hasn't
	 * been set.
	 */
	value_t getValue(key_t, value_t);
	/**
	 * Checks if a value for key has been set
	 */
	bool hasValue(key_t);

	friend io::Reader;
};

} /* namespace io */
