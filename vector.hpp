#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <stdexcept>
#include <algorithm>
#include <cstddef>
#include "iterator.hpp"
namespace ft
{
    template <class T, class Alloc = std::allocator<T> >
    class vector
    {
    public:
        typedef T                                        value_type;
        typedef Alloc                                    allocator_type;
        typedef typename allocator_type::reference       reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer         pointer;
        typedef typename allocator_type::const_pointer   const_pointer;
        typedef ptrdiff_t                                difference_type;
        typedef size_t                                   size_type;
        
        // Iterator types
        class iterator : public ft::iterator<ft::random_access_iterator_tag, T>
        {
        private:
            pointer _ptr;
        
        public:
            iterator() : _ptr(NULL) {}
            iterator(pointer ptr) : _ptr(ptr) {}
            iterator(const iterator &other) : _ptr(other._ptr) {}
            ~iterator() {}
            
            iterator &operator=(const iterator &other)
            {
                if (this != &other)
                    _ptr = other._ptr;
                return *this;
            }
            
            reference operator*() const { return *_ptr; }
            pointer operator->() const { return _ptr; }
            
            iterator &operator++()
            {
                ++_ptr;
                return *this;
            }
            
            iterator operator++(int)
            {
                iterator tmp(*this);
                ++(*this);
                return tmp;
            }
            
            iterator &operator--()
            {
                --_ptr;
                return *this;
            }
            
            iterator operator--(int)
            {
                iterator tmp(*this);
                --(*this);
                return tmp;
            }
            
            iterator operator+(difference_type n) const
            {
                return iterator(_ptr + n);
            }
            
            iterator operator-(difference_type n) const
            {
                return iterator(_ptr - n);
            }
            
            iterator &operator+=(difference_type n)
            {
                _ptr += n;
                return *this;
            }
            
            iterator &operator-=(difference_type n)
            {
                _ptr -= n;
                return *this;
            }
            
            reference operator[](difference_type n) const
            {
                return *(_ptr + n);
            }
            
            friend bool operator==(const iterator &lhs, const iterator &rhs)
            {
                return lhs._ptr == rhs._ptr;
            }
            
            friend bool operator!=(const iterator &lhs, const iterator &rhs)
            {
                return lhs._ptr != rhs._ptr;
            }
            
            friend bool operator<(const iterator &lhs, const iterator &rhs)
            {
                return lhs._ptr < rhs._ptr;
            }
            
            friend bool operator<=(const iterator &lhs, const iterator &rhs)
            {
                return lhs._ptr <= rhs._ptr;
            }
            
            friend bool operator>(const iterator &lhs, const iterator &rhs)
            {
                return lhs._ptr > rhs._ptr;
            }
            
            friend bool operator>=(const iterator &lhs, const iterator &rhs)
            {
                return lhs._ptr >= rhs._ptr;
            }
            
            friend difference_type operator-(const iterator &lhs, const iterator &rhs)
            {
                return lhs._ptr - rhs._ptr;
            }
            
            friend iterator operator+(difference_type n, const iterator &it)
            {
                return iterator(it._ptr + n);
            }
        };
        
        class const_iterator : public ft::iterator<ft::random_access_iterator_tag, const T>
        {
        private:
            const_pointer _ptr;
        
        public:
            const_iterator() : _ptr(NULL) {}
            const_iterator(pointer ptr) : _ptr(ptr) {}
            const_iterator(const_pointer ptr) : _ptr(ptr) {}
            const_iterator(const const_iterator &other) : _ptr(other._ptr) {}
            const_iterator(const iterator &other) : _ptr(&(*other)) {}
            ~const_iterator() {}
            
            const_iterator &operator=(const const_iterator &other)
            {
                if (this != &other)
                    _ptr = other._ptr;
                return *this;
            }
            
            const_reference operator*() const { return *_ptr; }
            const_pointer operator->() const { return _ptr; }
            
            const_iterator &operator++()
            {
                ++_ptr;
                return *this;
            }
            
            const_iterator operator++(int)
            {
                const_iterator tmp(*this);
                ++(*this);
                return tmp;
            }
            
            const_iterator &operator--()
            {
                --_ptr;
                return *this;
            }
            
            const_iterator operator--(int)
            {
                const_iterator tmp(*this);
                --(*this);
                return tmp;
            }
            
