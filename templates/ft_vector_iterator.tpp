#ifndef FT_VECTOR_ITERATOR_TPP
#define FT_VECTOR_ITERATOR_TPP

#define DIF_TYPE vector_iterator::difference_type

namespace ft {
	template <typename T>
	class vector_iterator: public std::iterator<std::random_access_iterator_tag, T> {
		private:
			T* _ptr;
		public:
			vector_iterator(): _ptr(0) {}
			explicit vector_iterator(T* ptr): _ptr(ptr) {}
			vector_iterator(const vector_iterator& other): _ptr(other._ptr) {}
			vector_iterator& operator=(const vector_iterator& other);
			~vector_iterator() {}

			T*					operator->() {return _ptr;}
			T&					operator*() {return *_ptr;}
			T&					operator[](const typename DIF_TYPE n) {return *(_ptr + n);}
			vector_iterator&	operator++();
			vector_iterator		operator++(int);
			vector_iterator&	operator--();
			vector_iterator		operator--(int);
			vector_iterator&	operator+=(const typename DIF_TYPE& n);
			vector_iterator&	operator-=(const typename DIF_TYPE& n);
			vector_iterator		operator+(const typename DIF_TYPE& n) {return vector_iterator(_ptr + n);}
			vector_iterator		operator-(const typename DIF_TYPE& n) {return vector_iterator(_ptr - n);}
			typename DIF_TYPE	operator-(const vector_iterator& rhs) {return this->_ptr - rhs._ptr;}
			bool				operator<(const vector_iterator& rhs) {return this->_ptr < rhs._ptr;}
			bool				operator>(const vector_iterator& rhs) {return this->_ptr > rhs._ptr;}
			bool				operator<=(const vector_iterator& rhs) {return !(this->_ptr > rhs._ptr);}
			bool				operator>=(const vector_iterator& rhs) {return !(this->_ptr < rhs._ptr);}
			bool				operator==(const vector_iterator& rhs) {return this->_ptr == rhs._ptr;}
			bool				operator!=(const vector_iterator& rhs) {return this->_ptr != rhs._ptr;}
	};

	template <typename T>
	vector_iterator<T>& vector_iterator<T>::operator=(const vector_iterator& other) {
		if (this != other) {
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
	vector_iterator<T>&	vector_iterator<T>::operator+=(const typename vector_iterator<T>::difference_type& n) {
		_ptr += n;
		return *this;
	}

	template <typename T>
	vector_iterator<T>&	vector_iterator<T>::operator-=(const typename vector_iterator<T>::difference_type& n) {
		_ptr -= n;
		return *this;
	}

	template <typename T>
	vector_iterator<T> operator+(const typename vector_iterator<T>::difference_type& n, \
								const vector_iterator<T>& rhs) {
		return vector_iterator<T>(rhs + n);
	}
}

#endif