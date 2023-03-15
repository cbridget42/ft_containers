#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include "node.hpp"
#include "utility.hpp"
#include "map_iterator.hpp"

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
//			Rbt(const Rbt& other);//do it later!!
			~Rbt();
//			Rbt& operator=(const Rbt& other);//do it later!

			size_type	get_size() const;
			Node<T>*	get_nil() const;
			Node<T>*	get_root() const;
			void		rb_delete(Node<T>* z);
			Node<T>*	tree_search(const T& key);
			Node<T>*	tree_minimum(Node<T>* x);
			Node<T>*	tree_maximum(Node<T>* x);
			Node<T>*	tree_successor(Node<T>* x);
			Node<T>*	tree_predecessor(Node<T>* x);
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