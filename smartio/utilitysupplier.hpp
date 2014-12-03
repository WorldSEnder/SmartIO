/*
 * utilitysupplier.hpp
 *
 *  Created on: 29.11.2014
 *      Author: Carbon
 */
#pragma once

#include <array>

#include "Supplier.hpp"

namespace io
{
namespace utility
{

template<typename T>
struct memcpy_supplier : Supplier<T> {
	using item_t = typename Supplier<T>::item_t;
	static constexpr std::size_t size = sizeof(item_t);
	union {
		char buffer[size];
		item_t object;
	} mutable converter;

	item_t
	supply(Context& ctx) const override {
		istream& stream = ctx.getStream();
		stream.read(converter.buffer, size);
		return converter.object;
	}
};
/**
 * This supplier can be used when the type to be supplied can be
 * brace-initialized.
 */
template<typename T, typename... args>
struct aggregate_supplier : Supplier<T> {
	typename Supplier<T>::item_t
	supply(Context& ctx) const override {
		return { ctx.construct<args>()... };
	}
};
/**
 * This supplier can be used when the type to be supplied can be
 * move-constructed.
 */
template<typename T, typename... args>
struct move_supplier : Supplier<T> {
	typename Supplier<T>::item_t
	supply(Context& ctx) const override {
		return T(std::move(ctx.construct<args>())...);
	}
};
/**
 * This supplier returns a static-size array
 */
template<typename T, std::size_t N, bool b=false>
struct array_supplier : Supplier<std::array<T, N>> {
	using item_t = typename Supplier<T>::item_t;
	item_t
	supply(Context& ctx) const override {
		// TODO: array supplier
		static_assert(b, "Array supplier not implemented yet");
		return *((item_t*) nullptr);
	}
};

} /* namespace utility */
} /* namespace io */
