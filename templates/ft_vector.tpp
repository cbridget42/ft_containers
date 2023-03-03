#ifndef FT_VECTOR_TPP
#define FT_VECTOR_TPP

#include <memory>

#define _VEC vector<T, Allocator>

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
//			template< class InputIt >
//			vector(InputIt first, InputIt last, const Allocator& alloc = Allocator());//do it latter!!!
			vector(const vector& other): _ptr(0), _size(0), _capacity(0), \
				_allocator(other._allocator) {*this = other;}
			~vector();
			vector& operator=(const vector& other);
			reference operator[](size_type pos) {return _ptr[pos];}
			const_reference operator[](size_type pos) const {return _ptr[pos];}
			void assign(size_type count, const T& value);
//			template< class InputIt >
//			void assign(InputIt first, InputIt last);//do it latter!!!
			allocator_type get_allocator() const {return _allocator;}
			reference at(size_type pos);
			const_reference at(size_type pos) const;
			reference front() {return *_ptr;}
			const_reference front() const {return *_ptr;}
			reference back() {return *(_ptr + _size - 1);}
			const_reference back() const {return *(_ptr + _size - 1);}
			T* data() {return _ptr;}
			const T* data() const {return _ptr;}
			bool empty() const {return !(_size);}
			size_type size() const {return _size;}
			size_type max_size() const {return _allocator.max_size();}
	};

	template<class T, class Allocator>
	_VEC::vector(size_type count, const T& value, \
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
	_VEC::~vector() {
		for (vector::size_type i = 0; i < _size; ++i)
			_allocator.destroy(_ptr + i);
		_allocator.deallocate(_ptr, _capacity);
	}

	template<class T, class Allocator>
	_VEC& _VEC::operator=(const vector& other) {
		if (this != &other) {
			T* tmp = _allocator.allocate(other._capacity);
			for(vector::size_type i = 0; i < other._size; ++i) {
				try {
					_allocator.construct(tmp + i, other._ptr[i]);
				} catch (...) {
					for (vector::size_type j = 0; j < i; ++j)
						_allocator.destroy(tmp + j);
					_allocator.deallocate(tmp, other._capacity);
					throw;
				}
			}
			if (_capacity)
				_allocator.deallocate(_ptr, _capacity);
			_ptr = tmp;
			_capacity = other._capacity;
			_size = other._size;
		}
		return *this;
	}

	template<class T, class Allocator>
	void _VEC::assign(size_type count, const T& value) {
		for (size_type i = 0; i < _size; ++i)
				_allocator.destroy(_ptr + i);
		if (_capacity < count) {
			_allocator.deallocate(_ptr, _capacity);
			_capacity = _size = 0;
			_ptr = _allocator.allocate(count);
			_capacity = count;
		}
		_size = count;
		for (size_type i = 0; i < _size; ++i) {
			try {
				_allocator.construct(_ptr + i, value);
			} catch (...) {
				for (size_type j = 0; j < i; ++j)
					_allocator.destroy(_ptr + j);
				_allocator.deallocate(_ptr, _capacity);
				_capacity = _size = 0;
				throw;
			}
		}
	}
}

#include "ft_vector_methods.tpp"

#endif