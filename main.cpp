#include <iostream>
#include "vector.hpp"
//#include <vector>
//namespace ft = std;
int main()
{
	ft::vector<int> my(5,10);
	my.pop_back();
	my.push_back(9);
	ft::vector<int>::iterator it= my.begin();
	ft::vector<int>::iterator ite= my.end();

	while (it != ite)
	{
		std::cout << *it << std::endl;
		it++;
	}

	return (0);
}

