/*
 * Consumer.hpp
 *
 *  Created on: 06.12.2014
 *      Author: Carbon
 */

#pragma once

#include <ostream>

#include "smartio/traits.hpp"

namespace io
{

// Forward declare Context
// TODO: WriteContext
  class WriteContext;

  using std::ostream;
  /**
   * Base class for suppliers so we can store them in a list
   */
  class ConsumerBase
  {
  };
  /**
   * A supplier for the type T
   */
  template<typename T>
    class Consumer : public ConsumerBase
    {
    public:
      typedef typename consume_t<T>::type item_t;

      virtual
      ~Consumer ()
      {
      }
      ;
      /**
       * Use this to set environment variables you might need
       * to communicate to parents
       */
      virtual void
      prepare (const item_t&&) const = 0;
      /**
       * Consumes the item given.
       */
      virtual void
      consume (item_t&&, WriteContext&) const = 0;
    };

  template<typename T>
    class BoundConsumer
    {
      // TODO: change this to std::shared_ptr, too?
      const Consumer<T>& reference;
      WriteContext& ctx;
    public:
      BoundConsumer () = delete;
      BoundConsumer (const Consumer<T>& ref, WriteContext& context) :
	  reference (ref), ctx (context)
      {
      }
      BoundConsumer (Consumer<T> &&, WriteContext&) = delete;
      typedef typename supply_t<T>::type item_t;

      virtual
      ~BoundConsumer ()
      {
      }
      /**
       * Supplies an item from a previously bound context
       */
      void
      consume (item_t&& item)
      {
	reference.consume (item, ctx);
      }
    };

} /* namespace io */
