/*****************************************************************
 * Name: Martin Molzer
 * Project: smartio-build
 * File: /smartio-build/source/main/include/smartio/Writer.hpp
 *****************************************************************/

#pragma once

#include <ostream>

#include "smartio/detail.hpp"
#include "smartio/Context.hpp"
#include "smartio/Consumer.hpp"

namespace io {

  class Environment;

  class Writer
  {
  public:
    using output = ::std::ostream;

    virtual
    ~Writer ();
    /**
     * Gets a reference to a registered supplier for the given type. If none is
     * registered invalid_argument is thrown. The reference's lifetime is as long
     * as the lifetime of the Reader object is was retrieved from.
     *
     * <T> the type that should be supplied
     */
    template<typename T>
      ConstConsumerPtr<T>
      getSupplier (consumer_key<T> key = consumer_key<T>::default_ ()) const;
    /**
     * Creates a context that reads from the stream given.
     */
    WriteContext
    into (output& stream) const;

    template<typename T>
      void
      consume (output& stream, const T& item, supplier_key<T> key =
		     supplier_key<T>::default_ ()) const;
  private:
    Writer () = delete;
    /**
     * Constructs a new reader from a map of suppliers
     */
    Writer (consumer_map map);

    friend Environment;

    const consumer_map consumers;
  };
}  // namespace io

#include "smartio/Writer.tpp"
