/*****************************************************************
 * Name: Martin Molzer
 * Project: smartio-build
 * File: /smartio-build/source/main/include/smartio/Supplier.tpp
 *****************************************************************/

#pragma once

#include "smartio/Supplier.hpp"
#include <type_traits>

namespace io
{

  template<typename T>
    typename Supplier<T>::item_t
    Supplier<T>::supply (ReadContext& ctx) const
    {
      return this->dosupply (ctx);
    }

  template<typename T>
    bool
    Supplier<T>::apply (ReadContext& ctx, T& trgt) const
    {
      return this->doapply (ctx, trgt);
    }

}  // namespace io

