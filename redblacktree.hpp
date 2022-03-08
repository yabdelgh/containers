#ifndef __RED_BLACK_TREE__HPP
#define __RED_BLACK_TREE__HPP

#include <iostream>
#include "utility.hpp"
#include "functional.hpp"
#include "iterator.hpp"
namespace ft
{
	template < class T >
	struct node
	{
		public:
		T		*_data;
		node	*_left;
		node	*_right;
		node	*_parent;
		bool	_color;
		bool	_lorr; // left or right child

		public:
		node(T *data = nullptr, bool color = true ,bool lorr = true,
		node *parent = nullptr, node *left = nullptr, node *right = nullptr)
		:	_data(data), _color(color), _lorr(lorr), _parent(parent), _left(left), _right(right) {}
		node(const node& copy) : _data(copy._data), _color(copy._color), _lorr(copy._lorr),
		_parent(copy._parent), _left(copy._left), _right(copy._right) {}

		public:
		node& operator=(const node& copy)
		{
			_data = copy._data;
			_left = copy._left;
			_right = copy._right;
			return (*this);
		}

		public:
		bool get_uncle_color() const
		{
			node<T> *grandparent = _parent->_parent;
			if (_parent->_lorr && grandparent->_left != nullptr)
				return (grandparent->_left->_color);
			if (!_parent->_lorr && grandparent->_right != nullptr)
				return (grandparent->_right->_color);
			return (false);
		}
		
		node *successor()
		{
			node *tmp;
			tmp = _right;
			while (tmp->_left != nullptr)
				tmp = tmp->_left;
			return (tmp);
		}

		node *in_order_successor()
		{
			if (_right != nullptr)
				return(successor());
			else
			{
				node *tmp;
				tmp = this;
				while (tmp != nullptr && tmp->_lorr == true)
					tmp = tmp->_parent;
				if (tmp != nullptr)
					return (tmp->_parent);
			}
			return (nullptr);
		}
		
		node *in_order_predecessor()
		{
			if (_left != nullptr)
				return(predecessor());
			else
			{
				node *tmp;
				tmp = this;
				while (tmp != nullptr && tmp->_lorr == false)
					tmp = tmp->_parent;
				if (tmp != nullptr)
					return (tmp->_parent);
			}
			return (nullptr);
		}

		node *predecessor()
		{
			node *tmp;
			tmp = _left;
			while (tmp->_right != nullptr)
				tmp = tmp->_right;
			return (tmp);
		}

		public:
		virtual ~node() {}

	};
	
	template <class T>
	class rbt_iterator
	{
		public:
		typedef typename iterator_traits<T>::value_type         value_type;
		typedef typename iterator_traits<T>::difference_type    difference_type;
		typedef typename iterator_traits<T>::pointer            pointer;
		typedef typename iterator_traits<T>::reference          reference;
		typedef typename ft::bidirectional_iterator_tag			iterator_category;
		typedef node<value_type>*								node_ptr;

		private:
		node_ptr _current;
		
		public:
		rbt_iterator(): _current() {}
		rbt_iterator(node_ptr copy) : _current(copy) {}
		rbt_iterator(const rbt_iterator<value_type *> &copy): _current(copy.base()) {}
		rbt_iterator(const rbt_iterator< const value_type *> &copy): _current(copy.base()) {}
  
		public:
		reference operator* () const
		{
			return (*_current->_data);
		}
		
		pointer operator-> () const
		{
			return (_current->_data);
		}
		
		rbt_iterator<T>& operator++()
		{
			_current = _current->in_order_successor();
			return (*this);
		}
		
		rbt_iterator<T> operator++(int)
		{
			rbt_iterator<T> tmp(_current);
			_current = _current->in_order_successor();
			return (tmp);
		}
		
		rbt_iterator<T>& operator--()
		{
			_current = _current->in_order_predecessor();
			return (*this);
		}
		
		rbt_iterator<T> operator--(int)
		{
			rbt_iterator<T> tmp(_current);
			_current = _current->in_order_predecessor();
			return (tmp);
		}

		node_ptr base() const
		{
			return (_current);
		}
	};
	
	template <class T, class F>
	bool
	operator==(const rbt_iterator<T> & x, const rbt_iterator<F> & y)
	{
		return (y.base() == x.base());
	}
	
