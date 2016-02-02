#pragma once

#include "smartio/Context.hpp"
#include "smartio/ConsumerRegistry.hpp"
#include "smartio/BoundConsumer.hpp"

namespace io {

class Writer;

class WriteContext: public context_base, private consumer_registry {
	template<typename T, size_t N>
	using arr_ref = const T(&)[N];

public:
	using output = ::std::ostream;

	virtual
	~WriteContext();

	template<typename T>
	BoundConsumer<T>
	getConsumer(consumer_key<T> key = consumer_key < T > ::default_());

	template<typename T>
	void
	write(const T& object,
			consumer_key<T> key = consumer_key < T > ::default_());

	output&
	getStream();

	const output&
	getStream() const;

	template<typename T>
	WriteContext&
	operator<<(const T& object);

	template<typename T, size_t N>
	WriteContext&
	operator<<(arr_ref<T, N> object);

	friend Writer;
private:
	output& stream;

	WriteContext() = delete;
	WriteContext(consumer_registry mappings, output& stream);
};

}

#include "smartio/WriteContext.tpp"
