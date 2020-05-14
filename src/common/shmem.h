#pragma once
#include <type_traits>

namespace shmem {
	template<bool B>
	using IsUse = std::bool_constant<B>;
	using Use = std::true_type;
	using NotUse = std::false_type;

}