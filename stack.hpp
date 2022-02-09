#ifndef __STACK_HPP_
#define __STACK_HPP_

#include "vector.hpp"

namespace ft
{
	template < class T, class Container = vector<T> >
	class stack
	{
		public:
		typedef T value_type;
		typedef Container container_type;
		typedef size_t size_type;
		
		public:
		explicit stack (const container_type& ctnr = container_type()) : _c(ctnr) {};

		protected:
		Container _c;

		public:	
		bool empty() const
		{
			return (_c.empty());
		}
		
		size_type size() const
		{
			return (_c.size());
		}

		value_type& top()
		{
			return (_c.back());
		}
		
		const value_type& top() const
		{
			return (_c.back());
		}
		
		void push (const value_type& val)
		{
			return (_c.push_back(val));
		}
	
		template <class TF, class CF>
		friend
  		bool
		operator== (const stack<TF,CF>& lhs, const stack<TF,CF>& rhs);
		
		template <class TF, class CF>
		friend
 		bool
		operator< (const stack<TF,CF>& lhs, const stack<TF,CF>& rhs);
	};
	
	template < class T, class Container>
  	bool
	operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs._c == rhs._c);
	}
	
	template <class T, class Container>
 	bool
	operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class Container>
 	bool
	operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs._c < rhs._c);
	}

	template <class T, class Container>
  	bool
	operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class T, class Container>
 	bool
	operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Container>
 	bool
	operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return !(lhs < rhs);
	}
}

#endif
