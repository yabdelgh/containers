#ifndef RB_TREE_HPP
# define RB_TREE_HPP

# include <memory>      // std::allocator
# include <functional>  // std::less
# include <algorithm>   // std::swap
# include <cstddef>     // std::ptrdiff_t
# include <limits>      // std::numeric_limits
# include "utility.hpp"  // ft::pair
# include "iterator.hpp" // ft::iterator_traits

namespace ft
{
    // Red-Black Tree node colors
    enum rb_tree_color { RED, BLACK };

    // Red-Black Tree node structure

    template <class Value>
    struct rb_tree_node
    {
        Value       value;
        rb_tree_node*  parent;
        rb_tree_node*  left;
        rb_tree_node*  right;
        rb_tree_color  color;
        rb_tree_node(const Value& v) : 
            value(v), parent(0), left(0), right(0), color(RED) {}
    };

    // Red-Black Tree implementation
    template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
    class rb_tree 
    {
    public:
        typedef Key                                      key_type;
        typedef Value                                    value_type;
        typedef size_t                                   size_type;
        typedef ptrdiff_t                                difference_type;
        typedef Compare                                  key_compare;
        typedef Allocator                                allocator_type;
        typedef value_type&                              reference;
        typedef const value_type&                        const_reference;
        typedef typename Allocator::pointer              pointer;
        typedef typename Allocator::const_pointer        const_pointer;
        typedef rb_tree_node<Value>                      node_type;
        typedef rb_tree_node<Value>*                     node_pointer;
        typedef const rb_tree_node<Value>*                     const_node_pointer;
        typedef typename Allocator::template rebind<node_type>::other node_allocator_type;
    // Bidirectional iterator for Red-Black Tree
    // template <class Value, class Pointer = Value*, class Reference = Value&>
    public: 
         node_pointer minimum(node_pointer node) const
        {
            while (node && node->left && node->left != _nil)
            {
                node = node->left;
            }
            return node;
        }

        node_pointer maximum(node_pointer node) const
        {
            while (node && node->right && node->right != _nil)
            {
                node = node->right;
            }
            return node;
        }

        node_pointer successor(node_pointer node) const
        {
            if (!node)
                return 0;
            if (node->right && node->right != _nil)
                return minimum(node->right);

            node_pointer parent = node->parent;
            while (parent && parent != _nil && node == parent->right)
            {
                node = parent;
                parent = parent->parent;
            }
            return parent;
        }
        
        const_node_pointer successor(const_node_pointer node) const
        {
            if (!node)
                return 0;
            if (node->right && node->right != _nil)
                return minimum(node->right);

            node_pointer parent = node->parent;
            while (parent && parent != _nil && node == parent->right)
            {
                node = parent;
                parent = parent->parent;
            }
            return parent;
        }
        
        node_pointer predecessor(node_pointer node) const
        {
            if (!node)
                return 0;
            if (node->left && node->left != _nil)
                return maximum(node->left);

            node_pointer parent = node->parent;
            while (parent && parent != _nil && node == parent->left)
            {
                node = parent;
                parent = parent->parent;
            }
            return parent;
        }
        
        const_node_pointer predecessor(const_node_pointer node) const
        {
            if (!node)
                return 0;
            if (node->left && node->left != _nil)
                return maximum(node->left);

            node_pointer parent = node->parent;
            while (parent && parent != _nil && node == parent->left)
            {
                node = parent;
                parent = parent->parent;
            }
            return parent;
        }

    private:
        node_pointer     _nil;     // Sentinel node
        node_pointer     _root;
        size_type        _size;
        key_compare      _comp;
        node_allocator_type _node_alloc;
    public:
    class iterator
    {
    public:
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef Value                          value_type;
        typedef Value*                        pointer;
        typedef Value&                      reference;
        typedef ptrdiff_t                      difference_type;
        typedef rb_tree_node<Value>*           node_pointer;

    private:
        node_pointer _node;
        
