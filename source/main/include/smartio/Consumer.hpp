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
   * A supplier for the type T
   */
  template<typename T>
    class Consumer
    {
    public:
      // Check for valid template arguments
      typedef consume_t<T> item_t;

      virtual
      ~Consumer ();
      /**
       * Consumes the item given.
       */
      void
      consume (WriteContext&, const item_t&) const;
    private:
      virtual void
      doconsume (WriteContext&, const item_t&) const = 0;
    };

  template<typename T>
    using ConsumerPtr = std::shared_ptr<Consumer< T >>;

  template<typename T>
    using ConstConsumerPtr = std::shared_ptr<const Consumer< T >>;

  template<typename T>
    class BoundConsumer
    {
      typedef typename Consumer<T>::item_t item_t;

      ConstConsumerPtr<T> reference;
      WriteContext& ctx;
    public:
      BoundConsumer () = delete;
      BoundConsumer (ConstConsumerPtr<T> ref, WriteContext& context);

      virtual
      ~BoundConsumer ();
      /**
       * Supplies an item from a previously bound context
       */
      void
      doconsume (const item_t& item) const override;
    };

} /* namespace io */

#include "smartio/Consumer.tpp"
