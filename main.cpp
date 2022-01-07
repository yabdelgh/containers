#include <iostream>
#include "vector.hpp"
#include <vector>

int main()
{
	ft::vector<int> name1(1999);
	std::vector<int> name2(1999);
	
	std::cout << name1.size() << std::endl;
	std::cout << name1.max_size() << std::endl;
	std::cout << name1.capacity() << std::endl;
	std::cout << name1.empty() << std::endl;
	std::cout << "||||||||||||||||||||||||||||||||||" << std::endl;
	std::cout << name2.size() << std::endl;
	std::cout << name2.max_size() << std::endl;
	std::cout << name2.capacity() << std::endl;
	std::cout << name2.empty() << std::endl;
	
	return (0);
}
