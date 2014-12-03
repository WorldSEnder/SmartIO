/*
 * Environement.h
 *
 *  Created on: 27.11.2014
 *      Author: Carbon
 */
#pragma once

#include <memory>
#include <unordered_map>

#include "typetoken.hpp"
#include "Supplier.hpp"
#include "Reader.hpp"
#include "defaultSuppliers.hpp"
#include "traits.hpp"

namespace io
{
using std::unordered_map;
using std::shared_ptr;
using typetoken::token_t;
/**
 * This class serves as a Builder for Readers
 */
class Environment
{
	using supplier_map = unordered_map<token_t, shared_ptr<const SupplierBase>>;
private:
	supplier_map suppliers;
public:
	Environment();
	virtual ~Environment();
	/**
	 * Forwards to addSupplier.
	 *
	 * <T> the type of the supplier
	 * <Q> the type to register for
	 */
	template<typename T, typename Q=base_deduction<Supplier, T>>
	Environment& addDefaultConstructibeSupplier() {
		return addSupplier<T, Q>(shared_ptr<T>(new T));
	}
	/**
	 * Adds a supplier to the collection of suppliers used by all Readers
	 * built by this Environment. Registering a nullptr has no effect.<br>
	 * Returns this Environment to support the Builder-concept.
	 *
	 * <T> the type of the supplier
	 * <Q> the type to register for
	 */
	template<typename T, typename Q=base_deduction<Supplier, T>>
	Environment& addSupplier(shared_ptr<T> supplier) {
		static_assert(std::is_base_of<Supplier<Q>, T>::value, "T must extend Supplier<Q>");
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
	/**
	 * Builds a new Reader from all registered suppliers. The Reader will
	 * be capable of building objects of all types previously registered in
	 * this environment.<br>
	 * The returned Reader-object has a lifetime that is limited to this
	 * Environment's lifetime and should not be used after the Environment
	 * used to create it has been destroyed. This has to do with the nature
	 * of the Supplier object as only references to registered suppliers can
	 * be kept around. Default suppliers are destroyed when this Environment
	 * is destroyed.<br>
	 * Only when you are sure that you don't use the default suppliers you
	 * may use the returned Reader after this Environment has been destroyed
	 * and only if you are sure that all registered Suppliers are alive.
	 */
	Reader build(void);
};

} /* namespace io */