    public:
        rb_tree * _tree;

    public:
        iterator() : _node(0), _tree(0) {}
        
        explicit iterator(node_pointer node, rb_tree *tree) : _node(node), _tree(tree) {}
        
        // template <class V, class P, class R>
        iterator(const iterator& other) : _node(other.base()), _tree(other._tree) {}

        ~iterator() {}

        node_pointer base() const { return _node; }

        reference operator*() const { return _node->value; }
        pointer operator->() const { return &(_node->value); }

        iterator& operator++() 
        {
            _node = _tree->successor(_node);
            return *this;
        }

        iterator operator++(int) 
        {
            iterator tmp(*this);
            ++(*this);
            return tmp;
        }

        iterator& operator--() 
        {
            _node = _tree->predecessor(_node);
            return *this;
        }

        iterator operator--(int) 
        {
            iterator tmp(*this);
            --(*this);
            return tmp;
        }

        bool operator==(const iterator& rhs) const 
        {
            return _node == rhs._node;
        }

        bool operator!=(const iterator& rhs) const 
        {
            return _node != rhs._node;
        }
    };

    class const_iterator
    {
    public:
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef Value                          value_type;
        typedef const Value*                      pointer;
        typedef const Value&                      reference;
        typedef ptrdiff_t                      difference_type;
        typedef const rb_tree_node<Value>*     node_pointer;

    private:
        node_pointer _node;
        const rb_tree *_tree;

    public:
        const_iterator() : _node(0), _tree(0) {}
        
        explicit const_iterator(node_pointer node, const rb_tree *tree) : _node(node), _tree(tree) {}
        
        const_iterator(const iterator& other) : _node(other.base()), _tree(other._tree) {}

        ~const_iterator() {}

        node_pointer base() const { return _node; }

        reference operator*() const { return _node->value; }
        pointer operator->() const { return &(_node->value); }

        const_iterator& operator++() 
        {
            _node = _tree->successor(_node);
            return *this;
        }

        const_iterator operator++(int) 
        {
            const_iterator tmp(*this);
            ++(*this);
            return tmp;
        }

        const_iterator& operator--() 
        {
            _node = _tree->predecessor(_node);
            return *this;
        }

        const_iterator operator--(int) 
        {
            const_iterator tmp(*this);
            --(*this);
            return tmp;
        }

        bool operator==(const const_iterator& rhs) const 
        {
            return _node == rhs._node;
        }

        bool operator!=(const const_iterator& rhs) const 
        {
            return _node != rhs._node;
        }
    };
        typedef ft::reverse_iterator<iterator>           reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>     const_reverse_iterator;

    

    
    private:
        void _create_nil() 
        {
            _nil = _node_alloc.allocate(1);
            // Do not construct value for _nil to avoid unnecessary default construction
            _nil->color = BLACK;
            _nil->left = _nil;
            _nil->right = _nil;
            _nil->parent = _nil;
            _root = _nil;
        }

        void _left_rotate(node_pointer x) 
        {
            if (!x || x == _nil) return;
            node_pointer y = x->right;
            if (!y || y == _nil) return;
            
            x->right = y->left;
            if (y->left != _nil)
                y->left->parent = x;
            
            y->parent = x->parent;
            if (x->parent == _nil)
                _root = y;
            else if (x == x->parent->left)
                x->parent->left = y;
            else
                x->parent->right = y;
            
            y->left = x;
            x->parent = y;
        }

        void _right_rotate(node_pointer y) 
        {
            if (!y || y == _nil) return;
            node_pointer x = y->left;
            if (!x || x == _nil) return;
            
            y->left = x->right;
            if (x->right != _nil)
                x->right->parent = y;
            
            x->parent = y->parent;
            if (y->parent == _nil)
                _root = x;
            else if (y == y->parent->left)
                y->parent->left = x;
            else
                y->parent->right = x;
            
            x->right = y;
            y->parent = x;
        }
        
