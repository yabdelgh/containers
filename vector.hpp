#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__
#include <iostream>
#include "iterator.hpp"

namespace ft
{
	template < class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
		typedef T											value_type;
		typedef Allocator									allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef wrap_iterator<pointer>						iterator;
		typedef wrap_iterator<const_pointer>                const_iterator;
		typedef ft::reverse_iterator<iterator>					reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
		typedef typename allocator_type::difference_type	difference_type;
		typedef typename allocator_type::size_type			size_type;

		private:
		size_type		_size;
		size_type		_capacity;
		value_type		*_data;
		allocator_type 	A;
		
	/*************** constructors *****************/
		
		public:
		explicit vector (const allocator_type& allocator = allocator_type());
		explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& allocator = allocator_type());
		//template <class InputIterator>
		//vector (InputIterator first, InputIterator last,
		//		const allocator_type& allocator = allocator_type());
		//vector (const vector& x);
		
	/*************** iterators *******************/
		
		public:
		iterator begin();
		const_iterator begin() const;
  		iterator end();
		const_iterator end() const;
	
	/*************** capacity *******************/
		
		public:
		size_type size(void) const;
		size_type max_size(void) const;
		size_type capacity(void) const;
		bool empty() const;
		void reserve (size_type n);
		void resize (size_type n, value_type val = value_type());
	
	/*************** element access **************/
		
		public:
		reference operator[] (size_type n);
		const_reference operator[] (size_type n) const;
		reference at (size_type n);
		const_reference at (size_type n) const;
		reference front();
		const_reference front() const;
		reference back();
		const_reference back() const;

	/*************** modifiers *****************/
		
		public:
		void clear();
		void pop_back();
		void swap (vector& x);
		void push_back (const value_type& val);
		void assign (size_type n, const value_type& val);
		template <class InputIterator>
  		void assign (InputIterator first, InputIterator last);
		iterator erase (iterator position);
		iterator erase (iterator first, iterator last);
		iterator insert (iterator position, const value_type& val);
    	void insert (iterator position, size_type n, const value_type& val);
		template <class InputIterator>
    	void insert (iterator position, InputIterator first, InputIterator last);
	
	/*************** destructor *****************/
		
		public:
		virtual ~vector()
		{
			this->clear();
			A.deallocate(_data, _capacity);
		}
	};


	
	//  Constructors --------->
	
	template < class T, class Allocator >
	vector<T, Allocator>::vector (const allocator_type& allocator)
	{
		_size = 0;
		_capacity = 0;
		_data = nullptr;
	}

	template < class T, class Allocator >
	vector<T, Allocator>::vector (size_type n, const value_type& val, const allocator_type& allocator)
	{
		_size = n;
		_capacity = n;
		_data = (n == 0) ? nullptr : A.allocate(n);
		for (int i = 0; i < n; i++)
			A.construct(_data + i, val);
		
	}
	
	// iterators ------------->
	
	template < class T, class Allocator>
	typename vector<T, Allocator>::iterator
	vector<T, Allocator>::begin()
	{
		return (iterator(_data));
	}
	
	template < class T, class Allocator>
	typename vector<T, Allocator>::const_iterator
	vector<T, Allocator>::begin() const
	{
		return (iterator(_data));
	}
	
	template < class T, class Allocator>
	typename vector<T, Allocator>::iterator
	vector<T, Allocator>::end()
	{
		return (iterator(_data + _size));
	}
	
	template < class T, class Allocator>
	typename vector<T, Allocator>::const_iterator
	vector<T, Allocator>::end() const
	{
		return (iterator(_data + _size));
	}

	// Capacity ----------->
	
	template < class T, class Allocator >
	typename vector<T, Allocator>::size_type
	vector<T, Allocator>::size(void) const
	{
		return (_size);
	}

	template < class T, class Allocator >
	typename vector<T, Allocator>::size_type
	vector<T, Allocator>::max_size(void) const
	{
		return (A.max_size());
	}

	template < class T, class Allocator >
	typename vector<T, Allocator>::size_type
	vector<T, Allocator>::capacity(void) const
	{
		return (_capacity);
	}

	template < class T, class Allocator >
	bool
	vector<T, Allocator>::empty() const
	{
		return (!_size);
	}
	
	template < class T, class Allocator >
	void
	vector<T, Allocator>::reserve (size_type n)
	{
		if (n > _capacity)
		{
			value_type *tmp;
			tmp = A.allocate(n);
			for(int i = 0; i < _size; i++)
			{
				A.construct(&tmp[i], _data[i]);
				A.destroy(&_data[i]);
			}
			A.deallocate(_data, _capacity);
			_data = tmp;
			_capacity = n;
		}
	}
	
	template < class T, class Allocator >
	void
	vector<T, Allocator>::resize (size_type n, value_type val )
	{
		iterator it;
		iterator ite;
		it = this->begin();
		ite = this->end();
		if (n < _size)
			this->erase(it + n, ite);
		else if (n > _size)
			this->insert(ite, n - _size, val);
	}

	
	// Element access ------------>
	
	template < class T, class Allocator >
	typename vector<T, Allocator>::reference
	vector<T, Allocator>::operator[](size_type n)
	{
		return (_data[n]);
	}

	template < class T, class Allocator >
	typename vector<T, Allocator>::const_reference
	vector<T, Allocator>::operator[](size_type n) const
	{
		return (_data[n]);
	}

	template < class T, class Allocator >
	typename vector<T, Allocator>::reference
	vector<T, Allocator>::at(size_type n)
	{
		if (n >= _size)
			throw std::out_of_range("vector::at");
		return (_data[n]);
	}
	
	template < class T, class Allocator >
	typename vector<T, Allocator>::const_reference
	vector<T, Allocator>::at(size_type n) const
	{
		if (n >= _size)
			throw std::out_of_range("vector::at");
		return (_data[n]);
	}
	
	template < class T, class Allocator >
	typename vector<T, Allocator>::reference
	vector<T, Allocator>::front()
	{
			return (_data[0]);
	}
	
	template < class T, class Allocator >
	typename vector<T, Allocator>::const_reference
	vector<T, Allocator>::front() const
	{
			return (_data[0]);
	}
	
	template < class T, class Allocator >
	typename vector<T, Allocator>::const_reference
	vector<T, Allocator>::back() const
	{
			return (_data[_size - 1]);
	}
	
	template < class T, class Allocator >
	typename vector<T, Allocator>::reference
	vector<T, Allocator>::back()
	{
			return (_data[_size - 1]);
	}

	// Modifiers --------->
		
	template < class T, class Allocator >
	void
	vector<T, Allocator>::pop_back()
	{
		_size -= 1;
		A.destroy(_data +_size);
	}
	
	template < class T, class Allocator >
	void
	vector<T, Allocator>::clear()
	{
		for (int i = 0; i < _size ; i++)
			A.destroy(_data + i);
	}

	template < class T, class Allocator >
	void
	vector<T, Allocator>::push_back (const value_type& val)
	{
		if (_capacity == 0)
			reserve(1);
		else if (_size  == _capacity)
			reserve(_capacity * 2);
		A.construct(&_data[_size], val);
		_size += 1;
	}
	

	template < class T, class Allocator >
	template <class InputIterator>
  	void
  	vector<T, Allocator>::assign (InputIterator first, InputIterator last)
	{
		difference_type	len = last - first;
		this->clear();
        if (len > _capacity)
        {
            A.deallocate(_data, _capacity);
            _data = A.allocate(len);
            _capacity = len;
        }
        _size = len;
        for (size_t i = 0; i < _size; i++)
            A.construct(_data + i, *(first + i));
	}
	
	template < class T, class Allocator >
	void
	vector<T, Allocator>::assign (size_type n, const value_type& val)
	{
		this->clear();
		if (n > _capacity)
		{
			A.deallocate(_data, _capacity);
			_data = A.allocate(n);
			_capacity = n;
		}
		_size = n;
		for( size_t i = 0 ; i < _size ; i++ )
			A.construct(_data + i, val);
	}
	
	template < class T, class Allocator >
	typename vector<T, Allocator>::iterator
	vector<T, Allocator>::erase (iterator position)
	{
		return (erase(position, position + 1));
	}
	
	template < class T, class Allocator >
	typename vector<T, Allocator>::iterator
	vector<T, Allocator>::erase (iterator first, iterator last)
	{
		iterator e = this->end();
		iterator ret = first;
		_size -= last - first;
		while (last != e)
		{
			*first = *last;
			last++;
			first++;
		}
		while (first != e)
		{
			A.destroy(first.base());
			first++;
		}
		return (ret);	
	}
	
	template < class T, class Allocator >
	void
	vector<T, Allocator>::swap (vector& x)
	{
		size_type		tmp;
		value_type* 	tmp_ptr;

		tmp = _size;
		_size = x._size;
		x._size = tmp;

		tmp = _capacity;
		_capacity = x._capacity;
		x._capacity = tmp;

		tmp_ptr = _data;
		_data = x._data;
		x._data = tmp_ptr;
	}
	
	template < class T, class Allocator >
	typename vector<T, Allocator>::iterator
	vector<T, Allocator>::insert (iterator position, const value_type& val)
	{
		difference_type tmp;
		tmp = position - this->begin();
		insert(position, 1, val);
		return (this->begin() + tmp);
	}
	
	template < class T, class Allocator >
	void
	vector<T, Allocator>::insert (iterator position, size_type n, const value_type& val)
	{
		if (_size + n > _capacity)
		{
			value_type *tmp;
			iterator it;
			iterator ite;
			size_t i;

			it = this->begin();
			ite = this->end();
			_size += n;
			if (_size  > _capacity * 2)
				tmp = A.allocate(_size);
			else
				tmp = A.allocate(_capacity * 2);
			i = 0;
			while (it != position)
			{
				A.construct(tmp + i, *it);
				i++;
				it++;
			}
			while (n--)
			{
				A.construct(tmp + i, val);
				i++;
			}
			while (it != ite)
			{
				A.construct(tmp + i, *it);
				i++;
				it++;
			}
			it = this->begin();
			while (it != position)
			{
				A.destroy(it.base());
				it++;
			}
			A.deallocate(_data, _capacity);	
			_data = tmp;
			if (_size > _capacity * 2)
				_capacity = _size;
			else
				_capacity *= 2;
		}
		else
		{
			iterator it = this->end() + n - 1;
			iterator end = this->end() - 1;
			
			while (it != end && (it - n) != position -1)
			{
				A.construct(it.base(), *(it - n));
				it--;
			}
			while (it - n != position - 1)
			{
				*it = *(it - n);
				it--;
			}
			while (it != position - 1)
			{
				if (it > end)
					A.construct(it.base(), val);
				else
					*it = val;
				it--;
			}
			_size += n;
		}
	}

	template < class T, class Allocator >
	template < class InputIterator	>
    void
	vector<T, Allocator>::insert (iterator position, InputIterator first, InputIterator last)
	{
		iterator a(first.base());
		iterator b(last.base());
		size_t n = b - a;
		if (_size + n > _capacity)
		{
			value_type *tmp;
			iterator it;
			iterator ite;
			size_t i;

			it = this->begin();
			ite = this->end();
			_size += n;
			if (_size  > _capacity * 2)
				tmp = A.allocate(_size);
			else
				tmp = A.allocate(_capacity * 2);
			i = 0;
			while (it != position)
			{
				A.construct(tmp + i, *it);
				i++;
				it++;
			}
			while (first != last)
			{
				A.construct(tmp + i, *first);
				first++;
				i++;
			}
			while (it != ite)
			{
				A.construct(tmp + i, *it);
				i++;
				it++;
			}
			it = this->begin();
			while (it != position)
			{
				A.destroy(it.base());
				it++;
			}
			A.deallocate(_data, _capacity);	
			_data = tmp;
			if (_size > _capacity * 2)
				_capacity = _size;
			else
				_capacity *= 2;
		}
		else
		{
			iterator it = this->end() + n - 1;
			iterator end = this->end() - 1;
			
			while (it != end && (it - n) != position -1)
			{
				A.construct(it.base(), *(it - n));
				it--;
			}
			while (it - n != position - 1)
			{
				*it = *(it - n);
				it--;
			}
			while (it != position - 1)
			{
				b--;
				if (it > end)
					A.construct(it.base(), *b);
				else
					*it = *b;
				it--;
			}
			_size += n;
		}
	}
}

#endif

