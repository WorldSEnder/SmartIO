/*
 * Context.cpp
 *
 *  Created on: 29.11.2014
 *      Author: Carbon
 */

#include <smartio/Context.hpp>

namespace io
{

Context::Context(const supplier_map reader, istream& stream)
	: reference(std::move(reader)), stream(stream) {}

Context::~Context() {}

istream&
Context::getStream() {
	return stream;
}

void
Context::setValue(key_t key, value_t val) {
	contextVars[key] = val;
}

Context::value_t
Context::getValue(key_t key, value_t defaultVal) {
	auto&& it = contextVars.find(key);
	if(it == contextVars.end())
		return defaultVal;
	return it->second;
}

bool
Context::hasValue(key_t key) {
	return contextVars.find(key) != contextVars.end();
}

} /* namespace io */
