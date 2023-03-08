#include "ft_containers.hpp"


class bla {
	public:
		int a;
		int b;
	bla(): a(42), b(21) {}
};

class bla_bla {
	public:
		int *x;
		static int y;
		bla_bla() {x = new int;}
		bla_bla(const bla_bla& other) {
			(void)other;
			if (y == 12)
				throw 5;
			x = new int;
			y++;
		}
		bla_bla& operator=(const bla_bla& rhs) {
			if (this != &rhs) {
				delete x;
				x = new int;
			}
			return *this;
		}
		~bla_bla() {delete x;}
};

int bla_bla::y = 0;

int main(void) {
	std::cout << "containers!\n";

//	ft::vector<bla> test;
//	test.push_back(bla());
//	ft::vector<bla>::reverse_iterator rit = test.rbegin();
//	std::cout << rit->a;

/*	ft::vector<bla_bla> v1;
	v1.push_back(bla_bla());
	v1.push_back(bla_bla());
	v1.push_back(bla_bla());
	v1.push_back(bla_bla());
	v1.push_back(bla_bla());
	v1.erase(v1.begin() + 1, v1.end());*/
//	try {
//		v1.insert(v1.begin() + 1, 3, bla_bla());
//	} catch (int) {
//		std::cout << "exception caught!";
//	}

//	std::cout << v1[0].y;

/*	ft::stack<int> test1;
	ft::stack<int> test2;

	test1.push(1);
	test2.push(1);
	test2.push(2);

	if (test1 >= test2)
		std::cout << "dude!\n";*/

	ft::vector<int> test4;

	test4.push_back(42);
	test4.push_back(14);
	test4.push_back(88);
	test4.push_back(123);
	test4.push_back(21);

	ft::vector<int> test5(test4);

//	test5.push_back(4);

	if (test4 >= test5)
		std::cout << "dude!\n";

//	test4.at(1) = 21;

//	std::cout << *(test4.insert(test4.begin() + 2, 6)) << '\n';
//	test4.erase(test4.begin() + 1, test4.end());

//	for (unsigned int i = 0; i < test4.size(); ++i)
//		std::cout << test4[i] << ' ';

//	ft::vector<int>::reverse_iterator rit = test4.rbegin();
//	std::cout << *rit << '\n';

/*	const ft::vector<int> test3(test4);

	ft::vector<int>::reverse_iterator it_test = test4.rbegin();
	ft::vector<int>::const_reverse_iterator it(it_test);

	it_test++;
	if (it_test > it)
		std::cout << "it works!\n";

	for (; it < test4.rend(); ++it) {
		std::cout << *it << ' ';
	}*/
/*	std::cout << '\n';
	for (unsigned int i = 0; i < test4.size(); ++i) {
		std::cout << test4[i] << ' ';
	}*/

	std::cout << '\n';

//	std::cout << "capacity: " << test3.capacity() << '\n';

	return 0;
}
