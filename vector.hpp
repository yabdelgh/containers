#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__
#include <iostream>

namespace ft
{
	
	template < class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
		typedef T                                        value_type;
		typedef Allocator                                allocator_type;
		typedef typename allocator_type::reference       reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer         pointer;
		typedef typename allocator_type::const_pointer   const_pointer;
	//	typedef implementation-defined                   iterator;
	//	typedef implementation-defined                   const_iterator;
	//	typedef std::reverse_iterator<iterator>          reverse_iterator;
	//	typedef std::reverse_iterator<const_iterator>    const_reverse_iterator;
		typedef typename allocator_type::difference_type difference_type;
		typedef typename allocator_type::size_type       size_type;

		public: // constructors
		explicit vector (const allocator_type& allocator = allocator_type())
		{
			_size = 0;
			_capacity = 0;
			_data = nullptr;
		}
		explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& allocator = allocator_type())
		{
			_size = n;
			_capacity = n;
			_data = allocator.allocate(n);
		}
		//template <class InputIterator>
        //vector (InputIterator first, InputIterator last,
		//		const allocator_type& allocator = allocator_type());
		//vector (const vector& x);

		public: // Iterators
		public: // Capacity
		size_type size(void) const
		{
			return (_size);
		}
		size_type capacity(void) const
		{
			return (_capacity);
		}
		public: // Element access
		public: // Modifiers
		public: // Allocator
		public: // Non-member function overloads
		public: // Template specializations
		private:
		size_t	_size;
		size_t	_capacity;
		T		*_data;
	};


	
}

#endif

