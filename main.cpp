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
		str = strdup("yassine abdelghafour");
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
		std::cout << b <<  "assignment operator called" << std::endl;
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
	ft::vector<int> vec;
	ft::vector<int>::iterator it = vec.begin();
	ft::vector<int>::iterator ite = vec.end();
	vec.reserve(10);
	it = vec.begin();
	std::cout << "size: " << vec.size() << std::endl;
	std::cout << "capacity: " << vec.capacity() << std::endl;
	std::cout << "size: " << vec.size() << std::endl;
	std::cout << "capacity: " << vec.capacity() << std::endl;
	vec.push_back(1);
	std::cout << "size: " << vec.size() << std::endl;
	std::cout << "capacity: " << vec.capacity() << std::endl;
	vec.push_back(2);
	std::cout << "size: " << vec.size() << std::endl;
	std::cout << "capacity: " << vec.capacity() << std::endl;
	vec.push_back(3);
	std::cout << "size: " << vec.size() << std::endl;
	std::cout << "capacity: " << vec.capacity() << std::endl;
	vec.push_back(4);
	std::cout << "size: " << vec.size() << std::endl;
	std::cout << "capacity: " << vec.capacity() << std::endl;
	it = vec.begin();
	vec.insert(it,it+1, it+3);
	std::cout << "size: " << vec.size() << std::endl;
	std::cout << "capacity: " << vec.capacity() << std::endl;
	it = vec.begin();
	ite = vec.end();
	while (it != ite)
	{
		std::cout << *it << std::endl;
		it++;
	}
	vec.resize(-1);
	std::cout << std::endl;
	it = vec.begin();
	ite = vec.end();
	while (it != ite)
	{
		std::cout << *it << std::endl;
		it++;
	}
	return (0);
}

