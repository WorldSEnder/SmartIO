/*
 * ReadContext.cpp
 *
 *  Created on: 01.02.2016
 *      Author: WorldSEnder
 */

#include <utility>

#include "smartio/ReadContext.hpp"

namespace io {

ReadContext::ReadContext(supplier_registry reader, input& stream) :
		supplier_registry(std::move(reader)), stream(stream) {
}

ReadContext::~ReadContext() {
}

ReadContext::input&
ReadContext::getStream() {
	return stream;
}

const ReadContext::input&
ReadContext::getStream() const {
	return stream;
}

}
