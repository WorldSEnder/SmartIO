#pragma once

#include "smartio/Environment.hpp"

#include <utility>
#include <type_traits>

namespace io
{

  template<typename T>
    supplier_key<T>
    Environment::addSupplier (SupplierPtr<T> supplier)
    {
      return io::putSupplier(this->suppliers, supplier);
    }

  template<typename T>
    consumer_key<T>
    Environment::addConsumer (ConsumerPtr<T> consumer)
    {
      return io::putConsumer(this->consumers, consumer);
    }

}
