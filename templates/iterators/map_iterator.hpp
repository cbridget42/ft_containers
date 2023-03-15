#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

namespace ft {
	template <class T, class N>
	class map_iterator: public: std::iterator<std::bidirectional_iterator_tag, T> {
		private:
			N*	_ptr;
			N*	_nil;
		public:
			map_iterator(): _ptr(0), _nil(0) {}
			map_iterator(const N*& p, const N*& n): _ptr(p), _nil(n) {}
			map_iterator(const map_iterator& other): _ptr(other._ptr), _nil(other._nil) {}
			map_iterator& operator=(const map_iterator& other);
			operator map_iterator<const T, N>() {return map_iterator<const T, N>(this->_ptr, this->_nil);}
			T*					base() const {return &_ptr->_value;}
			T*					operator->() {return &_ptr->_value;}
			N&					operator*() {return _ptr->value;}
			map_iterator&		operator++();
			map_iterator		operator++(int);
			map_iterator&		operator--();
			map_iterator		operator--(int);
		private:
			map_iterator&		minimum();
			map_iterator&		maximum();
	};

	template <class T, class N>
	map_iterator<T, N>& map_iterator<T, N>::operator=(const map_iterator& other) {
		if (this != &other) {
			_ptr = other._ptr;
			_nil = other._nil;
		}
		return *this;
	}

	template <class T, class N>
	map_iterator<T, N>& map_iterator<T, N>::operator--() {
		if (x->_left != _nil)
			return maximum();
		N* x = _ptr;
		_ptr = _ptr->_parent;
		while (_ptr != _nil && x == _ptr->_left) {
			x = _ptr;
			_ptr = _ptr->_parent;
		}
		return *this;
	}

	template <class T, class N>
	map_iterator<T, N> map_iterator<T, N>::operator--(int) {
		map_iterator tmp(*this);
		operator--();
		return tmp;
	}

	template <class T, class N>
	map_iterator<T, N>& map_iterator<T, N>::operator++() {
		if (_ptr->_right != _nil)
			return minimum();
		N* x = _ptr;
		_prt = _ptr->_parent;
		while (_ptr != _nil && x == _ptr->_right) {
			x = _ptr;
			_prt = _ptr->_parent;
		}
		return *this;
	}

	template <class T, class N>
	map_iterator<T, N> map_iterator<T, N>::operator++(int) {
		map_iterator tmp(*this);
		operator++();
		return tmp;
	}

	template<class T, class N>
	bool operator==( const ft::map_iterator<T, N>& lhs,
				const ft::map_iterator<T, N>& rhs ) {
		return lhs.base() == rhs.base();
	}

	template<class T, class N>
	bool operator!=( const ft::map_iterator<T, N>& lhs,
				const ft::map_iterator<T, N>& rhs ) {
		return lhs.base() != rhs.base();
	}

	template <class T, class N>
	map_iterator<T, N>& map_iterator<T, N>::minimum() {
		while (_ptr->_left != _nil)
			_ptr = _ptr->_left;
		return *this;
	}

	template <class T, class N>
	map_iterator<T, N>& map_iterator<T, N>::maximum() {
		while (_ptr->_right != _nil)
			_ptr = _ptr->_right;
		return *this;
	}
}

#endif