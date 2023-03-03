#ifndef FT_VECTOR_TPP
#define FT_VECTOR_TPP

#include <memory>

namespace ft {
	template<class T, class Allocator = std::allocator<T> >
	class vector {
		protected:

		public:
			typedef T value_type;
			typedef Allocator allocator_type;
			typedef unsigned long size_type;
			typedef long difference_type;
			typedef value_type& reference;
			typedef const value_type& const_reference;
			typedef typename Allocator::pointer pointer;
			typedef typename Allocator::const_pointer const_pointer;
			//iterator typedef should be here!!!
	};
}

#endif