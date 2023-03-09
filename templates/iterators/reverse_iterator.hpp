#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

namespace ft {
	template <class Iter>
	class reverse_iterator: public std::iterator<typename Iter::iterator_category, \
			typename Iter::value_type> {
		private:
			Iter _iter;
		public:
			typedef Iter iterator_type;
			reverse_iterator(): _iter(0) {}
			explicit reverse_iterator(iterator_type x): _iter(x) {}
			template<class U>
			reverse_iterator(const reverse_iterator<U>& other): _iter(other.base()) {}
			template<class U>
			reverse_iterator& operator=(const reverse_iterator<U>& other) {
				if (this != other) {
					_iter = other.base();
				}
				return *this;
			}
			~reverse_iterator() {}

			iterator_type				base() const {return _iter;}
			typename Iter::pointer		operator->() {return &(operator*());}
			typename Iter::reference	operator*();
			typename Iter::reference	operator[](const typename Iter::difference_type n) \
			{return *(_iter - n);}
			reverse_iterator&	operator++();
			reverse_iterator	operator++(int);
			reverse_iterator&	operator--();
			reverse_iterator	operator--(int);
			reverse_iterator&	operator+=(const typename Iter::difference_type n);
			reverse_iterator&	operator-=(const typename Iter::difference_type n);
			reverse_iterator	operator+(const typename Iter::difference_type n) \
			{return reverse_iterator(_iter - n);}
			reverse_iterator	operator-(const typename Iter::difference_type n) \
			{return reverse_iterator(_iter + n);}
	};

	template <class Iter>
	typename Iter::reference reverse_iterator<Iter>::operator*() {
		Iter tmp(_iter);
		return *(--tmp);
	}

	template <class Iter>
	reverse_iterator<Iter>& reverse_iterator<Iter>::operator++() {
		--_iter;
		return *this;
	}

	template <class Iter>
	reverse_iterator<Iter> reverse_iterator<Iter>::operator++(int) {
		reverse_iterator tmp(*this);
		operator++();
		return tmp;
	}

	template <class Iter>
	reverse_iterator<Iter>& reverse_iterator<Iter>::operator--() {
		++_iter;
		return *this;
	}

	template <class Iter>
	reverse_iterator<Iter> reverse_iterator<Iter>::operator--(int) {
		reverse_iterator tmp(*this);
		operator--();
		return tmp;
	}

	template <class Iter>
	reverse_iterator<Iter>&	reverse_iterator<Iter>::operator+=(const typename Iter::difference_type n) {
		_iter -= n;
		return *this;
	}

	template <class Iter>
	reverse_iterator<Iter>&	reverse_iterator<Iter>::operator-=(const typename Iter::difference_type n) {
		_iter += n;
		return *this;
	}

	template<class Iterator1, class Iterator2>
	bool operator==( const ft::reverse_iterator<Iterator1>& lhs,
				const ft::reverse_iterator<Iterator2>& rhs ) {
		return lhs.base() == rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator!=( const ft::reverse_iterator<Iterator1>& lhs,
				const ft::reverse_iterator<Iterator2>& rhs ) {
		return lhs.base() != rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator<( const ft::reverse_iterator<Iterator1>& lhs,
				const ft::reverse_iterator<Iterator2>& rhs ) {
		return lhs.base() > rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator<=( const ft::reverse_iterator<Iterator1>& lhs,
				const ft::reverse_iterator<Iterator2>& rhs ) {
		return lhs.base() >= rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator>( const ft::reverse_iterator<Iterator1>& lhs,
				const ft::reverse_iterator<Iterator2>& rhs ) {
		return lhs.base() < rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator>=( const ft::reverse_iterator<Iterator1>& lhs,
				const ft::reverse_iterator<Iterator2>& rhs ) {
		return lhs.base() <= rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	typename reverse_iterator<Iterator1>::difference_type \
	operator-( const reverse_iterator<Iterator1>& lhs,
				const reverse_iterator<Iterator2>& rhs ) {
		return rhs.base() - lhs.base();
	}

	template <class Iter>
	reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n, \
								const reverse_iterator<Iter>& it) {
		return reverse_iterator<Iter>(it.base() - n);
	}

}

#endif