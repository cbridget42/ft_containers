#pragma once

namespace ft {

	template <class T>
	struct Node {
		T		_value;
		Node*	_right;
		Node*	_left;
		Node*	_parent;
		bool	_is_red;

		Node(const T& val = T(), bool c = 0): _value(val), _right(0), _left(0), \
			_parent(0), _is_red(c) {}
		Node(const Node& other): _value(other._value), \
			_right(other._right), _left(other._left), \
			_parent(other._parent), _is_red(other._is_red) {}
		~Node() {}
		Node& operator=(const Node& other) {
			if (this != &other) {
				_value = other._value;
				_right = other._right;
				_left = other._left;
				_parent = other._parent;
				_is_red = other._is_red;
			}
			return *this;
		}
	};

}
