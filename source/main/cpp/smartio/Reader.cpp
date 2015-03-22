/*
 * Reader.cpp
 *
 *  Created on: 27.11.2014
 *      Author: Carbon
 */

#include <utility>

#include "smartio/Reader.hpp"

namespace io
{

Reader::Reader(map_t supply) :
        suppliers(std::move(supply))
{
}

Reader::~Reader()
{
}

ReadContext Reader::from(input& stream) const
{
    return ReadContext(this->suppliers, stream);
}

} /* namespace io */
