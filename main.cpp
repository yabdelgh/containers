#include <iostream>
#include "vector.hpp"
//#include <vector>
//namespace ft = std;
int main()
{
	ft::vector<int > my(10,9);
	ft::vector<int > your(20,5);
	ft::vector< int >::iterator ib = my.begin();
	ft::vector< int >::iterator ie = my.end();

	while (ib != ie)
	{
		std::cout << " "  << *ib << " " ;
		ib++;
	}
	
	std::cout << std::endl;
	my.pop_back();
	ib = my.begin();
	ie = my.end();
	
	while (ib != ie)
	{
		std::cout << " "  << *ib << " " ;
		ib++;
	}

	ib = my.begin();
	ie = my.end();

	my.swap(your);
	std::cout << std::endl;
	while (ib != ie)
	{
		std::cout << " "  << *ib << " " ;
		ib++;
	}

	ib = my.begin();
	ie = my.end();

	std::cout << std::endl;	
	while (ib != ie)
	{
		std::cout << " "  << *ib << " " ;
		ib++;
	}

	return (0);
}

