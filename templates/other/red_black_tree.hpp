#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include "node.hpp"

#define _RBT Rbt<T, Compare, Allocator>

namespace ft {
	template <class T, class Compare, class Allocator>
	class Rbt {
		public:
			typedef unsigned long size_type;
		private:
			Node<T>*	_root;
			Node<T>*	_nil;
			Compare		_comp;
			Allocator	_alloc;
			size_type	_size;
		public:
			Rbt();
//			Rbt(const Rbt& other);//do it later!!
			~Rbt();
//			Rbt& operator=(const Rbt& other);//do it later!

			size_type	get_size() const;
			void		insert(T& val);
			Node<T>*	tree_search(T& key);
			Node<T>*	tree_minimum(Node<T>* x);
			Node<T>*	tree_maximum(Node<T>* x);
			Node<T>*	tree_successor(Node<T>* x);
			Node<T>*	tree_predecessor(Node<T>* x);

		private:
			void		delete_tree(Node<T>* x);
			void		left_rotate(Node<T>* x);
			void		right_rotate(Node<T>* x);
			void		insert_fixup(Node<T>* z);
			void		transplant(Node<T>* u, Node<T>* v);
	};

	template <class T, class Compare, class Allocator>
	_RBT::Rbt(): _comp(Compare()), _alloc(_alloc()), _size(0) {
		_nil = _alloc.allocate(1);
		_root = _nil;
		_nil->_is_red = _nil->_parent = 0;
		_nil->_right = _nil->_left = _root;
	}

	template <class T, class Compare, class Allocator>
	_RBT::~Rbt() {
		if (_root != _nil)
			delete_tree(_root);
		_alloc.deallocate(_nil);
	}
}

#endif