            const_iterator operator+(difference_type n) const
            {
                return const_iterator(_ptr + n);
            }
            
            const_iterator operator-(difference_type n) const
            {
                return const_iterator(_ptr - n);
            }
            
            const_iterator &operator+=(difference_type n)
            {
                _ptr += n;
                return *this;
            }
            
            const_iterator &operator-=(difference_type n)
            {
                _ptr -= n;
                return *this;
            }
            
            const_reference operator[](difference_type n) const
            {
                return *(_ptr + n);
            }
            
            friend bool operator==(const const_iterator &lhs, const const_iterator &rhs)
            {
                return lhs._ptr == rhs._ptr;
            }
            
            friend bool operator!=(const const_iterator &lhs, const const_iterator &rhs)
            {
                return lhs._ptr != rhs._ptr;
            }
            
            friend bool operator<(const const_iterator &lhs, const const_iterator &rhs)
            {
                return lhs._ptr < rhs._ptr;
            }
            
            friend bool operator<=(const const_iterator &lhs, const const_iterator &rhs)
            {
                return lhs._ptr <= rhs._ptr;
            }
            
            friend bool operator>(const const_iterator &lhs, const const_iterator &rhs)
            {
                return lhs._ptr > rhs._ptr;
            }
            
            friend bool operator>=(const const_iterator &lhs, const const_iterator &rhs)
            {
                return lhs._ptr >= rhs._ptr;
            }
            
            friend difference_type operator-(const const_iterator &lhs, const const_iterator &rhs)
            {
                return lhs._ptr - rhs._ptr;
            }
            
            friend const_iterator operator+(difference_type n, const const_iterator &it)
            {
                return const_iterator(it._ptr + n);
            }
        };
        
        typedef ft::reverse_iterator<iterator>       reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
        
    private:
        allocator_type  _alloc;
        pointer         _start;
        pointer         _finish;
        pointer         _end_of_storage;
        
    public:
        // Constructors
        explicit vector(const allocator_type &alloc = allocator_type())
            : _alloc(alloc), _start(NULL), _finish(NULL), _end_of_storage(NULL) {}
        
        explicit vector(size_type n, const value_type &val = value_type(),
                       const allocator_type &alloc = allocator_type())
            : _alloc(alloc)
        {
            _start = _alloc.allocate(n);
            _finish = _start;
            _end_of_storage = _start + n;
            
            while (n--)
                _alloc.construct(_finish++, val);
        }
        
