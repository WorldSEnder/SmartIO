/*
 * Environement.h
 *
 *  Created on: 27.11.2014
 *      Author: Carbon
 */

#pragma once
#ifndef ENVIRONEMENT_H_
#define ENVIRONEMENT_H_

#include <functional>
#include <unordered_map>

#include "typetoken.hpp"
#include "Supplier.hpp"
#include "Reader.hpp"
#include "defaultSuppliers.hpp"

namespace io
{
using std::unordered_map;
using std::reference_wrapper;
using typetoken::token_t;

#pragma push_macro("DECLSUPPLIER")
#define DECLSUPPLIER(type) defaultsuppliers::type *refto##type
/**
 * This class serves as a Builder for Readers
 */
class Environment
{
	// TODO: change this to shared_pointer?!
	using supplier_map = unordered_map<token_t, reference_wrapper<const SupplierBase>>;
private:
	DECLSUPPLIER(bsupplier_t);
	//	DECLSUPPLIER(csupplier_t);
	//	DECLSUPPLIER(ucsupplier_t);
	//	DECLSUPPLIER(ssupplier_t);
	//	DECLSUPPLIER(ussupplier_t);
	//	DECLSUPPLIER(isupplier_t);
	//	DECLSUPPLIER(uisupplier_t);
	//	DECLSUPPLIER(llsupplier_t);
	//	DECLSUPPLIER(ullsupplier_t);
	// Floating point types
	DECLSUPPLIER(floatsupplier_t);
	DECLSUPPLIER(doublesupplier_t);
	DECLSUPPLIER(ldoublesupplier_t);
	// Fixed size types
	DECLSUPPLIER(i8supplier_t);
	DECLSUPPLIER(ui8supplier_t);
	DECLSUPPLIER(i16supplier_t);
	DECLSUPPLIER(ui16supplier_t);
	DECLSUPPLIER(i32supplier_t);
	DECLSUPPLIER(ui32supplier_t);
	DECLSUPPLIER(i64supplier_t);
	DECLSUPPLIER(ui64supplier_t);
	supplier_map suppliers;
public:
	Environment();
	virtual ~Environment();
	/**
	 * Adds a supplier to the collection of suppliers used by all Readers
	 * built by this Environment. The lifetime of the given supplier should
	 * be at least the lifetime of the Environment it has been registered
	 * in.<br>
	 * Returns this Environment to support the Builder-concept
	 */
	template<typename T>
	Environment& addSupplier(const Supplier<T>& supplier) {
		using item_t = typename supply_t<T>::type;
		token_t token = typetoken::getToken<item_t>();
		// We use this instead of map[key] = value because Supplier is abstract
		suppliers.insert(
				std::make_pair(token,
						std::cref(supplier)));
		return *this;
	}
	template<typename T>
	void addSupplier(Supplier<T>&&) = delete;
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
#pragma pop_macro("DECLSUPPLIER")

} /* namespace io */

#endif /* ENVIRONEMENT_H_ */
