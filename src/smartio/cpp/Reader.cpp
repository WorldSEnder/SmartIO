/*
 * Reader.cpp
 *
 *  Created on: 27.11.2014
 *      Author: Carbon
 */

#include <utility>

#include "smartio/Reader.hpp"

namespace io {

Reader::Reader(supplier_registry suppliers) :
		supplier_registry(std::move(suppliers)) {
}

Reader::~Reader() {
}

ReadContext Reader::from(input& stream) const {
	const supplier_registry& suppliers = *this;
	return ReadContext(suppliers, stream);
}

} /* namespace io */
