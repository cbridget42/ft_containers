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

	return 0;
}
