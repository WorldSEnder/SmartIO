/*
 * defaultSuppliers.hpp
 *
 *  Created on: 27.11.2014
 *      Author: Carbon
 */

#pragma once

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

// integral types
USINGSUPPLIER(b, bool)
USINGSUPPLIER(c, char)
USINGSUPPLIER(c16, char16_t)
USINGSUPPLIER(c32, char32_t)
USINGSUPPLIER(wc, wchar_t)
// Floating point types
USINGSUPPLIER(float, float)
USINGSUPPLIER(double, double)
USINGSUPPLIER(ldouble, long double)
// Fixed size types
USINGSUPPLIER(sc, signed char)
USINGSUPPLIER(uc, unsigned char)
USINGSUPPLIER(h, short int)
USINGSUPPLIER(uh, unsigned short int)
USINGSUPPLIER(i, int)
USINGSUPPLIER(ui, unsigned int)
USINGSUPPLIER(l, long int)
USINGSUPPLIER(ul, unsigned long int)
USINGSUPPLIER(ll, long long int)
USINGSUPPLIER(ull, unsigned long long int)
// integral types
EXTERNSUPPLIER(bool)
EXTERNSUPPLIER(char)
EXTERNSUPPLIER(char16_t)
EXTERNSUPPLIER(char32_t)
EXTERNSUPPLIER(wchar_t)
// Floating point types
EXTERNSUPPLIER(float)
EXTERNSUPPLIER(double)
EXTERNSUPPLIER(long double)
// Fixed size types
EXTERNSUPPLIER(signed char)
EXTERNSUPPLIER(unsigned char)
EXTERNSUPPLIER(short int)
EXTERNSUPPLIER(unsigned short int)
EXTERNSUPPLIER(int)
EXTERNSUPPLIER(unsigned int)
EXTERNSUPPLIER(long int)
EXTERNSUPPLIER(unsigned long int)
EXTERNSUPPLIER(long long int)
EXTERNSUPPLIER(unsigned long long int)

#pragma pop_macro("USINGSUPPLIER")
#pragma pop_macro("EXTERNSUPPLIER")
} /* namespace defaultsuppliers */
} /* namespace io */
