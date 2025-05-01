#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>

namespace ft
{
    // Iterator tags
    typedef std::input_iterator_tag input_iterator_tag;
    typedef std::output_iterator_tag output_iterator_tag;
    typedef std::forward_iterator_tag forword_iterator_tag;
    typedef std::bidirectional_iterator_tag bidirectional_iterator_tag;
    typedef std::random_access_iterator_tag random_access_iterator_tag;

    // Base iterator template
    template <class Category, class T, class Distance = ptrdiff_t,
             class Pointer = T*, class Reference = T&>
    struct iterator
    {
        typedef T         value_type;
        typedef Distance  difference_type;
        typedef Pointer   pointer;
        typedef Reference reference;
        typedef Category  iterator_category;
    };

    // Iterator traits
    template <class Iterator>
    struct iterator_traits
    {
        typedef typename Iterator::difference_type   difference_type;
        typedef typename Iterator::value_type        value_type;
        typedef typename Iterator::pointer           pointer;
        typedef typename Iterator::reference         reference;
        typedef typename Iterator::iterator_category iterator_category;
    };

    template <class T>
    struct iterator_traits<T*>
    {
        typedef ptrdiff_t                  difference_type;
        typedef T                          value_type;
        typedef T*                         pointer;
        typedef T&                         reference;
        typedef random_access_iterator_tag iterator_category;
    };

    template <class T>
    struct iterator_traits<const T*>
    {
        typedef ptrdiff_t                  difference_type;
        typedef T                          value_type;
        typedef const T*                   pointer;
        typedef const T&                   reference;
        typedef random_access_iterator_tag iterator_category;
    };

    // Reverse iterator
    template <class Iterator>
    class reverse_iterator
    {
    public:
        typedef Iterator                                                iterator_type;
        typedef typename iterator_traits<Iterator>::iterator_category   iterator_category;
        typedef typename iterator_traits<Iterator>::value_type          value_type;
        typedef typename iterator_traits<Iterator>::difference_type     difference_type;
        typedef typename iterator_traits<Iterator>::pointer             pointer;
        typedef typename iterator_traits<Iterator>::reference           reference;

    protected:
        Iterator _base;

    public:
        // Constructors
        reverse_iterator() : _base() {}

        explicit reverse_iterator(iterator_type it) : _base(it) {}

        template <class Iter>
        reverse_iterator(const reverse_iterator<Iter>& rev_it) : _base(rev_it.base()) {}

        // Base method
        iterator_type base() const { return _base; }

        // Operators
        reference operator*() const
        {
            Iterator tmp = _base;
            return *--tmp;
        }

        pointer operator->() const
        {
            return &(operator*());
        }

        reverse_iterator& operator++()
        {
            --_base;
            return *this;
        }

        reverse_iterator operator++(int)
        {
            reverse_iterator tmp = *this;
            --_base;
            return tmp;
        }

        reverse_iterator& operator--()
        {
            ++_base;
            return *this;
        }

        reverse_iterator operator--(int)
        {
            reverse_iterator tmp = *this;
            ++_base;
            return tmp;
        }

        reverse_iterator operator+(difference_type n) const
        {
            return reverse_iterator(_base - n);
        }

        reverse_iterator& operator+=(difference_type n)
        {
            _base -= n;
            return *this;
        }

        reverse_iterator operator-(difference_type n) const
        {
            return reverse_iterator(_base + n);
        }

        reverse_iterator& operator-=(difference_type n)
        {
            _base += n;
            return *this;
        }

        reference operator[](difference_type n) const
        {
            return *(*this + n);
        }
    };

    // Non-member function overloads for reverse_iterator
    template <class Iterator>
    bool operator==(const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iterator>& rhs)
    {
        return lhs.base() == rhs.base();
    }

    template <class Iterator>
    bool operator!=(const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iterator>& rhs)
    {
        return lhs.base() != rhs.base();
    }

    template <class Iterator>
    bool operator<(const reverse_iterator<Iterator>& lhs,
                  const reverse_iterator<Iterator>& rhs)
    {
        return lhs.base() > rhs.base();
    }

    template <class Iterator>
    bool operator<=(const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iterator>& rhs)
    {
        return lhs.base() >= rhs.base();
    }

    template <class Iterator>
    bool operator>(const reverse_iterator<Iterator>& lhs,
                  const reverse_iterator<Iterator>& rhs)
    {
        return lhs.base() < rhs.base();
    }

