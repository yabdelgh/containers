#include <iostream>
#include "vector.hpp"
#include <vector>

int main()
{
	ft::vector<int> my(10);

	std::cout << my.front() << std::endl;
	std::cout << my.back() << std::endl;
	std::cout << my[9] << std::endl;
	try
	{
		std::cout << my.at(66666) << std::endl;
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}
