/*
 * Context.hpp
 *
 *  Created on: 29.11.2014
 *      Author: Carbon
 */

#pragma once

#include <unordered_map>
#include <istream>
#include <ostream>

#include "smartio/detail.hpp"
#include "smartio/Supplier.hpp"

namespace io
{

// Forward declare for friend
  class Reader;
  class Writer;

  using context_key = size_t;
  using context_val = size_t;
  /**
   * Holds all of context that is shared between Read and Write
   */
  class context_base
  {
  public:
    context_base ();
    virtual
    ~context_base ();
    /**
     * Sets the context variable for key.
     */
    void
    setValue (context_key, context_val);
    /**
     * Retrieves the value previously set for the key or default if it hasn't
     * been set. The context is not changed by this call.
     */
    context_val
    getValue (context_key, context_val) const;
    /**
     * Checks if a value for key has been set
     */
    bool
    hasValue (context_key) const;
    /**
     * A suitable variant to setValue/getValue.
     * If the key doesn't yet exist a value of zero is assigned to it. The returned
     * reference can be used to effectively change the value of the Context-value.
     */
    context_val&
    operator[] (context_key);
  private:
    using key_t = context_key;
    using value_t = context_val;

    using var_map = std::unordered_map<context_key, context_val>;

    var_map contextVars;
  };

  /**
   * Works as a temporary context for Suppliers.<br>
   *
   * The difference to Reader is that also the input stream is already set
   * and kept as a reference - introducing another lifetime dependence.
   */
  class ReadContext : public context_base
  {
    template<typename T, size_t N>
      using arr_ref = T(&)[N];

  public:
    using input = ::std::istream;

    virtual
    ~ReadContext ();
    /**
     * Gets a reference to a registered supplier for the given type. If none is
     * registered invalid_argument is thrown. The reference's lifetime is as long
     * as the lifetime of the Reader object is was retrieved from.
     * The returned object reads directly from the i-stream bound to this context.
     *
     * <T> the type that should be supplied
     */
    template<typename T>
      BoundSupplier<T>
      getSupplier (supplier_key<T> key = supplier_key<T>::default_ ());
    /**
     * Constructs a new object from this context using the stream that was
     * supplied in the context's constructor. Altering the stream
     * effectively changes the context thus this method can't be called from
     * a constant Context object.<br>
     * Normally the return type is the requested type (assuming a valid
     * request), the only exception being an array type with specified
     * - constexpr - length. In this case a pointer to the created data
     * is returned and can be used to manipulate the data further.
     */
    template<typename T>
      supply_t<T>
      get (supplier_key<T> key = supplier_key<T>::default_ ());
    /**
     * Constructs a new value on the stack. This is seperated in three
     * parts
     */
    template<typename T>
      T
      construct (T start_val = T{},
		 supplier_key<T> key = supplier_key<T>::default_ ());
    /**
     * Returns the i-stream this Context is bound to. Altering the stream
     * effectively changes the context thus this method can't be called from
     * a constant Context object.
     */
    input&
    getStream ();
    const input&
    getStream () const;

    // Read-like operations (uses default key)
    /**
     * Reads one standard constructible object. To use the returned
     * object use operator>>=, to use the context like an istream use operator>>.
     */
    template<typename T>
      ReadContext&
      operator>> (T& out);
    template<typename T>
      T&
      operator>>= (T& out);
    /**
     * Reads an array of standard constructible objects. To use the returned
     * object use operator>>=, to use the context like an istream use operator>>.
     */
    template<typename T, size_t N>
      ReadContext&
      operator>> (arr_ref<T, N> out);
    template<typename T, size_t N>
      arr_ref<T, N>
      operator>>= (arr_ref<T, N> out);

    friend io::Reader;
  private:
    // Context variables
    const supplier_map reference;
    input& stream;
    ReadContext () = delete;
    /**
     * Constructs a Context from a reference to a (non-temporary) map of
     * suppliers and a given i-stream to read objects from. We can never be
     * sure that supplier_map is type safe when given from a user, so we
     * friend Reader.
     */
    ReadContext (supplier_map suppliers, input& stream);
    // Helper function to find supplier in map
    template<typename T>
      ConstSupplierPtr<T>
      retrieveSupplier (supplier_key<T> key =
	  supplier_key<T>::default_ ()) const;
  };

  class WriteContext : public context_base
  {
    template<typename T, size_t N>
      using arr_ref = const T(&)[N];

  public:
    using output = ::std::ostream;

    virtual
    ~WriteContext ();

    template<typename T>
      BoundConsumer<T>
      getConsumer (consumer_key<T> key = consumer_key<T>::default_ ());

    template<typename T>
      void
      write (const T& object, consumer_key<T> key = consumer_key<T>::default_ ());

    output&
    getStream ();

    const output&
    getStream () const;

    template<typename T>
      WriteContext&
      operator<< (const T& object);

    template<typename T, size_t N>
      WriteContext&
      operator<< (arr_ref<T, N> object);

    friend io::Writer;
  private:
    const consumer_map reference;
    output& stream;

    WriteContext () = delete;
    WriteContext (consumer_map mappings, output& stream);

    template<typename T>
      ConstConsumerPtr<T>
      retrieveConsumer (consumer_key<T> key =
	  consumer_key<T>::default_ ()) const;
  };

} /* namespace io */

#include "Context.tpp"
