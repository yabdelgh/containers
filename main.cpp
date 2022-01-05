#include <iostream>
#include "vector.hpp"
#include <vector>

int main()
{
	ft::vector<int> name(10);
	
	std::cout << name.size() << std::endl;
	std::cout << name.capacity() << std::endl;
	return (0);
}
