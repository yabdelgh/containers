#include <iostream>
#include <vector>
#include <iterator>
#include "vector.hpp"
int main()
{
	ft::vector<int> my(10,245);
	ft::vector<int>::iterator it = my.begin();
	ft::vector<int>::iterator ite = my.end();

	while (it != ite)
	{
		std::cout << *it << std::endl;
		it++;
	}
	return (0);
}