        void _insert_fixup(node_pointer z) 
       {
           if (!z || z == _nil) return;
           
           while (z != _root && z->parent != _nil && z->parent->color == RED) 
           {
               if (z->parent->parent == _nil) break;
               
               if (z->parent == z->parent->parent->left) 
               {
                   node_pointer y = z->parent->parent->right;
                   
                   if (y != _nil && y->color == RED) 
                   {
                       z->parent->color = BLACK;
                       y->color = BLACK;
                       z->parent->parent->color = RED;
                       z = z->parent->parent;
                   } 
                   else 
                   {
                       if (z == z->parent->right) 
                       {
                           z = z->parent;
                           _left_rotate(z);
                       }
                       z->parent->color = BLACK;
                       if (z->parent->parent != _nil) 
                       {
                           z->parent->parent->color = RED;
                           _right_rotate(z->parent->parent);
                       }
                   }
               } 
               else 
               {
                   // Same logic for the right case
                   node_pointer y = z->parent->parent->left;
                   
                   if (y != _nil && y->color == RED) 
                   {
                       z->parent->color = BLACK;
                       y->color = BLACK;
                       z->parent->parent->color = RED;
                       z = z->parent->parent;
                   } 
                   else 
                   {
                       if (z == z->parent->left) 
                       {
                           z = z->parent;
                           _right_rotate(z);
                       }
                       z->parent->color = BLACK;
                       if (z->parent->parent != _nil) 
                       {
                           z->parent->parent->color = RED;
                           _left_rotate(z->parent->parent);
                       }
                   }
               }
           }
           _root->color = BLACK;
       }

        node_pointer _find(const key_type& k) const 
        {
            node_pointer current = _root;
            
            while (current != _nil) 
            {
                if (!_comp(KeyOfValue()(current->value), k) && 
                    !_comp(k, KeyOfValue()(current->value)))
                    return current;
                current = _comp(k, KeyOfValue()(current->value)) ? 
                         current->left : current->right;
            }
            return _nil;
        }

        ft::pair<node_pointer, bool> _find_position(const key_type& k) const 
        {
            node_pointer current = _root;
            node_pointer parent = _nil;
            bool is_left = true;
            
            while (current != _nil) 
            {
                parent = current;
                if (!_comp(KeyOfValue()(current->value), k) && 
                    !_comp(k, KeyOfValue()(current->value)))
                    return ft::make_pair(current, false);
                is_left = _comp(k, KeyOfValue()(current->value));
                current = is_left ? current->left : current->right;
            }
            return ft::make_pair(parent, true);
        }


        void _erase_fixup(node_pointer x, node_pointer x_parent) 
        {
            while (x != _root && (x == _nil || x->color == BLACK)) 
            {
                if (!x_parent || x_parent == _nil) break;

                if (x == x_parent->left) 
                {
                    node_pointer w = x_parent->right;
                    if (!w || w == _nil) break;

                    if (w->color == RED) 
                    {
                        w->color = BLACK;
                        x_parent->color = RED;
                        _left_rotate(x_parent);
                        w = x_parent->right;
                        if (!w || w == _nil) break;
                    }

                    bool left_black = (w->left == _nil || w->left->color == BLACK);
                    bool right_black = (w->right == _nil || w->right->color == BLACK);

                    if (left_black && right_black) 
                    {
                        w->color = RED;
                        x = x_parent;
                        x_parent = x->parent;
                    } 
                    else 
                    {
                        if (right_black) 
                        {
                            if (w->left != _nil)
                                w->left->color = BLACK;
                            w->color = RED;
                            _right_rotate(w);
                            w = x_parent->right;
                            if (!w || w == _nil) break;
                        }
                        w->color = x_parent->color;
                        x_parent->color = BLACK;
                        if (w->right != _nil)
                            w->right->color = BLACK;
                        _left_rotate(x_parent);
                        x = _root;
                    }
                } 
                else 
                {
                    // Same logic for the right case with left/right swapped
                    node_pointer w = x_parent->left;
                    if (!w || w == _nil) break;

                    if (w->color == RED) 
                    {
                        w->color = BLACK;
                        x_parent->color = RED;
                        _right_rotate(x_parent);
                        w = x_parent->left;
                        if (!w || w == _nil) break;
                    }

                    bool right_black = (w->right == _nil || w->right->color == BLACK);
                    bool left_black = (w->left == _nil || w->left->color == BLACK);

                    if (right_black && left_black) 
                    {
                        w->color = RED;
                        x = x_parent;
                        x_parent = x->parent;
                    } 
                    else 
                    {
                        if (left_black) 
                        {
                            if (w->right != _nil)
                                w->right->color = BLACK;
                            w->color = RED;
                            _left_rotate(w);
                            w = x_parent->left;
                            if (!w || w == _nil) break;
                        }
                        w->color = x_parent->color;
                        x_parent->color = BLACK;
                        if (w->left != _nil)
                            w->left->color = BLACK;
                        _right_rotate(x_parent);
                        x = _root;
                    }
                }
            }

            if (x != _nil && x != NULL)
                x->color = BLACK;
        }

