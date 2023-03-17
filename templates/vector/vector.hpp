#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <stdexcept>
#include "../other/algorithm.hpp"
#include "../iterators/vector_iterator.hpp"
#include "../iterators/reverse_iterator.hpp"
#include "../other/type_traits.hpp"

#define _VEC vector<T, Allocator>

namespace ft {
	template<class T, class Allocator = std::allocator<T> >
	class vector {
		public:
			typedef T										value_type;
			typedef Allocator								allocator_type;
			typedef unsigned long							size_type;
			typedef long									difference_type;
			typedef value_type&								reference;
			typedef const value_type&						const_reference;
			typedef typename Allocator::pointer				pointer;
			typedef typename Allocator::const_pointer		const_pointer;
			typedef vector_iterator<T>						iterator;
			typedef vector_iterator<const T>				const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

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
			vector(InputIt first, InputIt last, const Allocator& alloc = Allocator(), \
				typename ft::enable_if<!ft::is_integral<InputIt>::value>::type * = 0);
			vector(const vector& other): _ptr(0), _size(0), _capacity(0), \
				_allocator(other._allocator) {*this = other;}
			~vector();
			vector&			operator=(const vector& other);
			reference		operator[](size_type pos) {return _ptr[pos];}
			const_reference	operator[](size_type pos) const {return _ptr[pos];}
			void			assign(size_type count, const T& value);
			template< class InputIt>
			void			assign(InputIt first, InputIt last, \
					typename ft::enable_if<!ft::is_integral<InputIt>::value>::type * = 0);
			allocator_type	get_allocator() const {return _allocator;}
			reference		at(size_type pos);
			const_reference	at(size_type pos) const;
			reference		front() {return *_ptr;}
			const_reference	front() const {return *_ptr;}
			reference		back() {return *(_ptr + _size - 1);}
			const_reference	back() const {return *(_ptr + _size - 1);}
			T*				data() {return _ptr;}
			const T*		data() const {return _ptr;}
			bool			empty() const {return !(_size);}
			size_type		size() const {return _size;}
			size_type		max_size() const {return _allocator.max_size();}
			void			reserve(size_type new_cap);
			size_type		capacity() const {return _capacity;}
			void			clear();
			iterator		insert(const_iterator pos, const T& value);
			iterator		insert(const_iterator pos, size_type count, const T& value);
			template< class InputIt >
			iterator		insert(const_iterator pos, InputIt first, InputIt last, \
					typename ft::enable_if<!ft::is_integral<InputIt>::value>::type * = 0);
			iterator		erase(iterator pos);
			iterator		erase(iterator first, iterator last);
			void			push_back( const T& value );
			void			pop_back() {_allocator.destroy(_ptr + (--_size));}
			void			resize(size_type count, T value = T());
			void			swap(vector& other);
			iterator		begin() {return iterator(_ptr);}
			const_iterator	begin() const {return const_iterator(_ptr);}
			iterator		end() {return iterator(_ptr + _size);}
			const_iterator	end() const {return const_iterator(_ptr + _size);}
			reverse_iterator		rbegin() {return reverse_iterator(iterator(_ptr + _size));}
			const_reverse_iterator	rbegin() const {return const_reverse_iterator(iterator(_ptr + _size));}
			reverse_iterator		rend() {return reverse_iterator(iterator(_ptr));}
			const_reverse_iterator	rend() const {return reverse_iterator(iterator(_ptr));}

			private:
				void		copy_array(const vector& other, size_type new_capacity);
				void		fix_vec(T* tmp, size_type count);
				
				
				template<class U>
				void		insert_range_iter(T* ptr, size_type &i, size_type count, U& value);
				template<class U>
				void		insert_range_val(T* ptr, size_type &i, size_type count, const U& value);
				
				
				iterator	insert_method(const_iterator& pos, size_type count);
				void		insert_failed(const_iterator& pos, size_type count, size_type &i);
	};

