#include <iostream>
#include <vector>

int main()
{
	std::vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	vec.push_back(5);

	std::vector<int>::iterator it = vec.begin()+1;
	std::cout << it[-1] << std::endl;

	
	return (0);
}
