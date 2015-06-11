/*
 * Context.cpp
 *
 *  Created on: 29.11.2014
 *      Author: Carbon
 */

#include "smartio/Context.hpp"

namespace io
{

  ReadContext::ReadContext (const map_t reader, input& stream) :
      reference (std::move (reader)), stream (stream)
  {
  }

  ReadContext::~ReadContext ()
  {
  }

  auto
  ReadContext::getStream ()
  -> input&
  {
    return stream;
  }

  auto
  ReadContext::getStream () const -> const input&
  {
    return stream;
  }

  void
  ReadContext::setValue (key_t key, value_t val)
  {
    contextVars[key] = val;
  }

  ReadContext::value_t
  ReadContext::getValue (key_t key, value_t defaultVal) const
  {
    const auto& it = contextVars.find (key);
    if (it == contextVars.end ())
      return defaultVal;
    return it->second;
  }

  bool
  ReadContext::hasValue (key_t key) const
  {
    return contextVars.find (key) != contextVars.end ();
  }

  ReadContext::value_t&
  ReadContext::operator[] (key_t key)
  {
    return contextVars[key];
  }

} /* namespace io */
