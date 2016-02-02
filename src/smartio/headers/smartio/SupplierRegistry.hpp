#pragma once

#include "smartio/StorageMap.hpp"
#include "smartio/Supplier.hpp"

namespace io {

template<class T>
using supplier_key = _detail::storage_key<T>;
using supplier_entry = _detail::storage_entry;
using supplier_map = _detail::storage_map;

class supplier_registry {
public:
	supplier_registry() = default;
	supplier_registry(const supplier_registry&) = default;
	supplier_registry(supplier_registry&&) = default;
	virtual ~supplier_registry() = default;

protected:
	template<typename T>
	supplier_key<T>
	registerSupplier(ConstSupplierSharedPtr<T> ptr);

	template<typename T>
	ConstSupplierSharedPtr<T>
	resolveSupplier(const supplier_key<T>& key = supplier_key<T>::default_());

	template<typename T>
	bool
	makeDefaultEntry(const supplier_key<T>& key);
private:
	supplier_map suppliers;
	/**
	 * Casts a supplier to an entry that can be stored in a supplier_list
	 */
	template<typename T>
	inline supplier_entry
	toEntry(const ConstSupplierSharedPtr<T>& ptr);
	/**
	 * Reverse of #toEntry().
	 * Note: No type-check is performed.
	 */
	template<typename T>
	inline ConstSupplierSharedPtr<T>
	supplierFromEntry(const supplier_entry& entry);
};

}

#include "smartio/SupplierRegistry.tpp"
