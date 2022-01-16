#include <iostream>
#include "vector.hpp"
int main()
{
	ft::vector<int > my(10,9);
	ft::vector< int >::iterator it = my.begin();
	ft::vector< int >::iterator in = it + 9;
<<<<<<< HEAD
	std::cout << it - in << std::endl;	
=======
	
	std::cout << *in << std::endl;
>>>>>>> 570084370ce2313ef9275bb1a203b7cec93f4109
	return (0);
}

