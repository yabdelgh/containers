#ifndef SET_HPP
# define SET_HPP

# include <memory>      // std::allocator
# include <functional>  // std::less
# include <algorithm>   // std::swap
# include <cstddef>     // std::ptrdiff_t
# include <limits>      // std::numeric_limits
# include "utility.hpp" // ft::pair
# include "rbtree.hpp"

namespace ft
{
    // Forward declarations
    template <class T, class Compare = std::less<T>,
              class Allocator = std::allocator<T> >
    class set;

    template <class T, class Compare, class Allocator>
    bool operator==(const set<T, Compare, Allocator>& lhs,
                   const set<T, Compare, Allocator>& rhs);

    template <class T, class Compare, class Allocator>
    bool operator<(const set<T, Compare, Allocator>& lhs,
                  const set<T, Compare, Allocator>& rhs);

    // Identity functor to use with the rb_tree
    template <class T>
    struct Identity
    {
        T& operator()(T& x) const
        {
            return x;
        }
        
        const T& operator()(const T& x) const
        {
            return x;
        }
    };
    template <class T, class Compare, class Allocator>
    class set
    {
    public:
        typedef T                                        key_type;
        typedef T                                        value_type;
        typedef Compare                                  key_compare;
        typedef Compare                                  value_compare;
        typedef Allocator                                allocator_type;
        typedef typename allocator_type::reference       reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer         pointer;
        typedef typename allocator_type::const_pointer   const_pointer;
        typedef typename allocator_type::size_type       size_type;
        typedef typename allocator_type::difference_type difference_type;

    private:
        typedef rb_tree<key_type, value_type, Identity<value_type>, key_compare, allocator_type> tree_type;
        tree_type _tree;

    public:
        // Iterator types
        // For set, all iterators are const iterators (set elements shouldn't be modified)
        // But we need to use regular iterators internally to match rb_tree API
        typedef typename tree_type::iterator         iterator;
        typedef typename tree_type::const_iterator         const_iterator;
        typedef typename tree_type::reverse_iterator reverse_iterator;
        typedef typename tree_type::const_reverse_iterator const_reverse_iterator;

        // Constructors, destructor and assignment operator
        explicit set(const key_compare& comp = key_compare(),
                    const allocator_type& alloc = allocator_type())
            : _tree(comp, alloc) {}

        template <class InputIterator>
        set(InputIterator first, InputIterator last,
           const key_compare& comp = key_compare(),
           const allocator_type& alloc = allocator_type())
            : _tree(comp, alloc)
        {
            insert(first, last);
        }

        set(const set& x) : _tree(x._tree) {}

        ~set() {}

        set& operator=(const set& x)
        {
            if (this != &x)
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
        ft::pair<iterator, bool> insert(const value_type& val)
        {
            return _tree.insert(val);
        }

        // Since rb_tree::insert with hint returns an iterator but we need a const_iterator,
        // we need to provide a custom implementation that ignores the hint
        iterator insert(iterator position, const value_type& val)
        {
            // Ignore the position hint, which is a const_iterator, 
            // since rb_tree expects a non-const iterator
            (void)position;
            return _tree.insert(val).first;
        }

        template <class InputIterator>
        void insert(InputIterator first, InputIterator last)
        {
            for (; first != last; ++first)
                _tree.insert(*first);
        }

        // For set, we need custom erase implementation 
        // that works with const_iterator
        void erase(iterator position)
        {
            // We need to find the element by its key since we cannot convert const_iterator to iterator
            if (position != end())
                _tree.erase(*position);
        }

        size_type erase(const key_type& k)
        {
            return _tree.erase(k);
        }

        void erase(iterator first, iterator last)
        {
            // Erase elements one by one by their keys
            while (first != last)
            {
                // Make a copy of the value before incrementing the iterator
                value_type val = *first;
                ++first;
                _tree.erase(val);
            }
        }

        void swap(set& x)
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
            return _tree.key_comp();
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
            return _tree.count(k);
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

    // Non-member functions
    template <class T, class Compare, class Allocator>
    bool operator==(const set<T, Compare, Allocator>& lhs,
                   const set<T, Compare, Allocator>& rhs)
    {
        if (lhs.size() != rhs.size())
            return false;
        
        typename set<T, Compare, Allocator>::const_iterator lit = lhs.begin();
        typename set<T, Compare, Allocator>::const_iterator rit = rhs.begin();
        
        for (; lit != lhs.end() && rit != rhs.end(); ++lit, ++rit)
        {
            if (*lit != *rit)
                return false;
        }
        return lit == lhs.end() && rit == rhs.end();
    }

    template <class T, class Compare, class Allocator>
    bool operator!=(const set<T, Compare, Allocator>& lhs,
                   const set<T, Compare, Allocator>& rhs)
    {
        return !(lhs == rhs);
    }

    template <class T, class Compare, class Allocator>
    bool operator<(const set<T, Compare, Allocator>& lhs,
                  const set<T, Compare, Allocator>& rhs)
    {
        typename set<T, Compare, Allocator>::const_iterator lit = lhs.begin();
        typename set<T, Compare, Allocator>::const_iterator rit = rhs.begin();
        
        for (; lit != lhs.end() && rit != rhs.end(); ++lit, ++rit)
        {
            if (*lit < *rit)
                return true;
            if (*rit < *lit)
                return false;
        }
        return lit == lhs.end() && rit != rhs.end();
    }

    template <class T, class Compare, class Allocator>
    bool operator<=(const set<T, Compare, Allocator>& lhs,
                   const set<T, Compare, Allocator>& rhs)
    {
        return !(rhs < lhs);
    }

    template <class T, class Compare, class Allocator>
    bool operator>(const set<T, Compare, Allocator>& lhs,
                  const set<T, Compare, Allocator>& rhs)
    {
        return rhs < lhs;
    }

    template <class T, class Compare, class Allocator>
    bool operator>=(const set<T, Compare, Allocator>& lhs,
                   const set<T, Compare, Allocator>& rhs)
    {
        return !(lhs < rhs);
    }

    template <class T, class Compare, class Allocator>
    void swap(set<T, Compare, Allocator>& x,
             set<T, Compare, Allocator>& y)
    {
        x.swap(y);
    }
}

#endif