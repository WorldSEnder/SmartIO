/*****************************************************************
 * Name: Martin Molzer
 * Project: smartio-build
 * File: /smartio-build/source/main/include/smartio/endianess.hpp
 *****************************************************************/

#pragma once

#include <algorithm>

namespace util {

enum endianess {
	LITTLE, BIG
};

namespace {
using test_t = unsigned short;

static_assert(sizeof(test_t) == 2, "Use a type with width 2 to test endianess");
}

constexpr endianess inspectSystem() {
	// Some type with width 2
	// Until we find a reliable way to find a unsigned integral type with width 2
	// Or we can figure out endianess in a portable way
	// Using ntoh() and such is not portable at all...
	// Consider systems where sizeof(long long) == 1 == sizeof(char)
	// We don't have a way to figure out the endianess, because the largest
	// Integral type is long long. The conversion byte*->char* is done
	// in read() already
	//test_t test = 0x0001;
	//return *reinterpret_cast<char*>(&test) == 00 ? BIG : LITTLE;
	return BIG;
}

constexpr util::endianess NATIVE_ENDIAN = util::inspectSystem();

/**
 * Unpack from and pack into char-array-like structures with native
 * byteorder.
 */
struct native_byteorder {
	inline static void unpack(char* buffer, size_t size) {
		// Nothing at all
	}
	inline static void pack(char* buffer, size_t size) {
		// Nothing at all
	}
};
using native_endian = native_byteorder;
/**
 * Unpack from and pack into char-array-like structures with little endian
 * byteorder.
 */
struct little_endian {
	/**
	 * Transforms a little endian buffer into a native one.
	 */
	inline static void unpack(char* buffer, size_t size) {
		if (util::NATIVE_ENDIAN == LITTLE)
			return;
		std::reverse(buffer, buffer + size);
	}
	inline static void pack(char* buffer, size_t size) {
		if (util::NATIVE_ENDIAN == LITTLE)
			return;
		std::reverse(buffer, buffer + size);
	}
};
/**
 * Unpack from and pack into char-array-like structures with big endian
 * byteorder.
 */
struct big_endian {
	inline static void unpack(char* buffer, size_t size) {
		if (util::NATIVE_ENDIAN == BIG)
			return;
		std::reverse(buffer, buffer + size);
	}
	inline static void pack(char* buffer, size_t size) {
		if (util::NATIVE_ENDIAN == BIG)
			return;
		std::reverse(buffer, buffer + size);
	}
};

using network_endian = big_endian;

}

