#include <iostream>
#include "redblacktree.hpp"
#include "utility.hpp"
#define COUNT 15
#include <utility>
template <typename node_ptr>
void printUtils(node_ptr root, int space, int depth, int &size)
{
	if (root == 0)
		return;

	space += COUNT;

	printUtils(static_cast<node_ptr>(root->_right), space, depth + 1, size);

	std::cout << std::endl;
	if (root->_color)
		std::cout << "\e[1;31m" << std::endl;
	else 
		std::cout << "\e[1;30m" << std::endl;
	for (int i = COUNT; i < space; i++) std::cout << " ";
	std::cout << "value: " << root->_data->first << std::endl;
	size++;
	printUtils(static_cast<node_ptr>(root->_left), space, depth + 1, size);
}
template <typename node_ptr>
void print2D(node_ptr *root)
{
	int size;

	size = 0;
	printUtils(root, 0, 0, size);
	std::cout << std::endl << "*********************************************** size: "
	          << size << std::endl;
}


int main()
{
using namespace std::rel_ops;
	ft::rbt<int,int> r;
	ft::pair<int,int> a(10,10);
	ft::pair<int,int> b(20,11230);
	ft::pair<int,int> c(20,11290);
	ft::pair<int,int> d(30,11290);
	r.insert_node(ft::make_pair(46450,34));
	r.insert_node(ft::make_pair(4,34));
	r.insert_node(ft::make_pair(888,34));
	r.insert_node(ft::make_pair(85,34));
	r.insert_node(ft::make_pair(-8,34));
	r.insert_node(ft::make_pair(-48,34));
	r.insert_node(ft::make_pair(9,34));
	r.insert_node(ft::make_pair(55,34));
	r.insert_node(ft::make_pair(564,34));
	r.insert_node(ft::make_pair(34,34));
	r.insert_node(ft::make_pair(9787,34));
	r.insert_node(ft::make_pair(567,34));
	r.insert_node(ft::make_pair(987,34));
	r.insert_node(ft::make_pair(21,34));
	r.insert_node(ft::make_pair(434,34));
	r.insert_node(ft::make_pair(46451,34));
	r.insert_node(ft::make_pair(46452,34));
	r.insert_node(ft::make_pair(48888,34));
	r.insert_node(ft::make_pair(433,34));
	r.insert_node(ft::make_pair(224,34));
	r.insert_node(ft::make_pair(411,34));
	r.insert_node(ft::make_pair(6625,34));
	r.insert_node(ft::make_pair(46449,34));
	r.insert_node(c);
	r.insert_node(d);
//	print2D(r.base());
//	r.display();
//	std::cout << std::endl;
//	ft::rbt<int,int>::const_iterator it = r.begin();
//	ft::rbt<int,int>::const_iterator ite = r.end();
	ft::rbt<int,int>::iterator it = r.begin();
	ft::rbt<int,int>::iterator ite = r.end();
//	it->second = 99999999;
	while (it != ite)
	{
		std::cout << it->first << "   " << it->second << std::endl;
		++it;
	}
	std::cout << std::endl;	
	ft::rbt<int,int>::reverse_iterator rit = r.rbegin();
	ft::rbt<int,int>::reverse_iterator rite = r.rend();
//	it->second = 99999999;
	while (rit != rite)
	{
		std::cout << rit->first << "   " << rit->second << std::endl;
		++rit;
	}

	
//	ft::rbt<int,int>::reverse_iterator rit;
	//std::cout << rit->first << std::endl;
	return (0);
}
