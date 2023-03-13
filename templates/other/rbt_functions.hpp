#ifndef RBT_FUNCTIONS_HPP
#define RBT_FUNCTIONS_HPP

#include "red_black_tree.hpp"

namespace ft {

	template <class T, class Compare, class Allocator>
	Node<T>* _RBT::tree_search(T& key) {
		Node<T>* x = _root;
		while (x != _nil && !(!_comp(key, x->_value) && !_comp(x->_value, key))) {
			if (_comp(key, x->_value))
				x = x->_left;
			else
				x = x->_right;
		}
		return x;
	}

	template <class T, class Compare, class Allocator>
	Node<T>* _RBT::tree_minimum(Node<T>* x) {
		while (x->_left != _nil)
			x = x->_left;
		return x;
	}

	template <class T, class Compare, class Allocator>
	Node<T>* _RBT::tree_maximum(Node<T>* x) {
		while (x->_right != _nil)
			x = x->_right;
		return x;
	}

	template <class T, class Compare, class Allocator>
	Node<T>* _RBT::tree_successor(Node<T>* x) {//next element
		if (x->_right != _nil)
			return tree_minimum(x->_right);
		Node<T>* y = x->_parent;
		while (y != _nil && x == y->_right) {
			x = y;
			y = y->_parent;
		}
		return y;
	}

	template <class T, class Compare, class Allocator>
	Node<T>* _RBT::tree_predecessor(Node<T>* x) {//previous element
		if (x->_left != _nil)
			return tree_maximum(x->_left);
		Node<T>* y = x->_parent;
		while (y != _nil && x == y->_left) {
			x = y;
			y = y->_parent;
		}
		return y;
	}

	template <class T, class Compare, class Allocator>
	void _RBT::delete_tree(Node<T>* x) {
		if (x->_left != _nil)
			delete_tree(x->_left);
		if (x->_right != _nil)
			delete_tree(x->_right);
		_alloc.destroy(x->_value);
		_alloc.deallocate(x, 1);
	}

	template <class T, class Compare, class Allocator>
	void _RBT::left_rotate(Node<T>* x) {
		Node<T>* y = x->_right;
		x->_right = y->_left;
		if (y->_left != _nil)
			y->_left->_parent = x;

		y->_parent = x->_parent;
		if (x->_parent == _nil)
			_root = y;
		else if (x == x->_parent->_left)
			x->_parent->_left = y;
		else
			x->_parent->_right = y;
		y->_left = x;
		x->_parent = y;
	}

	template <class T, class Compare, class Allocator>
	void _RBT::right_rotate(Node<T>* x) {
		Node<T>* y = x->_left;
		x->_left = y->_right;
		if (y->_right != _nil)
			y->_right->_parent = x;

		y->_parent = x->_parent;
		if (x->_parent == _nil)
			_root = y;
		else if (x == x->_parent->_right)
			x->_parent->_right = y;
		else
			x->_parent->_left = y;
		y->_right = x;
		x->_parent = y;
	}

}

#endif