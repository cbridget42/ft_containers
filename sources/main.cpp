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

	ft::vector<int> test3;
	ft::vector<int> test4;

	test3.push_back(42);
	test3.resize(5, 21);

	test4.push_back(14);
	test4.push_back(88);

	for (unsigned int i = 0; i < test3.size(); ++i) {
		std::cout << test3[i] << ' ';
	}
	std::cout << '\n';
	for (unsigned int i = 0; i < test4.size(); ++i) {
		std::cout << test4[i] << ' ';
	}

	test3.swap(test4);
	std::cout << "\n\n";
	for (unsigned int i = 0; i < test3.size(); ++i) {
		std::cout << test3[i] << ' ';
	}
	std::cout << '\n';
	for (unsigned int i = 0; i < test4.size(); ++i) {
		std::cout << test4[i] << ' ';
	}
	std::cout << '\n';

//	std::cout << "capacity: " << test3.capacity() << '\n';

	return 0;
}
