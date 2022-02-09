#ifndef __UTILITY_HPP__
#define __UTILITY_HPP__

namespace ft
{
	template< class T1, class T2 >
	struct pair
	{
		public:
		typedef T1 first_type;
		typedef T2 second_type;

		public:
		T1 first;
		T2 second;

		public:
		pair() : first(), second() {}
		template<class U, class V>
		pair (const pair<U,V>& pr) : first(pr.first), second(pr.second) {}
		pair (const first_type& a, const second_type& b) : first(a), second(b) {}

		public:
		pair& operator= (const pair& pr);
	};

	template< class T1, class T2 >
	pair< T1, T2>&
	pair< T1, T2 >::operator=(const pair& pr)
	{
		first = pr.first;
		second = pr.second;
		return (*this);
	}
	
	template <class T1, class T2>
  	bool
	operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (lhs.first==rhs.first && lhs.second==rhs.second); 
	}

	template <class T1, class T2>
  	bool
	operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ 
		return !(lhs==rhs); 
	}

	template <class T1, class T2>
  	bool
	operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ 
		return (lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second)); 
	}

	template <class T1, class T2>
  	bool
	operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ 
		return !(rhs<lhs); 
	}

	template <class T1, class T2>
  	bool
	operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ 
		return (rhs<lhs); 
	}

	template <class T1, class T2>
  	bool
	operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ 
		return !(lhs<rhs); 
	}

}

#endif
