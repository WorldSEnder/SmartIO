/*
 * defaultSuppliers.hpp
 *
 *  Created on: 27.11.2014
 *      Author: Carbon
 */

#pragma once

#include <type_traits>
#include <string>

#include "smartio/Supplier.hpp"
#include "smartio/Context.hpp"
#include "smartio/detail.hpp"

namespace io
{
  namespace defaultsuppliers
  {

    template<typename I>
      class stdsupplier_t : public Supplier<I>
      {
	using typename Supplier<I>::item_t;
	typedef I val_t;

	static constexpr std::size_t item_size = sizeof(val_t);
	union convert_t
	{
	  char (*buffer)[item_size];
	  val_t *item;
	}mutable converter;
      public:
	stdsupplier_t (void);
//	Default constructible is a needed for I, for dosupply()
	static_assert(std::is_default_constructible<I>::value,
	    "std type not default constructible?!?!?");
	bool
	doapply (ReadContext& reader, val_t& type) const override;
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

    /**
//     * Reads a string, that is a sequence of chars with a trailing null-byte
//     */
//    class stringsupplier : public Supplier<std::string>
//    {
//      using typename Supplier<std::string>::item_t;
//
//      bool
//      doapply (ReadContext& reader, std::string& string) const override;
//    };
    /**
     * Reads a string in the "network-fashion". That is an unsigned
     * integer followed by that amount of characters forming the string.
     *
     * To read the integer context.construct<uint32_t>() is being used,
     * so you can change the default supplier to the correct endianess.
     */
    class netstringsupplier : public Supplier<std::string>
    {
      using typename Supplier<std::string>::item_t;

      bool
      doapply (ReadContext& reader, std::string& string) const override;
    };

  } /* namespace defaultsuppliers */
} /* namespace io */
