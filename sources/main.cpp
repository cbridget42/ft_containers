#include "ft_containers.hpp"

int main(void) {
	std::cout << "containers!\n";

	ft::stack<int> test1;
	ft::stack<int> test2;

	test1.push(1);
	test2.push(1);
	test2.push(2);

	if (test1 >= test2)
		std::cout << "dude!\n";

	ft::vector<int> test4;

	test4.push_back(42);
	test4.push_back(14);
	test4.push_back(88);

	const ft::vector<int> test3(test4);

	for (ft::vector<int>::const_iterator it = test3.begin(); it < test3.end(); ++it) {
		std::cout << *it << ' ';
	}
/*	std::cout << '\n';
	for (unsigned int i = 0; i < test4.size(); ++i) {
		std::cout << test4[i] << ' ';
	}*/

	std::cout << '\n';


//	std::cout << "capacity: " << test3.capacity() << '\n';

	return 0;
}
