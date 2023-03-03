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

	std::vector<int> c(5, 0);
	c.push_back(1);
	c.push_back(1);

	std::cout << c.max_size()  <<'\n';

	ft::vector<int> test3(5, 0);
	ft::vector<int> test4(test3);

	test3 = test4;

	test4.assign(10, 42);

	std::cout << test4.at(5) << '\n';

	const ft::vector<int> test5(test4);

	std::cout << test5.max_size() << '\n';

	return 0;
}
