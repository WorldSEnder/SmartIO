/*
 * Environement.cpp
 *
 *  Created on: 27.11.2014
 *      Author: Carbon
 */

#include "Environment.hpp"

namespace io
{
#pragma push_macro("INITSUPPLIER")
#define INITSUPPLIER(type) refto##type(new defaultsuppliers::type())
#pragma push_macro("ADDSUPPLIER")
#define ADDSUPPLIER(type) this->addSupplier(*refto##type)
#pragma push_macro("DELSUPPLIER")
#define DELSUPPLIER(type) delete refto##type

Environment::Environment() :
	INITSUPPLIER(bsupplier_t),
//	INITSUPPLIER(csupplier_t),
//	INITSUPPLIER(ucsupplier_t),
//	INITSUPPLIER(ssupplier_t),
//	INITSUPPLIER(ussupplier_t),
//	INITSUPPLIER(isupplier_t),
//	INITSUPPLIER(uisupplier_t),
//	INITSUPPLIER(llsupplier_t),
//	INITSUPPLIER(ullsupplier_t),
	// Floating point types
	INITSUPPLIER(floatsupplier_t),
	INITSUPPLIER(doublesupplier_t),
	INITSUPPLIER(ldoublesupplier_t),
	// Fixed size types
	INITSUPPLIER(i8supplier_t),
	INITSUPPLIER(ui8supplier_t),
	INITSUPPLIER(i16supplier_t),
	INITSUPPLIER(ui16supplier_t),
	INITSUPPLIER(i32supplier_t),
	INITSUPPLIER(ui32supplier_t),
	INITSUPPLIER(i64supplier_t),
	INITSUPPLIER(ui64supplier_t)
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
	DELSUPPLIER(bsupplier_t);
//	DELSUPPLIER(csupplier_t);
//	DELSUPPLIER(ucsupplier_t);
//	DELSUPPLIER(ssupplier_t);
//	DELSUPPLIER(ussupplier_t);
//	DELSUPPLIER(isupplier_t);
//	DELSUPPLIER(uisupplier_t);
//	DELSUPPLIER(llsupplier_t);
//	DELSUPPLIER(ullsupplier_t);
	// Floating point types
	DELSUPPLIER(floatsupplier_t);
	DELSUPPLIER(doublesupplier_t);
	DELSUPPLIER(ldoublesupplier_t);
	// Fixed size types
	DELSUPPLIER(i8supplier_t);
	DELSUPPLIER(ui8supplier_t);
	DELSUPPLIER(i16supplier_t);
	DELSUPPLIER(ui16supplier_t);
	DELSUPPLIER(i32supplier_t);
	DELSUPPLIER(ui32supplier_t);
	DELSUPPLIER(i64supplier_t);
	DELSUPPLIER(ui64supplier_t);
}

Reader Environment::build()
{
	return Reader(this->suppliers);
}
#pragma pop_macro("INITSUPPLIER")
#pragma pop_macro("ADDSUPPLIER")
#pragma pop_macro("DELSUPPLIER")

} /* namespace io */
