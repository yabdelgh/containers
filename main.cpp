#include <iostream>
#include "vector.hpp"
//#include <vector>
#include <cstring>
//namespace ft = std;
class A
{
	public:
	A(int a)
	{
		b = a;
		str = strdup("y");
		std::cout << b <<  "constructor called" << std::endl;
	}
	A(const A& copie)
	{
		this->b = copie.b;
		this->str = strdup(copie.str);
		std::cout << b << "copie constructor called" << std::endl;
	}
	A& operator=(const A& copie)
	{
		if (str != nullptr)
			delete str;
		b = copie.b;
		str = strdup(copie.str);
		std::cout << "assignment operator called" << std::endl;
		return (*this);
	}
	public:
	int b;
	char *str;
	public:
	virtual ~A()
	{
		delete str;
		std::cout << b << "destructor called " << std::endl;
	}
};

int main()
{
	ft::vector<A> vec;
	std::cout << std::endl;
	vec.push_back(1);
	std::cout << std::endl;
	vec.push_back(2);
	std::cout << std::endl;
	vec.push_back(3);
	std::cout << std::endl;
	vec.push_back(4);
	std::cout << std::endl;
	ft::vector<A>::iterator it = vec.begin() + 1;
	ft::vector<A>::iterator b = vec.begin();
	ft::vector<A>::iterator e = vec.end();
	while (b != e)
	{
		std::cout << b->b << std::endl;
		b++;
	}
	std::cout << std::endl;
	it = vec.erase(it,it+2); 
	std::cout << "ret" << it->b << std::endl;
	std::cout << std::endl;
	 b = vec.begin();
	 e = vec.end();
	while (b != e)
	{
		std::cout << b->b << std::endl;
		b++;
	}
	return (0);
}

