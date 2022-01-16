#ifndef __ITERATOR_HPP__
#define __ITERATOR_HPP__

namespace ft
{
	struct input_iterator_tag  {};
	struct output_iterator_tag {};
	struct forward_iterator_tag       : public input_iterator_tag         {};
	struct bidirectional_iterator_tag : public forward_iterator_tag       {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};
	
	template<class Iterator>
	struct iterator_traits
	{
   		typedef typename Iterator::difference_type difference_type;
  	 	typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};

	template<class T>
	struct iterator_traits<T*>
	{
    	typedef ptrdiff_t difference_type;
    	typedef T value_type;
    	typedef T* pointer;
    	typedef T& reference;
    	typedef random_access_iterator_tag iterator_category;
	};

	template <class T>
	struct iterator_traits<const T*>
	{
    	typedef ptrdiff_t difference_type;
    	typedef T value_type;
    	typedef const T* pointer;
    	typedef const T& reference;
    	typedef random_access_iterator_tag iterator_category;
	};

	template< class T >
	class vec_iterator
	{
		public:
		typedef T															iterator_type;
		typedef typename iterator_traits<iterator_type>::value_type			value_type;
  		typedef typename iterator_traits<iterator_type>::difference_type	difference_type;
    	typedef typename iterator_traits<iterator_type>::pointer			pointer;
    	typedef typename iterator_traits<iterator_type>::reference			reference;
    	typedef typename iterator_traits<iterator_type>::iterator_category	iterator_category;

		protected:
		pointer _ptr;

		public:
		explicit vec_iterator(pointer ptr) : _ptr(ptr) {};
		vec_iterator() : _ptr(0) {};
		vec_iterator( const vec_iterator<value_type *> &copie) : _ptr(copie._ptr) {};
		vec_iterator( const vec_iterator<const value_type *> &copie) : _ptr(copie._ptr) {};

		public: // operators
		
		// assignment
		vec_iterator& operator=(const vec_iterator &copie) 
		{
			if (this != &copie)
				_ptr = copie._ptr;
			return (*this);
		}
		
		// Comparison operators
		bool operator== (const vec_iterator& r)  const
		{  return _ptr == r.m_ptr;  }
		bool operator!= (const vec_iterator& r)  const
		{  return _ptr != r._ptr;  }
		bool operator<(const vec_iterator& r)  const
		{  return _ptr < r._ptr;  }
		bool operator<=(const vec_iterator& r)  const
		{  return _ptr <= r._ptr;  }
		bool operator>(const vec_iterator& r)  const
		{  return _ptr > r._ptr;  }
		bool operator>=(const vec_iterator& r)  const
		{  return _ptr >= r._ptr;  }

		//	Increment and Decrement
		vec_iterator& operator++()
		{ 
			++_ptr;
			return *this; 
		}
		vec_iterator operator++(int)
		{  
			pointer tmp = _ptr; 
			++*this; 
			return vec_iterator(tmp);  
		}
		vec_iterator& operator--()
		{  
			--_ptr; 
			return *this; 
	   	}
		vec_iterator operator--(int)
		{  
			pointer tmp = _ptr; 
			--*this;
		   	return vec_iterator(tmp); 
		}

		// Arithmetic operators + and -
		vec_iterator operator+(int n)
		{
			return (vec_iterator(_ptr + n));
		}
		vec_iterator operator-(int n)
		{
			return (vec_iterator(_ptr - n));
		}
		vec_iterator& operator+=(int n)
		{
			_ptr += n;
			return (*this);
		}
		vec_iterator& operator-=(int n)
		{
			_ptr -= n;
			return (*this);
		}
	 	
		reference operator*() const
		{	return (*_ptr);		}
		pointer operator->() const
		{	return (_ptr);		}

		public:
		virtual ~vec_iterator() {};

	};

}

#endif
