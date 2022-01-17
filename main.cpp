#include <iostream>
#include "vector.hpp"
//#include <vector>
//namespace ft = std;
int main()
{
	ft::vector<int> my(400,10);

	std::cout << my.capacity() << std::endl;
	my.reserve(10002);
	std::cout << my.capacity() << std::endl;

	return (0);
}

