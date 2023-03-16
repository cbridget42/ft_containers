#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include "node.hpp"
#include "utility.hpp"
#include "map_iterator.hpp"
#include <limits>

#define _RBT Rbt<T, Compare, Allocator>

namespace ft {
	template <class T, class Compare, class Allocator>
	class Rbt {
		public:
			typedef unsigned long				size_type;
			typedef map_iterator<T, Node<T> >	iterator;
		private:
			Node<T>*	_root;
			Node<T>*	_nil;
			Compare		_comp;
			Allocator	_alloc;
			size_type	_size;
		public:
			Rbt(Compare c);
			Rbt(const Rbt& other);
			~Rbt();
			Rbt& operator=(const Rbt& other);

			void		clear();
			void		swap(Rbt& other);
			size_type	get_size() const;
			size_type	max_size() const;
			Node<T>*	get_nil() const;
			Node<T>*	get_root() const;
			void		rb_delete(Node<T>* z);
			Node<T>*	tree_search(const T& key) const;
			Node<T>*	tree_minimum(Node<T>* x) const;
			Node<T>*	tree_maximum(Node<T>* x) const;
			Node<T>*	tree_successor(Node<T>* x) const;
			Node<T>*	tree_predecessor(Node<T>* x) const;
			ft::pair<iterator, bool> insert(const T& val);

		private:
			void		delete_tree(Node<T>* x);
			void		left_rotate(Node<T>* x);
			void		right_rotate(Node<T>* x);
			void		insert_fixup(Node<T>* z);
			void		transplant(Node<T>* u, Node<T>* v);
			void		rb_delete_fixup(Node<T>* x);
	};

	template <class T, class Compare, class Allocator>
	Rbt<T, Compare, Allocator>& _RBT::operator=(const Rbt& other) {
		if (this != &other) {
			if (_nil && _root != _nil)
				delete_tree(_root);
			if (_nil)
				_alloc.deallocate(_nil, 1);
			_comp = other._comp;
			_alloc = other._alloc;
			_nil = _alloc.allocate(1);
			_root = _nil;
			_nil->_is_red = 0;
			_nil->_parent = 0;
			_nil->_right = _nil->_left = _root;
			_size = 0;
			iterator it(other._nil, other._nil);
			iterator e_it(other._nil, other._nil);
			++it;
			for (; it != e_it; ++it)
				insert(*it);
		}
		return *this;
	}

	template <class T, class Compare, class Allocator>
	_RBT::Rbt(const Rbt& other): _nil(0), _comp(other._comp), _alloc(other._alloc), 
			_size(0) {
		*this = other;
	}

	template <class T, class Compare, class Allocator>
	_RBT::Rbt(Compare c): _comp(c), _alloc(Allocator()), _size(0) {
		_nil = _alloc.allocate(1);
		_root = _nil;
		_nil->_is_red = 0;
		_nil->_parent = 0;
		_nil->_right = _nil->_left = _root;
	}

	template <class T, class Compare, class Allocator>
	_RBT::~Rbt() {
		if (_root != _nil)
			delete_tree(_root);
		_alloc.deallocate(_nil, 1);
	}
}

#include "rbt_functions.hpp"

#endif