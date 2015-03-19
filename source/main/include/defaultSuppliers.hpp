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
class stdsupplier_t : public Supplier< I >
{
private:
    using typename Supplier< I >::item_t;
    static constexpr std::size_t item_size = sizeof(I);
    union convert_t
    {
        char (*buffer)[item_size];
        I *item;
    } mutable converter;
public:
    stdsupplier_t(void);
    item_t supply(Context& reader) const override;
};

#pragma push_macro("DECLSUPPLIER")
#define DECLSUPPLIER(name, type) using name##supplier_t = stdsupplier_t< type >;\
    extern template class stdsupplier_t< type >;

// integral types
DECLSUPPLIER(b, bool)
DECLSUPPLIER(c, char)
DECLSUPPLIER(c16, char16_t)
DECLSUPPLIER(c32, char32_t)
DECLSUPPLIER(wc, wchar_t)
// Floating point types
DECLSUPPLIER(float, float)
DECLSUPPLIER(double, double)
DECLSUPPLIER(ldouble, long double)
// Fixed size types
DECLSUPPLIER(sc, signed char)
DECLSUPPLIER(uc, unsigned char)
DECLSUPPLIER(h, short int)
DECLSUPPLIER(uh, unsigned short int)
DECLSUPPLIER(i, int)
DECLSUPPLIER(ui, unsigned int)
DECLSUPPLIER(l, long int)
DECLSUPPLIER(ul, unsigned long int)
DECLSUPPLIER(ll, long long int)
DECLSUPPLIER(ull, unsigned long long int)

#pragma pop_macro("DECLSUPPLIER")
} /* namespace defaultsuppliers */
} /* namespace io */
