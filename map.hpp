#ifndef MAP_HPP
# define MAP_HPP

# include "multimap.hpp"  // Include the multimap implementation

namespace ft
{
    // Forward declarations
    template <class Key, class T, class Compare = std::less<Key>,
              class Allocator = std::allocator<ft::pair<const Key, T> > >
    class map;

    template <class Key, class T, class Compare, class Allocator>
    bool operator==(const map<Key, T, Compare, Allocator>& lhs,
                   const map<Key, T, Compare, Allocator>& rhs);

    template <class Key, class T, class Compare, class Allocator>
    bool operator<(const map<Key, T, Compare, Allocator>& lhs,
                  const map<Key, T, Compare, Allocator>& rhs);

    template <class Key, class T, class Compare, class Allocator>
    class map
    {
    public:
        typedef Key                                      key_type;
        typedef T                                        mapped_type;
        typedef ft::pair<const Key, T>                   value_type;
        typedef Compare                                  key_compare;
        typedef Allocator                                allocator_type;
        typedef typename allocator_type::reference       reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer         pointer;
        typedef typename allocator_type::const_pointer   const_pointer;
        typedef typename allocator_type::size_type       size_type;
        typedef typename allocator_type::difference_type difference_type;

        class value_compare
        {
            friend class map;
        protected:
            key_compare comp;
            value_compare(const key_compare &c) : comp(c) {}
        public:
            bool operator()(const value_type& x, const value_type& y) const
            {
                return comp(x.first, y.first);
            }
        };

    private:
        typedef ft::multimap<Key, T, Compare, Allocator> multimap_type;
        multimap_type _multimap;

    public:
        typedef typename multimap_type::iterator               iterator;
        typedef typename multimap_type::const_iterator         const_iterator;
        typedef typename multimap_type::reverse_iterator       reverse_iterator;
        typedef typename multimap_type::const_reverse_iterator const_reverse_iterator;

        // Constructors
        explicit map(const key_compare& comp = key_compare(),
                    const allocator_type& alloc = allocator_type())
            : _multimap(comp, alloc) {}

        template <class InputIterator>
        map(InputIterator first, InputIterator last,
           const key_compare& comp = key_compare(),
           const allocator_type& alloc = allocator_type())
            : _multimap(comp, alloc)
        {
            insert(first, last);
        }

        map(const map& x) : _multimap(x._multimap) {}

        ~map() {}

        map& operator=(const map& x)
        {
            if (this != &x)
                _multimap = x._multimap;
            return *this;
        }

        // Iterators
        iterator begin() { return _multimap.begin(); }
        const_iterator begin() const { return _multimap.begin(); }
        iterator end() { return _multimap.end(); }
        const_iterator end() const { return _multimap.end(); }
        reverse_iterator rbegin() { return _multimap.rbegin(); }
        const_reverse_iterator rbegin() const { return _multimap.rbegin(); }
        reverse_iterator rend() { return _multimap.rend(); }
        const_reverse_iterator rend() const { return _multimap.rend(); }

        // Capacity
        bool empty() const { return _multimap.empty(); }
        size_type size() const { return _multimap.size(); }
        size_type max_size() const { return _multimap.max_size(); }

        // Element access
        mapped_type& operator[](const key_type& k)
        {
            iterator it = find(k);
            if (it == end())
                it = _multimap.insert(ft::make_pair(k, mapped_type()));
            return it->second;
        }

        mapped_type& at(const key_type& k)
        {
            iterator it = find(k);
            if (it == end())
                throw std::out_of_range("map::at: key not found");
            return it->second;
        }

        const mapped_type& at(const key_type& k) const
        {
            const_iterator it = find(k);
            if (it == end())
                throw std::out_of_range("map::at: key not found");
            return it->second;
        }

        // Modifiers
        ft::pair<iterator, bool> insert(const value_type& val)
        {
            iterator it = find(val.first);
            if (it != end())
                return ft::make_pair(it, false);
            return ft::make_pair(_multimap.insert(val), true);
        }

        iterator insert(iterator position, const value_type& val)
        {
            iterator it = find(val.first);
            if (it != end())
                return it;
            return _multimap.insert(position, val);
        }

        template <class InputIterator>
        void insert(InputIterator first, InputIterator last)
        {
            for (; first != last; ++first)
                insert(*first);
        }

