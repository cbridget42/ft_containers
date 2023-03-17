#ifndef MAP_HPP
#define MAP_HPP

#include <functional>
#include <memory>
#include <stdexcept>
#include "../other/utility.hpp"
#include "../other/red_black_tree.hpp"
#include "../iterators/map_iterator.hpp"
#include "../iterators/reverse_iterator.hpp"
#include "../other/algorithm.hpp"

#define _MAP map<Key, T, Compare, Allocator>

namespace ft {
	template<class Key, class T, class Compare = std::less<Key>, \
	class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map {
		public:
			typedef Key											key_type;
			typedef T											mapped_type;
			typedef ft::pair<const Key, T>						value_type;
			typedef unsigned long								size_type;
			typedef long										difference_type;
			typedef Compare										key_compare;
			typedef Allocator									allocator_type;
			typedef value_type&									reference;
			typedef const value_type&							const_reference;
			typedef typename Allocator::pointer					pointer;
			typedef typename Allocator::const_pointer			const_pointer;
			typedef map_iterator<value_type, Node<value_type> >			iterator;
			typedef map_iterator<const value_type, Node<value_type> >	const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
			class value_compare: public std::binary_function<value_type, value_type, bool> {
				protected:
					friend class map;
					Compare comp;
					value_compare(Compare c = Compare()): comp(c) {}
				public:
					bool operator()(const value_type& lhs, const value_type& rhs) const \
						{return comp(lhs.first, rhs.first);}
			};
		protected:
			typedef typename Allocator::template rebind<Node<value_type> >::other	Node_alloc;
			value_compare	_comp;
			Allocator		_alloc;
			Rbt<value_type, value_compare, Node_alloc>	_data;
		public:
			map(): _comp(Compare()), _alloc(Allocator()), _data(_comp) {}
			explicit map(const Compare& comp, const Allocator& alloc = Allocator()): \
					_comp(comp), _alloc(alloc), _data(_comp) {}
			template< class InputIt >
			map(InputIt first, InputIt last, const Compare& comp = Compare(), \
				const Allocator& alloc = Allocator());
			map(const map& other): _comp(other._comp), _alloc(other._alloc), \
					_data(other._data) {}
			~map() {}
			map&			operator=(const map& other);
			T&				operator[](const Key& key) {return \
					(*(insert(ft::make_pair(key, T())).first)).second;}
			allocator_type	get_allocator() const {return _alloc;}
			T&				at(const Key& key);
			const T&		at( const Key& key ) const;
			iterator		begin() {return iterator(_data.tree_minimum(_data.get_root()), \
					_data.get_nil());}
			const_iterator	begin() const {return const_iterator(_data.tree_minimum(_data.get_root()), \
					_data.get_nil());}
			iterator		end() {return iterator(_data.get_nil(), _data.get_nil());}
			const_iterator	end() const {return const_iterator(_data.get_nil(), \
					_data.get_nil());}
			reverse_iterator rbegin() {return reverse_iterator(end());}
			const_reverse_iterator rbegin() const {return const_reverse_iterator(end());}
			reverse_iterator rend() {return reverse_iterator(begin());}
			const_reverse_iterator rend() const {return const_reverse_iterator(begin());}
			bool			empty() const {return !_data.get_size();}
			size_type		size() const {return _data.get_size();}
			size_type		max_size() const {return _data.max_size();}
			void			clear() {_data.clear();}
			ft::pair<iterator, bool> insert(const value_type& value) {return _data.insert(value);}
			iterator		insert(iterator pos, const value_type& value);
			template<class InputIt>
			void			insert(InputIt first, InputIt last);
			iterator		erase(iterator pos);
			iterator		erase(iterator first, iterator last);
			size_type		erase(const Key& key);
			void			swap(map& other) {_data.swap(other._data);}
			size_type		count(const Key& key) const {return search(key) == _data.get_nil()? 0 : 1;}
			iterator		find(const Key& key) {return iterator(search(key), _data.get_nil());}
			const_iterator	find(const Key& key) const {return const_iterator(search(key), \
			_data.get_nil());}
			iterator		lower_bound(const Key& key) {return iterator(_lower_bound(key), \
			_data.get_nil());}
			const_iterator	lower_bound(const Key& key) const {return \
			const_iterator(_lower_bound(key), _data.get_nil());}
			iterator		upper_bound(const Key& key) {return iterator(_upper_bound(key), \
			_data.get_nil());}
			const_iterator	upper_bound(const Key& key) const {return \
			const_iterator(_upper_bound(key), _data.get_nil());}
			ft::pair<iterator,iterator> equal_range(const Key& key) \
			{return ft::make_pair(lower_bound(key), upper_bound(key));}
			ft::pair<const_iterator,const_iterator> equal_range(const Key& key) const \
			{return ft::make_pair(lower_bound(key), upper_bound(key));}
			key_compare		key_comp() const {return key_compare();}
			value_compare	value_comp() const {return _comp;}

			void			debug_tree() {_data.print_tree();}

			private:
				Node<value_type>*	search(const Key& key) const;
				Node<value_type>*	_lower_bound(const Key& key) const;
				Node<value_type>*	_upper_bound(const Key& key) const;
	};

	template<class Key, class T, class Compare, class Allocator>
	typename _MAP::size_type _MAP::erase(const Key& key) {
		Node<value_type>* n = search(key);
		if (n == _data.get_nil())
			return 0;
		_data.rb_delete(n);
		return 1;
	}

