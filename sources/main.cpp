
#include "map.hpp"
#include <string>
#include <iostream>
#include <map>

int main() {
	ft::map<int, std::string> test;

	test.insert(ft::make_pair(1, "hello"));
	test.insert(ft::make_pair(2, "world"));
	test.insert(ft::make_pair(-5, "bla_bla"));

	ft::map<int, std::string> test2(test);
//	test2 = test;
	ft::map<int, std::string>::iterator it = test2.begin();

	for (; it != test2.end(); ++it)
		std::cout << (*it).second << '\n';

//	int x = 2;
	std::map<int, std::string> test3;
	std::cout << test3.max_size() << '\n' << test2.max_size() << '\n';

	return 0;
}
