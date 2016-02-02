#pragma once

#include <memory>

#include "smartio/Context.hpp"
#include "smartio/SupplierRegistry.hpp"
#include "smartio/BoundSupplier.hpp"

namespace io {

class Reader;

/**
 * Works as a temporary context for Suppliers.<br>
 *
 * The difference to Reader is that also the input stream is already set
 * and kept as a reference - introducing another lifetime dependence.
 */
class ReadContext: public context_base, private supplier_registry {
	template<typename T, size_t N>
	using arr_ref = T(&)[N];

public:
	using input = ::std::istream;

	virtual
	~ReadContext();

	template<typename T, typename Alloc = std::allocator<T>>
	std::unique_ptr<T> get(
			supplier_key<T> key = supplier_key < T > ::default_(),
			const Alloc& = { });
	/**
	 * Gets a reference to a registered supplier for the given type. If none is
	 * registered invalid_argument is thrown. The reference's lifetime is as long
	 * as the lifetime of the i-stream bound to this Context.
	 * The returned object reads directly from the i-stream bound to this context.
	 *
	 * <T> the type that should be supplied
	 */
	template<typename T>
	BoundSupplier<T>
	getSupplier(supplier_key<T> key = supplier_key < T > ::default_());
	/**
	 * Constructs a new object from this context using the stream that was
	 * supplied in the context's constructor and at the pointer that is being given.
	 */
	template<typename T>
	T& construct(T const* ptr,
			supplier_key<T> key = supplier_key < T > ::default_());
	/**
	 * Returns the i-stream this Context is bound to. Altering the stream
	 * effectively changes the context thus this method can't be called from
	 * a constant Context object.
	 */
	input& getStream();
	const input& getStream() const;

	// Read-like operations (uses default key)
	/**
	 * Reads one standard constructible object. To use the returned
	 * object use operator>>=, to use the context like an istream use operator>>.
	 */
	template<typename T>
	ReadContext& operator>>(T& out);
	template<typename T>
	T& operator>>=(T& out);
	/**
	 * Reads an array of standard constructible objects. To use the returned
	 * object use operator>>=, to use the context like an istream use operator>>.
	 */
	template<typename T, size_t N>
	ReadContext& operator>>(arr_ref<T, N> out);
	template<typename T, size_t N>
	arr_ref<T, N> operator>>=(arr_ref<T, N> out);

	friend Reader;
private:
	// Context variables
	input& stream;

	ReadContext() = delete;
	/**
	 * Constructs a Context from a reference to a (non-temporary) map of
	 * suppliers and a given i-stream to read objects from. We can never be
	 * sure that supplier_map is type safe when given from a user, so we
	 * friend Reader.
	 */
	ReadContext(supplier_registry suppliers, input& stream);
};

}

#include "smartio/ReadContext.tpp"
