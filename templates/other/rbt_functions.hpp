#ifndef RBT_FUNCTIONS_HPP
#define RBT_FUNCTIONS_HPP

#include "node.hpp"

namespace ft {

	template <class T, class Compare>
	Node<T>* tree_search(Node<T>* x, T& key, Compare& cmp) {
		while (x != 0 && !(!cmp(key, x->_value) && !cmp(x->_value, key))) {
			if (cmp(key, x->_value))
				x = x->_left;
			else
				x = x->_right;
		}
		return x;
	}

	template <class T>
	Node<T>* tree_minimum(Node<T>* x) {
		while (x->_left)
			x = x->_left;
		return x;
	}

	template <class T>
	Node<T>* tree_maximum(Node<T>* x) {
		while (x->_right)
			x = x->_right;
		return x;
	}

	template <class T>
	Node<T>* tree_successor(Node<T>* x) {//next element
		if (x->_right)
			return tree_minimum(x->_right);
		Node<T>* y = x->_parent;
		while (y && x == y->_right) {
			x = y;
			y = y->_parent;
		}
		return y;
	}

	template <class T>
	Node<T>* tree_predecessor(Node<T>* x) {//previous element
		if (x->_left)
			return tree_maximum(x->_left);
		Node<T>* y = x->_parent;
		while (y && x == y->_left) {
			x = y;
			y = y->_parent;
		}
		return y;
	}

}

#endif