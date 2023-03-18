#ifndef VECTOR_METHODS_HPP
#define VECTOR_METHODS_HPP

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

	template<class T, class Allocator>
	void _VEC::reserve(size_type new_cap) {
		if (new_cap <= _capacity)
			return;
		else if (new_cap > this->max_size())
			throw std::length_error("new_cap is greater than max_size!");
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
			throw std::length_error("size exceeds max_size!");
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
	void _VEC::resize(size_type count, T value) {
		if (count > this->max_size())
			throw std::length_error("count exceeds max_size!");
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

	template<class T, class Allocator>
	typename _VEC::iterator _VEC::insert(const_iterator pos, const T& value) {
		long dst = 0;
		typename _VEC::iterator tmp = begin();
		for (; tmp != pos; ++tmp, ++dst)
			;
		insert(pos, 1, value);
		return iterator(begin() + dst);
	}

	template<class T, class Allocator>
	typename _VEC::iterator _VEC::insert(const_iterator pos, size_type count, const T& value) {
		if (count == 0)
			return _VEC::iterator(const_cast<T*>(pos.base()));
		else if (_capacity < _size + count) {
			T* tmp = _allocator.allocate((_capacity + count) * 2);
			size_type j, i;
			i = j = 0;
			typename _VEC::iterator it;
			try {
				for (; i < _size + count; ++i) {
					if (_ptr + i == pos.base()) {
						it = typename _VEC::iterator(tmp + i);
						this->insert_range_val(tmp, i, count, value);
					} else
						_allocator.construct(tmp + i, _ptr[j++]);
				}
			} catch (...) {
				for (j = 0; j < i; ++j)
					_allocator.destroy(tmp + j);
				_allocator.deallocate(tmp, (_capacity + count) * 2);
				throw;
			}
			fix_vec(tmp, count);
			return it;
		}
		size_type i = pos.base() - _ptr;
		_VEC::iterator it = this->insert_method(pos, count);
		try {
			this->insert_range_val(_ptr, i, count, value);
			++it;
		} catch (...) {
			this->insert_failed(pos, count, i);
			throw;
		}
		_size += count;
		return it;
	}

	template<class T, class Allocator>
	template< class InputIt >
	typename _VEC::iterator _VEC::insert(const_iterator pos, InputIt first, InputIt last, \
					typename ft::enable_if<!ft::is_integral<InputIt>::value>::type*) {
		size_type count = 0;
		for (InputIt it = first; it != last; ++it)
			++count;
		if (count == 0)
			return _VEC::iterator(const_cast<T*>(pos.base()));
		else if (_capacity < _size + count) {
			T* tmp = _allocator.allocate((_capacity + count) * 2);
			size_type j, i;
			i = j = 0;
			typename _VEC::iterator it;
			try {
				for (; i < _size + count; ++i) {
					if (_ptr + i == pos.base()) {
						it = typename _VEC::iterator(tmp + i);
						this->insert_range_iter(tmp, i, count, first);
					} else
						_allocator.construct(tmp + i, _ptr[j++]);
				}
			} catch (...) {
				for (j = 0; j < i; ++j)
					_allocator.destroy(tmp + j);
				_allocator.deallocate(tmp, (_capacity + count) * 2);
				throw;
			}
			fix_vec(tmp, count);
			return it;
		}
		size_type i = pos.base() - _ptr;
		_VEC::iterator it = insert_method(pos, count);
		try {
			this->insert_range_iter(_ptr, i, count, first);
			++it;
		} catch (...) {
			insert_failed(pos, count, i);
			throw;
		}
		_size += count;
		return it;
	}

	template<class T, class Allocator>
	typename _VEC::iterator _VEC::erase(iterator pos) {
		try {
			for (typename _VEC::iterator it = pos; it != this->end() - 1; ++it)
				*it = *(it + 1);
		} catch (...) {
			this->clear();
			throw;
		}
		_allocator.destroy(_ptr + _size - 1);
		--_size;
		return pos;
	}

	template<class T, class Allocator>
	typename _VEC::iterator _VEC::erase(iterator first, iterator last) {
		if (first == last)
			return last;
		size_type tmp = _size - (last - first);
		iterator res(first);
		try {
			typename _VEC::iterator it = last;
			for (; it != this->end(); ++it, ++first)
				*first = *it;
		} catch (...) {
			this->clear();
			throw;
		}
		for (;first != this->end(); ++first)
			_allocator.destroy(first.base());
		_size = tmp;
		return res;
	}

	template<class T, class Allocator>
	void _VEC::copy_array(const vector& other, size_type new_capacity) {
		if (new_capacity) {
			T* tmp = _allocator.allocate(new_capacity);
			for (size_type i = 0; i < other._size; ++i) {
				try {
					_allocator.construct(tmp + i, other._ptr[i]);
				} catch (...) {
					for (size_type j = 0; j < i; ++j)
						_allocator.destroy(tmp + j);
					_allocator.deallocate(tmp, other._capacity);
					throw;
				}
			}
			for (size_type i = 0; i < _size; ++i)
				_allocator.destroy(_ptr + i);
			if (_capacity)
				_allocator.deallocate(_ptr, _capacity);
			_ptr = tmp;
			_capacity = new_capacity;
			_size = other._size;
		} else {
			_capacity = _size = 0;
			_ptr = 0;
		}
	}

	template<class T, class Allocator>
	void _VEC::fix_vec(T* tmp, size_type count) {
		for (size_type i = 0; i < _size; ++i)
			_allocator.destroy(_ptr + i);
		if (_capacity)
			_allocator.deallocate(_ptr, (_capacity + count) * 2);
		_ptr = tmp;
		_capacity = (_capacity + count) * 2;
		_size += count;
	}

	template<class T, class Allocator>
	template<class U>
	void _VEC::insert_range_val(T* ptr, size_type &i, size_type count, const U& value) {
		size_type j = 0;
		for (; j < count; ++j) {
			_allocator.construct(ptr + i, value);
			if (j + 1 != count)
				++i;
		}
	}

	template<class T, class Allocator>
	template<class U>
	void _VEC::insert_range_iter(T* ptr, size_type &i, size_type count, U& value) {
		size_type j = 0;
		for (; j < count; ++j, ++value) {
			_allocator.construct(ptr + i, *value);
			if (j + 1 != count)
				++i;
		}
	}

	template<class T, class Allocator>
	typename _VEC::iterator _VEC::insert_method(const_iterator& pos, size_type count) {
		typename vector<T>::iterator it = this->end() - 1;
		try {
			for (; it >= pos; --it) {
				_allocator.construct((it + count).base(), *it);
				_allocator.destroy(it.base());
			}
		} catch (...) {
			if (it == this->end() - 1)
				throw;
			size_type j = 0;
			for (typename vector<T>::iterator tmp = this->begin(); \
				tmp != it + 1; ++tmp) {
				_allocator.destroy(tmp.base());
				j++;
			}
			++it;
			for (; j < _size; ++j) {
				_allocator.destroy((it + count).base());
				++it;
			}
			_size = 0;
			throw;
		}
		return it;
	}

	template<class T, class Allocator>
	void _VEC::insert_failed(const_iterator& pos, size_type count, size_type &i) {
		size_type m_pos = pos.base() - _ptr;
		for (size_type j = 0; j < _size + count; ++j) {
			if (j < m_pos)
				_allocator.destroy(_ptr + j);
			else if (j >= m_pos && j < m_pos + count) {
				if (j < i)
					_allocator.destroy(_ptr + j);
			} else
				_allocator.destroy(_ptr + j);
		}
		_size = 0;
	}
}

#endif