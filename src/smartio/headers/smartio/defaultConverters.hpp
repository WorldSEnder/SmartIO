/*
 * defaultSuppliers.hpp
 *
 *  Created on: 27.11.2014
 *      Author: Carbon
 */

#pragma once

#include <type_traits>
#include <string>

#include "smartio/endianess.hpp"
#include "smartio/Supplier.hpp"
#include "smartio/Consumer.hpp"
#include "smartio/Context.hpp"
#include "smartio/ReadContext.hpp"
#include "smartio/WriteContext.hpp"

namespace io {
namespace defaultsuppliers {

template<typename I, typename Mem>
class stdconverter_t: public supplier_base<I>, public consumer_base<I> {
	using item_t = typename supplier_base<I>::item_t;

	static constexpr std::size_t item_size = sizeof(item_t);
public:
	stdconverter_t();
	~stdconverter_t();
private:
//	Default constructible is a needed for I, for dosupply()
	static_assert(std::is_default_constructible<I>::value,
			"std type not default constructible?!?!?");
	void DoConstruct(ReadContext& reader, item_t* const value) const override;
	void DoConsume(WriteContext& reader, const item_t& value) const override;
};

template<typename I, typename M>
using stdsupplier_t = stdconverter_t<I, M>;

template<typename I, typename M>
using stdconsumer_t = stdconverter_t<I, M>;

#pragma push_macro("DECLCONVERTER")
#pragma push_macro("DECLCONVERTERN")
#pragma push_macro("DECLCONVERTERLE")
#pragma push_macro("DECLCONVERTERBE")

#define DECLCONVERTERN(name, type)\
  using name##supplier_t = stdsupplier_t<type, util::native_endian>;\
  using name##consumer_t = stdconsumer_t<type, util::native_endian>;\
  extern template class stdconverter_t<type, util::native_endian>;\

#define DECLCONVERTERLE(name, type)\
  using name##supplierLE_t = stdsupplier_t<type, util::little_endian>;\
  using name##consumerLE_t = stdconsumer_t<type, util::little_endian>;\
  extern template class stdconverter_t<type, util::little_endian>;\

#define DECLCONVERTERBE(name, type)\
  using name##supplierBE_t = stdsupplier_t<type, util::big_endian>;\
  using name##consumerBE_t = stdconsumer_t<type, util::big_endian>;\
  extern template class stdconverter_t<type, util::big_endian>;\

#define DECLCONVERTER(name, type)\
    DECLCONVERTERN(name, type)\
    DECLCONVERTERLE(name, type)\
    DECLCONVERTERBE(name, type)

// Basic types
DECLCONVERTER(b, bool)
DECLCONVERTER(c, char)
DECLCONVERTER(c16, char16_t)
DECLCONVERTER(c32, char32_t)
DECLCONVERTER(wc, wchar_t)
// Floating point types
DECLCONVERTER(f, float)
DECLCONVERTER(d, double)
DECLCONVERTER(ld, long double)
// Integral types
DECLCONVERTER(sc, signed char)
DECLCONVERTER(uc, unsigned char)
DECLCONVERTER(h, short int)
DECLCONVERTER(uh, unsigned short int)
DECLCONVERTER(i, int)
DECLCONVERTER(ui, unsigned int)
DECLCONVERTER(l, long int)
DECLCONVERTER(ul, unsigned long int)
DECLCONVERTER(ll, long long int)
DECLCONVERTER(ull, unsigned long long int)

#pragma pop_macro("DECLCONVERTERBE")
#pragma pop_macro("DECLCONVERTERLE")
#pragma pop_macro("DECLCONVERTERN")
#pragma pop_macro("DECLCONVERTER")

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
class netstringconverter: public supplier_base<std::string>,
		public consumer_base<std::string> {
	using typename supplier_base<std::string>::item_t;

	void DoConstruct(ReadContext& reader, std::string* const string) const
			override;
	void DoConsume(WriteContext& writer, const std::string& string) const
			override;
};

using netstringsupplier = netstringconverter;
using netstringconsumer = netstringconverter;

} /* namespace defaultsuppliers */
} /* namespace io */
