/*
 * Context.cpp
 *
 *  Created on: 29.11.2014
 *      Author: Carbon
 */

#include "smartio/Context.hpp"

namespace io
{
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

  ReadContext::ReadContext (supplier_map reader, input& stream) :
      reference (std::move (reader)), stream (stream)
  {
  }

  ReadContext::~ReadContext ()
  {
  }

  ReadContext::input&
  ReadContext::getStream ()
  {
    return stream;
  }

  const ReadContext::input&
  ReadContext::getStream () const
  {
    return stream;
  }

  WriteContext::WriteContext (consumer_map mappings, output& s)
    : reference(mappings), stream(s){

  }

  WriteContext::~WriteContext () {}

  WriteContext::output&
  WriteContext::getStream ()
  {
    return stream;
  }

  const WriteContext::output&
  WriteContext::getStream () const
  {
    return stream;
  }

} /* namespace io */
