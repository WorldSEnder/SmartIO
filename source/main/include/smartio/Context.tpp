#pragma once

#include "smartio/Context.hpp"

#include <stdexcept>

#include "smartio/typetoken.hpp"

namespace io
{
  using std::invalid_argument;

  using typetoken::token_t;

  template<typename T>
    ConstSupplierPtr<T>
    ReadContext::retrieveSupplier (supplier_key<T> key) const
    {
      return io::getSupplier (this->reference, key);
    }

  template<typename T>
    BoundSupplier<T>
    ReadContext::getSupplier (supplier_key<T> key)
    {
      return BoundSupplier<supply_t<T> > (this->retrieveSupplier<T> (key),
					  *this);
    }

  template<typename T>
    supply_t<T>
    ReadContext::get (supplier_key<T> key)
    {
      ConstSupplierPtr<T> ptr = this->retrieveSupplier<T> (key);
      if (ptr == nullptr)
	return
	  { nullptr};
      return ptr->supply (*this);
    }
  template<typename T>
    T
    ReadContext::construct (T start, supplier_key<T> key)
    {
      ConstSupplierPtr<T> s = this->retrieveSupplier (key);
      if (s != nullptr && s->apply (*this, start))
	return start;
      T *ptr = this->get<T> (key).release ();
      if (ptr == nullptr)
	return start;
      return *ptr;
    }

  template<typename T>
    inline ReadContext&
    ReadContext::operator>> (T& out)
    {
      using cv_item_t = typename ::std::remove_reference<T>::type;
      using item_t = typename ::std::remove_cv< cv_item_t >::type;

      ConstSupplierPtr<item_t> s = this->retrieveSupplier<item_t> ();
      if (s == nullptr)
	{
	  // FIXME: Overthink when to scream (like here?)
	  // Reason: No supplier for the object
	  return *this;
	}
      if (!s->apply (*this, out))
	{
	  item_t *ptr = this->get<item_t> ().release ();
	  if (ptr == nullptr)
	    {
	      // Or maybe scream here
	      return *this;
	    }
	  out = *ptr;
	}
      return *this;
    }

  template<typename T>
    inline T&
    ReadContext::operator>>= (T& out)
    {
      (*this) >> out;
      return out;
    }

  template<typename T, size_t N>
    inline auto
    ReadContext::operator>>= (arr_ref<T, N> out)
    -> arr_ref<T, N>
    {
      using item_t = typename ::std::remove_cv< T >::type;

      for (size_t i = 0; i < N; ++i)
	{
	  (*this) >> out[i];
	}
      return out;

    }

  template<typename T, size_t N>
    inline ReadContext&
    ReadContext::operator>> (arr_ref<T, N> out)
    {
      (*this) >> out;
      return *this;
    }

  template<typename T>
    ConstConsumerPtr<T>
    WriteContext::retrieveConsumer (consumer_key<T> key) const
    {
      return io::getConsumer (this->reference, key);
    }

  template<typename T>
    BoundConsumer<T>
    WriteContext::getConsumer (consumer_key<T> key)
    {
      return
	{ this->retrieveConsumer(key), stream};
    }

  template<typename T>
    void
    WriteContext::write (const T& object, consumer_key<T> key)
    {
      ConstConsumerPtr<T> writer = this->retrieveConsumer (key);
      writer->consume (*this, object);
    }

  template<typename T>
    WriteContext&
    WriteContext::operator<< (const T& object)
    {
      this->write (object);
      return *this;
    }

  template<typename T, size_t N>
    WriteContext&
    WriteContext::operator<< (arr_ref<T, N> in)
    {
      for (size_t i = 0; i < N; ++i)
	{
	  (*this) << in[i];
	}
      return *this;
    }
}
