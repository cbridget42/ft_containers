#pragma once

#define DIF_TYPE vector_iterator::difference_type

namespace ft {
	template <typename T>
	class vector_iterator: public std::iterator<std::random_access_iterator_tag, T> {
		private:
			T* _ptr;
			typedef vector_iterator<const T> c_it;
		public:
			vector_iterator(): _ptr(0) {}
			explicit vector_iterator(T* ptr): _ptr(ptr) {}
			vector_iterator(const vector_iterator& other): _ptr(other._ptr) {}
			vector_iterator& operator=(const vector_iterator& other);
			operator c_it() {return vector_iterator<const T>(this->_ptr);}
			~vector_iterator() {}

			T*					base() const {return _ptr;}
			T*					operator->() const {return _ptr;}
			T&					operator*() const {return *_ptr;}
			T&					operator[](const typename DIF_TYPE n) {return *(_ptr + n);}
			vector_iterator&	operator++();
			vector_iterator		operator++(int);
			vector_iterator&	operator--();
			vector_iterator		operator--(int);
			vector_iterator&	operator+=(const typename DIF_TYPE n);
			vector_iterator&	operator-=(const typename DIF_TYPE n);
			vector_iterator		operator+(const typename DIF_TYPE n) {return vector_iterator(_ptr + n);}
			vector_iterator		operator-(const typename DIF_TYPE n) {return vector_iterator(_ptr - n);}
	};

	template <typename T>
	vector_iterator<T>& vector_iterator<T>::operator=(const vector_iterator& other) {
		if (this != &other) {
			_ptr = other._ptr;
		}
		return *this;
	}

	template <typename T>
	vector_iterator<T>& vector_iterator<T>::operator++() {
		++_ptr;
		return *this;
	}

	template <typename T>
	vector_iterator<T> vector_iterator<T>::operator++(int) {
		vector_iterator tmp(*this);
		operator++();
		return tmp;
	}

	template <typename T>
	vector_iterator<T>& vector_iterator<T>::operator--() {
		--_ptr;
		return *this;
	}

	template <typename T>
	vector_iterator<T> vector_iterator<T>::operator--(int) {
		vector_iterator tmp(*this);
		operator--();
		return tmp;
	}

	template <typename T>
	vector_iterator<T>&	vector_iterator<T>::operator+=(const typename vector_iterator<T>::difference_type n) {
		_ptr += n;
		return *this;
	}

	template <typename T>
	vector_iterator<T>&	vector_iterator<T>::operator-=(const typename vector_iterator<T>::difference_type n) {
		_ptr -= n;
		return *this;
	}

	template<class F, class J>
	bool operator==( const ft::vector_iterator<F>& lhs,
				const ft::vector_iterator<J>& rhs ) {
		return lhs.base() == rhs.base();
	}

	template< class F, class J >
	bool operator!=( const ft::vector_iterator<F>& lhs,
				const ft::vector_iterator<J>& rhs ) {
		return lhs.base() != rhs.base();
	}

	template< class F, class J >
	bool operator<( const ft::vector_iterator<F>& lhs,
				const ft::vector_iterator<J>& rhs ) {
		return lhs.base() < rhs.base();
	}

	template< class F, class J >
	bool operator<=( const ft::vector_iterator<F>& lhs,
				const ft::vector_iterator<J>& rhs ) {
		return lhs.base() <= rhs.base();
	}

	template< class F, class J >
	bool operator>( const ft::vector_iterator<F>& lhs,
				const ft::vector_iterator<J>& rhs ) {
		return lhs.base() > rhs.base();
	}

	template< class F, class J >
	bool operator>=( const ft::vector_iterator<F>& lhs,
				const ft::vector_iterator<J>& rhs ) {
		return lhs.base() >= rhs.base();
	}

	template <typename T>
	vector_iterator<T> operator+(typename vector_iterator<T>::difference_type n, \
								const vector_iterator<T>& it) {
		return vector_iterator<T>(it.base() + n);
	}

	template< class F, class J >
	typename vector_iterator<F>::difference_type \
	operator-( const vector_iterator<F>& lhs,
				const vector_iterator<J>& rhs ) {
		return lhs.base() - rhs.base();
	}
}