    template <class Iterator>
    bool operator>=(const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iterator>& rhs)
    {
        return lhs.base() <= rhs.base();
    }

    template <class Iterator>
    typename reverse_iterator<Iterator>::difference_type
    operator-(const reverse_iterator<Iterator>& lhs,
             const reverse_iterator<Iterator>& rhs)
    {
        return rhs.base() - lhs.base();
    }

    template <class Iterator>
    reverse_iterator<Iterator>
    operator+(typename reverse_iterator<Iterator>::difference_type n,
             const reverse_iterator<Iterator>& rev_it)
    {
        return reverse_iterator<Iterator>(rev_it.base() - n);
    }

    // Type traits
    template <bool B, class T = void>
    struct enable_if {};

    template <class T>
    struct enable_if<true, T> { typedef T type; };

    template <class T, T v>
    struct integral_constant
    {
        static const T value = v;
        typedef T value_type;
        typedef integral_constant<T, v> type;
    };

    typedef integral_constant<bool, true> true_type;
    typedef integral_constant<bool, false> false_type;

    template <class T> struct is_integral : public false_type {};
    template <> struct is_integral<bool> : public true_type {};
    template <> struct is_integral<char> : public true_type {};
    template <> struct is_integral<signed char> : public true_type {};
    template <> struct is_integral<unsigned char> : public true_type {};
    template <> struct is_integral<wchar_t> : public true_type {};
    template <> struct is_integral<short> : public true_type {};
    template <> struct is_integral<unsigned short> : public true_type {};
    template <> struct is_integral<int> : public true_type {};
    template <> struct is_integral<unsigned int> : public true_type {};
    template <> struct is_integral<long> : public true_type {};
    template <> struct is_integral<unsigned long> : public true_type {};

    // Iterator functions
    template <class InputIterator>
    typename iterator_traits<InputIterator>::difference_type
    distance(InputIterator first, InputIterator last)
    {
        typename iterator_traits<InputIterator>::difference_type n = 0;
        while (first != last)
        {
            ++first;
            ++n;
        }
        return n;
    }

    // Algorithm implementations
    template <class InputIterator1, class InputIterator2>
    bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
    {
        while (first1 != last1)
        {
            if (!(*first1 == *first2))
                return false;
            ++first1;
            ++first2;
        }
        return true;
    }

    template <class InputIterator1, class InputIterator2, class BinaryPredicate>
    bool equal(InputIterator1 first1, InputIterator1 last1,
               InputIterator2 first2, BinaryPredicate pred)
    {
        while (first1 != last1)
        {
            if (!pred(*first1, *first2))
                return false;
            ++first1;
            ++first2;
        }
        return true;
    }

    template <class InputIterator1, class InputIterator2>
    bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                                InputIterator2 first2, InputIterator2 last2)
    {
        while (first1 != last1)
        {
            if (first2 == last2 || *first2 < *first1)
                return false;
            else if (*first1 < *first2)
                return true;
            ++first1;
            ++first2;
        }
        return (first2 != last2);
    }

    template <class InputIterator1, class InputIterator2, class Compare>
    bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                                InputIterator2 first2, InputIterator2 last2,
                                Compare comp)
    {
        while (first1 != last1)
        {
            if (first2 == last2 || comp(*first2, *first1))
                return false;
            else if (comp(*first1, *first2))
                return true;
            ++first1;
            ++first2;
        }
        return (first2 != last2);
    }

    template <typename T>
    void swap(T& a, T& b) {
        T temp = a;
        a = b;
        b = temp;
    }

    // Non-member function overloads
    template <typename Container>
   bool operator==(const Container& lhs, const Container& rhs) {
       return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
   }
   
   template <typename Container>
   bool operator!=(const Container& lhs, const Container& rhs) {
       return !(lhs == rhs);
   }
   
   // Less-than
   template <typename Container>
   bool operator<(const Container& lhs, const Container& rhs) {
       return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
   }
   
   template <typename Container>
   bool operator<=(const Container& lhs, const Container& rhs) {
       return !(rhs < lhs);
   }
   
   template <typename Container>
   bool operator>(const Container& lhs, const Container& rhs) {
       return rhs < lhs;
   }
   
   template <typename Container>
   bool operator>=(const Container& lhs, const Container& rhs) {
       return !(lhs < rhs);
   } 
}
#endif