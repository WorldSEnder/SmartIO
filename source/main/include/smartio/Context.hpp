/*
 * Context.hpp
 *
 *  Created on: 29.11.2014
 *      Author: Carbon
 */

#pragma once

#include <unordered_map>
#include <istream>

#include "smartio/detail.hpp"
#include "smartio/Supplier.hpp"

namespace io
{

// Forward declare for friend
  class Reader;

  /**
   * Works as a temporary context for Suppliers and thus is dependent
   * on a previously created Reader to create objects from. This reader
   * is kept by reference so the Context's lifetime should be at most as
   * long as the Reader's.<br>
   * The difference to Reader is that also the input stream is already set
   * and also kept as a reference - introducing another lifetime dependence.
   */
  class ReadContext
  {
    template<typename T, size_t N>
      using arr_ref = T(&)[N];

  public:
    using input = ::std::istream;
    using key_t = std::size_t;
    using value_t = std::size_t;

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
      getSupplier (supplier_key<T> key);
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
      get (supplier_key<T> key);
    template<typename T>
      T
      construct (supplier_key<T> key);
    /**
     * Default-reads an object. That is, uses the currently for the object
     * type registered default supplier.
     */
    template<typename T>
      supply_t<T>
      get ();
    template<typename T>
      T
      construct ();
    /**
     * Returns the i-stream this Context is bound to. Altering the stream
     * effectively changes the context thus this method can't be called from
     * a constant Context object.
     */
    input&
    getStream ();
    const input&
    getStream () const;

    /**
     * Sets the context variable for key.
     */
    void
    setValue (key_t, value_t);
    /**
     * Retrieves the value previously set for the key or default if it hasn't
     * been set. The context is not changed by this call.
     */
    value_t
    getValue (key_t, value_t) const;
    /**
     * Checks if a value for key has been set
     */
    bool
    hasValue (key_t) const;
    /**
     * A suitable variant to setValue/getValue.
     * If the key doesn't yet exist a value of zero is assigned to it. The returned
     * reference can be used to effectively change the value of the Context-value.
     */
    value_t&
    operator[] (key_t);

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
    // TODO: think over that again friending

  private:
    using map_t = _detail::supplier_map;
    using var_map = std::unordered_map<key_t, value_t>;
    // Context variables
    const map_t reference;
    input& stream;
    var_map contextVars;
    ReadContext () = delete;
    /**
     * Constructs a Context from a reference to a (non-temporary) map of
     * suppliers and a given i-stream to read objects from. We can never be
     * sure that supplier_map is type safe when given from a user, so we
     * friend Reader.
     */
    ReadContext (const map_t suppliers, input& stream);
    // Helper function to find supplier in map
    template<typename S>
      SupplierPtr<S>
      retrieveSupplier (supplier_key<S> key) const;
    // Finds the "default supplier", currently simple the first one
    // in the map...
    template<typename S>
      SupplierPtr<S>
      retrieveSupplier () const;
  };

} /* namespace io */

#include "Context.tpp"
