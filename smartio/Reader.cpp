/*
 * Reader.cpp
 *
 *  Created on: 27.11.2014
 *      Author: Carbon
 */

#include "Reader.hpp"

#include <utility>

namespace io
{

Reader::Reader(supplier_map supply) :
        suppliers(std::move(supply))
{
}

Reader::~Reader()
{
}

} /* namespace io */
