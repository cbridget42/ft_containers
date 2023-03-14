
#include <functional>
#include <memory>
#include <iostream>
#include "red_black_tree.hpp"
#include "rbt_functions.hpp"

int main() {
	ft::Rbt<int, std::less<int>, std::allocator<ft::Node<int> > > test;

	for (int i = 0; i < 10; ++i)
		test.insert(i);

	std::cout << "size: " << test.get_size() << '\n';

	ft::Node<int>* x = test.tree_minimum(test.get_root());
//	std::cout << x->_value << ' ';

	test.rb_delete(test.tree_search(5));
	test.rb_delete(test.tree_search(6));

	for (size_t i = 0; i < test.get_size(); ++i) {
		std::cout << x->_value << ' ';
		x = test.tree_successor(x);
	}

	if (x == test.get_nil())
		std::cout << "x = nil!";

	x = test.tree_predecessor(x);

	std::cout << ' ' << x->_value;

	std::cout << std::endl;

	return 0;
}