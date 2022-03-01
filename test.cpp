#include <iostream>
#include "type_traits.hpp"


template <class T>
  void f(T f, typename std::enable_if<std::is_integral<T>::value>::type *pf = nullptr) {
		  std::cout << f << std::endl;
		std::cout << pf << std::endl;
   }

class A
{
	public:
	int i;
};

std::ostream& operator<<(std::ostream &o, A& ele)
{
	o << ele.i;
	return o;
}

int main() {
	int j;
	j = 9;
	A a;
   f<A>(a);
   // f(v); // serait illégal
}
