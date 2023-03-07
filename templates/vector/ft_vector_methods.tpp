#ifndef FT_VECTOR_ACCESS_TPP
#define FT_VECTOR_ACCESS_TPP

namespace ft {

	template<class T, class Allocator>
	typename _VEC::reference _VEC::at(size_type pos) {
		if (pos >= _size)
			throw ::std::out_of_range("pos is out of range!");
		return _ptr[pos];
	}

	template<class T, class Allocator>
	typename _VEC::const_reference _VEC::at(size_type pos) const {
		if (pos >= _size)
			throw ::std::out_of_range("pos is out of range!");
		return _ptr[pos];
	}

	template<class T, class Allocator>
	void _VEC::reserve(size_type new_cap) {
		if (new_cap <= _capacity)
			return;
		else if (new_cap > this->max_size())
			throw ::std::length_error("new_cap is greater than max_size!");
		this->copy_array(*this, new_cap);
	}

	template<class T, class Allocator>
	void _VEC::clear() {
		for (size_type i = 0; i < _size; ++i)
			_allocator.destroy(_ptr + i);
		_size = 0;
	}

	template<class T, class Allocator>
	void _VEC::push_back( const T& value ) {
		if (_size + 1 > this->max_size())
			throw ::std::length_error("size exceeds max_size!");
		else if (_size + 1 <= _capacity)
			_allocator.construct(_ptr + _size++, value);
		else {
			if (!_capacity)
				this->copy_array(*this, 1);
			else
				this->copy_array(*this, _capacity * 2);
			_allocator.construct(_ptr + _size++, value);
		}
	}

	template<class T, class Allocator>
	void _VEC::resize(size_type count) {
		if (count > this->max_size())
			throw ::std::length_error("count exceeds max_size!");
		else if (count <= _size) {
			for (size_type i = count; i < _size; ++i)
				_allocator.destroy(_ptr + i);
			_size = count;
		} else {
			if (count > _capacity)
				this->copy_array(*this, count);
			for (size_type i = _size; i < count; ++i)
				_allocator.construct(_ptr + i, value_type());
			_size = count;
		}
	}

	template<class T, class Allocator>
	void _VEC::resize(size_type count, T value) {
		if (count > this->max_size())
			throw ::std::length_error("count exceeds max_size!");
		else if (count <= _size) {
			for (size_type i = count; i < _size; ++i)
				_allocator.destroy(_ptr + i);
			_size = count;
		} else {
			if (count > _capacity)
				this->copy_array(*this, count);
			for (size_type i = _size; i < count; ++i)
				_allocator.construct(_ptr + i, value);
			_size = count;
		}
	}

	template<class T, class Allocator>
	void _VEC::swap(vector& other) {
		value_type* tmp_ptr = _ptr;
		_ptr = other._ptr;
		other._ptr = tmp_ptr;
		size_type tmp = _size;
		_size = other._size;
		other._size = tmp;
		tmp = _capacity;
		_capacity = other._capacity;
		other._capacity = tmp;
	}

	template< class T, class Alloc >
	bool operator==(const ft::vector<T, Alloc>& lhs, \
				const ft::vector<T, Alloc>& rhs) {
		if (lhs.size() != rhs.size())
			return false;
		for (unsigned long i = 0; i < lhs.size(); ++i) {
			if (lhs[i] != rhs[i])
				return false;
		}
		return true;
	 }

	template< class T, class Alloc >
	bool operator!=(const ft::vector<T, Alloc>& lhs, \
				const ft::vector<T, Alloc>& rhs) {
		return !(lhs == rhs);
	}

/*	template< class T, class Alloc >
	bool operator<(const ft::vector<T, Alloc>& lhs, \
				const ft::vector<T, Alloc>& rhs) {
		
	}*/


	template<class T, class Allocator>
	void _VEC::copy_array(const vector& other, size_type new_capacity) {
		T* tmp = _allocator.allocate(new_capacity);
		for(size_type i = 0; i < other._size; ++i) {
			try {
				_allocator.construct(tmp + i, other._ptr[i]);
			} catch (...) {
				for (size_type j = 0; j < i; ++j)
					_allocator.destroy(tmp + j);
				_allocator.deallocate(tmp, other._capacity);
				throw;
			}
		}
		if (_capacity)
			_allocator.deallocate(_ptr, _capacity);
		_ptr = tmp;
		_capacity = new_capacity;
		_size = other._size;
	}
}

#endif