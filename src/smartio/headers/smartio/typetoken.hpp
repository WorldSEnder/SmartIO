/*
 * typetoken.hpp
 *
 *  Created on: 27.11.2014
 *      Author: Carbon
 */
#pragma once

#include <atomic>
#include <typeinfo>
#include <typeindex>
#include <cstddef>

namespace typetoken {

using token_t = std::type_index;
/**
 * Gets a typetoken for the given type. The returned token can be
 * used in maps and unordered collections as a key and uniquely
 * identifies the type requested.
 */
template<typename T>
inline token_t getToken(void) {
	return std::type_index(typeid(T));
}

}
// namespace typetoken