        void _transplant(node_pointer u, node_pointer v) 
        {
            if (!u || u == _nil) return;
            
            // Make sure v is _nil if null
            if (v == NULL) v = _nil;
            
            if (u->parent == _nil)
                _root = v;
            else if (u == u->parent->left)
                u->parent->left = v;
            else
                u->parent->right = v;
            
            v->parent = u->parent;  // Always update parent, even for _nil
        }

        void _clear_recursive(node_pointer node) 
        {
            if (node == _nil || !node)
                return;
            
            _clear_recursive(node->left);
            _clear_recursive(node->right);
            
            _node_alloc.destroy(node);
            _node_alloc.deallocate(node, 1);
        }

        node_pointer _copy_recursive(node_pointer src, node_pointer parent) 
        {
            if (!src || src == _nil)
                return _nil;
            
            node_pointer new_node = _node_alloc.allocate(1);
            _node_alloc.construct(new_node, src->value);
            
            new_node->color = src->color;
            new_node->parent = parent;
            new_node->left = _copy_recursive(src->left, new_node);
            new_node->right = _copy_recursive(src->right, new_node);
            
            return new_node;
        }

    public:
        rb_tree(const key_compare& comp = key_compare(),
               const allocator_type& alloc = allocator_type())
            : _nil(0), _root(_nil), _size(0), _comp(comp), _node_alloc(alloc)
        {
            _create_nil();
        }

        rb_tree(const rb_tree& other)
        : _nil(0), _root(0), _size(0), _comp(other._comp), _node_alloc(other._node_alloc)
        {
            _create_nil();
            if (other._root != other._nil)
            {
                _root = _copy_recursive(other._root, _nil);
                _size = other._size;
                _update_nil_pointers(_root);
            }
            else
            {
                _root = _nil;
                _size = 0;
            }
        }

        ~rb_tree()
        {
            clear();
            if (_nil)
            {
                _node_alloc.deallocate(_nil, 1);
                _nil = 0;
            }
        }


        rb_tree& operator=(const rb_tree& other)
        {
            if (this != &other)
            {
                clear();
                _comp = other._comp;

                if (other._root != other._nil)
                {
                    _root = _copy_recursive(other._root, _nil);
                    _size = other._size;
                    // Ensure that all leaf nodes point to _nil
                    _update_nil_pointers(_root);
                }
                else
                {
                    _root = _nil;
                    _size = 0;
                }
            }
            return *this;
        }

        void _update_nil_pointers(node_pointer node)
        {
            if (!node || node == _nil)
                return;

            if (node->left == NULL)
                node->left = _nil;
            if (node->right == NULL)
                node->right = _nil;

            _update_nil_pointers(node->left);
            _update_nil_pointers(node->right);
        }

