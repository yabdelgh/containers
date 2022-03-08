#ifndef __FUNCTIONAL_HPP__
#define __FUNCTIONAL_HPP__

namespace ft
{
	template <class Arg1, class Arg2, class Result>
  	struct binary_function
	{
		typedef Arg1 first_argument_type;
   	 	typedef Arg2 second_argument_type;
   	 	typedef Result result_type;
  	};
}
#endif 
