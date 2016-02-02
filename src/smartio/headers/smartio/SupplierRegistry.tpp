#pragma once

#include "smartio/SupplierRegistry.hpp"

namespace io {

template<typename T>
supplier_entry supplier_registry::toEntry(
		const ConstSupplierSharedPtr<T>& ptr) {
	return std::static_pointer_cast < _detail::storage_t > (ptr);
}

template<typename T>
ConstSupplierSharedPtr<T> supplier_registry::supplierFromEntry(
		const supplier_entry& entry) {
	return std::static_pointer_cast<const supplier_base<T>>(entry);
}

template<typename T>
supplier_key<T> supplier_registry::registerSupplier(
		ConstSupplierSharedPtr<T> ptr) {
	return suppliers.putEntry < T > (toEntry(ptr));
}

template<typename T>
ConstSupplierSharedPtr<T> supplier_registry::resolveSupplier(
		const supplier_key<T>& key) {
	return supplierFromEntry < T > (suppliers.getEntry(key));
}

template<typename T>
bool supplier_registry::makeDefaultEntry(const supplier_key<T>& key) {
	return suppliers.makeDefault(key);
}

}