        allocator_type get_allocator() const { return _node_alloc; }

        iterator begin()
        {
            return iterator(_size ? minimum(_root) : _nil, this);
        }
        
        const_iterator begin() const
        {
            return const_iterator(_size ? minimum(_root) : _nil, this);
        }
        
        iterator end() { return iterator(_nil, this); }
        
        const_iterator end() const { return const_iterator(_nil, this); }
        
        reverse_iterator rbegin() { return reverse_iterator(end()); }
        
        const_reverse_iterator rbegin() const
        {
            return const_reverse_iterator(end());
        }
        
        reverse_iterator rend() { return reverse_iterator(begin()); }
        
        const_reverse_iterator rend() const
        {
            return const_reverse_iterator(begin());
        }

        bool empty() const { return _size == 0; }
        
        size_type size() const { return _size; }
        
        size_type max_size() const
        {
            size_type alloc_max = _node_alloc.max_size();
            size_type diff_max = static_cast<size_type>(std::numeric_limits<std::ptrdiff_t>::max());
            return alloc_max < diff_max ? alloc_max : diff_max;
        }

        void clear()
        {
            _clear_recursive(_root);
            _root = _nil;
            _size = 0;
        }

        ft::pair<iterator, bool> insert(const value_type& value)
        {
            ft::pair<node_pointer, bool> pos = _find_position(KeyOfValue()(value));

            if (!pos.second)
                return ft::make_pair(iterator(pos.first, this), false);

            node_pointer new_node = _node_alloc.allocate(1);
            _node_alloc.construct(new_node,value);
            
            new_node->parent = pos.first;
            new_node->left = _nil;
            new_node->right = _nil;
            new_node->color = RED;

            if (pos.first == _nil)
                _root = new_node;
            else if (_comp(KeyOfValue()(value), KeyOfValue()(pos.first->value)))
                pos.first->left = new_node;
            else
                pos.first->right = new_node;

            _insert_fixup(new_node);
            ++_size;
            
            return ft::make_pair(iterator(new_node, this), true);
        }

        iterator insert(iterator hint, const value_type& value)
        {
            (void)hint; // Note: Hint is ignored; could be optimized in the future
            return insert(value).first;
        }

        void erase(iterator position)
        {
            node_pointer z = position.base();
            if (z == _nil || !z)
                return;

            node_pointer y = z;
            node_pointer x;
            rb_tree_color y_original_color = y->color;

            if (z->left == _nil)
            {
                x = z->right;
                _transplant(z, z->right);
            }
            else if (z->right == _nil)
            {
                x = z->left;
                _transplant(z, z->left);
            }
            else
            {
                y = minimum(z->right);
                y_original_color = y->color;
                x = y->right;

                if (y->parent == z)
                    x->parent = y;
                else
                {
                    _transplant(y, y->right);
                    y->right = z->right;
                    y->right->parent = y;
                }

                _transplant(z, y);
                y->left = z->left;
                y->left->parent = y;
                y->color = z->color;
            }

            node_pointer x_parent = x == _nil ? y->parent : x->parent;
            _node_alloc.destroy(z);
            _node_alloc.deallocate(z, 1);
            
            if (y_original_color == BLACK)
                _erase_fixup(x, x_parent);
            
            --_size;
        }

        size_type erase(const key_type& k)
        {
            node_pointer node = _find(k);
            if (node == _nil)
                return 0;
            
            erase(iterator(node, this));
            return 1;
        }

        void erase(iterator first, iterator last)
        {
            while (first != last)
            {
                iterator tmp = first++;
                erase(tmp);
            }
        }

        void swap(rb_tree& other)
        {
            node_pointer tmp_root = _root;
            node_pointer tmp_nil = _nil;
            size_type tmp_size = _size;
            key_compare tmp_comp = _comp;
            node_allocator_type tmp_alloc = _node_alloc;
            
            _root = other._root;
            _nil = other._nil;
            _size = other._size;
            _comp = other._comp;
            _node_alloc = other._node_alloc;
            
            other._root = tmp_root;
            other._nil = tmp_nil;
            other._size = tmp_size;
            other._comp = tmp_comp;
            other._node_alloc = tmp_alloc;
        }

