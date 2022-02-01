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

	template< class Iterator >
	class wrap_iterator
	{
		public:
		typedef Iterator													iterator_type;
		typedef typename iterator_traits<iterator_type>::value_type			value_type;
  		typedef typename iterator_traits<iterator_type>::difference_type	difference_type;
    	typedef typename iterator_traits<iterator_type>::pointer			pointer;
    	typedef typename iterator_traits<iterator_type>::reference			reference;
    	typedef typename iterator_traits<iterator_type>::iterator_category	iterator_category;

		protected:
		iterator_type _current;

		public:
		explicit wrap_iterator(const iterator_type &current) : _current(current) {};
		wrap_iterator() : _current() {};
		wrap_iterator( const wrap_iterator<value_type *> &copie) : _current(copie.base()) {};
		wrap_iterator( const wrap_iterator<const value_type *> &copie) : _current(copie.base()) {};
		
		public: // forward iterator requirements
		
		reference operator*() const
		{	
			return (*_current);		
		}
		pointer operator->() const
		{	
			return (_current);		
		}
		wrap_iterator& operator++()
		{ 
			++_current;
			return *this; 
		}
		wrap_iterator operator++(int)
		{  
			return wrap_iterator(_current++);  
		}
 		
		public: // bidirectional iterator requirements
		
		wrap_iterator& operator--()
		{  
			--_current; 
			return (*this); 
	   	}
		wrap_iterator operator--(int)
		{  
		   	return (vec_iterator(_current--)); 
		}
	
		public: // random access iterator requirements

	 	reference operator[](difference_type n) const
		{	
			return (_current[n]);	
		}
		wrap_iterator operator+(difference_type n)
		{
			return (wrap_iterator(_current + n));
		}
		wrap_iterator operator-(difference_type n)
		{
			return (wrap_iterator(_current - n));
		}
		wrap_iterator& operator+=(difference_type n)
		{
			_current += n;
			return (*this);
		}
		wrap_iterator& operator-=(difference_type n)
		{
			_current -= n;
			return (*this);
		}
		const iterator_type& base() const
		{
			return (_current);
		}
	};
		
	// forward iterator requirements
	
	template < class IteratorL, class IteratorR >
	bool
	operator==(const wrap_iterator<IteratorL> &it_l, const wrap_iterator<IteratorR> &it_r)
	{
		return (it_l.base() == it_r.base());
	}
	
	template < class Iterator >
	bool
	operator==(const wrap_iterator<Iterator> &it_l, const wrap_iterator<Iterator> &it_r)
	{
		return (it_l.base() == it_r.base());
	}
	
	template < class IteratorL, class IteratorR >
	bool
	operator!=(const wrap_iterator<IteratorL> &it_l, const wrap_iterator<IteratorR> &it_r)
	{
		return (it_l.base() != it_r.base());
	}
	
	template < class Iterator >
	bool
	operator!=(const wrap_iterator<Iterator> &it_l, const wrap_iterator<Iterator> &it_r)
	{
		return (it_l.base() != it_r.base());
	}
	
	// random access iterator requirements
	
	template < class IteratorL, class IteratorR >
	bool
	operator<=(const wrap_iterator<IteratorL> &it_l, const wrap_iterator<IteratorR> &it_r)
	{
		return (it_l.base() <= it_r.base());
	}
	
	template < class Iterator >
	bool
	operator<=(const wrap_iterator<Iterator> &it_l, const wrap_iterator<Iterator> &it_r)
	{
		return (it_l.base() <= it_r.base());
	}
	
	template < class IteratorL, class IteratorR >
	bool
	operator>=(const wrap_iterator<IteratorL> &it_l, const wrap_iterator<IteratorR> &it_r)
	{
		return (it_l.base() >= it_r.base());
	}
	
	template < class Iterator >
	bool
	operator>=(const wrap_iterator<Iterator> &it_l, const wrap_iterator<Iterator> &it_r)
	{
		return (it_l.base() >= it_r.base());
	}
	
	template < class IteratorL, class IteratorR >
	bool
	operator<(const wrap_iterator<IteratorL> &it_l, const wrap_iterator<IteratorR> &it_r)
	{
		return (it_l.base() < it_r.base());
	}
	
	template < class Iterator >
	bool
	operator<(const wrap_iterator<Iterator> &it_l, const wrap_iterator<Iterator> &it_r)
	{
		return (it_l.base() < it_r.base());
	}
	
	template < class IteratorL, class IteratorR >
	bool
	operator>(const wrap_iterator<IteratorL> &it_l, const wrap_iterator<IteratorR> &it_r)
	{
		return (it_l.base() > it_r.base());
	}
	
	template < class Iterator >
	bool
	operator>(const wrap_iterator<Iterator> &it_l, const wrap_iterator<Iterator> &it_r)
	{
		return (it_l.base() > it_r.base());
	}
	
	template < class Iterator >
	wrap_iterator<Iterator>
	operator+(typename wrap_iterator<Iterator>::difference_type n, const wrap_iterator<Iterator> &it)
	{
		return (wrap_iterator<Iterator>(it.base() + n));
	}

	
	
	template < class Iterator>
	class reverse_iterator
	{
		public:
		typedef Iterator													iterator_type;
		typedef typename iterator_traits<iterator_type>::value_type			value_type;
  		typedef typename iterator_traits<iterator_type>::difference_type	difference_type;
    	typedef typename iterator_traits<iterator_type>::pointer			pointer;
    	typedef typename iterator_traits<iterator_type>::reference			reference;
    	typedef typename iterator_traits<iterator_type>::iterator_category	iterator_category;

		protected:
		iterator_type _current;
	
		public:
		reverse_iterator() : _current() {}
		explicit reverse_iterator(itrator_type it) : _current(it) {}
		template <class Iter>
		reverse_iterator(const reverse_iterator<Iter>& rev_it) : _current(rev_it.base()) {}

		public:
		iterator_type base() const
		{
			return (_current);
		}
		
		reference operator*()
		{
			iterator_type copy(_current);
			--copy;
			return (*copy);
		}
		
		reverse_iterator operator+(difference_type n) const
		{
			return (reverse_iterator(_current - n));
		}
		
		reverse_iterator& operator++()
		{
			--_current;
			return (*this);
		}
		
		reverse_iterator operator++(int)
		{
			reverse_iterator tmp(_current);
			_current--;
			return (*this);
		}

		reverse_iterator& operator+=(difference_type n)
		{
			_current -= n;
			return (*this);
		}
		
		reverse_iterator operator-(difference_type n) const
		{
			return (reverse_iterator(_current + n));
		}
		
		
		reverse_iterator& operator--()
		{
			++_current;
			return (*this);
		}
		
		reverse_iterator operator--(int)
		{
			reverse_iterator tmp(_current);
			_current++;
			return (*this);
		}
		
		reverse_iterator& operator-=(difference_type n)
		{
			_current += n;
			return (*this);
		}

		pointer operator->() const
		{
			return (&operator*());
		}
		
		reference operator[](difference_type n) const
		{
			reverse_iterator tmp(_current - n);
			return (*tmp);
		}
		
	};
}

#endif
