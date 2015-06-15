/*****************************************************************
 * Name: Martin Molzer
 * Project: smartio-build
 * File: /smartio-build/source/main/include/smartio/configurations.hpp
 *****************************************************************/

#pragma once

namespace io
{

  namespace config
  {

    class network_reading_t
    {
      static void
      configure (Environment& env) const;
    }const network_reading;

    class network_writing_t
    {
      static void
      configure (Environment& env) const;
    }const network_writing;

    /**
     * Registers network readers and writers
     */
    class networking_t : network_reading_t, network_writing_t
    {
      static void
      configure (Environment& env) const;
    }const networking;
    /**
     * Registers file readers and writers
     */
    class fileworking_t
    {
      static void
      configure (Environment& env) const;
    }const fileworking;

  }  // namespace config

}  // namespace io

