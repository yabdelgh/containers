#ifndef LIST_HPP
#define LIST_HPP

#include <memory>
#include <limits>
#include <algorithm>
#include <cstddef>

namespace ft {

// C++98 type traits for SFINAE
template<bool B, class T = void>
struct enable_if {};

template<class T>
struct enable_if<true, T> { typedef T type; };

// is_integral type trait
template<class T>
struct is_integral { static const bool value = false; };

template<> struct is_integral<bool> { static const bool value = true; };
template<> struct is_integral<char> { static const bool value = true; };
template<> struct is_integral<signed char> { static const bool value = true; };
template<> struct is_integral<unsigned char> { static const bool value = true; };
template<> struct is_integral<wchar_t> { static const bool value = true; };
template<> struct is_integral<short> { static const bool value = true; };
template<> struct is_integral<unsigned short> { static const bool value = true; };
template<> struct is_integral<int> { static const bool value = true; };
template<> struct is_integral<unsigned int> { static const bool value = true; };
template<> struct is_integral<long> { static const bool value = true; };
template<> struct is_integral<unsigned long> { static const bool value = true; };

template <typename T>
struct ListNode {
    T data;
    ListNode* prev;
    ListNode* next;

    ListNode() : prev(NULL), next(NULL) {}
    explicit ListNode(const T& val) : data(val), prev(NULL), next(NULL) {}
};

template <typename T>
class ListIterator {
public:
    typedef T                   value_type;
    typedef T&                  reference;
    typedef T*                  pointer;
    typedef std::ptrdiff_t      difference_type;
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef ListNode<T>*        node_pointer;

private:
    node_pointer _node;

public:
    ListIterator() : _node(NULL) {}
    explicit ListIterator(node_pointer node) : _node(node) {}
    ListIterator(const ListIterator& other) : _node(other._node) {}
    ~ListIterator() {}

    ListIterator& operator=(const ListIterator& other) {
        if (this != &other)
            _node = other._node;
        return *this;
    }

    reference operator*() const { return _node->data; }
    pointer operator->() const { return &(_node->data); }

    ListIterator& operator++() {
        _node = _node->next;
        return *this;
    }

    ListIterator operator++(int) {
        ListIterator tmp(*this);
        _node = _node->next;
        return tmp;
    }

    ListIterator& operator--() {
        _node = _node->prev;
        return *this;
    }

    ListIterator operator--(int) {
        ListIterator tmp(*this);
        _node = _node->prev;
        return tmp;
    }

    bool operator==(const ListIterator& rhs) const { return _node == rhs._node; }
    bool operator!=(const ListIterator& rhs) const { return _node != rhs._node; }

    node_pointer getNode() const { return _node; }
};

// Const List Iterator
template <typename T>
class ConstListIterator {
public:
    typedef T                   value_type;
    typedef const T&            reference;
    typedef const T*            pointer;
    typedef std::ptrdiff_t      difference_type;
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef const ListNode<T>*  node_pointer;
    typedef ListIterator<T>     iterator;

private:
    node_pointer _node;

public:
    ConstListIterator() : _node(NULL) {}
    explicit ConstListIterator(node_pointer node) : _node(node) {}
    ConstListIterator(const ConstListIterator& other) : _node(other._node) {}
    ConstListIterator(const iterator& other) : _node(other.getNode()) {}
    ~ConstListIterator() {}

    ConstListIterator& operator=(const ConstListIterator& other) {
        if (this != &other)
            _node = other._node;
        return *this;
    }

    reference operator*() const { return _node->data; }
    pointer operator->() const { return &(_node->data); }

    ConstListIterator& operator++() {
        _node = _node->next;
        return *this;
    }

    ConstListIterator operator++(int) {
        ConstListIterator tmp(*this);
        _node = _node->next;
        return tmp;
    }

    ConstListIterator& operator--() {
        _node = _node->prev;
        return *this;
    }

    ConstListIterator operator--(int) {
        ConstListIterator tmp(*this);
        _node = _node->prev;
        return tmp;
    }

    bool operator==(const ConstListIterator& rhs) const { return _node == rhs._node; }
    bool operator!=(const ConstListIterator& rhs) const { return _node != rhs._node; }

    node_pointer getNode() const { return _node; }
};

// Reverse Iterator Adapter
template <typename Iterator>
class ReverseIterator {
public:
    typedef Iterator                                                iterator_type;
    typedef typename Iterator::value_type                          value_type;
    typedef typename Iterator::reference                           reference;
    typedef typename Iterator::pointer                             pointer;
    typedef typename Iterator::difference_type                     difference_type;
    typedef typename Iterator::iterator_category                   iterator_category;

private:
    iterator_type _base;

public:
    ReverseIterator() : _base() {}
    explicit ReverseIterator(iterator_type it) : _base(it) {}
    