	template<class T, class Allocator>
	_VEC::vector(size_type count, const T& value, \
				const Allocator& alloc): _ptr(0), _size(0), _capacity(0), \
				_allocator(alloc) {
		if (!count)
			return;
		_ptr = _allocator.allocate(count);
		for(size_type i = 0; i < count; ++i) {
			try {
				_allocator.construct(_ptr + i, value);
			} catch (...) {
				for (size_type j = 0; j < i; ++j)
					_allocator.destroy(_ptr + j);
				_allocator.deallocate(_ptr, count);
				throw;
			}
		}
		_size = _capacity = count;
	}

	template<class T, class Allocator>
	template< class InputIt >
	_VEC::vector(InputIt first, InputIt last, const Allocator& alloc, \
				typename ft::enable_if<!ft::is_integral<InputIt>::value>::type*): \
				_ptr(0), _size(0), _capacity(0), _allocator(alloc) {
		size_type count = 0;
		for (InputIt it = first; it != last; ++it)
			++count;
		if (!count)
			return;
		_ptr = _allocator.allocate(count);
		for(size_type i = 0; i < count; ++i, ++first) {
			try {
				_allocator.construct(_ptr + i, *first);
			} catch (...) {
				for (size_type j = 0; j < i; ++j)
					_allocator.destroy(_ptr + j);
				_allocator.deallocate(_ptr, count);
				throw;
			}
		}
		_size = _capacity = count;
	}

	template<class T, class Allocator>
	_VEC::~vector() {
		for (size_type i = 0; i < _size; ++i)
			_allocator.destroy(_ptr + i);
		_allocator.deallocate(_ptr, _capacity);
	}

	template<class T, class Allocator>
	_VEC& _VEC::operator=(const vector& other) {
		if (this != &other)
			this->copy_array(other, other._capacity);
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

	template<class T, class Allocator>
	template<class InputIt>
	void _VEC::assign(InputIt first, InputIt last, \
		typename ft::enable_if<!ft::is_integral<InputIt>::value>::type*) {
		size_type count = 0;
		for (InputIt it = first; it != last; ++it)
			++count;
		for (size_type i = 0; i < _size; ++i)
				_allocator.destroy(_ptr + i);
		if (_capacity < count) {
			_allocator.deallocate(_ptr, _capacity);
			_capacity = _size = 0;
			_ptr = _allocator.allocate(count);
			_capacity = count;
		}
		_size = count;
		for (size_type i = 0; i < _size; ++i, ++first) {
			try {
				_allocator.construct(_ptr + i, *first);
			} catch (...) {
				for (size_type j = 0; j < i; ++j)
					_allocator.destroy(_ptr + j);
				_allocator.deallocate(_ptr, _capacity);
				_capacity = _size = 0;
				throw;
			}
		}
	}

	template< class T, class Alloc >
	bool operator==(const ft::vector<T, Alloc>& lhs, \
				const ft::vector<T, Alloc>& rhs) {
		if (lhs.size() != rhs.size())
			return false;
		else
			return ft::equal(rhs.begin(), rhs.end(), lhs.begin());
	}

	template< class T, class Alloc >
	bool operator!=(const ft::vector<T, Alloc>& lhs, \
				const ft::vector<T, Alloc>& rhs) {
		return !(lhs == rhs);
	}

	template< class T, class Alloc >
	bool operator<(const ft::vector<T, Alloc>& lhs, \
				const ft::vector<T, Alloc>& rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template< class T, class Alloc >
	bool operator<=( const ft::vector<T, Alloc>& lhs,
				const ft::vector<T, Alloc>& rhs ) {
		return !(lhs > rhs);
	}

	template< class T, class Alloc >
	bool operator>( const ft::vector<T, Alloc>& lhs,
				const ft::vector<T, Alloc>& rhs ) {
		return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
	}

	template< class T, class Alloc >
	bool operator>=(const ft::vector<T, Alloc>& lhs, \
				const ft::vector<T, Alloc>& rhs) {
		return !(lhs < rhs);
	}

	template< class T, class Alloc >
	void swap(ft::vector<T, Alloc>& lhs,
			ft::vector<T, Alloc>& rhs) {
		lhs.swap(rhs);
	}
}

#include "vector_methods.hpp"

#endif