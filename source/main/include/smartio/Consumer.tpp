/*****************************************************************
 * Name: Martin Molzer
 * Project: smartio-build
 * File: /smartio-build/source/main/include/smartio/Consumer.tpp
 *****************************************************************/

#pragma once

#include "smartio/Consumer.hpp"

namespace io
{

  template<typename T>
    Consumer<T>::~Consumer ()
    {
    }

  template<typename T>
    void
    Consumer<T>::consume (WriteContext& ctx, const item_t& item) const
    {
      this->doconsume (ctx, item);
    }

  template<typename T>
    BoundConsumer<T>::BoundConsumer (ConstConsumerPtr<T> ref,
				     WriteContext& context) :
	reference (ref), ctx (context)
    {
      if (reference == nullptr)
	{
	  // FIXME: scream as loud as we can
	}
    }

  template<typename T>
    BoundConsumer<T>::~BoundConsumer ()
    {
    }

  template<typename T>
    void
    BoundConsumer<T>::doconsume (const item_t& item) const
    {
      reference.consume (item, ctx);
    }

}
// namespace io