    template <typename Iter>
    ReverseIterator(const ReverseIterator<Iter>& rev_it) : _base(rev_it.base()) {}
    
    ~ReverseIterator() {}

    iterator_type base() const { return _base; }

    reference operator*() const {
        iterator_type tmp = _base;
        return *--tmp;
    }

    pointer operator->() const {
        return &(operator*());
    }

    ReverseIterator& operator++() {
        --_base;
        return *this;
    }

    ReverseIterator operator++(int) {
        ReverseIterator tmp(*this);
        --_base;
        return tmp;
    }

    ReverseIterator& operator--() {
        ++_base;
        return *this;
    }

    ReverseIterator operator--(int) {
        ReverseIterator tmp(*this);
        ++_base;
        return tmp;
    }

    bool operator==(const ReverseIterator& rhs) const { return _base == rhs._base; }
    bool operator!=(const ReverseIterator& rhs) const { return _base != rhs._base; }
};

// For C++98 SFINAE template selection
// template <typename T>
// struct is_iterator_tagged {
//     typedef char one;
//     typedef struct { char arr[2]; } two;

//     template <typename U>
//     static one test(typename U::iterator_category*);
    
//     template <typename U>
//     static two test(...);

//     enum { value = sizeof(test<T>(0)) == 1 };
// };

// List container
template <typename T, typename Alloc = std::allocator<T> >
class list {
public:
    // Member types
    typedef T                                                   value_type;
    typedef Alloc                                               allocator_type;
    typedef typename allocator_type::reference                  reference;
    typedef typename allocator_type::const_reference            const_reference;
    typedef typename allocator_type::pointer                    pointer;
    typedef typename allocator_type::const_pointer              const_pointer;
    typedef ListIterator<T>                                     iterator;
    typedef ConstListIterator<T>                                const_iterator;
    typedef ReverseIterator<iterator>                           reverse_iterator;
    typedef ReverseIterator<const_iterator>                     const_reverse_iterator;
    typedef std::ptrdiff_t                                      difference_type;
    typedef std::size_t                                         size_type;
    typedef ListNode<T>                                         node_type;
    
    // C++98 rebind syntax
    typedef typename Alloc::template rebind<node_type>::other   node_allocator_type;

private:
    node_type*          _end_node;
    size_type           _size;
    node_allocator_type _node_alloc;
    allocator_type      _alloc;

    // Helper functions
    void initialize_end_node() {
        _end_node = _node_alloc.allocate(1);
        _node_alloc.construct(_end_node, node_type());
        _end_node->next = _end_node;
        _end_node->prev = _end_node;
    }

    void clear_list() {
        node_type* current = _end_node->next;
        node_type* temp;

        while (current != _end_node) {
            temp = current;
            current = current->next;
            _alloc.destroy(&temp->data);
            _node_alloc.deallocate(temp, 1);
        }
        _end_node->next = _end_node;
        _end_node->prev = _end_node;
        _size = 0;
    }

    node_type* create_node(const value_type& val) {
        node_type* new_node = _node_alloc.allocate(1);
        _node_alloc.construct(new_node, node_type(val));
        return new_node;
    }

    void insert_node(node_type* position, node_type* new_node) {
        new_node->next = position;
        new_node->prev = position->prev;
        position->prev->next = new_node;
        position->prev = new_node;
        ++_size;
    }

    void remove_node(node_type* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        _alloc.destroy(&node->data);
        _node_alloc.deallocate(node, 1);
        --_size;
    }

public:
    // Constructors
    explicit list(const allocator_type& alloc = allocator_type())
        : _size(0), _node_alloc(node_allocator_type()), _alloc(alloc) {
        initialize_end_node();
    }

    explicit list(size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type())
        : _size(0), _node_alloc(node_allocator_type()), _alloc(alloc) {
        initialize_end_node();
        insert(begin(), n, val);
    }

    // Constructor template for iterators
    template <typename InputIterator>
    list(InputIterator first, InputIterator last,
         const allocator_type& alloc = allocator_type(),
         typename enable_if<!is_integral<InputIterator>::value>::type* = 0)
        : _size(0), _node_alloc(node_allocator_type()), _alloc(alloc) {
        initialize_end_node();
        insert(begin(), first, last);
    }

    // Specialization for integral types
    // template <typename Integer>
    // list(Integer n, Integer val,
    //      const allocator_type& alloc = allocator_type(),
    //      typename enable_if<is_integral<Integer>::value>::type* = 0)
    //     : _size(0), _node_alloc(node_allocator_type()), _alloc(alloc) {
    //     initialize_end_node();
    //     insert(begin(), static_cast<size_type>(n), static_cast<value_type>(val));
    // }

