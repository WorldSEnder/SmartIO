/*
 * defaultSuppliers.cpp
 *
 * Created on: 27.11.2014
 *   Author: Carbon
 */
#include <istream>

#include "defaultSuppliers.hpp"
#include "fileformatexception.h"

namespace io
{
namespace defaultsuppliers
{
template<typename T>
stdsupplier_t< T >::stdsupplier_t()
{
}
;

template<typename T>
auto stdsupplier_t< T >::supply(
        Context& context) const -> typename stdsupplier_t<T>::item_t
{
    istream& is = context.getStream();
    this->converter.item = new T;
    is.read(*(this->converter.buffer), item_size);
    if (is.fail())
        throw fileformatexception(
                "Unexpected eof. Couldn't fully read std-type");
    return std::unique_ptr<T>(this->converter.item);
}

#pragma push_macro("DEFINESUPPLIER")
#define DEFINESUPPLIER(type) template class stdsupplier_t< type >;
// integral types
DEFINESUPPLIER(bool)
DEFINESUPPLIER(char)
DEFINESUPPLIER(char16_t)
DEFINESUPPLIER(char32_t)
DEFINESUPPLIER(wchar_t)
// Floating point types
DEFINESUPPLIER(float)
DEFINESUPPLIER(double)
DEFINESUPPLIER(long double)
// Fixed size types
DEFINESUPPLIER(signed char)
DEFINESUPPLIER(unsigned char)
DEFINESUPPLIER(short int)
DEFINESUPPLIER(unsigned short int)
DEFINESUPPLIER(int)
DEFINESUPPLIER(unsigned int)
DEFINESUPPLIER(long int)
DEFINESUPPLIER(unsigned long int)
DEFINESUPPLIER(long long int)
DEFINESUPPLIER(unsigned long long int)

#pragma pop_macro("DEFINESUPPLIER")
} /* namespace defaultsuppliers */
} /* namespace io */