	template <class T, class F>
	bool
	operator!=(const rbt_iterator<T> & x, const rbt_iterator<F> & y)
	{
		return (y.base() != x.base());
	}
	
	template <class T>
	bool
	operator==(const rbt_iterator<T> & x, const rbt_iterator<T> & y)
	{
		return (y.base() == x.base());
	}
	
	template <class T>
	bool
	operator!=(const rbt_iterator<T> & x, const rbt_iterator<T> & y)
	{
		return (y.base() != x.base());
	}
	
	

	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator< ft::pair<const Key, T> > >
	class rbt
	{
		public:
		typedef T												mapped_type;
		typedef Key												key_type;
		typedef Alloc											allocator_type;
		typedef Compare											key_compare;
		typedef typename allocator_type::value_type				value_type;
		typedef typename allocator_type::reference 				reference;
		typedef typename allocator_type::const_reference		const_reference;
		typedef typename allocator_type::pointer				pointer;
		typedef typename allocator_type::const_pointer 			const_pointer;
		typedef typename allocator_type::difference_type		difference_type;
		typedef typename allocator_type::size_type      		size_type;
		typedef typename ft::rbt_iterator<pointer>				iterator;
		typedef typename ft::rbt_iterator<const_pointer>		const_iterator;
		typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		typedef node<value_type>*								node_ptr;
		
		public:
		class value_compare: public ft::binary_function<value_type, value_type, bool>
		{
		    friend class rbt<Key, T, Compare, Alloc>;
		    
		    protected:
		    Compare comp;
		    value_compare(Compare c): comp(c) { }
		    
		    public:
		    bool operator()(const_reference x, const_reference y) const 
		    { 
		        return comp(x.first, y.first);
		    }
		};

		private:
		node_ptr			_root;
		allocator_type		_alloc;
		size_type			_size;
		node<value_type>	_end;
		
		public:
		iterator begin()
		{
			node<value_type> *tmp;
			tmp = _root;
			while(tmp->_left != nullptr)
				tmp = tmp->_left;
			return iterator(tmp);
		}
		
		const_iterator begin() const
		{
			node<value_type> *tmp;
			tmp = _root;
			while(tmp->_left != nullptr)
				tmp = tmp->_left;
			return const_iterator(tmp);
		}
		
		iterator end()
		{
			return iterator(nullptr);
		}
		
