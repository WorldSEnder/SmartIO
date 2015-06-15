/*
 * Environement.cpp
 *
 *  Created on: 27.11.2014
 *      Author: Carbon
 */

#include "smartio/Environment.hpp"
#include "smartio/defaultSuppliers.hpp"
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
  Environment::build () const
  {
    return
      { this->suppliers};
  }

} /* namespace io */