    list(const list& x)
        : _size(0), _node_alloc(node_allocator_type()), _alloc(x._alloc) {
        initialize_end_node();
        insert(begin(), x.begin(), x.end());
    }

    // Destructor
    ~list() {
        clear_list();
        _node_alloc.deallocate(_end_node, 1);
    }

    // Assignment operator
    list& operator=(const list& x) {
        if (this != &x) {
            clear();
            insert(begin(), x.begin(), x.end());
        }
        return *this;
    }

    // Iterators
    iterator begin() { return iterator(_end_node->next); }
    const_iterator begin() const { return const_iterator(_end_node->next); }
    
    iterator end() { return iterator(_end_node); }
    const_iterator end() const { return const_iterator(_end_node); }
    
    reverse_iterator rbegin() { return reverse_iterator(end()); }
    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
    
    reverse_iterator rend() { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

    // Capacity
    bool empty() const { return _size == 0; }
    size_type size() const { return _size; }
    size_type max_size() const { return _node_alloc.max_size(); }

    // Element access
    reference front() { return _end_node->next->data; }
    const_reference front() const { return _end_node->next->data; }
    
    reference back() { return _end_node->prev->data; }
    const_reference back() const { return _end_node->prev->data; }

    // Modifiers
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last, 
                typename enable_if<!is_integral<InputIterator>::value>::type* = 0) {
        clear();
        insert(begin(), first, last);
    }

    void assign(size_type n, const value_type& val) {
        clear();
        insert(begin(), n, val);
    }

    void push_front(const value_type& val) {
        insert(begin(), val);
    }

    void pop_front() {
        if (!empty())
            erase(begin());
    }

    void push_back(const value_type& val) {
        insert(end(), val);
    }

    void pop_back() {
        if (!empty())
            erase(--end());
    }

    iterator insert(iterator position, const value_type& val) {
        node_type* new_node = create_node(val);
        node_type* pos_node = position.getNode();
        
        insert_node(pos_node, new_node);
        return iterator(new_node);
    }

    void insert(iterator position, size_type n, const value_type& val) {
        for (size_type i = 0; i < n; ++i)
            insert(position, val);
    }

    template <typename InputIterator>
    void insert(iterator position, InputIterator first, InputIterator last,
                typename enable_if<!is_integral<InputIterator>::value>::type* = 0) {
        for (; first != last; ++first)
            insert(position, *first);
    }

    iterator erase(iterator position) {
        if (empty() || position == end())
            return position;
            
        node_type* node = position.getNode();
        iterator next_it(node->next);
        remove_node(node);
        return next_it;
    }

    iterator erase(iterator first, iterator last) {
        while (first != last)
            first = erase(first);
        return last;
    }

    void swap(list& x) {
        std::swap(_end_node, x._end_node);
        std::swap(_size, x._size);
        std::swap(_node_alloc, x._node_alloc);
        std::swap(_alloc, x._alloc);
    }

    void resize(size_type n, value_type val = value_type()) {
        if (n < _size) {
            iterator it = begin();
            for (size_type i = 0; i < n; ++i, ++it)
                ; // Move to the nth position
            erase(it, end());
        } else if (n > _size) {
            insert(end(), n - _size, val);
        }
    }

    void clear() {
        clear_list();
    }

    // Operations
    void splice(iterator position, list& x) {
        if (x.empty())
            return;
            
        node_type* pos_node = position.getNode();
        node_type* first = x._end_node->next;
        node_type* last = x._end_node->prev;
        
        // Detach from x
        x._end_node->next = x._end_node;
        x._end_node->prev = x._end_node;
        
        // Insert into this list
        first->prev = pos_node->prev;
        last->next = pos_node;
        pos_node->prev->next = first;
        pos_node->prev = last;
        
        _size += x._size;
        x._size = 0;
    }

    void splice(iterator position, list& x, iterator i) {
        node_type* pos_node = position.getNode();
        node_type* i_node = i.getNode();
        
        if (pos_node == i_node || pos_node == i_node->next)
            return;
            
        // Detach from x
        i_node->prev->next = i_node->next;
        i_node->next->prev = i_node->prev;
        
        // Insert into this list
        i_node->prev = pos_node->prev;
        i_node->next = pos_node;
        pos_node->prev->next = i_node;
        pos_node->prev = i_node;
        
        ++_size;
        --x._size;
    }

