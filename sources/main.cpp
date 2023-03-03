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

	std::cout << c.capacity() << ' ' << c.size() <<'\n';

	c.push_back(1);
	c.push_back(1);

	std::cout << c.capacity() << ' ' << c.size() <<'\n';

	ft::vector<int> test3((unsigned long)5, 0);
	ft::vector<int> test4(test3);

	return 0;
}
