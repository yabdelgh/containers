#include <iostream>
#include "vector.hpp"

int main()
{
	ft::vector<int > my(10,9);
	ft::vector< int >::iterator it = my.begin();
	ft::vector< int >::iterator in = it + 9;
	
	std::cout << *in << std::endl;
	return (0);
}