        void erase(iterator position)
        {
            _multimap.erase(position);
        }

        size_type erase(const key_type& k)
        {
            iterator it = find(k);
            if (it == end())
                return 0;
            _multimap.erase(it);
            return 1;
        }

        void erase(iterator first, iterator last)
        {
            _multimap.erase(first, last);
        }

        void swap(map& x)
        {
            _multimap.swap(x._multimap);
        }

        void clear()
        {
            _multimap.clear();
        }

        // Observers
        key_compare key_comp() const
        {
            return _multimap.key_comp();
        }

        value_compare value_comp() const
        {
            return value_compare(_multimap.key_comp());
        }

        // Operations
        iterator find(const key_type& k)
        {
            return _multimap.find(k);
        }

        const_iterator find(const key_type& k) const
        {
            return _multimap.find(k);
        }

        size_type count(const key_type& k) const
        {
            return _multimap.count(k) > 0 ? 1 : 0;
        }

        iterator lower_bound(const key_type& k)
        {
            return _multimap.lower_bound(k);
        }

        const_iterator lower_bound(const key_type& k) const
        {
            return _multimap.lower_bound(k);
        }

        iterator upper_bound(const key_type& k)
        {
            return _multimap.upper_bound(k);
        }

        const_iterator upper_bound(const key_type& k) const
        {
            return _multimap.upper_bound(k);
        }

        ft::pair<iterator, iterator> equal_range(const key_type& k)
        {
            return _multimap.equal_range(k);
        }

        ft::pair<const_iterator, const_iterator> equal_range(const key_type& k) const
        {
            return _multimap.equal_range(k);
        }

        allocator_type get_allocator() const
        {
            return _multimap.get_allocator();
        }
    };

    // Non-member functions
    template <class Key, class T, class Compare, class Allocator>
    bool operator==(const map<Key, T, Compare, Allocator>& lhs,
                   const map<Key, T, Compare, Allocator>& rhs)
    {
        if (lhs.size() != rhs.size())
            return false;
        
        typename map<Key, T, Compare, Allocator>::const_iterator lit = lhs.begin();
        typename map<Key, T, Compare, Allocator>::const_iterator rit = rhs.begin();
        
        for (; lit != lhs.end() && rit != rhs.end(); ++lit, ++rit)
        {
            if (*lit != *rit)
                return false;
        }
        return lit == lhs.end() && rit == rhs.end();
    }

    template <class Key, class T, class Compare, class Allocator>
    bool operator!=(const map<Key, T, Compare, Allocator>& lhs,
                   const map<Key, T, Compare, Allocator>& rhs)
    {
        return !(lhs == rhs);
    }

    template <class Key, class T, class Compare, class Allocator>
    bool operator<(const map<Key, T, Compare, Allocator>& lhs,
                  const map<Key, T, Compare, Allocator>& rhs)
    {
        typename map<Key, T, Compare, Allocator>::const_iterator lit = lhs.begin();
        typename map<Key, T, Compare, Allocator>::const_iterator rit = rhs.begin();
        
        for (; lit != lhs.end() && rit != rhs.end(); ++lit, ++rit)
        {
            if (*lit < *rit)
                return true;
            if (*rit < *lit)
                return false;
        }
        return lit != lhs.end() ? false : rit != rhs.end();
    }

    template <class Key, class T, class Compare, class Allocator>
    bool operator<=(const map<Key, T, Compare, Allocator>& lhs,
                   const map<Key, T, Compare, Allocator>& rhs)
    {
        return !(rhs < lhs);
    }

    template <class Key, class T, class Compare, class Allocator>
    bool operator>(const map<Key, T, Compare, Allocator>& lhs,
                  const map<Key, T, Compare, Allocator>& rhs)
    {
        return rhs < lhs;
    }

    template <class Key, class T, class Compare, class Allocator>
    bool operator>=(const map<Key, T, Compare, Allocator>& lhs,
                   const map<Key, T, Compare, Allocator>& rhs)
    {
        return !(lhs < rhs);
    }

    template <class Key, class T, class Compare, class Allocator>
    void swap(map<Key, T, Compare, Allocator>& x,
             map<Key, T, Compare, Allocator>& y)
    {
        x.swap(y);
    }
}

#endif