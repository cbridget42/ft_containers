#pragma once

#include <limits>

namespace ft {
	template< bool B, class T = void >
	struct enable_if {};

	template<class T>
	struct enable_if<true, T> { typedef T type; };

	template <typename T>
	struct is_integral {
		static const bool value;
	};

	template <typename T>
	const bool is_integral<T>::value = std::numeric_limits<T>::is_integer;
}
