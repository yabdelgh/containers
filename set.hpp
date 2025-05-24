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
    class multiset;

    template <class T, class Compare = std::less<T>,
              class Allocator = std::allocator<T> >
    class set;

    template <class T, class Compare, class Allocator>
    bool operator==(const multiset<T, Compare, Allocator>& lhs,
                   const multiset<T, Compare, Allocator>& rhs);

    template <class T, class Compare, class Allocator>
    bool operator<(const multiset<T, Compare, Allocator>& lhs,
                  const multiset<T, Compare, Allocator>& rhs);

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
    class multiset
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
        typedef typename tree_type::iterator         iterator;
        typedef typename tree_type::const_iterator         const_iterator;
        typedef typename tree_type::reverse_iterator reverse_iterator;
        typedef typename tree_type::const_reverse_iterator const_reverse_iterator;

        // Constructors, destructor and assignment operator
        explicit multiset(const key_compare& comp = key_compare(),
                         const allocator_type& alloc = allocator_type())
            : _tree(comp, alloc) {}

        template <class InputIterator>
        multiset(InputIterator first, InputIterator last,
                const key_compare& comp = key_compare(),
                const allocator_type& alloc = allocator_type())
            : _tree(comp, alloc)
        {
            insert(first, last);
        }

        multiset(const multiset& x) : _tree(x._tree) {}

        ~multiset() {}

        multiset& operator=(const multiset& x)
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
        iterator insert(const value_type& val)
        {
            return _tree.insert(val).first;
        }

        iterator insert(iterator position, const value_type& val)
        {
            (void)position;
            return _tree.insert(val).first;
        }

        template <class InputIterator>
        void insert(InputIterator first, InputIterator last)
        {
            for (; first != last; ++first)
                _tree.insert(*first);
        }

        void erase(iterator position)
        {
            if (position != end())
                _tree.erase(*position);
        }

        size_type erase(const key_type& k)
        {
            return _tree.erase(k);
        }

        void erase(iterator first, iterator last)
        {
            while (first != last)
            {
                value_type val = *first;
                ++first;
                _tree.erase(val);
            }
        }

        void swap(multiset& x)
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
        typedef multiset<key_type, key_compare, allocator_type> multiset_type;
        multiset_type _mset;

    public:
        // Iterator types
        typedef typename multiset_type::iterator         iterator;
        typedef typename multiset_type::const_iterator         const_iterator;
        typedef typename multiset_type::reverse_iterator reverse_iterator;
        typedef typename multiset_type::const_reverse_iterator const_reverse_iterator;

        // Constructors, destructor and assignment operator
        explicit set(const key_compare& comp = key_compare(),
                    const allocator_type& alloc = allocator_type())
            : _mset(comp, alloc) {}

        template <class InputIterator>
        set(InputIterator first, InputIterator last,
           const key_compare& comp = key_compare(),
           const allocator_type& alloc = allocator_type())
            : _mset(comp, alloc)
        {
            insert(first, last);
        }

        set(const set& x) : _mset(x._mset) {}

        ~set() {}

        set& operator=(const set& x)
        {
            if (this != &x)
                _mset = x._mset;
            return *this;
        }

        // Iterators
        iterator begin() { return _mset.begin(); }
        const_iterator begin() const { return _mset.begin(); }
        iterator end() { return _mset.end(); }
        const_iterator end() const { return _mset.end(); }
        reverse_iterator rbegin() { return _mset.rbegin(); }
        const_reverse_iterator rbegin() const { return _mset.rbegin(); }
        reverse_iterator rend() { return _mset.rend(); }
        const_reverse_iterator rend() const { return _mset.rend(); }

        // Capacity
        bool empty() const { return _mset.empty(); }
        size_type size() const { return _mset.size(); }
        size_type max_size() const { return _mset.max_size(); }

        // Modifiers
        ft::pair<iterator, bool> insert(const value_type& val)
        {
            if (_mset.find(val) != _mset.end())
                return ft::pair<iterator, bool>(_mset.find(val), false);
            return ft::pair<iterator, bool>(_mset.insert(val), true);
        }

        iterator insert(iterator position, const value_type& val)
        {
            if (_mset.find(val) != _mset.end())
                return _mset.find(val);
            (void)position;
            return _mset.insert(val);
        }

        template <class InputIterator>
        void insert(InputIterator first, InputIterator last)
        {
            for (; first != last; ++first)
                insert(*first);
        }

        void erase(iterator position)
        {
            _mset.erase(position);
        }

        size_type erase(const key_type& k)
        {
            if (_mset.find(k) != _mset.end())
            {
                _mset.erase(k);
                return 1;
            }
            return 0;
        }

        void erase(iterator first, iterator last)
        {
            _mset.erase(first, last);
        }

        void swap(set& x)
        {
            _mset.swap(x._mset);
        }

        void clear()
        {
            _mset.clear();
        }

        // Observers
        key_compare key_comp() const
        {
            return _mset.key_comp();
        }

        value_compare value_comp() const
        {
            return _mset.value_comp();
        }

        // Operations
        iterator find(const key_type& k)
        {
            return _mset.find(k);
        }

        const_iterator find(const key_type& k) const
        {
            return _mset.find(k);
        }

        size_type count(const key_type& k) const
        {
            return _mset.find(k) != _mset.end() ? 1 : 0;
        }

        iterator lower_bound(const key_type& k)
        {
            return _mset.lower_bound(k);
        }

        const_iterator lower_bound(const key_type& k) const
        {
            return _mset.lower_bound(k);
        }

        iterator upper_bound(const key_type& k)
        {
            return _mset.upper_bound(k);
        }

        const_iterator upper_bound(const key_type& k) const
        {
            return _mset.upper_bound(k);
        }

        ft::pair<iterator, iterator> equal_range(const key_type& k)
        {
            return _mset.equal_range(k);
        }

        ft::pair<const_iterator, const_iterator> equal_range(const key_type& k) const
        {
            return _mset.equal_range(k);
        }

        // Allocator
        allocator_type get_allocator() const
        {
            return _mset.get_allocator();
        }
    };

    // Non-member functions for multiset
    template <class T, class Compare, class Allocator>
    bool operator==(const multiset<T, Compare, Allocator>& lhs,
                   const multiset<T, Compare, Allocator>& rhs)
    {
        if (lhs.size() != rhs.size())
            return false;
        
        typename multiset<T, Compare, Allocator>::const_iterator lit = lhs.begin();
        typename multiset<T, Compare, Allocator>::const_iterator rit = rhs.begin();
        
        for (; lit != lhs.end() && rit != rhs.end(); ++lit, ++rit)
        {
            if (*lit != *rit)
                return false;
        }
        return lit == lhs.end() && rit == rhs.end();
    }

    template <class T, class Compare, class Allocator>
    bool operator!=(const multiset<T, Compare, Allocator>& lhs,
                   const multiset<T, Compare, Allocator>& rhs)
    {
        return !(lhs == rhs);
    }

    template <class T, class Compare, class Allocator>
    bool operator<(const multiset<T, Compare, Allocator>& lhs,
                  const multiset<T, Compare, Allocator>& rhs)
    {
        typename multiset<T, Compare, Allocator>::const_iterator lit = lhs.begin();
        typename multiset<T, Compare, Allocator>::const_iterator rit = rhs.begin();
        
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
    bool operator<=(const multiset<T, Compare, Allocator>& lhs,
                   const multiset<T, Compare, Allocator>& rhs)
    {
        return !(rhs < lhs);
    }

    template <class T, class Compare, class Allocator>
    bool operator>(const multiset<T, Compare, Allocator>& lhs,
                  const multiset<T, Compare, Allocator>& rhs)
    {
        return rhs < lhs;
    }

    template <class T, class Compare, class Allocator>
    bool operator>=(const multiset<T, Compare, Allocator>& lhs,
                   const multiset<T, Compare, Allocator>& rhs)
    {
        return !(lhs < rhs);
    }

    template <class T, class Compare, class Allocator>
    void swap(multiset<T, Compare, Allocator>& x,
             multiset<T, Compare, Allocator>& y)
    {
        x.swap(y);
    }

    // Non-member functions for set
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