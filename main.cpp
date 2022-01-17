#include <iostream>
#include "vector.hpp"
//#include <vector>
//namespace ft = std;
int main()
{
	ft::vector<int> my(5,10);
	ft::vector<int> your(20,20);
	
	ft::vector<int>::iterator a= my.begin();
	ft::vector<int>::iterator b= my.end();
	
	ft::vector<int>::iterator it= your.begin();
	ft::vector<int>::iterator ite= your.end();

	while (it != ite)
	{
		std::cout << *it << " ";
		it++;
	}

	it = your.begin();
	ite = your.end();
	your.assign(it,ite);
	std::cout << std::endl;
	it = your.begin();
	ite = your.end();

	while (it != ite)
	{
		std::cout << *it << " ";
		it++;
	}
	return (0);
}

