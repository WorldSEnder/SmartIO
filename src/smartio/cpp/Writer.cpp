/*****************************************************************
 * Name: Martin Molzer
 * Project: smartio-build
 * File: /smartio-build/source/main/cpp/smartio/Writer.cpp
 *****************************************************************/

#include <utility>

#include "smartio/Writer.hpp"

namespace io {

Writer::Writer(consumer_registry registry) :
		consumer_registry(std::move(registry)) {

}

Writer::~Writer() {
}

WriteContext Writer::into(output& stream) const {
	const consumer_registry& consumers = *this;
	return {consumers, stream};
}

}  // namespace io
