#include <iostream>
#include "vector.hpp"
#include <vector>

int main()
{
	ft::vector<int> name1(1999);
	std::vector<int> name2(1999);
	try
	{
		std::cout << name2.at(9999) << std::endl;
	}
	catch (std::out_of_range & e)
	{
		std::cout << e.what() << std::endl;
	}
	
	return (0);
}
