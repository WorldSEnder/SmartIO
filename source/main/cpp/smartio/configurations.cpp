/*****************************************************************
 * Name: Martin Molzer
 * Project: smartio-build
 * File: /smartio-build/source/main/cpp/smartio/configurations.cpp
 *****************************************************************/

#include "smartio/configurations.hpp"
#include "smartio/defaultSuppliers.hpp"

namespace io
{

  namespace config
  {

#pragma push_macro("ADDSUPPLIER")
#define ADDSUPPLIER(type) env.emplaceSupplier<defaultsuppliers::stdsupplier_t<type>> ()

    void
    network_reading_t::configure (Environment& env) const
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
      env.emplaceSupplier<defaultsuppliers::netstringsupplier> ();
    }

#pragma pop_macro("ADDSUPPLIER")


  }  // namespace config

}  // namespace io
