#ifndef __ALGORITHM_HPP__
#define __ALGORITHM_HPP__

namespace ft
{
	template <class InputIterator1, class InputIterator2>
	bool
	equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
	{
		while (first1!=last1)
		{
			if (!(*first1 == *first2))  
				return false;
			++first1;
			++first2;
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool
	equal (InputIterator1 first1, InputIterator1 last1,	InputIterator2 first2, BinaryPredicate pred)
	{
		while (first1!=last1)
		{
			if (!pred(*first1,*first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2==last2 || *first2 < *first1)
				return (false);
			else if (*first1 < *first2)
				return (true);
			++first1;
			++first2;
		}
		return (first2!=last2);
	}
	
	/** comp is:
	 *	A binary function that accepts two arguments of the types pointed by the iterators,
	 *	and returns a value convertible to bool. The value returned indicates whether the 
	 *	first argument is considered to go before the second in the specific strict weak 
	 *	ordering it defines.The function shall not modify any of its arguments.
	 *	This can either be a function pointer or a function object.
	**/
	
	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		while (first1 != last1)
 		{
    		if (first2==last2 || comp(*first2, *first1))
				return false;
   			else if (comp(*first1 ,*first2))
				return true;
    		++first1;
			++first2;
  		}
		return (first2!=last2);
	}
}

#endif
