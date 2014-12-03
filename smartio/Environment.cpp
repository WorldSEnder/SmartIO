/*
 * Environement.cpp
 *
 *  Created on: 27.11.2014
 *      Author: Carbon
 */

#include "Environment.hpp"

namespace io
{
#pragma push_macro("ADDSUPPLIER")
#define ADDSUPPLIER(type) this->addDefaultConstructibeSupplier<defaultsuppliers::type>()

Environment::Environment()
{
	ADDSUPPLIER(bsupplier_t);
//	ADDSUPPLIER(csupplier_t);
//	ADDSUPPLIER(ucsupplier_t);
//	ADDSUPPLIER(ssupplier_t);
//	ADDSUPPLIER(ussupplier_t);
//	ADDSUPPLIER(isupplier_t);
//	ADDSUPPLIER(uisupplier_t);
//	ADDSUPPLIER(llsupplier_t);
//	ADDSUPPLIER(ullsupplier_t);
	// Floating point types
	ADDSUPPLIER(floatsupplier_t);
	ADDSUPPLIER(doublesupplier_t);
	ADDSUPPLIER(ldoublesupplier_t);
	// Fixed size types
	ADDSUPPLIER(i8supplier_t);
	ADDSUPPLIER(ui8supplier_t);
	ADDSUPPLIER(i16supplier_t);
	ADDSUPPLIER(ui16supplier_t);
	ADDSUPPLIER(i32supplier_t);
	ADDSUPPLIER(ui32supplier_t);
	ADDSUPPLIER(i64supplier_t);
	ADDSUPPLIER(ui64supplier_t);
}

Environment::~Environment() {
}

Reader Environment::build()
{
	return Reader(this->suppliers);
}
#pragma pop_macro("ADDSUPPLIER")

} /* namespace io */
