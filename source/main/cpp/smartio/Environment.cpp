/*
 * Environement.cpp
 *
 *  Created on: 27.11.2014
 *      Author: Carbon
 */

#include "smartio/Environment.hpp"
#include "smartio/defaultSuppliers.hpp"
#include "smartio/detail.hpp"

namespace io
{
#pragma push_macro("ADDSUPPLIER")
#define ADDSUPPLIER(type) this->emplaceSupplier< defaultsuppliers::stdsupplier_t< type >>()

Environment::Environment()
{
    // integral types
    ADDSUPPLIER(bool);
    ADDSUPPLIER(char);
    ADDSUPPLIER(char16_t);
    ADDSUPPLIER(char32_t);
    ADDSUPPLIER(wchar_t);
    // Floating point types
    ADDSUPPLIER(float);
    ADDSUPPLIER(double);
    ADDSUPPLIER(long double);
    // Fixed size types
    ADDSUPPLIER(signed char);
    ADDSUPPLIER(unsigned char);
    ADDSUPPLIER(short int);
    ADDSUPPLIER(unsigned short int);
    ADDSUPPLIER(int);
    ADDSUPPLIER(unsigned int);
    ADDSUPPLIER(long int);
    ADDSUPPLIER(unsigned long int);
    ADDSUPPLIER(long long int);
    ADDSUPPLIER(unsigned long long int);
}

Environment::~Environment()
{
}

Reader Environment::build()
{
    return {this->suppliers};
}
#pragma pop_macro("ADDSUPPLIER")

} /* namespace io */
