/*
 * Reader.cpp
 *
 *  Created on: 27.11.2014
 *      Author: Carbon
 */

#include <utility>

#include "Reader.hpp"

namespace io
{

Reader::Reader(supplier_map supply) :
        suppliers(std::move(supply))
{
}

Reader::~Reader()
{
}

Context Reader::createContext(istream& stream) const
{
    return Context(this->suppliers, stream);
}

} /* namespace io */
