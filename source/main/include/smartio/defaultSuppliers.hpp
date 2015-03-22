/*
 * defaultSuppliers.hpp
 *
 *  Created on: 27.11.2014
 *      Author: Carbon
 */

#pragma once

#include "smartio/Supplier.hpp"
#include "smartio/Context.hpp"
#include "smartio/detail.hpp"

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
    static const ::io::supplier_key<I> KEY;

    stdsupplier_t(void);
    item_t supply(ReadContext& reader) const override;
};

#pragma push_macro("DECLSUPPLIER")
#define DECLKEY(name, type) using name##supplier_t = stdsupplier_t< type >;\
    extern template class stdsupplier_t< type >;

// Basic types
DECLKEY(b, bool)
DECLKEY(c, char)
DECLKEY(c16, char16_t)
DECLKEY(c32, char32_t)
DECLKEY(wc, wchar_t)
// Floating point types
DECLKEY(float, float)
DECLKEY(double, double)
DECLKEY(ldouble, long double)
// Integral types
DECLKEY(sc, signed char)
DECLKEY(uc, unsigned char)
DECLKEY(h, short int)
DECLKEY(uh, unsigned short int)
DECLKEY(i, int)
DECLKEY(ui, unsigned int)
DECLKEY(l, long int)
DECLKEY(ul, unsigned long int)
DECLKEY(ll, long long int)
DECLKEY(ull, unsigned long long int)

#pragma pop_macro("DECLSUPPLIER")
} /* namespace defaultsuppliers */
} /* namespace io */
