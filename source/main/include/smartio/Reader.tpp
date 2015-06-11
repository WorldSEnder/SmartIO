#pragma once

#include "smartio/Reader.hpp"

namespace io
{

  template<typename T>
    SupplierPtr<T>
    Reader::getSupplier (supplier_key<T> key) const
    {
      return io::getSupplier (this->suppliers, key);
    }

  template<typename T>
    T
    Reader::construct (input& stream, supplier_key<T> key) const
    {
      return from (stream).construct (key);
    }

}
