/*
 * Environement.cpp
 *
 *  Created on: 27.11.2014
 *      Author: Carbon
 */

#include "smartio/Environment.hpp"
#include "smartio/detail.hpp"

namespace io
{
  Environment::Environment ()
  {
  }

  Environment::~Environment ()
  {
  }

  Reader
  Environment::buildReader() const
  {
    return
      { this->suppliers};
  }

  Writer
  Environment::buildWriter() const
  {
    return
      { this->consumers};
  }

} /* namespace io */
