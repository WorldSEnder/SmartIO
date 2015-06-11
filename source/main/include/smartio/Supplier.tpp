/*****************************************************************
 * Name: Martin Molzer
 * Project: smartio-build
 * File: /smartio-build/source/main/include/smartio/Supplier.tpp
 *****************************************************************/

#pragma once

#include "smartio/Supplier.hpp"

namespace io {

  template<typename T>
    typename Supplier<T>::item_t
    Supplier<T>::supply(ReadContext& ctx) const
    {
      return this->dosupply(ctx);
    }

}  // namespace io

