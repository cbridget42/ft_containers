#ifndef FT_STACK_TPP
#define FT_STACK_TPP

#include <vector>

namespace ft {
	template <class T, class Container = std::vector<T> >
	class stack {
		protected:
			Container c;
		public:
			typedef T value_type;
			typedef Container container_type;
			typedef typename Container::size_type size_type;
			typedef typename Container::reference reference;
			typedef typename Container::const_reference const_reference;

			explicit stack(const Container& cont = Container());
			~stack();
			stack(const stack& other);
			stack& operator=(const stack& other);

			T& top() {return c.back();}
			const T& top() const {return c.back();}
			bool empty() const {return c.empty();}
			size_type size() const {return c.size();}
			void push( const value_type& value ) {return c.push_back(value);}
			void pop() {return c.pop_back();}

			friend bool operator==(const ft::stack<T, Container>& lhs, \
					const ft::stack<T, Container>& rhs) {return lhs.c == rhs.c;}
			friend bool operator!=(const ft::stack<T, Container>& lhs, \
					const ft::stack<T, Container>& rhs) {return lhs.c != rhs.c;}
			friend bool operator<=(const ft::stack<T, Container>& lhs, \
					const ft::stack<T, Container>& rhs) {return lhs.c <= rhs.c;}
			friend bool operator>=(const ft::stack<T, Container>& lhs, \
					const ft::stack<T, Container>& rhs) {return lhs.c >= rhs.c;}
			friend bool operator<(const ft::stack<T, Container>& lhs, \
					const ft::stack<T, Container>& rhs) {return lhs.c < rhs.c;}
			friend bool operator>(const ft::stack<T, Container>& lhs, \
					const ft::stack<T, Container>& rhs) {return lhs.c > rhs.c;}
	};
}

template <typename T, typename Container>
ft::stack<T, Container>::stack(const Container& cont) {
	c = cont;
}

template <typename T, typename Container>
ft::stack<T, Container>::~stack() {}

template <typename T, typename Container>
ft::stack<T, Container>::stack(const stack& other) {
	c = other.c;
}

template <typename T, typename Container>
ft::stack<T, Container>& ft::stack<T, Container>::operator=(const stack& other) {
	if (*this != other) {
		c = other.c;
	}
	return *this;
}

#endif