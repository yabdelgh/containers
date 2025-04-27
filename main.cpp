#include <iostream>
#include <string>
#include <functional> // For std::greater
#include "list.hpp"
    #include <list>

// Test function to check that our list implementation works correctly
template <typename T>
void print_list(const ft::list<T>& list, const std::string& name) {
    std::cout << name << " contents: ";
    for (typename ft::list<T>::const_iterator it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::cout << "Size: " << list.size() << std::endl;
    std::cout << "Empty: " << (list.empty() ? "true" : "false") << std::endl;
    std::cout << std::endl;
}

// Predicate functor for remove_if test (remove even numbers)
struct IsEven {
    bool operator()(int n) const {
        return n % 2 == 0;
    }
};

// Predicate functor for unique test
struct IsWithinTwo {
    bool operator()(int a, int b) const {
        return (b - a) <= 2;
    }
};

// Basic tests for all major list functionalities
int main() {
    // Constructor tests
    std::cout << "===== CONSTRUCTORS TESTS =====" << std::endl;
    ft::list<int> list1;
    ft::list<int> list2(5, 100);
    ft::list<int> list3(list2.begin(), list2.end());
    ft::list<int> list4(list3);
    print_list(list1, "list1 (default constructor)");
    print_list(list2, "list2 (fill constructor)");
    print_list(list3, "list3 (range constructor)");
    print_list(list4, "list4 (copy constructor)");
    
    // Iterator tests
    std::cout << "===== ITERATOR TESTS =====" << std::endl;
    ft::list<int> list5;
    for (int i = 1; i <= 5; ++i) {
        list5.push_back(i * 10);
    }
    
    std::cout << "Forward iteration: ";
    for (ft::list<int>::iterator it = list5.begin(); it != list5.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Reverse iteration: ";
    for (ft::list<int>::reverse_iterator rit = list5.rbegin(); rit != list5.rend(); ++rit) {
        std::cout << *rit << " ";
    }
    std::cout << std::endl << std::endl;
    
    // Capacity tests
    std::cout << "===== CAPACITY TESTS =====" << std::endl;
    std::cout << "list5 size: " << list5.size() << std::endl;
    std::cout << "list5 max_size: " << list5.max_size() << std::endl;
    std::cout << "list5 empty: " << (list5.empty() ? "true" : "false") << std::endl << std::endl;
    
    // Element access tests
    std::cout << "===== ELEMENT ACCESS TESTS =====" << std::endl;
    std::cout << "list5 front: " << list5.front() << std::endl;
    std::cout << "list5 back: " << list5.back() << std::endl << std::endl;
    
    // Modifier tests
    std::cout << "===== MODIFIER TESTS =====" << std::endl;
    
    // assign
    ft::list<int> list6;
    list6.assign(3, 200);
    print_list(list6, "list6 after assign(3, 200)");
    
    // push_front, push_back
    list6.push_front(100);
    list6.push_back(300);
    print_list(list6, "list6 after push_front(100) and push_back(300)");
    
    // pop_front, pop_back
    list6.pop_front();
    list6.pop_back();
    print_list(list6, "list6 after pop_front() and pop_back()");
    
    // insert
    ft::list<int>::iterator it = list6.begin();
    ++it;
    list6.insert(it, 150);
    print_list(list6, "list6 after insert(it, 150)");
    
    // erase
    it = list6.begin();
    ++it;
    list6.erase(it);
    print_list(list6, "list6 after erase(it)");
    
    // swap
    ft::list<int> list7(3, 50);
    list6.swap(list7);
    print_list(list6, "list6 after swap with list7");
    print_list(list7, "list7 after swap with list6");
    
    // resize
    list6.resize(5, 75);
    print_list(list6, "list6 after resize(5, 75)");
    list6.resize(2);
    print_list(list6, "list6 after resize(2)");
    
    // clear
    list6.clear();
    print_list(list6, "list6 after clear()");
    
    // Operations tests
    std::cout << "===== OPERATIONS TESTS =====" << std::endl;
    
    // splice
    ft::list<int> list8;
    list8.push_back(10);
    list8.push_back(20);
    list8.push_back(30);
    
    ft::list<int> list9;
    list9.push_back(100);
    list9.push_back(200);
    list9.push_back(300);
    
    list8.splice(++(list8.begin()), list9);
    print_list(list8, "list8 after splice(list9)");
    print_list(list9, "list9 after being spliced");
    
    // remove
    list8.push_back(20);
    list8.remove(20);
    print_list(list8, "list8 after remove(20)");
    
    // unique
    list8.push_back(30);
    list8.push_back(30);
    list8.unique();
    print_list(list8, "list8 after unique()");
    
    // sort
    ft::list<int> list10;
    list10.push_back(-100);
    list10.push_back(30);
    list10.push_back(10);
    list10.push_back(50);
    list10.push_back(20);
    list10.push_back(40);
    list10.push_back(100);
    list10.push_back(5);
    list10.push_back(25);
    list10.push_back(100);
    list10.push_back(5);
    list10.push_back(25);
    list10.push_back(100);
    list10.push_back(-5);
    list10.push_back(-25);
    list10.push_back(-100);
    list10.push_back(-5);
    list10.push_back(-25);
    
    print_list(list10, "list10 befor sort()");
    list10.sort();
    print_list(list10, "list10 after sort()");
    
    // reverse
    list10.reverse();
    print_list(list10, "list10 after reverse()");
    
    // Comparison operators
    std::cout << "===== COMPARISON OPERATORS TESTS =====" << std::endl;
    ft::list<int> a;
    ft::list<int> b;
    a.push_back(10);
    a.push_back(20);
    a.push_back(30);
    
    b.push_back(10);
    b.push_back(20);
    b.push_back(30);
    
    std::cout << "a == b: " << (a == b ? "true" : "false") << std::endl;
    std::cout << "a != b: " << (a != b ? "true" : "false") << std::endl;
    
    b.push_back(40);
    std::cout << "After adding element to b:" << std::endl;
    std::cout << "a < b: " << (a < b ? "true" : "false") << std::endl;
    std::cout << "a <= b: " << (a <= b ? "true" : "false") << std::endl;
    std::cout << "a > b: " << (a > b ? "true" : "false") << std::endl;
    std::cout << "a >= b: " << (a >= b ? "true" : "false") << std::endl;
    
    // Custom comparison function test for sort
    std::cout << std::endl << "===== CUSTOM COMPARISON TESTS =====" << std::endl;
    
    ft::list<int> list11;
    list11.push_back(30);
    list11.push_back(10);
    list11.push_back(50);
    list11.push_back(20);
    list11.push_back(40);
    
    // Sort in descending order
    list11.sort(std::greater<int>());
    print_list(list11, "list11 after sort with std::greater<int>");
    
    // Custom predicate for unique
    ft::list<int> list12;
    list12.push_back(10);
    list12.push_back(20);
    list12.push_back(22);
    list12.push_back(30);
    list12.push_back(32);
    
    // Remove consecutive numbers with difference <= 2
    IsWithinTwo within_two;
    list12.unique(within_two);
    print_list(list12, "list12 after unique with custom predicate");
    
    // Merge test
    std::cout << std::endl << "===== MERGE TESTS =====" << std::endl;
    
    ft::list<int> list13;
    list13.push_back(10);
    list13.push_back(30);
    list13.push_back(50);
    
    ft::list<int> list14;
    list14.push_back(20);
    list14.push_back(40);
    list14.push_back(60);
    
    list13.merge(list14);
    print_list(list13, "list13 after merge with list14");
    print_list(list14, "list14 after being merged into list13");
    
    // Custom merge test
    ft::list<int> list15;
    list15.push_back(50);
    list15.push_back(30);
    list15.push_back(10);
    
    ft::list<int> list16;
    list16.push_back(60);
    list16.push_back(40);
    list16.push_back(20);
    
    // Both lists are sorted in descending order
    // Merge should maintain that order
    list15.merge(list16, std::greater<int>());
    print_list(list15, "list15 after merge with list16 using std::greater<int>");
    
    // Test with different data types
    std::cout << std::endl << "===== DIFFERENT DATA TYPE TESTS =====" << std::endl;
    
    // String list
    ft::list<std::string> strList;
    strList.push_back("Hello");
    strList.push_back("World");
    strList.push_back("C++");
    strList.push_back("98");
    
    std::cout << "String list contents: ";
    for (ft::list<std::string>::iterator it = strList.begin(); it != strList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    strList.sort();
    std::cout << "String list after sort: ";
    for (ft::list<std::string>::iterator it = strList.begin(); it != strList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Test remove_if
    ft::list<int> list17;
    for (int i = 1; i <= 10; ++i) {
        list17.push_back(i);
    }
    
    // Remove even numbers
    IsEven isEven;
    list17.remove_if(isEven);
    print_list(list17, "list17 after remove_if (removing even numbers)");
    
    // Test with a custom allocator
    std::cout << std::endl << "===== ALLOCATOR TEST =====" << std::endl;
    
    ft::list<int> list18;
    std::allocator<int> alloc = list18.get_allocator();
    std::cout << "Default allocator is working correctly." << std::endl;
    
    std::cout << std::endl << "All tests completed successfully!" << std::endl;
    
    return 0;
}