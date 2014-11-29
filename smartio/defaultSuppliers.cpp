/*
 * defaultSuppliers.cpp
 *
 * Created on: 27.11.2014
 *   Author: Carbon
 */

#include "defaultSuppliers.hpp"
#include "fileformatexception.h"

namespace io
{
namespace defaultsuppliers
{
template<typename T>
stdsupplier_t<T>::stdsupplier_t() {};

template<typename T>
auto stdsupplier_t<T>::supply(Context& context) const
		-> typename stdsupplier_t<T>::item_t {
	istream& is = context.getStream();
	is.read(this->converter.buffer, item_size);
	if(!is)
		// TODO: more information pls, also this is too early
		throw fileformatexception("Couldn't read stdtype");
	return this->converter.item;
}

#pragma push_macro("DEFINESUPPLIER")
#define DEFINESUPPLIER(type) template class stdsupplier_t< type >;
// STD types
DEFINESUPPLIER(bool)
//DEFINESUPPLIER(char)
//DEFINESUPPLIER(unsigned char)
//DEFINESUPPLIER(short)
//DEFINESUPPLIER(unsigned short)
//DEFINESUPPLIER(int)
//DEFINESUPPLIER(unsigned int)
//DEFINESUPPLIER(long long int)
//DEFINESUPPLIER(unsigned long long int)
// Floating point types
DEFINESUPPLIER(float)
DEFINESUPPLIER(double)
DEFINESUPPLIER(long double)
// Fixed size types
DEFINESUPPLIER(int8_t)
DEFINESUPPLIER(uint8_t)
DEFINESUPPLIER(int16_t)
DEFINESUPPLIER(uint16_t)
DEFINESUPPLIER(int32_t)
DEFINESUPPLIER(uint32_t)
DEFINESUPPLIER(int64_t)
DEFINESUPPLIER(uint64_t)

#pragma pop_macro("DEFINESUPPLIER")
} /* namespace defaultsuppliers */
} /* namespace io */
