/*
 * fileformatexception.cpp
 *
 *  Created on: 29.11.2014
 *      Author: Carbon
 */

#include "smartio/fileformatexception.h"

namespace io
{

  fileformatexception::fileformatexception (const char *message) :
      std::logic_error ("Illegal file format"), mess (message)
  {

  }

  std::ostringstream fileformatexception::cnvt;

  const char*
  fileformatexception::what () const throw ()
  {
    cnvt.str ("");
    cnvt << logic_error::what () << ":" << mess;
    return cnvt.str ().c_str ();
  }

  fileformatexception::~fileformatexception ()
  {
  }

} /* namespace io */
