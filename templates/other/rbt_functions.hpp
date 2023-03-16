#ifndef RBT_FUNCTIONS_HPP
#define RBT_FUNCTIONS_HPP

namespace ft {

	template <class T, class Compare, class Allocator>
	void _RBT::swap(Rbt& other) {
		Node<T>*	tmp_root = other._root;
		Node<T>*	tmp_nil = other._nil;
		Compare		tmp_comp = other._comp;
		Allocator	tmp_alloc = other._alloc;
		size_type	tmp_size = other._size;

		other._root = _root;
		other._nil = _nil;
		other._comp = _comp;
		other._alloc = _alloc;
		other._size = _size;

		_root = tmp_root;
		_nil = tmp_nil;
		_comp = tmp_comp;
		_alloc = tmp_alloc;
		_size = tmp_size;
	}

	template <class T, class Compare, class Allocator>
	void _RBT::clear() {
		if (_root != _nil) {
			delete_tree(_root);
			_root = _nil;
			_nil->_left = _nil->_right = _root;
			_size = 0;
		}
	}
	
	template <class T, class Compare, class Allocator>
	typename _RBT::size_type _RBT::get_size() const {
		return _size;
	}

	template <class T, class Compare, class Allocator>
	typename _RBT::size_type _RBT::max_size() const {
		return static_cast<size_type>(std::numeric_limits<long>::max() / \
		sizeof(ft::Node<T>));
	}

	template <class T, class Compare, class Allocator>
	Node<T>* _RBT::get_nil() const {
		return _nil;
	}

	template <class T, class Compare, class Allocator>
	Node<T>* _RBT::get_root() const {
		return _root;
	}

