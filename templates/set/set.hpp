#pragma once

#include <functional>
#include <memory>
#include <stdexcept>
#include "../other/utility.hpp"
#include "../other/red_black_tree.hpp"
#include "../iterators/map_iterator.hpp"
#include "../iterators/reverse_iterator.hpp"
#include "../other/algorithm.hpp"

#define _SET set<Key, Compare, Allocator>

namespace ft {
	template<class Key, class Compare = std::less<Key>, \
	class Allocator = std::allocator<Key> >
	class set {
		public:
			typedef Key											key_type;
			typedef Key											value_type;
			typedef unsigned long								size_type;
			typedef long										difference_type;
			typedef Compare										key_compare;
			typedef Compare										value_compare;
			typedef Allocator									allocator_type;
			typedef value_type&									reference;
			typedef const value_type&							const_reference;
			typedef typename Allocator::pointer					pointer;
			typedef typename Allocator::const_pointer			const_pointer;
			typedef map_iterator<const value_type, Node<value_type> >	iterator;
			typedef map_iterator<const value_type, Node<value_type> >	const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
		protected:
			typedef typename Allocator::template rebind<Node<value_type> >::other	Node_alloc;
			Compare			_comp;
			Allocator		_alloc;
			Rbt<value_type, Compare, Node_alloc>	_data;
		public:
			set(): _comp(Compare()), _alloc(Allocator()), _data(_comp) {}
			explicit set(const Compare& comp, const Allocator& alloc = Allocator()): \
				_comp(comp), _alloc(alloc), _data(_comp) {}
			template< class InputIt >
			set(InputIt first, InputIt last, const Compare& comp = Compare(), \
				const Allocator& alloc = Allocator());
			set(const set& other): _comp(other._comp), _alloc(other._alloc), \
				_data(other._data) {}
			~set() {}
			set& operator=(const set& other);
			allocator_type	get_allocator() const {return _alloc;}
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
			ft::pair<iterator, bool> insert(const value_type& value);
			iterator		insert(iterator pos, const value_type& value);
			template<class InputIt>
			void			insert(InputIt first, InputIt last);
			iterator		erase(iterator pos);
			iterator		erase(iterator first, iterator last);
			size_type		erase(const Key& key);
			void			swap(set& other) {_data.swap(other._data);}
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

			private:
				Node<value_type>*	search(const Key& key) const;
				Node<value_type>*	_lower_bound(const Key& key) const;
				Node<value_type>*	_upper_bound(const Key& key) const;
	};

	template<class Key, class Compare, class Allocator>
	template< class InputIt >
	_SET::set(InputIt first, InputIt last, const Compare& comp, const Allocator& alloc): \
			_comp(comp), _alloc(alloc), _data(_comp) {
		insert(first, last);
	}

	template<class Key, class Compare, class Allocator>
	set<Key, Compare, Allocator>& _SET::operator=(const set& other) {
		if (this != &other) {
			_comp = other._comp;
			_alloc = other._alloc;
			_data = other._data;
		}
		return *this;
	}

	template<class Key, class Compare, class Allocator>
	ft::pair<typename _SET::iterator, bool> _SET::insert(const value_type& value) {
		ft::pair<Node<typename _SET::value_type>*, bool> tmp = _data.insert(value);
		return ft::make_pair(iterator(tmp.first, _data.get_nil()), tmp.second);
	}

	template<class Key, class Compare, class Allocator>
	template< class InputIt >
	void _SET::insert(InputIt first, InputIt last) {
		for (;first != last; ++first)
			_data.insert(*first);
	}

	template<class Key, class Compare, class Allocator>
	typename _SET::iterator _SET::insert(iterator pos, const value_type& value) {
		(void)pos;
		return iterator(_data.insert(value).first, _data.get_nil());
	}

	template<class Key, class Compare, class Allocator>
	typename _SET::size_type _SET::erase(const Key& key) {
		Node<value_type>* n = search(key);
		if (n == _data.get_nil())
			return 0;
		_data.rb_delete(n);
		return 1;
	}

