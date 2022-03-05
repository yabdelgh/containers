#ifndef __RED_BLACK_TREE__HPP
#define __RED_BLACK_TREE__HPP

#include <iostream>
#include "utility.hpp"
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


	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator< ft::pair<const Key, T> > >
	class rbt
	{
		public:
		typedef Key									key_type;
		typedef Alloc								allocator_type;
		typedef T									mapped_type;
		typedef Compare								key_compare;
		typedef typename allocator_type::value_type	value_type;

		private:
		node<value_type> *_root;
		allocator_type _alloc;
		

		public:
		rbt() : _root(nullptr) {}
		rbt(const rbt& copy) : _root(copy._root) {}

		public:
		rbt& operator=(const rbt& copy)
		{
			_root = copy._root;
			return (*this);
		}

		public:
		void insert(const value_type& data);
	//	friend void insert(const value_type& data);
		/*void _delete(node<value_type> *tmp);
		void _delete(const T& data);
		node<T> *search(const T& data);
		void replace(node<value_type> *tmp, node<value_type> *new_node);
		void delete_fix(node<value_type> *node);*/

		public:
		node<value_type> *base()
		{
			return (_root);
		}

		public:
		virtual ~rbt() {}
	};

	template <class Key, class T, class Compare, class Alloc>
	void
	rbt<Key, T, Compare, Alloc>::insert(const value_type& data)
	{
		node<value_type> *tmp;

		if (_root == nullptr)
			_root = new node<value_type>(new value_type(data), false);
		tmp = _root;
		while (*tmp->_data != data)
		{
			if (data > *tmp->_data)
			{
				if (tmp->_right == nullptr)
					tmp->_right = new node<value_type>(new value_type(data), true, true, tmp);
				tmp = tmp->_right;
			}
			else
			{
				if (tmp->_left == nullptr)
					tmp->_left = new node<value_type>(new value_type(data), true, false, tmp);
				tmp = tmp->_left;
			}
		}
		if (tmp->_parent != nullptr && tmp->_parent->_color == true)
			balance(_root, tmp);
	}
	/*template < class T >
	void
	rbt<T>::_delete(const T& data)
	{
		node<T> *tmp;
		tmp = search(data);
		if (tmp != nullptr)
			_delete(tmp);
	}

	template < class T >
	void
	rbt<T>::_delete(node<T> *tmp)
	{
		while (tmp->_left != nullptr && tmp->_right != nullptr)
		{
			node<T> *s = tmp->successor();
			tmp->_data = s->_data;
			tmp = s;
		}
		if (tmp->_color == true)
				replace(tmp, nullptr);
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
				replace(tmp, nullptr);
				if (tmp->_lorr)
					delete_fix(tmp->_parent->_left);
				else
					delete_fix(tmp->_parent->_right);
			}
		}
	}

	template < class T >
	void
	rbt<T>::delete_fix(node<T> *node)
	{
		if (!is_red(node) && !is_red(node->_left) && !is_red(node->_right))
		{
			node->_color = true;
			if (node->_parent == _root || node->_parent->_color == true)
				node->_parent->_color = false;
			else
			{
				if (node->_parent->_lorr)
					delete_fix(node->_parent->_parent->_left);
				else
					delete_fix(node->_parent->_parent->_right);

			}
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
	
	template < class T >
	void
	rbt<T>::replace(node<value_type> *tmp, node<value_type> *new_node)
	{
		if (tmp->_lorr == true)
			tmp->_parent->_right = new_node;
		else
			tmp->_parent->_left = new_node;
		if (new_node != nullptr)
			new_node->_parent = tmp->_parent;
		// free
	}

	template < class T >
	node<T>*
	rbt<T>::search(const T& data)
	{
		node<T> *tmp;
		
		tmp = _root;
		while (tmp != nullptr)
		{
			if (data == *(tmp->_data))
				return (tmp);
			else if (data > (*tmp->_data))
				tmp = tmp->_right;
			else
				tmp = tmp->_left;
		}
		return (nullptr);
	}*/

	
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
