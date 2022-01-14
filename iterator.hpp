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
	class iterator_traits<const T*>
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
		typedef T													iterator_type;
		typedef iterator_traits<iterator_type>::value_type			value_type;
  		typedef iterator_traits<iterator_type>::difference_type		difference_type;
    	typedef iterator_traits<iterator_type>::pointer				pointer;
    	typedef iterator_traits<iterator_type>::reference			reference;
    	typedef iterator_traits<iterator_type>::iterator_category	iterator_category;

		protected:
		pointer _ptr;

		public: //constructors
		explicit vec_iterator(pointer ptr);
		vec_iterator();
	}

}
#endif
