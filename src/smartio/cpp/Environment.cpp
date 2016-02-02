/*
 * Environement.cpp
 *
 *  Created on: 27.11.2014
 *      Author: Carbon
 */

#include "smartio/Environment.hpp"

namespace io {
Environment::Environment() {
}

Environment::~Environment() {
}

Reader Environment::buildReader() const {
	const supplier_registry& suppliers = *this;
	return {suppliers};
}

Writer Environment::buildWriter() const {
	const consumer_registry& consumers = *this;
	return {consumers};
}

} /* namespace io */
