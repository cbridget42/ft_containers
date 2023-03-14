#ifndef UTILITY_HPP
#define UTILITY_HPP

namespace ft {
	template<class T1, class T2>
	struct pair {
		typedef T1 first_type;
		typedef T2 second_type;
		T1	first;
		T2	second;
		pair() {}
		pair(const T1& x, const T2& y): first(x), second(y) {}
		template< class U1, class U2 >
		pair(const pair<U1, U2>& p): first(p.first), \
			second(p.second) {}
		pair(const pair& p) = default;
		~pair() {}
		pair& operator=(const pair& other) {
			if (this != &other) {
				first = other.first;
				second = other.second;
			}
			return *this;
		}
	};

	template< class T1, class T2 >
	pair<T1, T2> make_pair(T1 t, T2 u) {
		return pair(t, u);
	}

	template< class T1, class T2, class U1, class U2 >
	bool operator==(const ft::pair<T1, T2>& lhs, const ft::pair<U1, U2>& rhs) {
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	template< class T1, class T2, class U1, class U2 >
	bool operator!=(const ft::pair<T1, T2>& lhs, const ft::pair<U1, U2>& rhs) {
		return !(lhs == rhs);
	}

	template< class T1, class T2, class U1, class U2 >
	bool operator<(const ft::pair<T1, T2>& lhs, const ft::pair<U1, U2>& rhs) {
		if (lhs.first < rhs.first)
			return true;
		else if (rhs.first < lhs.first)
			return false;
		else if (lhs.second < rhs.second)
			return true;
		else
			return false;
	}

	template< class T1, class T2, class U1, class U2 >
	bool operator<=(const ft::pair<T1, T2>& lhs, const ft::pair<U1, U2>& rhs) {
		return !(rhs < lhs);
	}

	template< class T1, class T2, class U1, class U2 >
	bool operator>(const ft::pair<T1, T2>& lhs, const ft::pair<U1, U2>& rhs) {
		return rhs < lhs;
	}

	template< class T1, class T2, class U1, class U2 >
	bool operator>=(const ft::pair<T1, T2>& lhs, const ft::pair<U1, U2>& rhs) {
		return !(lhs < rhs);
	}
}

#endif