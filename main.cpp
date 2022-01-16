#include <iostream>
#include "vector.hpp"

int main()
{
	ft::vector<int > my(10,10);
	const ft::vector< int >::iterator it = my.begin();
	it++;
	std::cout << *it << std::endl;
	return (0);
}