    void splice(iterator position, list& x, iterator first, iterator last) {
        if (first == last)
            return;
            
        node_type* pos_node = position.getNode();
        node_type* first_node = first.getNode();
        node_type* last_node = last.getNode()->prev;
        
        // Count elements to be moved
        size_type count = 0;
        iterator it = first;
        while (it != last) {
            ++count;
            ++it;
        }
        
        // Detach from x
        first_node->prev->next = last.getNode();
        last.getNode()->prev = first_node->prev;
        
        // Insert into this list
        first_node->prev = pos_node->prev;
        last_node->next = pos_node;
        pos_node->prev->next = first_node;
        pos_node->prev = last_node;
        
        _size += count;
        x._size -= count;
    }

    void remove(const value_type& val) {
        iterator it = begin();
        while (it != end()) {
            if (*it == val)
                it = erase(it);
            else
                ++it;
        }
    }

    template <typename Predicate>
    void remove_if(Predicate pred) {
        iterator it = begin();
        while (it != end()) {
            if (pred(*it))
                it = erase(it);
            else
                ++it;
        }
    }

    void unique() {
        if (_size <= 1)
            return;
            
        iterator first = begin();
        iterator next = first;
        ++next;
        
        while (next != end()) {
            if (*first == *next)
                next = erase(next);
            else {
                first = next;
                ++next;
            }
        }
    }

    template <typename BinaryPredicate>
    void unique(BinaryPredicate binary_pred) {
        if (_size <= 1)
            return;
            
        iterator first = begin();
        iterator next = first;
        ++next;
        
        while (next != end()) {
            if (binary_pred(*first, *next))
                next = erase(next);
            else {
                first = next;
                ++next;
            }
        }
    }

    void merge(list& x) {
        if (this == &x)
            return;
            
        iterator it1 = begin();
        iterator it2 = x.begin();
        
        while (it1 != end() && it2 != x.end()) {
            if (*it2 < *it1) {
                iterator next = it2;
                ++next;
                splice(it1, x, it2);
                it2 = next;
            } else {
                ++it1;
            }
        }
        
        if (it2 != x.end())
            splice(end(), x);
    }

    template <typename Compare>
    void merge(list& x, Compare comp) {
        if (this == &x)
            return;
            
        iterator it1 = begin();
        iterator it2 = x.begin();
        
        while (it1 != end() && it2 != x.end()) {
            if (comp(*it2, *it1)) {
                iterator next = it2;
                ++next;
                splice(it1, x, it2);
                it2 = next;
            } else {
                ++it1;
            }
        }
        
        if (it2 != x.end())
            splice(end(), x);
    }

    void sort() {
        if (_size <= 1)
            return;
            
        list carry;
        list tmp[7];
        int fill = 0;
        
        while (!empty()) {
            carry.splice(carry.begin(), *this, begin());
            
            int i = 0;
            while (i < fill && !tmp[i].empty()) {
                tmp[i].merge(carry);
                carry.swap(tmp[i]);
                ++i;
            }
            
            carry.swap(tmp[i]);
            if (i == fill)
                ++fill;
        }
        
        for (int i = 1; i < fill; ++i)
            tmp[i].merge(tmp[i-1]);
            
        swap(tmp[fill-1]);
    }

    template <typename Compare>
    void sort(Compare comp) {
        if (_size <= 1)
            return;
            
        list carry;
        list tmp[64];
        int fill = 0;
        
        while (!empty()) {
            carry.splice(carry.begin(), *this, begin());
            
            int i = 0;
            while (i < fill && !tmp[i].empty()) {
                tmp[i].merge(carry, comp);
                carry.swap(tmp[i]);
                ++i;
            }
            
            carry.swap(tmp[i]);
            if (i == fill)
                ++fill;
        }
        
        for (int i = 1; i < fill; ++i)
            tmp[i].merge(tmp[i-1], comp);
            
        swap(tmp[fill-1]);
    }

    void reverse() {
        if (_size <= 1)
            return;
            
        iterator it = begin();
        ++it;
        
        while (it != end()) {
            iterator old = it;
            ++it;
            splice(begin(), *this, old);
        }
    }

    // Allocator
    allocator_type get_allocator() const {
        return _alloc;
    }
};

// Non-member function overloads
template <typename T, typename Alloc>
bool operator==(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs) {
    if (lhs.size() != rhs.size())
        return false;
    return std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename T, typename Alloc>
bool operator!=(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs) {
    return !(lhs == rhs);
}

template <typename T, typename Alloc>
bool operator<(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs) {
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename T, typename Alloc>
bool operator<=(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs) {
    return !(rhs < lhs);
}

template <typename T, typename Alloc>
bool operator>(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs) {
    return rhs < lhs;
}

template <typename T, typename Alloc>
bool operator>=(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs) {
    return !(lhs < rhs);
}

template <typename T, typename Alloc>
void swap(list<T, Alloc>& x, list<T, Alloc>& y) {
    x.swap(y);
}

} // namespace ft

#endif // LIST_HPP