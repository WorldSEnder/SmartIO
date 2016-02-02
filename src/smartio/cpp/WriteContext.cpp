/*
 * WriteContext.cpp
 *
 *  Created on: 01.02.2016
 *      Author: WorldSEnder
 */

#include <utility>

#include "smartio/WriteContext.hpp"

namespace io {

WriteContext::WriteContext(consumer_registry writer, output& stream) :
		consumer_registry(std::move(writer)), stream(stream) {
}

WriteContext::~WriteContext() {
}

WriteContext::output&
WriteContext::getStream() {
	return stream;
}

const WriteContext::output&
WriteContext::getStream() const {
	return stream;
}

}