	template <class T, class Compare, class Allocator>
	Node<T>* _RBT::tree_search(const T& key) const {
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
	Node<T>* _RBT::tree_minimum(Node<T>* x) const {
		while (x->_left != _nil)
			x = x->_left;
		return x;
	}

	template <class T, class Compare, class Allocator>
	Node<T>* _RBT::tree_maximum(Node<T>* x) const {
		while (x->_right != _nil)
			x = x->_right;
		return x;
	}

	template <class T, class Compare, class Allocator>
	Node<T>* _RBT::tree_successor(Node<T>* x) const {//next element
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
	Node<T>* _RBT::tree_predecessor(Node<T>* x) const {//previous element
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
		_alloc.destroy(x);
		_alloc.deallocate(x, 1);
	}

	template <class T, class Compare, class Allocator>
	void _RBT::left_rotate(Node<T>* x) {
		Node<T>* y = x->_right;
		x->_right = y->_left;
		if (y->_left != _nil)
			y->_left->_parent = x;

		y->_parent = x->_parent;
		if (x->_parent == _nil) {
			_root = y;
			_nil->_right = _nil->_left = _root;
		} else if (x == x->_parent->_left)
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
		if (x->_parent == _nil) {
			_root = y;
			_nil->_right = _nil->_left = _root;
		} else if (x == x->_parent->_right)
			x->_parent->_right = y;
		else
			x->_parent->_left = y;
		y->_right = x;
		x->_parent = y;
	}

	template <class T, class Compare, class Allocator>
	ft::pair<typename _RBT::iterator, bool> _RBT::insert(const T& val) {
		Node<T>* y = _nil;
		Node<T>* x = _root;
		while (x != _nil && !(!_comp(val, x->_value) && !_comp(x->_value, val))) {
			y = x;
			if (_comp(val, x->_value))
				x = x->_left;
			else
				x = x->_right;
		}
		if (x != _nil)
			return ft::make_pair(iterator(x, _nil), false);
		Node<T>* z = _alloc.allocate(1);
		try {
			_alloc.construct(z, Node<T>(val, 1));
		} catch(...) {
			_alloc.deallocate(z, 1);
			throw;
		}
		z->_parent = y;
		if (y == _nil) {
			_root = z;
			_nil->_right = _nil->_left = _root;
		} else if (_comp(z->_value, y->_value))
			y->_left = z;
		else
			y->_right = z;
		z->_left = z->_right = _nil;
		++_size;
		insert_fixup(z);
		return ft::make_pair(iterator(z, _nil), false);
	}

	template <class T, class Compare, class Allocator>
	void _RBT::insert_fixup(Node<T>* z) {
		Node<T>* y;
		while (z != _nil && z->_parent->_is_red) {
			if (z->_parent == z->_parent->_parent->_left) {
				y = z->_parent->_parent->_right;
				if (y->_is_red) {//case 1
					z->_parent->_is_red = 0;
					y->_is_red = 0;
					z->_parent->_parent->_is_red = 1;
					z = z->_parent->_parent;
				} else {//case 3
					if (z == z->_parent->_right) {//case 2
						z = z->_parent;
						left_rotate(z);
					}
					z->_parent->_is_red = 0;
					z->_parent->_parent->_is_red = 1;
					right_rotate(z->_parent->_parent);
				}
			} else {
				y = z->_parent->_parent->_left;
				if (y->_is_red) {
					z->_parent->_is_red = 0;
					y->_is_red = 0;
					z->_parent->_parent->_is_red = 1;
					z = z->_parent->_parent;
				} else {
					if (z == z->_parent->_left) {
						z = z->_parent;
						right_rotate(z);
					}
					z->_parent->_is_red = 0;
					z->_parent->_parent->_is_red = 1;
					left_rotate(z->_parent->_parent);
				}
			}
		}
	}

	template <class T, class Compare, class Allocator>
	void _RBT::transplant(Node<T>* u, Node<T>* v) {
		if (u->_parent == _nil) {
			_root = v;
			_nil->_right = _nil->_left = _root;
		} else if (u == u->_parent->_left)
			u->_parent->_left = v;
		else
			u->_parent->_right = v;
		v->_parent = u->_parent;
	}

	template <class T, class Compare, class Allocator>
	void _RBT::rb_delete(Node<T>* z) {
		Node<T>* y = z;
		Node<T>* x;
		bool orig_color_y = y->_is_red;
		if (z->_left == _nil) {
			x = z->_right;
			transplant(z, z->_right);
		} else if (z->_right == _nil) {
			x = z->_left;
			transplant(z, z->_left);
		} else {
			y = tree_minimum(z->_right);
			orig_color_y = y->_is_red;
			x = y->_right;
			if (y->_parent == z)
				x->_parent = y;
			else {
				transplant(y, y->_right);
				y->_right = z->_right;
				y->_right->_parent = y;
			}
			transplant(z, y);
			y->_left = z->_left;
			y->_left->_parent = y;
			y->_is_red = z->_is_red;
		}
		_alloc.destroy(z);
		_alloc.deallocate(z, 1);
		--_size;
		if (!orig_color_y)
			rb_delete_fixup(x);
	}

	template <class T, class Compare, class Allocator>
	void _RBT::rb_delete_fixup(Node<T>* x) {
		Node<T>* w;
		while (x != _root && !x->_is_red) {
			if (x == x->_parent->_left) {
				w = x->_parent->_right;
				if (w->_is_red) {//case 1
					w->_is_red = 0;
					x->_parent->_is_red = 1;
					left_rotate(x->_parent);
					w = x->_parent->_right;
				}
				if (!w->_left->_is_red && !w->_right->_is_red) {//case 2
					w->_is_red = 1;
					x = x->_parent;
				} else {//case 4
					if (!w->_right->_is_red) {//case 3
						w->_left->_is_red = 0;
						w->_is_red = 1;
						right_rotate(w);
						w = x->_parent->_right;
					}
					w->_is_red = x->_parent->_is_red;
					x->_parent->_is_red = 0;
					w->_right->_is_red = 0;
					left_rotate(x->_parent);
					x = _root;
				}
			} else {
				w = x->_parent->_left;
				if (w->_is_red) {
					w->_is_red = 0;
					x->_parent->_is_red = 1;
					right_rotate(x->_parent);
					w = x->_parent->_left;
				}
				if (!w->_right->_is_red && !w->_left->_is_red) {
					w->_is_red = 1;
					x = x->_parent;
				} else {
					if (!w->_left->_is_red) {
						w->_right->_is_red = 0;
						w->_is_red = 1;
						left_rotate(w);
						w = x->_parent->_left;
					}
					w->_is_red = x->_parent->_is_red;
					x->_parent->_is_red = 0;
					w->_left->_is_red = 0;
					right_rotate(x->_parent);
					x = _root;
				}
			}
		}
		x->_is_red = 0;
	}

}

#endif