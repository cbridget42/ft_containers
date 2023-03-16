
#include "map.hpp"
#include <string>
#include <iostream>
#include <map>

int main() {
	ft::map<int, std::string> test;

	test.insert(ft::make_pair(1, "hello"));
	test.insert(ft::make_pair(2, "world"));
	test.insert(ft::make_pair(5, "bla_bla"));
	test.insert(ft::make_pair(7, "ha_ha"));

	ft::map<int, std::string> test2(test);

//	test2[2] = "lsadifjasdfj";
//	test2.insert(ft::make_pair(10, "ha_ha_ha"));

	if (test < test2)
		std::cout << "good!\n";

//	std::cout << test2.find(5)->second << '\n';

	return 0;
}
