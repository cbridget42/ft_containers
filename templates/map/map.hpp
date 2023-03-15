#ifndef MAP_HPP
#define MAP_HPP

#include <functional>
#include <memory>
#include <stdexcept>
#include "utility.hpp"
#include "red_black_tree.hpp"
#include "map_iterator.hpp"
#include "reverse_iterator.hpp"

#define MAP map<Key, T, Compare, Allocator>

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
			typedef map_iterator<T, Node<value_type> >			iterator;
			typedef map_iterator<const T, Node<value_type> >	const_iterator;
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
			Rbt<value_type, value_compare, Node_alloc >	_data;
		public:
			map(): _comp(Compare()), _alloc(Allocator()), _data(_comp) {}
			explicit map(const Compare& comp, const Allocator& alloc = Allocator()): \
					_comp(comp), _alloc(alloc), _data(comp) {}
/*			template< class InputIt >
			map(InputIt first, InputIt last, const Compare& comp = Compare(), \
				const Allocator& alloc = Allocator());
			map(const map& other);do it later!*/
			~map() {}
//			map&			operator=(const map& other); do it later!
//			T&				operator[](const Key& key); do it later!

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


			ft::pair<iterator, bool> insert(const value_type& value) {return _data.insert(value);}
			iterator		insert(iterator pos, const value_type& value);
			template< class InputIt >
			void			insert(InputIt first, InputIt last);
	};

	template<class Key, class T, class Compare, class Allocator>
	template< class InputIt >
	void MAP::insert(InputIt first, InputIt last) {
		for (;first != last; ++first)
			_data.insert(*first);
	}

	template<class Key, class T, class Compare, class Allocator>
	typename MAP::iterator MAP::insert(iterator pos, const value_type& value) {
		(void)pos;
		return _data.insert(value).first;
	}

	template<class Key, class T, class Compare, class Allocator>
	T& MAP::at(const Key& key) {
		Node<value_type>* x = _data.tree_search(key);
		if (x == _data.get_nil())
			throw std::out_of_range("key not found!");
		return x->_value.second;
	}

	template<class Key, class T, class Compare, class Allocator>
	const T& MAP::at(const Key& key) const {
		Node<value_type>* x = _data.tree_search(key);
		if (x == _data.get_nil())
			throw std::out_of_range("key not found!");
		return x->_value.second;
	}
}

#endif