/*****************************************************************
 * Name: Martin Molzer
 * Project: smartio-build
 * File: /smartio-build/source/main/include/smartio/configurations.hpp
 *****************************************************************/

#pragma once
#include "smartio/Environment.hpp"

namespace io
{

  namespace config
  {

    struct network_reading_t
    {
      void
      configure (Environment& env) const;
    }const network_reading;

    struct network_writing_t
    {
      void
      configure (Environment& env) const;
    }const network_writing;

    /**
     * Registers network readers and writers
     */
    struct networking_t : network_reading_t, network_writing_t
    {
      void
      configure (Environment& env) const;
    }const networking;

    /**
     * File reading registers suppliers working with the native endianess
     */
    struct file_reading_t
    {
      void
      configure (Environment& env) const;
    }const filereading;
    /**
     * File writing registers consumers working with the native endianess
     */
    struct file_writing_t
    {
      void
      configure (Environment& env) const;
    }const filewriting;
    /**
     * Registers file readers and writers
     */
    struct fileworking_t : public file_reading_t, public file_writing_t
    {
      void
      configure (Environment& env) const;
    }const fileworking;

  }  // namespace config

}  // namespace io

