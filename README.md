# ft_containers
The standard C++ containers have all a specific usage.  
To make sure you understand them, let’s re-implement them!

### Summary:
In this project, you will implement a few container types of the C++ standard  
template library.  
You have to take the structure of each standard container as reference.  

### Requirements:
* vector (You don’t have to do the vector<bool> specialization.)
* map
* stack (It will use your vector class as default underlying container.  
  But it must still be compatible with other containers, the STL ones included.)
* std::iterator_traits
* std::reverse_iterator
* std::enable_if
* std::is_integral
* std::equal and/or std::lexicographical_compare
* std::pair
* std::make_pair

You can see the full assignment here [subject](https://github.com/cbridget42/ft_containers/blob/main/subject/en.subject.pdf)

### Usage:
Include the header of the container you need and use it like a usual STL container!
simple code example:
```c++
#include <iostream>
#include "vector.hpp"

int main() {
	ft::vector<int> v(5, 42);
	std::cout << v.back() << std::endl;
	std::cout << v.size() << std::endl;
	return 0;
}
```
output:
```bash
42
5
```