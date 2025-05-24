#ifndef MULTIMAP_HPP
# define MULTIMAP_HPP

# include "rbtree.hpp"
# include "utility.hpp"
# include <functional>
# include <memory>

namespace ft
{
    template <class Key, class T, class Compare = std::less<Key>, 
              class Allocator = std::allocator<ft::pair<const Key, T> > >
    class multimap
    {
    public:
        typedef Key                                          key_type;
        typedef T                                            mapped_type;
        typedef ft::pair<const Key, T>                       value_type;
        typedef Compare                                      key_compare;
        typedef Allocator                                    allocator_type;
        typedef typename allocator_type::reference           reference;
        typedef typename allocator_type::const_reference     const_reference;
        typedef typename allocator_type::pointer             pointer;
        typedef typename allocator_type::const_pointer       const_pointer;
        typedef std::size_t                                  size_type;
        typedef std::ptrdiff_t                               difference_type;

        class value_compare
        {
            friend class multimap;
            protected:
                 Compare comp;
                 value_compare(Compare c) : comp(c) {}
            public:
                 typedef value_type first_argument_type;
                 typedef value_type second_argument_type;
                 typedef bool result_type;

                 bool operator()(const value_type& x, const value_type& y) const
                 {
                     return comp(x.first, y.first);
                 }
        };

        // Key extractor for rb_tree
        struct key_of_value
        {
            const Key& operator()(const value_type& x) const
            {
                return x.first;
            }
        };

    private:
        typedef rb_tree<Key, value_type, key_of_value, key_compare, allocator_type> tree_type;
        tree_type _tree;

    public:
        typedef typename tree_type::iterator                 iterator;
        typedef typename tree_type::const_iterator           const_iterator;
        typedef typename tree_type::reverse_iterator         reverse_iterator;
        typedef typename tree_type::const_reverse_iterator   const_reverse_iterator;

        // Constructors
        explicit multimap(const key_compare& comp = key_compare(),
                         const allocator_type& alloc = allocator_type())
            : _tree(comp, alloc) {}

        template <class InputIterator>
        multimap(InputIterator first, InputIterator last,
                const key_compare& comp = key_compare(),
                const allocator_type& alloc = allocator_type())
            : _tree(comp, alloc)
        {
            insert(first, last);
        }

        multimap(const multimap& x) : _tree(x._tree) {}

        // Destructor
        ~multimap() {}

        // Assignment operator
        multimap& operator=(const multimap& x)
        {
            _tree = x._tree;
            return *this;
        }

        // Iterators
        iterator begin() { return _tree.begin(); }
        const_iterator begin() const { return _tree.begin(); }
        iterator end() { return _tree.end(); }
        const_iterator end() const { return _tree.end(); }
        reverse_iterator rbegin() { return _tree.rbegin(); }
        const_reverse_iterator rbegin() const { return _tree.rbegin(); }
        reverse_iterator rend() { return _tree.rend(); }
        const_reverse_iterator rend() const { return _tree.rend(); }

        // Capacity
        bool empty() const { return _tree.empty(); }
        size_type size() const { return _tree.size(); }
        size_type max_size() const { return _tree.max_size(); }

        // Modifiers
        iterator insert(const value_type& val)
        {
            return _tree.insert_multi(val);
        }

        iterator insert(iterator position, const value_type& val)
        {
            return _tree.insert_multi(position, val);
        }

        template <class InputIterator>
        void insert(InputIterator first, InputIterator last)
        {
            for (; first != last; ++first)
                insert(*first);
        }

        void erase(iterator position)
        {
            _tree.erase(position);
        }

        size_type erase(const key_type& k)
        {
            return _tree.erase_multi(k);
        }

        void erase(iterator first, iterator last)
        {
            _tree.erase(first, last);
        }

        void swap(multimap& x)
        {
            _tree.swap(x._tree);
        }

        void clear()
        {
            _tree.clear();
        }

        // Observers
        key_compare key_comp() const
        {
            return _tree.key_comp();
        }

        value_compare value_comp() const
        {
            return value_compare(_tree.key_comp());
        }

        // Operations
        iterator find(const key_type& k)
        {
            return _tree.find(k);
        }

        const_iterator find(const key_type& k) const
        {
            return _tree.find(k);
        }

        size_type count(const key_type& k) const
        {
            return _tree.count_multi(k);
        }

        iterator lower_bound(const key_type& k)
        {
            return _tree.lower_bound(k);
        }

        const_iterator lower_bound(const key_type& k) const
        {
            return _tree.lower_bound(k);
        }

        iterator upper_bound(const key_type& k)
        {
            return _tree.upper_bound(k);
        }

        const_iterator upper_bound(const key_type& k) const
        {
            return _tree.upper_bound(k);
        }

        ft::pair<iterator, iterator> equal_range(const key_type& k)
        {
            return _tree.equal_range(k);
        }

        ft::pair<const_iterator, const_iterator> equal_range(const key_type& k) const
        {
            return _tree.equal_range(k);
        }

        // Allocator
        allocator_type get_allocator() const
        {
            return _tree.get_allocator();
        }
    };

    // Non-member function overloads
    template <class Key, class T, class Compare, class Alloc>
    bool operator==(const multimap<Key, T, Compare, Alloc>& lhs,
                   const multimap<Key, T, Compare, Alloc>& rhs)
    {
        return lhs.size() == rhs.size() && 
               ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator!=(const multimap<Key, T, Compare, Alloc>& lhs,
                   const multimap<Key, T, Compare, Alloc>& rhs)
    {
        return !(lhs == rhs);
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator<(const multimap<Key, T, Compare, Alloc>& lhs,
                  const multimap<Key, T, Compare, Alloc>& rhs)
    {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(),
                                          rhs.begin(), rhs.end());
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator<=(const multimap<Key, T, Compare, Alloc>& lhs,
                   const multimap<Key, T, Compare, Alloc>& rhs)
    {
        return !(rhs < lhs);
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator>(const multimap<Key, T, Compare, Alloc>& lhs,
                  const multimap<Key, T, Compare, Alloc>& rhs)
    {
        return rhs < lhs;
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator>=(const multimap<Key, T, Compare, Alloc>& lhs,
                   const multimap<Key, T, Compare, Alloc>& rhs)
    {
        return !(lhs < rhs);
    }

    template <class Key, class T, class Compare, class Alloc>
    void swap(multimap<Key, T, Compare, Alloc>& x,
             multimap<Key, T, Compare, Alloc>& y)
    {
        x.swap(y);
    }
}

#endif