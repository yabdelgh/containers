#ifndef __MAP_HPP__
#define __MAP_HPP__

#include "utility.hpp"
#include "redblacktree.hpp"

namespace ft
{
	template < class Key,                                 // map::key_type
           class T,                                       // map::mapped_type
           class Compare = less<Key>,                     // map::key_compare
           class Alloc = allocator<pair<const Key,T> >    // map::allocator_typ
	>
	class map
	{
		public;
		typedef Key											key_type;
		typedef T                   						mapped_type;
		typedef ft::pair<const _Key, _Tp>        			value_type;
		typedef Compare                  					key_compare;
		typedef Alloc                    					allocator_type;
		typedef typename allocator_type::reference          reference;
 		typedef typename allocator_type::const_reference    const_reference;
		typedef typename allocator_type::pointer            pointer;
		typedef typename allocator_type::const_pointer      const_pointer;
		typedef typename allocator_type::difference_type    difference_type;
		typedef typename allocator_type::size_type          size_type;
		//iterator
		//const iterator
		//typedef ft::reverse_iterator<iterator>                  reverse_iterator;
		//typedef ft::reverse_iterator<const_iterator>            const_reverse_iterator;

		private:
		rbt<Key, T, Compare, Alloc> tree;
		
		public:
  		class value_compare: public ft::binary_function<value_type, value_type, bool>
		{
			friend class map<_Key, _Tp, _Compare, _Alloc>;
  			
			protected:
			_Compare comp;
			value_compare(_Compare __c): comp(__c) { }
			
			public:
			bool operator()(const value_type& __x, const value_type& __y) const
			{
				return comp(__x.first, __y.first);
			}
  		};

		/******************Capacity***********************/
		bool empty() const
		{
			return (tree.empty());
		}
	
		size_type size() const
		{
			return (tree.size());
		}
		
		size_type max_size() const
		{
			return (tree.max_size());
		}

		/******************Observers**********************/

		key_compare key_comp() const
		{
			return (tree.key_comp());
		}
		
		value_compare value_comp() const
		{
			return (tree.value_comp());
		}
	
	};
}

#endif
