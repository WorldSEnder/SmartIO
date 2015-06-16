/*
 * defaultSuppliers.cpp
 *
 * Created on: 27.11.2014
 *   Author: Carbon
 */
#include <istream>
#include <ostream>
#include <memory>
#include <cinttypes>

#include "smartio/defaultConverters.hpp"
#include "smartio/fileformatexception.h"
#include "smartio/utilitysupplier.hpp"
#include "smartio/endianess.hpp"

namespace io
{
  namespace defaultsuppliers
  {

    template<typename T, typename M>
      stdconverter_t<T, M>::stdconverter_t ()
      {
      }

    template<typename T, typename M>
      stdconverter_t<T, M>::~stdconverter_t ()
      {
      }

    template<typename I, typename M>
      bool
      stdconverter_t<I, M>::doapply (ReadContext& reader, val_t& val) const
      {
	using ::std::istream;

	istream& is = reader.getStream ();
	this->converter.item = std::addressof (val);
	is.read (this->converter.buffer, item_size);
	M::unpack (this->converter.buffer, item_size);
	if (is.fail ())
	  throw fileformatexception (
	      "Unexpected eof. Couldn't fully read std-type");
	this->converter.item = nullptr;
	return true;
      }

    template<typename I, typename M>
      void
      stdconverter_t<I, M>::doconsume (WriteContext& writer,
				       const I& val) const
      {
	using ::std::ostream;

	ostream& is = writer.getStream ();
	this->converter.outitem = std::addressof (val);
	std::unique_ptr<char[]> outbuffer = std::make_unique<char[]> (
	    item_size);
	std::copy_n (this->converter.outbuffer, item_size, outbuffer.get ());
	M::pack (outbuffer.get (), item_size);
	is.write (outbuffer.get (), item_size);
	// Just to be safer
	this->converter.outitem = nullptr;
      }

#pragma push_macro("DEFINECONVERTER")
#pragma push_macro("DEFINECONVERTERN")
#pragma push_macro("DEFINECONVERTERLE")
#pragma push_macro("DEFINECONVERTERBE")

#define DEFINECONVERTERN(type) template class stdconverter_t<type, util::native_endian>;\

#define DEFINECONVERTERLE(type) template class stdconverter_t<type, util::little_endian>;\

#define DEFINECONVERTERBE(type) template class stdconverter_t<type, util::big_endian>;\

#define DEFINECONVERTER(type)\
  DEFINECONVERTERN(type)\
  DEFINECONVERTERLE(type)\
  DEFINECONVERTERBE(type)

// integral types
    DEFINECONVERTER(bool)
    DEFINECONVERTER(char)
    DEFINECONVERTER(char16_t)
    DEFINECONVERTER(char32_t)
    DEFINECONVERTER(wchar_t)
// Floating point types
    DEFINECONVERTER(float)
    DEFINECONVERTER(double)
    DEFINECONVERTER(long double)
// Fixed size types
    DEFINECONVERTER(signed char)
    DEFINECONVERTER(unsigned char)
    DEFINECONVERTER(short int)
    DEFINECONVERTER(unsigned short int)
    DEFINECONVERTER(int)
    DEFINECONVERTER(unsigned int)
    DEFINECONVERTER(long int)
    DEFINECONVERTER(unsigned long int)
    DEFINECONVERTER(long long int)
    DEFINECONVERTER(unsigned long long int)

#pragma push_macro("DEFINECONVERTERBE")
#pragma push_macro("DEFINECONVERTERLE")
#pragma push_macro("DEFINECONVERTERN")
#pragma pop_macro("DEFINESUPPLIER")

    bool
    netstringsupplier::doapply (ReadContext& ctx, std::string& str) const
    {
      uint32_t size;
      ctx >> size;
      char *buffer = new char[size];
      ctx.getStream ().get (buffer, size);
      str = std::string
	{ buffer, size };
      return true;
    }

    void
    netstringsupplier::doconsume (WriteContext& writer, const std::string& string) const
    {
      uint32_t size = string.size();
      writer << size;
      writer.getStream().write(string.c_str(), size);
    }
  } /* namespace defaultsuppliers */
} /* namespace io */
