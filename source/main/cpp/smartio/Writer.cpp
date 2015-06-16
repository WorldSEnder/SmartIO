/*****************************************************************
 * Name: Martin Molzer
 * Project: smartio-build
 * File: /smartio-build/source/main/cpp/smartio/Writer.cpp
 *****************************************************************/

#include "smartio/Writer.hpp"

namespace io
{

  Writer::Writer (consumer_map map) :
      consumers (map)
  {

  }

  Writer::~Writer ()
  {

  }

  WriteContext
  Writer::into (output& stream) const
  {
    return
      { consumers, stream};
  }

}  // namespace io