        template <class InputIterator>
        vector(InputIterator first, InputIterator last,
              const allocator_type &alloc = allocator_type(),
              typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
            : _alloc(alloc)
        {
            difference_type n = ft::distance(first, last);
            
            _start = _alloc.allocate(n);
            _finish = _start;
            _end_of_storage = _start + n;
            
            while (first != last)
                _alloc.construct(_finish++, *first++);
        }
        
        vector(const vector &x) : _alloc(x._alloc)
        {
            size_type n = x.size();
            
            _start = _alloc.allocate(n);
            _finish = _start;
            _end_of_storage = _start + n;
            
            const_pointer src = x._start;
            while (src != x._finish)
                _alloc.construct(_finish++, *src++);
        }
        
        // Destructor
        ~vector()
        {
            clear();
            if (_start)
                _alloc.deallocate(_start, capacity());
        }
        
        // Assignment operator
        vector &operator=(const vector &x)
        {
            if (this != &x)
            {
                clear();
                assign(x.begin(), x.end());
            }
            return *this;
        }
        
        // Iterators
        iterator begin() { return iterator(_start); }
        const_iterator begin() const { return const_iterator(_start); }
        
        iterator end() { return iterator(_finish); }
        const_iterator end() const { return const_iterator(_finish); }
        
        reverse_iterator rbegin() { return reverse_iterator(end()); }
        const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
        
        reverse_iterator rend() { return reverse_iterator(begin()); }
        const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
        
        // Capacity
        size_type size() const { return size_type(_finish - _start); }
        
        size_type max_size() const { return _alloc.max_size(); }
        
        void resize(size_type n, value_type val = value_type())
        {
            if (n < size())
            {
                erase(begin() + n, end());
            }
            else if (n > size())
            {
                insert(end(), n - size(), val);
            }
        }
        
        size_type capacity() const { return size_type(_end_of_storage - _start); }
        
        bool empty() const { return begin() == end(); }
        
        void reserve(size_type n)
        {
            if (n > max_size())
                throw std::length_error("vector::reserve");
            
            if (n > capacity())
            {
                pointer new_start = _alloc.allocate(n);
                pointer new_finish = new_start;
                
                try
                {
                    for (pointer p = _start; p != _finish; ++p)
                    {
                        _alloc.construct(new_finish, *p);
                        ++new_finish;
                    }
                }
                catch (...)
                {
                    for (pointer p = new_start; p != new_finish; ++p)
                        _alloc.destroy(p);
                    _alloc.deallocate(new_start, n);
                    throw;
                }
                
                for (pointer p = _start; p != _finish; ++p)
                    _alloc.destroy(p);
                
                if (_start)
                    _alloc.deallocate(_start, capacity());
                
                _start = new_start;
                _finish = new_finish;
                _end_of_storage = _start + n;
            }
        }
        
        // Element access
        reference operator[](size_type n) { return _start[n]; }
        const_reference operator[](size_type n) const { return _start[n]; }
        
        reference at(size_type n)
        {
            if (n >= size())
                throw std::out_of_range("vector::at");
            return _start[n];
        }
        
        const_reference at(size_type n) const
        {
            if (n >= size())
                throw std::out_of_range("vector::at");
            return _start[n];
        }
        
        reference front() { return *_start; }
        const_reference front() const { return *_start; }
        
        reference back() { return *(_finish - 1); }
        const_reference back() const { return *(_finish - 1); }
        
        // Modifiers
        template <class InputIterator>
        void assign(InputIterator first, InputIterator last,
                   typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
        {
            clear();
            
            difference_type n = ft::distance(first, last);
            
            if (size_type(n) > capacity())
            {
                if (_start)
                    _alloc.deallocate(_start, capacity());
                
                _start = _alloc.allocate(n);
                _finish = _start;
                _end_of_storage = _start + n;
            }
            
            while (first != last)
                _alloc.construct(_finish++, *first++);
        }
        
        void assign(size_type n, const value_type &val)
        {
            clear();
            
            if (n > capacity())
            {
                if (_start)
                    _alloc.deallocate(_start, capacity());
                
                _start = _alloc.allocate(n);
                _finish = _start;
                _end_of_storage = _start + n;
            }
            
            while (n--)
                _alloc.construct(_finish++, val);
        }
        
        void push_back(const value_type &val)
        {
            if (_finish == _end_of_storage)
            {
                size_type new_capacity = capacity() == 0 ? 1 : capacity() * 2;
                reserve(new_capacity);
            }
            
            _alloc.construct(_finish, val);
            ++_finish;
        }
        
        void pop_back()
        {
            if (!empty())
            {
                --_finish;
                _alloc.destroy(_finish);
            }
        }
        
        iterator insert(iterator position, const value_type &val)
        {
            size_type pos_index = position - begin();
            
            insert(position, 1, val);
            
            return begin() + pos_index;
        }
        
        void insert(iterator position, size_type n, const value_type &val)
        {
            if (n == 0)
                return;
            
            size_type pos_index = position - begin();
            
            if (size() + n > capacity())
            {
                size_type new_capacity = capacity() * 2;
                if (new_capacity < size() + n)
                    new_capacity = size() + n;
                
                pointer new_start = _alloc.allocate(new_capacity);
                pointer new_finish = new_start;
                
                try
                {
                    // Copy elements before position
                    for (size_type i = 0; i < pos_index; ++i)
                    {
                        _alloc.construct(new_finish, _start[i]);
                        ++new_finish;
                    }
                    
                    // Insert new elements
                    for (size_type i = 0; i < n; ++i)
                    {
                        _alloc.construct(new_finish, val);
                        ++new_finish;
                    }
                    
                    // Copy elements after position
                    for (size_type i = pos_index; i < size(); ++i)
                    {
                        _alloc.construct(new_finish, _start[i]);
                        ++new_finish;
                    }
                }
                catch (...)
                {
                    for (pointer p = new_start; p != new_finish; ++p)
                        _alloc.destroy(p);
                    _alloc.deallocate(new_start, new_capacity);
                    throw;
                }
                
                // Clean up old storage
                for (pointer p = _start; p != _finish; ++p)
                    _alloc.destroy(p);
                
                if (_start)
                    _alloc.deallocate(_start, capacity());
                
                _start = new_start;
                _finish = new_finish;
                _end_of_storage = _start + new_capacity;
            }
            else
            {
                // Move elements after position to make space
                for (int i = static_cast<int>(size()) - 1; i >= static_cast<int>(pos_index); --i)
                {
                    _alloc.construct(_start + i + n, _start[i]);
                    _alloc.destroy(_start + i);
                }
                
                // Insert new elements
                for (size_type i = 0; i < n; ++i)
                {
                    _alloc.construct(_start + pos_index + i, val);
                }
                
                _finish += n;
            }
        }
        
        template <class InputIterator>
        void insert(iterator position, InputIterator first, InputIterator last,
                   typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
        {
            if (first == last)
                return;
            
            difference_type n = ft::distance(first, last);
            size_type pos_index = position - begin();
            
            if (size() + n > capacity())
            {
                size_type new_capacity = capacity() * 2;
                if (new_capacity < size() + n)
                    new_capacity = size() + n;
                
                pointer new_start = _alloc.allocate(new_capacity);
                pointer new_finish = new_start;
                
                try
                {
                    // Copy elements before position
                    for (size_type i = 0; i < pos_index; ++i)
                    {
                        _alloc.construct(new_finish, _start[i]);
                        ++new_finish;
                    }
                    
                    // Insert new elements
                    for (; first != last; ++first)
                    {
                        _alloc.construct(new_finish, *first);
                        ++new_finish;
                    }
                    
                    // Copy elements after position
                    for (size_type i = pos_index; i < size(); ++i)
                    {
                        _alloc.construct(new_finish, _start[i]);
                        ++new_finish;
                    }
                }
                catch (...)
                {
                    for (pointer p = new_start; p != new_finish; ++p)
                        _alloc.destroy(p);
                    _alloc.deallocate(new_start, new_capacity);
                    throw;
                }
                
                // Clean up old storage
                for (pointer p = _start; p != _finish; ++p)
                    _alloc.destroy(p);
                
                if (_start)
                    _alloc.deallocate(_start, capacity());
                
                _start = new_start;
                _finish = new_finish;
                _end_of_storage = _start + new_capacity;
            }
            else
            {
                // Move elements after position to make space
                for (int i = static_cast<int>(size()) - 1; i >= static_cast<int>(pos_index); --i)
                {
                    _alloc.construct(_start + i + n, _start[i]);
                    _alloc.destroy(_start + i);
                }
                
                // Insert new elements
                for (size_type i = 0; first != last; ++first, ++i)
                {
                    _alloc.construct(_start + pos_index + i, *first);
                }
                
                _finish += n;
            }
        }
        
        iterator erase(iterator position)
        {
            if (position == end())
                return position;
            
            for (iterator it = position; it + 1 != end(); ++it)
            {
                _alloc.destroy(&(*it));
                _alloc.construct(&(*it), *(it + 1));
            }
            
            --_finish;
            _alloc.destroy(_finish);
            
            return position;
        }
        
        iterator erase(iterator first, iterator last)
        {
            if (first == last)
                return first;
            
            iterator result = first;
            iterator new_end = first;
            
            for (iterator it = last; it != end(); ++it, ++new_end)
            {
                _alloc.destroy(&(*first));
                _alloc.construct(&(*first), *it);
                ++first;
            }
            
            while (first != end())
            {
                _alloc.destroy(&(*first));
                ++first;
            }
            
            _finish = _start + (new_end - begin());
            
            return result;
        }
        
        void swap(vector &x)
        {
            ft::swap(_start, x._start);
            ft::swap(_finish, x._finish);
            ft::swap(_end_of_storage, x._end_of_storage);
            ft::swap(_alloc, x._alloc);
        }
        
        void clear()
        {
            for (pointer p = _start; p != _finish; ++p)
                _alloc.destroy(p);
            _finish = _start;
        }
        
        // Allocator
        allocator_type get_allocator() const { return _alloc; }
    };
    
}

#endif // VECTOR_HPP