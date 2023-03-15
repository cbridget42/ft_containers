
#include "map.hpp"
#include <string>

int main() {
	ft::map<int, int> test;

	ft::pair<ft::map<int, int>::iterator, bool> t(test.begin(), true);

	ft::pair<ft::map<int, int>::iterator, bool> t2(t);

//	ft::map<int, std::string>::iterator it = test.begin();
//	(void)it;
//	test.insert(ft::make_pair(1, 2));

	return 0;
}