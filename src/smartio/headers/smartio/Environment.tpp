#pragma once

#include "smartio/Environment.hpp"

#include <utility>
#include <type_traits>

namespace io {

template<typename Config>
Environment::Environment(const Config& c) {
	c.configure(*this);
}

template<typename T>
supplier_key<T> Environment::addSupplier(ConstSupplierSharedPtr<T> supplier) {
	return this->registerSupplier(supplier);
}

template<typename T>
consumer_key<T> Environment::addConsumer(ConstConsumerSharedPtr<T> consumer) {
	return registerConsumer(consumer);
}

template<typename T>
supplier_key<base_deduction_t<supplier_base, T> > Environment::addSupplier2(
		std::shared_ptr<T> ptr) {
	using item_t = base_deduction_t< supplier_base, T >;

	ConstSupplierSharedPtr<item_t> new_ptr = std::static_pointer_cast<
			const supplier_base<item_t>>(ptr);
	return addSupplier(new_ptr);
}

template<typename T>
consumer_key<base_deduction_t<consumer_base, T> > Environment::addConsumer2(
		std::shared_ptr<T> ptr) {
	using item_t = base_deduction_t< consumer_base, T >;

	ConstConsumerSharedPtr<item_t> new_ptr = std::static_pointer_cast<
			const consumer_base<item_t>>(ptr);
	return addConsumer(new_ptr);
}

template<typename T, class ... Args>
supplier_key<base_deduction_t<supplier_base, T> > Environment::emplaceSupplier(
		Args&& ... args) {
	using item_t = base_deduction_t< supplier_base, T >;

	return addSupplier(ConstSupplierSharedPtr<item_t> { new T {
			::std::forward<Args>(args)... } });
}

template<typename T, class ... Args>
consumer_key<base_deduction_t<consumer_base, T> > Environment::emplaceConsumer(
		Args&& ... args) {
	using item_t = base_deduction_t< consumer_base, T >;

	return addConsumer(ConstConsumerSharedPtr<item_t> { new T {
			::std::forward<Args>(args)... } });
}

template<typename T>
ConstSupplierSharedPtr<T> Environment::getSupplier(supplier_key<T> key) {
	return resolveSupplier(key);
}

template<typename T>
ConstConsumerSharedPtr<T> Environment::getConsumer(consumer_key<T> key) {
	return resolveConsumer(key);
}

}
