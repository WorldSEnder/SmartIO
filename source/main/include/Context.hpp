/*
 * Context.hpp
 *
 *  Created on: 29.11.2014
 *      Author: Carbon
 */

#pragma once

#include <unordered_map>
#include <memory>
#include <utility>
#include <istream>

#include "Supplier.hpp"
#include "typetoken.hpp"

namespace io
{
using std::istream;
using std::shared_ptr;

using typetoken::token_t;

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
class Context
{
    // Suppliers
    using supplier_map = std::unordered_map<token_t, shared_ptr<const SupplierBase>>;
    // Context variables
    using key_t = std::size_t;
    using value_t = std::size_t;
    using var_map = std::unordered_map<key_t, value_t>;
private:
    const supplier_map reference;
    istream& stream;
    var_map contextVars;
    Context() = delete;
    /**
     * Constructs a Context from a reference to a (non-temporary) map of
     * suppliers and a given i-stream to read objects from. We can never be
     * sure that supplier_map contains actual suppliers when handed over by
     * user so we have to friend Reader for this
     */
    Context(const supplier_map, istream&);
    // Helper function to find supplier in map
    template<typename T>
    const Supplier< T >& retrieveSupplier() const;
public:
    virtual ~Context();
    /**
     * Gets a reference to a registered supplier for the given type. If none is
     * registered invalid_argument is thrown. The reference's lifetime is as long
     * as the lifetime of the Reader object is was retrieved from.
     * The returned object reads directly from the i-stream bound to this context.
     *
     * <T> the type that should be supplied
     */
    template<typename T>
    BoundSupplier< supply_t< T > > getSupplier();
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
    supply_t< T > construct();
    /**
     * Returns the i-stream this Context is bound to. Altering the stream
     * effectively changes the context thus this method can't be called from
     * a constant Context object.
     */
    istream& getStream();
    /**
     * Sets the context variable for key.
     */
    void setValue(key_t, value_t);
    /**
     * Retrieves the value previously set for the key or default if it hasn't
     * been set. The context is not changed by this call.
     */
    value_t getValue(key_t, value_t) const;
    /**
     * Checks if a value for key has been set
     */
    bool hasValue(key_t) const;
    /**
     * Substitute for construct<T>
     */
    template<typename T>
    Context& operator>>(T&);
    // Delete const and rvalue
    template<typename T>
    Context& operator>>(const T&) = delete;
    /**
     * Substitute for construct<T> that returns the value
     * instead of the context.
     * Allows for constructs like copy = (ctx >>= val)
     */
    template<typename T>
    T& operator>>=(T&);
    // Delete const and rvalue
    template<typename T>
    T& operator>>=(const T&) = delete;
    /**
     * Another substitute for construct<T>. This allows for things like this:
     * foo((T) ctx); or even `T t = (T) ctx`
     */
    template<typename T>
    operator T(); // FIXME: mark this as explicit with gcc-4.10
    /**
     * Fills an array of constructible types
     */
    template<typename T, std::size_t N>
    Context& operator>>(T (&)[N]);
    // Delete if T is const type. Array can't be rvalue
    template<typename T, std::size_t N>
    Context& operator>>(const T (&)[N]) = delete;
    /**
     * A suitable variant to setValue/getValue.
     * If the key doesn't yet exist a value of zero is assigned to it. The returned
     * reference can be used to effectively change the value of the Context-value.
     */
    value_t& operator[](key_t);

    friend io::Reader;
    // TODO: think over that again friending
};

} /* namespace io */

#include "Context.tpp"
