#include <iostream>
//#include "../zz/vector/vector.hpp"
//#include <vector>
#include "vector.hpp"
#include <map>
#include <cstring>
//namespace ft = std;

template< class T >
class input_iterator
{
    public:
    typedef T                                                           iterator_type;
    typedef typename    std::iterator_traits<iterator_type>::value_type         value_type;
    typedef typename std::iterator_traits<iterator_type>::difference_type   difference_type;
    typedef typename std::iterator_traits<iterator_type>::pointer           pointer;
    typedef typename std::iterator_traits<iterator_type>::reference         reference;
    typedef typename std::input_iterator_tag    iterator_category;

    protected:
    pointer _ptr;

    public:
     input_iterator(pointer ptr) : _ptr(ptr) {};
    input_iterator() : _ptr(0) {};
    input_iterator( const input_iterator<value_type *> &copie) : _ptr(copie._ptr) {};
    input_iterator( const input_iterator<const value_type *> &copie) : _ptr(copie._ptr) {};

    public:
    pointer base() const
    {
        return (_ptr);
    }

    public: // operators

    // assignment
    input_iterator& operator=(const input_iterator &copie)
    {
        if (this != &copie)
            _ptr = copie._ptr;
        return (*this);
    }

    // Comparison
    bool operator== (const input_iterator& r)  const
    {  return _ptr == r._ptr;  }
    bool operator!= (const input_iterator& r)  const
    {  return _ptr != r._ptr;  }

    //  Increment and Decrement
    input_iterator& operator++()
    {
        ++_ptr;
        return *this;
    }
    input_iterator operator++(int)
    {
        pointer tmp = _ptr;
        ++*this;
        return input_iterator(tmp);
    }

    // Dereference 

    reference operator*() const
    {   return (*_ptr);     }
    pointer operator->() const
    {   return (_ptr);      }

    public:
    virtual ~input_iterator() {};

};

class A
{
	public:
	A(int a)
	{
		b = a;
		str = strdup("yassine abdelghafour");
		std::cout << b <<  "constructor called" << std::endl;
	}
	A(const A& copie)
	{
		this->b = copie.b;
		this->str = strdup(copie.str);
		std::cout << b << "copie constructor called" << std::endl;
	}
	A& operator=(const A& copie)
	{
		if (str != nullptr)
			delete str;
		b = copie.b;
		str = strdup(copie.str);
		std::cout << b <<  "assignment operator called" << std::endl;
		return (*this);
	}
	public:
	int b;
	char *str;
	public:
	virtual ~A()
	{
		delete str;
		std::cout << b << "destructor called " << std::endl;
	}
};

int main()
{
	ft::vector<int> vec;
	ft::vector<int>::iterator it = vec.begin();
	ft::vector<int>::iterator ite = vec.end();
	vec.reserve(10);
	it = vec.begin();
	std::cout << "size: " << vec.size() << std::endl;
	std::cout << "capacity: " << vec.capacity() << std::endl;
	std::cout << "size: " << vec.size() << std::endl;
	std::cout << "capacity: " << vec.capacity() << std::endl;
	vec.push_back(1);
	std::cout << "size: " << vec.size() << std::endl;
	std::cout << "capacity: " << vec.capacity() << std::endl;
	vec.push_back(2);
	std::cout << "size: " << vec.size() << std::endl;
	std::cout << "capacity: " << vec.capacity() << std::endl;
	vec.push_back(3);
	std::cout << "size: " << vec.size() << std::endl;
	std::cout << "capacity: " << vec.capacity() << std::endl;
	vec.push_back(4);
	std::cout << "size: " << vec.size() << std::endl;
	std::cout << "capacity: " << vec.capacity() << std::endl;
	it = vec.begin();
	input_iterator<int*> ia = vec.begin().base();
	input_iterator<int*> ib = vec.begin().base() + 3;
	vec.insert(it,ia, ib);
	std::cout << "size: " << vec.size() << std::endl;
	std::cout << "capacity: " << vec.capacity() << std::endl;
	it = vec.begin();
	ite = vec.end();
	while (it != ite)
	{
		std::cout << *it << std::endl;
		it++;
	}
	ft::vector<int>::iterator vv;
	std::cout << vv.base() << std::endl;
/*std::map<char,int> first;

  first['a']=10;
  first['b']=30;
  first['c']=50;
  first['d']=70;

  typedef std::map<char,int>::iterator iter_type;

  std::reverse_iterator<iter_type> rev_iterator = first.rbegin();


  std::cout << "The third element from the end is: " << rev_iterator->first << std::endl;

  return 0;*/
	return (0);
}

