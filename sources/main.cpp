#include "ft_containers.hpp"


class bla {
	public:
		int a;
		int b;
	bla(): a(42), b(21) {}
};


int main(void) {
	std::cout << "containers!\n";

//	ft::vector<bla> test;
//	test.push_back(bla());
//	ft::vector<bla>::reverse_iterator rit = test.rbegin();
//	std::cout << rit->a;



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

//	ft::vector<int>::reverse_iterator rit = test4.rbegin();
//	std::cout << *rit << '\n';

	const ft::vector<int> test3(test4);

	ft::vector<int>::reverse_iterator it_test = test4.rbegin();
	ft::vector<int>::const_reverse_iterator it(it_test);

	it_test++;
	if (it_test > it)
		std::cout << "it works!\n";

	for (; it < test4.rend(); ++it) {
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
