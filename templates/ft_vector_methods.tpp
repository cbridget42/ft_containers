#ifndef FT_VECTOR_ACCESS_TPP
#define FT_VECTOR_ACCESS_TPP

#include "ft_vector.tpp"//delete it!!

namespace ft {

	template<class T, class Allocator>
	typename _VEC::reference _VEC::at(size_type pos) {
		if (pos >= _size)
			throw std::out_of_range("pos is out of range!");
		return _ptr[pos];
	}

	template<class T, class Allocator>
	typename _VEC::const_reference _VEC::at(size_type pos) const {
		if (pos >= _size)
			throw std::out_of_range("pos is out of range!");
		return _ptr[pos];
	}
}

#endif