	template<class Key, class Compare, class Allocator>
	typename _SET::iterator _SET::erase(iterator first, iterator last) {
		Node<value_type>* n = search(*first);
		Node<value_type>* tmp;
		for (; first != last;) {
			tmp = _data.tree_successor(n);
			++first;
			_data.rb_delete(n);
			n = tmp;
		}
		return first;
	}

	template<class Key, class Compare, class Allocator>
	typename _SET::iterator _SET::erase(iterator pos) {
		Node<value_type>* n = search(*pos);
		++pos;
		_data.rb_delete(n);
		return pos;
	}

	template<class Key, class Compare, class Allocator>
	Node<typename _SET::value_type>* _SET::search(const Key& key) const { 
		Node<value_type>* x = _data.get_root();
		Compare c;
		while (x != _data.get_nil() && !(!c(key, x->_value) && !c(x->_value, key))) {
			if (c(key, x->_value))
				x = x->_left;
			else
				x = x->_right;
		}
		return x;
	}

	template<class Key, class Compare, class Allocator>
	Node<typename _SET::value_type>* _SET::_lower_bound(const Key& key) const {
		Compare c;
		Node<value_type>* tmp = _data.get_root();
		Node<value_type>* save = _data.get_nil();

		while (tmp != _data.get_nil()) {
			if (!c(tmp->_value, key)) {
				save = tmp;
				tmp = tmp->_left;
			} else {
				tmp = tmp->_right;
			}
		}
		return save;
	}

	template<class Key, class Compare, class Allocator>
	Node<typename _SET::value_type>* _SET::_upper_bound(const Key& key) const {
		Compare c;
		Node<value_type>* tmp = _data.get_root();
		Node<value_type>* save = _data.get_nil();

		while (tmp != _data.get_nil()) {
			if (c(key, tmp->_value)) {
				save = tmp;
				tmp = tmp->_left;
			} else {
				tmp = tmp->_right;
			}
		}
		return save;
	}

	template<class Key, class Compare, class Alloc>
	bool operator==(const ft::set<Key, Compare, Alloc>& lhs, \
				const ft::set<Key, Compare, Alloc>& rhs) {
		if (lhs.size() != rhs.size())
			return false;
		typename ft::set<Key, Compare, Alloc>::const_iterator lit = lhs.begin();
		typename ft::set<Key, Compare, Alloc>::const_iterator rit = rhs.begin();
		while (lit != lhs.end() && rit != rhs.end()) {
			if (!(*lit == *rit) || !(*lit == *rit))
				return false;
			++lit;
			++rit;
		}
		return true;
	}

	template<class Key, class Compare, class Alloc>
	bool operator!=(const ft::set<Key, Compare, Alloc>& lhs,
				const ft::set<Key, Compare, Alloc>& rhs) {
		return !(lhs == rhs);
	}

	template<class Key, class Compare, class Alloc>
	bool operator<(const ft::set<Key, Compare, Alloc>& lhs,
				const ft::set<Key, Compare, Alloc>& rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template<class Key, class Compare, class Alloc>
	bool operator<=(const ft::set<Key, Compare, Alloc>& lhs,
				const ft::set<Key, Compare, Alloc>& rhs) {
		return !(rhs < lhs);
	}

	template<class Key, class Compare, class Alloc>
	bool operator>(const ft::set<Key, Compare, Alloc>& lhs,
				const ft::set<Key, Compare, Alloc>& rhs) {
		return rhs < lhs;
	}

	template<class Key, class Compare, class Alloc>
	bool operator>=(const ft::set<Key, Compare, Alloc>& lhs,
				const ft::set<Key, Compare, Alloc>& rhs) {
		return !(lhs < rhs);
	}

	template<class Key, class Compare, class Alloc>
	void swap(ft::set<Key, Compare, Alloc>& lhs,
			ft::set<Key, Compare, Alloc>& rhs) {
		lhs.swap(rhs);
	}
}