        iterator find(const key_type& k)
        {
            return iterator(_find(k), this);
        }
        
        const_iterator find(const key_type& k) const
        {
            return const_iterator(_find(k), this);
        }

        size_type count(const key_type& k) const
        {
            return _find(k) != _nil ? 1 : 0;
        }

        iterator lower_bound(const key_type& k)
        {
            node_pointer current = _root;
            node_pointer result = _nil;
            
            while (current != _nil)
            {
                if (!_comp(KeyOfValue()(current->value), k))
                {
                    result = current;
                    current = current->left;
                }
                else
                    current = current->right;
            }
            
            return iterator(result, this);
        }
        
        const_iterator lower_bound(const key_type& k) const
        {
            node_pointer current = _root;
            node_pointer result = _nil;
            
            while (current != _nil)
            {
                if (!_comp(KeyOfValue()(current->value), k))
                {
                    result = current;
                    current = current->left;
                }
                else
                    current = current->right;
            }
            
            return const_iterator(result, this);
        }

        iterator upper_bound(const key_type& k)
        {
            node_pointer current = _root;
            node_pointer result = _nil;
            
            while (current != _nil)
            {
                if (_comp(k, KeyOfValue()(current->value)))
                {
                    result = current;
                    current = current->left;
                }
                else
                    current = current->right;
            }
            
            return iterator(result, this);
        }
        
        const_iterator upper_bound(const key_type& k) const
        {
            node_pointer current = _root;
            node_pointer result = _nil;
            
            while (current != _nil)
            {
                if (_comp(k, KeyOfValue()(current->value)))
                {
                    result = current;
                    current = current->left;
                }
                else
                    current = current->right;
            }
            
            return const_iterator(result, this);
        }

        ft::pair<iterator, iterator> equal_range(const key_type& k)
        {
            return ft::make_pair(lower_bound(k), upper_bound(k));
        }
        
        ft::pair<const_iterator, const_iterator> equal_range(const key_type& k) const
        {
            return ft::make_pair(lower_bound(k), upper_bound(k));
        }

        key_compare key_comp() const { return _comp; }

        // multimap
        public:
        
        iterator insert_multi(const value_type& value)
        {
            node_pointer parent = _nil;
            node_pointer current = _root;

            // Find insertion position (allows duplicates)
            while (current != _nil)
            {
                parent = current;
                current = _comp(KeyOfValue()(value), KeyOfValue()(current->value)) ? 
                         current->left : current->right;
            }

            node_pointer new_node = _node_alloc.allocate(1);
            _node_alloc.construct(new_node, value);

            new_node->parent = parent;
            new_node->left = _nil;
            new_node->right = _nil;
            new_node->color = RED;

            if (parent == _nil)
                _root = new_node;
            else if (_comp(KeyOfValue()(value), KeyOfValue()(parent->value)))
                parent->left = new_node;
            else
                parent->right = new_node;

            _insert_fixup(new_node);
            ++_size;

            return iterator(new_node, this);
        }

        iterator insert_multi(iterator hint, const value_type& value)
        {
            (void)hint; // Hint optimization can be added later
            return insert_multi(value);
        }

        size_type erase_multi(const key_type& k)
        {
            size_type count = 0;
            iterator first = lower_bound(k);
            iterator last = upper_bound(k);

            while (first != last)
            {
                iterator tmp = first++;
                erase(tmp);
                ++count;
            }

            return count;
        }

        size_type count_multi(const key_type& k) const
        {
            size_type count = 0;
            const_iterator first = lower_bound(k);
            const_iterator last = upper_bound(k);

            while (first != last)
            {
                ++first;
                ++count;
            }

            return count;
        }
    };
}
#endif