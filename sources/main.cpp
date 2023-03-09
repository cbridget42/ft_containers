#include "ft_containers.hpp"
#include <vector>


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

//int main(void) {
//	std::cout << "containers!\n";

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

/*	std::vector<int> test4;

	test4.push_back(42);
	test4.push_back(14);
	test4.push_back(88);
	test4.push_back(123);
	test4.push_back(21);

//	const ft::vector<int> test5(test4.begin() + 1, test4.end() - 1);

//	test5.push_back(4);

//	if (test4 >= test5)
//		std::cout << "dude!\n";

//	std::cout << !ft::is_integral<bla_bla>::value;

//	test5.assign(test4.begin() + 1, test4.end() - 1);

//	test4.at(1) = 21;

//	std::cout << *(test4.insert(test4.begin() + 2, 6)) << '\n';
//	test4.erase(test4.begin() + 1, test4.end());

	std::cout << *(test4.erase(test4.begin() + 1, test4.begin() + 3)) << '\n';

	for (unsigned int i = 0; i < test4.size(); ++i)
		std::cout << test4[i] << ' ';
*/
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

//	std::cout << '\n';

//	std::cout << "capacity: " << test3.capacity() << '\n';

//	return 0;
//}

#define TESTED_NAMESPACE ft
#define TESTED_TYPE foo<int>
#define T_SIZE_TYPE typename TESTED_NAMESPACE::vector<T>::size_type
#include <list>

template <typename T>
class foo {
	public:
		typedef T	value_type;

		foo(void) : value(), _verbose(false) { };
		foo(value_type src, const bool verbose = false) : value(src), _verbose(verbose) { };
		foo(foo const &src, const bool verbose = false) : value(src.value), _verbose(verbose) { };
		~foo(void) { if (this->_verbose) std::cout << "~foo::foo()" << std::endl; };
		void m(void) { std::cout << "foo::m called [" << this->value << "]" << std::endl; };
		void m(void) const { std::cout << "foo::m const called [" << this->value << "]" << std::endl; };
		foo &operator=(value_type src) { this->value = src; return *this; };
		foo &operator=(foo const &src) {
			if (this->_verbose || src._verbose)
				std::cout << "foo::operator=(foo) CALLED" << std::endl;
			this->value = src.value;
			return *this;
		};
		value_type	getValue(void) const { return this->value; };
		void		switchVerbose(void) { this->_verbose = !(this->_verbose); };

		operator value_type(void) const {
			return value_type(this->value);
		}
	private:
		value_type	value;
		bool		_verbose;
};

template <typename T>
std::ostream	&operator<<(std::ostream &o, foo<T> const &bar) {
	o << bar.getValue();
	return o;
}

template <typename T>
void	printSize(TESTED_NAMESPACE::vector<T> const &vct, bool print_content = true)
{
	const T_SIZE_TYPE size = vct.size();
	const T_SIZE_TYPE capacity = vct.capacity();
	const std::string isCapacityOk = (capacity >= size) ? "OK" : "KO";
	// Cannot limit capacity's max value because it's implementation dependent

	std::cout << "size: " << size << std::endl;
	std::cout << "capacity: " << isCapacityOk << std::endl;
	std::cout << "max_size: " << vct.max_size() << std::endl;
	if (print_content)
	{
		typename TESTED_NAMESPACE::vector<T>::const_iterator it = vct.begin();
		typename TESTED_NAMESPACE::vector<T>::const_iterator ite = vct.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << *it << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

int		main(void)
{
	const int size = 5;
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct(size);
	TESTED_NAMESPACE::vector<TESTED_TYPE>::reverse_iterator it(vct.rbegin());
	TESTED_NAMESPACE::vector<TESTED_TYPE>::const_reverse_iterator ite(vct.rend());

	for (int i = 1; it != ite; ++i)
		*it++ = (i * 7);
	printSize(vct, 1);

	it = vct.rbegin();
	ite = vct.rbegin();

	std::cout << *(++ite) << std::endl;
	std::cout << *(ite++) << std::endl;
	std::cout << *ite++ << std::endl;
	std::cout << *++ite << std::endl;

	it->m();
	ite->m();

	std::cout << *(++it) << std::endl;
	std::cout << *(it++) << std::endl;
	std::cout << *it++ << std::endl;
	std::cout << *++it << std::endl;

	std::cout << *(--ite) << std::endl;
	std::cout << *(ite--) << std::endl;
	std::cout << *--ite << std::endl;
	std::cout << *ite-- << std::endl;

	(*it).m();
	(*ite).m();

	std::cout << *(--it) << std::endl;
	std::cout << *(it--) << std::endl;
	std::cout << *it-- << std::endl;
	std::cout << *--it << std::endl;

	return (0);
}
