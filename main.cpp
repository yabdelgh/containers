#include <iostream>
#include <vector>
#include <iterator>
int main()
{
	std::vector<int> my;
	std::vector<int>::iterator it;
	std::vector<int>::iterator ite;
	it = my.begin();
	ite = my.end();
	for(int i= 0 ; i < 10000 ; i++)
		my.push_back(i);
	ite = my.end();
	while (it != ite)
		std::cout << *it++ << std::endl;
	
	return (0);
}

