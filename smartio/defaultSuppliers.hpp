/*
 * defaultSuppliers.hpp
 *
 *  Created on: 27.11.2014
 *      Author: Carbon
 */

#pragma once
#ifndef DEFAULTSUPPLIERS_HPP_
#define DEFAULTSUPPLIERS_HPP_

#include <stdint.h>

#include "Supplier.hpp"
#include "Context.hpp"

namespace io
{
namespace defaultsuppliers
{
template<typename I>
class stdsupplier_t : public Supplier<I> {
private:
	using item_t = typename Supplier<I>::item_t;
	static const std::size_t item_size = sizeof(I);
	union convert_t{
		char buffer[item_size];
		item_t item;
	} mutable converter;
public:
	stdsupplier_t(void);
	item_t supply(Context& reader) const override;
};

#pragma push_macro("EXTERNSUPPLIER")
#define EXTERNSUPPLIER(type) extern template class stdsupplier_t< type >;
#pragma push_macro("USINGSUPPLIER")
#define USINGSUPPLIER(name, type) using name##supplier_t = stdsupplier_t< type >;

// STD types
USINGSUPPLIER(b, bool)
// Floating point types
USINGSUPPLIER(float, float)
USINGSUPPLIER(double, double)
USINGSUPPLIER(ldouble, long double)
// Fixed size types
USINGSUPPLIER(i8, int8_t)
USINGSUPPLIER(ui8, uint8_t)
USINGSUPPLIER(i16, int16_t)
USINGSUPPLIER(ui16, uint16_t)
USINGSUPPLIER(i32, int32_t)
USINGSUPPLIER(ui32, uint32_t)
USINGSUPPLIER(i64, int64_t)
USINGSUPPLIER(ui64, uint64_t)
// STD types
EXTERNSUPPLIER(bool)
// Floating point types
EXTERNSUPPLIER(float)
EXTERNSUPPLIER(double)
EXTERNSUPPLIER(long double)
// Fixed size types
EXTERNSUPPLIER(int8_t)
EXTERNSUPPLIER(uint8_t)
EXTERNSUPPLIER(int16_t)
EXTERNSUPPLIER(uint16_t)
EXTERNSUPPLIER(int32_t)
EXTERNSUPPLIER(uint32_t)
EXTERNSUPPLIER(int64_t)
EXTERNSUPPLIER(uint64_t)

#pragma pop_macro("USINGSUPPLIER")
#pragma pop_macro("EXTERNSUPPLIER")
} /* namespace defaultsuppliers */
} /* namespace io */

#endif /* DEFAULTSUPPLIERS_HPP_ */