	template<class Key, class T, class Compare, class Allocator>
	typename _MAP::iterator _MAP::erase(iterator first, iterator last) {
		Node<value_type>* n = search(first->first);
		Node<value_type>* tmp;
		for (; first != last; ++first) {
			tmp = _data.tree_successor(n);
			_data.rb_delete(n);
			n = tmp;
		}
		return first;
	}

	template<class Key, class T, class Compare, class Allocator>
	typename _MAP::iterator _MAP::erase(iterator pos) {
		Node<value_type>* n = search(pos->first);
		++pos;
		_data.rb_delete(n);
		return pos;
	}

	template<class Key, class T, class Compare, class Allocator>
	map<Key, T, Compare, Allocator>& _MAP::operator=(const map& other) {
		if (this != &other) {
			_comp = other._comp;
			_alloc = other._alloc;
			_data = other._data;
		}
		return *this;
	}

	template<class Key, class T, class Compare, class Allocator>
	template< class InputIt >
	_MAP::map(InputIt first, InputIt last, const Compare& comp, const Allocator& alloc): \
			_comp(comp), _alloc(alloc), _data(_comp) {
		insert(first, last);
	}

	template<class Key, class T, class Compare, class Allocator>
	template< class InputIt >
	void _MAP::insert(InputIt first, InputIt last) {
		for (;first != last; ++first)
			_data.insert(*first);
	}

	template<class Key, class T, class Compare, class Allocator>
	typename _MAP::iterator _MAP::insert(iterator pos, const value_type& value) {
		(void)pos;
		return _data.insert(value).first;
	}

	template<class Key, class T, class Compare, class Allocator>
	T& _MAP::at(const Key& key) {
		Node<value_type>* x = search(key);
		if (x == _data.get_nil())
			throw std::out_of_range("key not found!");
		return x->_value.second;
	}

	template<class Key, class T, class Compare, class Allocator>
	const T& _MAP::at(const Key& key) const {
		Node<value_type>* x = search(key);
		if (x == _data.get_nil())
			throw std::out_of_range("key not found!");
		return x->_value.second;
	}

	template<class Key, class T, class Compare, class Allocator>
	Node<typename _MAP::value_type>* _MAP::search(const Key& key) const { 
		Node<value_type>* x = _data.get_root();
		Compare c;
		while (x != _data.get_nil() && !(!c(key, x->_value.first) && !c(x->_value.first, key))) {
			if (c(key, x->_value.first))
				x = x->_left;
			else
				x = x->_right;
		}
		return x;
	}

	template<class Key, class T, class Compare, class Allocator>
	Node<typename _MAP::value_type>* _MAP::_lower_bound(const Key& key) const {
		Compare c;
		Node<value_type>* x;
		Node<value_type>* res = _data.tree_minimum(_data.get_root());
		difference_type count, step;
		count = _data.get_size();

		while (count > 0) {
			x = res;
			step = count / 2;
			for (long i = 0; i < step; ++i)
				x = _data.tree_successor(x);
			if (c(x->_value.first, key)) {
				x = _data.tree_successor(x);
				res = x;
				count -= step + 1;
			} else
				count = step;
		}
		return res;
	}

	template<class Key, class T, class Compare, class Allocator>
	Node<typename _MAP::value_type>* _MAP::_upper_bound(const Key& key) const {
		Compare c;
		Node<value_type>* x;
		Node<value_type>* res = _data.tree_minimum(_data.get_root());
		difference_type count, step;
		count = _data.get_size();

		while (count > 0) {
			x = res;
			step = count / 2;
			for (long i = 0; i < step; ++i)
				x = _data.tree_successor(x);
			if (!c(key, x->_value.first)) {
				x = _data.tree_successor(x);
				res = x;
				count -= step + 1;
			} else
				count = step;
		}
		return res;
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator==(const ft::map<Key, T, Compare, Alloc>& lhs, \
				const ft::map<Key, T, Compare, Alloc>& rhs) {
		if (lhs.size() != rhs.size())
			return false;
		typename ft::map<Key, T, Compare, Alloc>::const_iterator lit = lhs.begin();
		typename ft::map<Key, T, Compare, Alloc>::const_iterator rit = rhs.begin();
		while (lit != lhs.end() && rit != rhs.end()) {
			if (!(lit->first == rit->first) || !(lit->second == rit->second))
				return false;
			++lit;
			++rit;
		}
		return true;
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator!=(const ft::map<Key, T, Compare, Alloc>& lhs,
				const ft::map<Key, T, Compare, Alloc>& rhs) {
		return !(lhs == rhs);
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator<(const ft::map<Key, T, Compare, Alloc>& lhs,
				const ft::map<Key, T, Compare, Alloc>& rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator<=(const ft::map<Key, T, Compare, Alloc>& lhs,
				const ft::map<Key, T, Compare, Alloc>& rhs) {
		return !(rhs < lhs);
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator>(const ft::map<Key, T, Compare, Alloc>& lhs,
				const ft::map<Key, T, Compare, Alloc>& rhs) {
		return rhs < lhs;
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator>=(const ft::map<Key, T, Compare, Alloc>& lhs,
				const ft::map<Key, T, Compare, Alloc>& rhs) {
		return !(lhs < rhs);
	}

	template<class Key, class T, class Compare, class Alloc>
	void swap(ft::map<Key, T, Compare, Alloc>& lhs,
			ft::map<Key, T, Compare, Alloc>& rhs) {
		lhs.swap(rhs);
	}
}

#endif