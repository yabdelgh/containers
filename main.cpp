#include <iostream>
#include "vector.hpp"
#include <vector>

int main()
{
	ft::vector<int> name1(1999);
	std::vector<int> name2(1999);

	std::cout << name1[9999999] << std::endl;
//	std::cout << name2[9999999] << std::endl;
	
	return (0);
}
