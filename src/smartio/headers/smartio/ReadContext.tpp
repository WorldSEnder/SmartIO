#pragma once

#include "smartio/ReadContext.hpp"
#include "smartio/Supplier.hpp"

namespace io {

template<typename T, typename Alloc>
std::unique_ptr<T> ReadContext::get(supplier_key<T> key, Alloc allocator) {
	using ptr_t = typename std::allocator_traits<Alloc>::pointer;
	ConstSupplierSharedPtr < T > supplier = resolveSupplier(key);
	if (supplier == nullptr) {
		return std::unique_ptr < T > (nullptr);
	}
	ptr_t new_val = std::allocator_traits < Alloc > ::allocate(allocator, 1);
	try {
		supplier->construct(*this, new_val);
	} catch (...) {
		std::allocator_traits < Alloc > ::deallocate(allocator, new_val, 1);
		return std::unique_ptr < T > (nullptr);
	}
	return std::unique_ptr < T > (new_val);
}

template<typename T>
BoundSupplier<T> ReadContext::getSupplier(supplier_key<T> key) {
	return {resolveSupplier < T > (key), *this};
}

template<typename T>
T& ReadContext::construct(T const* ptr, supplier_key<T> key) {
	ConstSupplierSharedPtr < T > s = resolveSupplier < T > (key);
	if (s == nullptr) {
		// FIXME: Overthink when to scream (like here?)
	}
	s->construct(*this, ptr);
	return *ptr;
}

template<typename T>
inline ReadContext&
ReadContext::operator>>(T& out) {
	using cv_item_t = typename ::std::remove_reference<T>::type;
	using item_t = typename ::std::remove_cv< cv_item_t >::type;

	ConstSupplierSharedPtr<item_t> s = resolveSupplier(
			supplier_key < T > ::default_());
	if (s == nullptr) {
		// FIXME: Overthink when to scream (like here?)
		// Reason: No supplier for the object
		return *this;
	}
	out.~T();
	T* ptr = std::addressof(out);
	s->construct(*this, ptr);
	return *this;
}

template<typename T>
inline T&
ReadContext::operator>>=(T& out) {
	(*this) >> out;
	return out;
}

template<typename T, size_t N>
inline auto ReadContext::operator>>=(arr_ref<T, N> out)
-> arr_ref<T, N> {
	using item_t = typename ::std::remove_cv< T >::type;

	for (size_t i = 0; i < N; ++i) {
		(*this) >> out[i];
	}
	return out;

}

template<typename T, size_t N>
inline ReadContext&
ReadContext::operator>>(arr_ref<T, N> out) {
	(*this) >> out;
	return *this;
}

}
