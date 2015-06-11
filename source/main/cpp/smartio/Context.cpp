/*
 * Context.cpp
 *
 *  Created on: 29.11.2014
 *      Author: Carbon
 */

#include "smartio/Context.hpp"

namespace io
{

  ReadContext::ReadContext (supplier_map reader, input& stream) :
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

  context_base::context_base () :
      contextVars ()
  {

  }

  context_base::~context_base ()
  {
  }

  void
  context_base::setValue (key_t key, value_t val)
  {
    contextVars[key] = val;
  }

  ReadContext::value_t
  context_base::getValue (key_t key, value_t defaultVal) const
  {
    const auto& it = contextVars.find (key);
    if (it == contextVars.end ())
      return defaultVal;
    return it->second;
  }

  bool
  context_base::hasValue (key_t key) const
  {
    return contextVars.find (key) != contextVars.end ();
  }

  ReadContext::value_t&
  context_base::operator[] (key_t key)
  {
    return contextVars[key];
  }

} /* namespace io */
