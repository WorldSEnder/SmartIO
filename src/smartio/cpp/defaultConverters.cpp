/*
 * defaultSuppliers.cpp
 *
 * Created on: 27.11.2014
 *   Author: Carbon
 */
#include <memory>
#include <cinttypes>

#include "smartio/defaultConverters.hpp"
#include "smartio/fileformatexception.h"
#include "smartio/utilitysupplier.hpp"
#include "smartio/endianess.hpp"

namespace io {
namespace defaultsuppliers {

template<typename T, typename M>
stdconverter_t<T, M>::stdconverter_t() {
}

template<typename T, typename M>
stdconverter_t<T, M>::~stdconverter_t() {
}

template<typename I, typename M>
void stdconverter_t<I, M>::DoConstruct(ReadContext& reader,
		item_t* const val) const {

	auto& is = reader.getStream();
	char* asChar = reinterpret_cast<char*>(val);
	if (!is.read(asChar, item_size))
		throw fileformatexception(
				"Unexpected eof. Couldn't fully read std-type");
	M::unpack(asChar, item_size);
}

template<typename I, typename M>
void stdconverter_t<I, M>::DoConsume(WriteContext& writer,
		const item_t& val) const {
	using ::std::ostream;

	char outbuffer[item_size];
	auto& os = writer.getStream();
	const char* asChar = reinterpret_cast<const char*>(std::addressof(val));
	std::copy_n(asChar, item_size, outbuffer);
	M::pack(outbuffer, item_size);
	os.write(outbuffer, item_size);
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

void netstringsupplier::DoConstruct(ReadContext& reader,
		std::string* const str) const {
	uint32_t size;
	reader >> size;
	char *buffer = new char[size];
	reader.getStream().get(buffer, size);
	::new (str) std::string { buffer, size };
}

void netstringsupplier::DoConsume(WriteContext& writer,
		const std::string& string) const {
	uint32_t size = string.size();
	writer << size;
	writer.getStream().write(string.c_str(), size);
}
} /* namespace defaultsuppliers */
} /* namespace io */
