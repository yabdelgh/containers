#include <iostream>
#include "redblacktree.hpp"
#include "utility.hpp"
#define COUNT 15
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
	ft::rbt<int,int> r;
	ft::pair<const int,int> a(10,10);
	ft::pair<const int,int> b(20,11230);
	ft::pair<const int,int> c(20,11290);
	ft::pair<const int,int> d(30,11290);
	r.insert_node(ft::make_pair(4,34));
	r.insert_node(ft::make_pair(5,34));
	r.insert_node(b);
	r.insert_node(c);
	r.insert_node(d);
	r.delete_node(c);
	print2D(r.base());
	return (0);
}