		const_iterator end() const
		{
			return const_iterator(nullptr);
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(&_end);
		}
		
		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(&_end);
		}
		
		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}
		
		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(begin());
		}

		public:
		rbt() : _root(nullptr) , _size(0) {}
		rbt(const rbt& copy) : _root(copy._root) , _size(copy._size) {}

		public:
		rbt& operator=(const rbt& copy)
		{
			_root = copy._root;
			return (*this);
		}

		public:
		void insert_node(const_reference data);
		void delete_node(node_ptr node);
		void delete_node(const_reference data);
		void delete_fix(node_ptr node);
		void replace_node(node_ptr old_node, node_ptr new_node);

		public:
		size_type size() const;
		size_type max_size() const;
		bool empty() const;
		void swap (rbt& x);
		void clear();
		void display();

		public:

		public:
		node_ptr search(const_reference data);
		node_ptr base()
		{
			return (_root);
		}

		
		value_compare value_comp() const
		{
			return value_compare(key_comp());
		}

		key_compare key_comp() const
		{
			return key_compare();
		}
		
		allocator_type get_allocator() const
		{
			return allocator_type();
		}


		public:
		virtual ~rbt() {}
	};

	
	template <class Key, class T, class Compare, class Alloc>
	void
	rbt<Key, T, Compare, Alloc>::display ()
	{
		node<value_type> *tmp;
		tmp = _root;
		while(tmp->_right != nullptr)
			tmp = tmp->_right;
		while (tmp != nullptr)
		{
			std::cout << tmp->_data->first << std::endl;
			tmp = tmp->in_order_predecessor();
		}
	}
	
	template <class Key, class T, class Compare, class Alloc>
	typename rbt<Key, T, Compare, Alloc>::size_type
	rbt<Key, T, Compare, Alloc>::size() const
	{
		return (_size);
	}
	
	template <class Key, class T, class Compare, class Alloc>
	bool
	rbt<Key, T, Compare, Alloc>::empty() const
	{
		return (!_size);
	}
	
	template <class Key, class T, class Compare, class Alloc>
	void
	rbt<Key, T, Compare, Alloc>::swap (rbt& x)
	{
		node_ptr tmp_root;
		size_type tmp_size;

		tmp_root = _root;
		tmp_size = _size;
		_root = x._root;
		_size = x._size;
		x._root = tmp_root;
		x._size = tmp_size;
	}
	
	template <class Key, class T, class Compare, class Alloc>
	typename rbt<Key, T, Compare, Alloc>::size_type
	rbt<Key, T, Compare, Alloc>::max_size() const
	{
		return (_alloc.max_size);
	}
	
	template <class Key, class T, class Compare, class Alloc>
	void
	rbt<Key, T, Compare, Alloc>::clear()
	{
		_size = 0;
		while(_root)
			delete_node(_root); // no performance
	}

	template <class Key, class T, class Compare, class Alloc>
	void
	rbt<Key, T, Compare, Alloc>::insert_node(const_reference data)
	{
		node_ptr tmp;
		value_compare comp = value_comp();

		if (_root == nullptr)
		{
			_root = new node<value_type>(new value_type(data), false);
			_end._left = _root;
			_size++;
		}
		tmp = _root;
		while (comp(*tmp->_data ,data) || comp(data, *tmp->_data))
		{
			if (!comp(data ,*tmp->_data))
			{
				if (tmp->_right == nullptr)
				{
					tmp->_right = new node<value_type>(new value_type(data), true, true, tmp);
					_size++;
				}
				tmp = tmp->_right;
			}
			else
			{
				if (tmp->_left == nullptr)
				{
					tmp->_left = new node<value_type>(new value_type(data), true, false, tmp);
					_size++;
				}
				tmp = tmp->_left;
			}
		}
		if (tmp->_parent != nullptr && tmp->_parent->_color == true)
			balance(_root, tmp);
	}
	
	template <class Key, class T, class Compare, class Alloc>
	void
	rbt<Key, T, Compare, Alloc>::delete_node(const_reference data)
	{
		node_ptr tmp;
		tmp = search(data);
		if (tmp != nullptr)
		{
			delete_node(tmp);
			_size--;
		}
	}

	template <class Key, class T, class Compare, class Alloc>
	void
	rbt<Key, T, Compare, Alloc>::delete_node(node_ptr tmp)
	{
		if (tmp == _root && tmp->_left == nullptr && tmp->_right == nullptr)
		{
			//free
			_root = nullptr;
			return ;
		}
		while (tmp->_left != nullptr && tmp->_right != nullptr)
		{
			node_ptr s = tmp->successor();
			tmp->_data = s->_data;
			tmp = s;
		}
		if (tmp->_color == true)
				replace_node(tmp, nullptr);
		else
		{
			if (tmp->_right != nullptr && tmp->_right->_color == true) // if tmp is black and his right child is red
			{
				// free tmp->_data
				tmp->_data = tmp->_right->_data;
				//free tmp->_right
				tmp->_right = nullptr;
			}
			else if (tmp->_left != nullptr && tmp->_left->_color == true) // if tmp is black and his left child is red
			{
				// free tmp->_data
				tmp->_data = tmp->_left->_data;
				//free tmp->_right
				tmp->_left = nullptr;
			}
			else
			{
				replace_node(tmp, nullptr);
				if (tmp->_lorr)
					delete_fix(tmp->_parent->_left);
				else
					delete_fix(tmp->_parent->_right);
			}
		}
	}

	template <class Key, class T, class Compare, class Alloc>
	void
	rbt<Key, T, Compare, Alloc>::delete_fix(node_ptr node)
	{
		if (!is_red(node) && !is_red(node->_left) && !is_red(node->_right))
		{
			node->_color = true;
			if (node->_parent == _root || node->_parent->_color == true)
				node->_parent->_color = false;
			else if (node->_parent->_lorr)
				delete_fix(node->_parent->_parent->_left);
			else
				delete_fix(node->_parent->_parent->_right);
		}
		else if ( is_red(node) )
		{
			if (node->_lorr)
			{
				rotateright(*node->_parent);
				delete_fix(node->_right);
			}
			else
			{
				rotateleft(*node->_parent);
				delete_fix(node->_left);
			}
		}
		else // if the node is black
		{
			if (node->_lorr && !is_red( node->_right))
			{
				rotateleft(*node);
				delete_fix(node);
			}
			else if (!node->_lorr && !is_red( node->_left))
			{
				rotateright(*node);
				delete_fix(node);
			}
			if (node->_lorr && is_red(node->_right))
			{
				node->_right->_color = false;
				rotateright(*node->_parent);
			}
			else if (!node->_lorr && is_red(node->_left))
			{
				node->_left->_color = false;
				rotateleft(*node->_parent);
			}
		}
	}

	template <class T>
	bool
	is_red(node<T> *node)
	{
		if (node == nullptr)
			return (false);
		else
			return (node->_color);
	}
	
	template <class Key, class T, class Compare, class Alloc>
	void
	rbt<Key, T, Compare, Alloc>::replace_node(node_ptr tmp, node_ptr new_node)
	{
		if (tmp->_lorr == true)
			tmp->_parent->_right = new_node;
		else
			tmp->_parent->_left = new_node;
		if (new_node != nullptr)
			new_node->_parent = tmp->_parent;
		// free
	}

	template <class Key, class T, class Compare, class Alloc>
	node<typename rbt<Key, T, Compare, Alloc>::value_type>*
	rbt<Key, T, Compare, Alloc>::search(const_reference data)
	{
		node_ptr tmp;
		value_compare comp = value_comp();
		
		tmp = _root;
		while (tmp != nullptr)
		{
			if (!comp(data, *(tmp->_data)) && !comp(*(tmp->_data), data))
				return (tmp);
			else if (!comp(data ,*tmp->_data))
				tmp = tmp->_right;
			else
				tmp = tmp->_left;
		}
		return (nullptr);
	}

	
