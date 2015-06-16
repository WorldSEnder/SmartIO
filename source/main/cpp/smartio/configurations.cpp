/*****************************************************************
 * Name: Martin Molzer
 * Project: smartio-build
 * File: /smartio-build/source/main/cpp/smartio/configurations.cpp
 *****************************************************************/

#include "smartio/configurations.hpp"
#include "smartio/defaultConverters.hpp"
#include "smartio/endianess.hpp"

namespace io
{

  namespace config
  {

    void
    network_reading_t::configure (Environment& env) const
    {
#pragma push_macro("ADDSUPPLIER")
#define ADDSUPPLIER(type)\
  env.emplaceSupplier<defaultsuppliers::stdsupplier_t<type, util::network_endian>> ()

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

#pragma pop_macro("ADDSUPPLIER")
    }

    void
    network_writing_t::configure(Environment& env) const
    {
#pragma push_macro("ADDCONSUMER")
#define ADDCONSUMER(type)\
  env.emplaceConsumer<defaultsuppliers::stdsupplier_t<type, util::network_endian>> ()

      // integral types
      ADDCONSUMER(bool);
      ADDCONSUMER(char);
      ADDCONSUMER(char16_t);
      ADDCONSUMER(char32_t);
      ADDCONSUMER(wchar_t);
      // Floating point types
      ADDCONSUMER(float);
      ADDCONSUMER(double);
      ADDCONSUMER(long double);
      // Fixed size types
      ADDCONSUMER(signed char);
      ADDCONSUMER(unsigned char);
      ADDCONSUMER(short int);
      ADDCONSUMER(unsigned short int);
      ADDCONSUMER(int);
      ADDCONSUMER(unsigned int);
      ADDCONSUMER(long int);
      ADDCONSUMER(unsigned long int);
      ADDCONSUMER(long long int);
      ADDCONSUMER(unsigned long long int);
      env.emplaceConsumer<defaultsuppliers::netstringconsumer> ();

#pragma pop_macro("ADDCONSUMER")
    }

    void
    networking_t::configure(Environment& env) const
    {
      network_reading_t::configure(env);
      network_writing_t::configure(env);
    }


    void
    file_reading_t::configure (Environment& env) const
    {
#pragma push_macro("ADDSUPPLIER")
#define ADDSUPPLIER(type)\
  env.emplaceSupplier<defaultsuppliers::stdsupplier_t<type, util::native_endian>> ()

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

#pragma pop_macro("ADDSUPPLIER")
    }

    void
    file_writing_t::configure(Environment& env) const
    {
#pragma push_macro("ADDCONSUMER")
#define ADDCONSUMER(type)\
  env.emplaceConsumer<defaultsuppliers::stdsupplier_t<type, util::native_endian>> ()

      // integral types
      ADDCONSUMER(bool);
      ADDCONSUMER(char);
      ADDCONSUMER(char16_t);
      ADDCONSUMER(char32_t);
      ADDCONSUMER(wchar_t);
      // Floating point types
      ADDCONSUMER(float);
      ADDCONSUMER(double);
      ADDCONSUMER(long double);
      // Fixed size types
      ADDCONSUMER(signed char);
      ADDCONSUMER(unsigned char);
      ADDCONSUMER(short int);
      ADDCONSUMER(unsigned short int);
      ADDCONSUMER(int);
      ADDCONSUMER(unsigned int);
      ADDCONSUMER(long int);
      ADDCONSUMER(unsigned long int);
      ADDCONSUMER(long long int);
      ADDCONSUMER(unsigned long long int);

#pragma pop_macro("ADDCONSUMER")
    }

    void
    fileworking_t::configure(Environment& env) const
    {
      file_reading_t::configure(env);
      file_writing_t::configure(env);
    }

  }  // namespace config

}  // namespace io
