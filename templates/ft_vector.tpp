#ifndef FT_VECTOR_TPP
#define FT_VECTOR_TPP

#include <memory>

namespace ft {
	template<class T, class Allocator = std::allocator<T> >
	class vector {
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

		protected:
			T*			_ptr;
			size_type	_size;
			size_type	_capacity;
			Allocator	_allocator;
		public:
			vector(): _ptr(0), _size(0), _capacity(0) {}
			explicit vector(const Allocator& alloc): _ptr(0), _size(0), \
				_capacity(0), _allocator(alloc) {}
			explicit vector(size_type count, const T& value = T(), \
				const Allocator& alloc = Allocator());
			template< class InputIt >
			vector(InputIt first, InputIt last, const Allocator& alloc = Allocator());//do it latter!!!
			vector(const vector& other);
			~vector();
			

	};
	template<class T, class Allocator>
	vector<T, Allocator>::vector(size_type count, const T& value, \
				const Allocator& alloc): _ptr(0), _size(0), _capacity(0), \
				_allocator(alloc) {
		if (!count)
			return;
		_ptr = _allocator.allocate(count);
		for(vector::size_type i = 0; i < count; ++i) {
			try {
				_allocator.construct(_ptr + i, value);
			} catch (...) {
				for (vector::size_type j = 0; j < i; ++j)
					_allocator.destroy(_ptr + j);
				_allocator.deallocate(_ptr, count);
				throw;
			}
		}
		_size = _capacity = count;
	}
	template<class T, class Allocator>
	vector<T, Allocator>::vector(const vector& other): _ptr(0), _size(other._size), \
	_capacity(other._capacity), _allocator(other._allocator) {
		_ptr = _allocator.allocate(other._capacity);
		for(vector::size_type i = 0; i < other._size; ++i) {
			try {
				_allocator.construct(_ptr + i, other._ptr[i]);
			} catch (...) {
				for (vector::size_type j = 0; j < i; ++j)
					_allocator.destroy(_ptr + j);
				_allocator.deallocate(_ptr, other._capacity);
				throw;
			}
		}
	}
	template<class T, class Allocator>
	vector<T, Allocator>::~vector() {
		for (vector::size_type i = 0; i < _size; ++i)
			_allocator.destroy(_ptr + i);
		_allocator.deallocate(_ptr, _capacity);
	}
}

#endif