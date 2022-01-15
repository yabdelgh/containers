#include <iostream>
#include <vector>
#include <iterator>
#include "vector.hpp"
int main()
{
	ft::vector<int> my(10,245);
	ft::vector<int>::iterator it = my.begin();
	ft::vector<int>::iterator ite = my.end();

	std::cout << *it << std::endl;
	return (0);
}

