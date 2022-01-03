#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

namespace ft
{
	template < class T, class Allocator = allocator<T> >
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
		explicit vector (const allocator_type& allocator = allocator_type());
		explicit vector (size_type n, const value_type& val = value_type(),
				const allocator_type& allocator = allocator_type());
		//template <class InputIterator>
        //vector (InputIterator first, InputIterator last,
		//		const allocator_type& allocator = allocator_type());
		//vector (const vector& x);

		public: // Iterators
		public: // Capacity
		public: // Element access
		public: // Modifiers
		public: // Allocator
		public: // Non-member function overloads
		public: // Template specializations
		private:
		size_t	m_size;
		size_t	m_capacity;
		T		*data;
	}
	explicit vector (const allocator_type& allocator = allocator_type())
	{
		m_size = 0;
		m_capacity = 0;
		data = nullptr;
	}
	explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& allocator = allocator_type())
	{
		m_size = n;
		m_capacity = n;
		data = allocator.allocate(n);
	}
}

#endif