/*	template <class T>
	node<T>*
	rbt<>create_node(const T& data)
	{
		node<T>* _node;
		node<T>* _data;
		
	}*/
	
	template <class T>
	void balance(node<T> *_root, node<T> *tmp)
	{
		if (tmp->get_uncle_color() == true)
		{
			node<T> *grandparent = tmp->_parent->_parent;
			grandparent->_left->_color = false;
			grandparent->_right->_color = false;
			if (grandparent != _root)
				grandparent->_color = true;
			if (grandparent->_parent != nullptr && grandparent->_parent->_color == true)
				balance(_root, grandparent);
		}
		else
			rotate(tmp);
	}

	template <class T>
	void rotate(node<T> *tmp)
	{
		if (tmp->_lorr == false && tmp->_parent->_lorr == false)
			rotateleft(*tmp->_parent->_parent);
		else if (tmp->_lorr == true && tmp->_parent->_lorr == true)
			rotateright(*tmp->_parent->_parent);
		else if (tmp->_lorr == true && tmp->_parent->_lorr == false)
		{
			rotateright(*tmp->_parent);
			rotateleft(*tmp->_parent->_parent);
		}
		else
		{
			rotateleft(*tmp->_parent);
			rotateright(*tmp->_parent->_parent);
		}
	}

	template < class T >
	void rotateleft(node<T>& ele)
	{
		node<T> tmp(ele);

		ele = *(ele._left);
		if (ele._left != nullptr)
			ele._left->_parent = &ele;
		tmp._left->_left = ele._right;
		if (ele._right != nullptr)
			ele._right->_lorr = false;
		tmp._left->_right = tmp._right;
		if (tmp._right != nullptr)
			tmp._right->_parent = tmp._left;
		ele._right = tmp._left;
		tmp._left->_lorr = true;
		tmp._left->_data = tmp._data;
	}

	template < class T >
	void rotateright(node<T>& ele)
	{
		node<T> tmp(ele);

		ele = *(ele._right);
		if (ele._right != nullptr)
			ele._right->_parent = &ele;
		tmp._right->_right = ele._left;
		if (ele._left != nullptr)
			ele._left->_lorr = true;
		tmp._right->_left = tmp._left;
		if (tmp._left != nullptr)
			tmp._left->_parent = tmp._right;
		ele._left = tmp._right;
		tmp._right->_lorr = false;
		tmp._right->_data = tmp._data;
	}

}


#endif
