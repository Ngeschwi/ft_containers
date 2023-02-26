#pragma once

#include <cstdlib>
#include <memory>
#include <sstream>
#include "../utils.hpp"

namespace ft {
    template<class Key, class _Tp, class Compare, class Allocator>
    class avl_node {
    public :

        typedef avl_node<Key, _Tp, Compare, Allocator> node;
        typedef node *node_ptr;
        typedef Key key_type;
        typedef _Tp value_type;
        typedef ft::pair<Key, _Tp> pair_type;
        typedef size_t size_type;
        typedef ssize_t balance_type;
        typedef Allocator allocator_type;

    public :

        typedef typename allocator_type::template rebind<node>::other node_allocator;
        pair_type _data;
        size_type _height;
        node_ptr left;
        node_ptr right;
        Compare key_compare;

    public :

        avl_node(pair_type data) : _data(data), _height(1), left(NULL), right(NULL) {}

        const key_type &key() const {
            return this->_data.first;
        }

        value_type &value() {
            return this->_data.second;
        }

        pair_type &key_value_pair() {
            return this->_data;
        }

        static size_type height(node *n) {
            if (n == NULL)
                return 0;
            return n->_height;
        }

        // the balance it's the differences between the size of the left and of the right
        // the balance have to be between -1 and 1
        static balance_type balance(node_ptr n) {
            if (n == NULL)
                return 0;
            return height(n->left) - height(n->right);
        }

        // if balance > 1 (if the tree have more nodes on the left side)
        static node_ptr right_rotate(node_ptr node_init) {
            node_ptr new_node = node_init->left;
            node_ptr temp = new_node->right;

            // perform rotation
            new_node->right = node_init;
            node_init->left = temp;

            node_init->_height = ft::max(height(node_init->left), height(node_init->right)) + 1;
            new_node->_height = ft::max(height(new_node->left), height(new_node->right)) + 1;

            return new_node;
        }

        //if balance < -1 (if the tree have more nodes on the right side)
        static node_ptr left_rotate(node_ptr node_init) {
            node_ptr new_node = node_init->right;
            avl_node *temp = new_node->left;

            // perform rotation
            new_node->left = node_init;
            node_init->right = temp;

            node_init->_height = ft::max(height(node_init->left), height(node_init->right)) + 1;
            new_node->_height = ft::max(height(new_node->left), height(new_node->right)) + 1;

            return new_node;
        }

        // function to find a key
        // 1 : we return the node if we find the key
        // 2 : if not, we compare the actual key to know if we have to look on the left side or on the right side
        static node_ptr find(node_ptr node, key_type key) {
            while (node != NULL) {
                if (node->key() == key)
                    return node;
                if (node->key_compare(key, node->key()))
                    node = node->left;
                else if (node->key_compare(node->key(), key))
                    node = node->right;
            }
            return NULL;
        }

        // we create a new node
        static node_ptr new_node(pair_type data, node_allocator &alloc) {
            node_ptr node = alloc.allocate(1);
            alloc.construct(node, data);
            return node;
        }

        // insert node in the tree
        // like the find juste we create a node at the end
        static node_ptr insert(node_ptr node, pair_type data, node_allocator &alloc) {
            if (node == NULL)
                return (new_node(data, alloc));
            if (node->key_compare(data.first, node->key()))
                node->left = insert(node->left, data, alloc);
            else if (node->key_compare(node->key(), data.first))
                node->right = insert(node->right, data, alloc);
            else // Duplicate keys are not allowed
                return node;

            node->_height = 1 + ft::max(height(node->left), height(node->right));

            int bal = balance(node);

            // do a rotate if the balance is not good
            // Left Left
            if (bal > 1 && node->key_compare(data.first, node->left->key()))
                return right_rotate(node);
            // Right Right
            if (bal < -1 && node->key_compare(node->right->key(), data.first))
                return left_rotate(node);
            // Left Right
            if (bal > 1 && node->key_compare(node->left->key(), data.first)) {
                node->left = left_rotate(node->left);
                return right_rotate(node);
            }
            // Right Left
            if (bal < -1 && node->key_compare(data.first, node->right->key())) {
                node->right = right_rotate(node->right);
                return left_rotate(node);
            }

            return node;
        }

        // we find the minimal key
        static node_ptr min(node_ptr node) {
            node_ptr current = node;
            while (current->left != NULL)
                current = current->left;
            return current;
        }

        // we find the maximal key
        static node_ptr max(node_ptr node) {
            node_ptr current = node;
            while (current->right != NULL)
                current = current->right;
            return current;
        }

        // returns root of modified subtree
        static node_ptr del_node(node_ptr root, key_type key, node_allocator &alloc) {
            if (root == NULL)
                return root;

            if (root->key_compare(key, root->key()))
                root->left = del_node(root->left, key, alloc);
            else if (root->key_compare(root->key(), key))
                root->right = del_node(root->right, key, alloc);
            else { // we found the key to delete
                if ((root->left == NULL) || (root->right == NULL)) { // if node has 0 or 1 child
                    node_ptr temp = root->left ? root->left : root->right;

                    // node has no child
                    if (temp == NULL) {
                        temp = root;
                        root = NULL;
                    } else // node has one child
                        *root = *temp; // Copy the contents of
                    alloc.destroy(temp);
                    alloc.deallocate(temp, 1);
                } else // node has 2 children
                {
                    // temp = inorder successor
                    node_ptr temp = min(root->right);
                    root->_data = temp->_data;

                    // delete inorder successor
                    root->right = del_node(root->right, temp->key(), alloc);
                }
            }

            // if the tree had only one node then return
            if (root == NULL)
                return root;

            root->_height = ft::max(height(root->left), height(root->right)) + 1;

            int bal = balance(root);
            // Left Left
            if (bal > 1 && balance(root->left) >= 0)
                return right_rotate(root);
            // Left Right
            if (bal > 1 && balance(root->left) < 0) {
                root->left = left_rotate(root->left);
                return right_rotate(root);
            }
            // Right Right
            if (bal < -1 && balance(root->right) <= 0)
                return left_rotate(root);
            // Right Left
            if (bal < -1 && balance(root->right) > 0) {
                root->right = right_rotate(root->right);
                return left_rotate(root);
            }

            return root;
        }

        // find the just bigger key
        static node_ptr upper(node_ptr root, key_type key) {
            node_ptr current = root;
            node_ptr last_valid = NULL;
            while (current) {
                if (key == current->key()) {
                    if (current->right)
                        return min(current->right);
                    break;
                }
                if (root->key_compare(key, current->key())) {
                    last_valid = current;
                    current = current->left;
                } else
                    current = current->right;
            }
            return (last_valid);
        }

        // find the just lower key
        static node_ptr lower(node_ptr root, key_type key) {
            node_ptr current = root;
            node_ptr last_valid = NULL;
            while (current) {
                if (key == current->key()) {
                    if (current->left)
                        return max(current->left);
                    break;
                }
                if (root->key_compare(key, current->key()))
                    current = current->left;
                else {
                    last_valid = current;
                    current = current->right;
                }
            }
            return (last_valid);
        }

        static node_ptr next(node_ptr node, node_ptr root) {
            if (node->right)
                return min(node->right);
            return upper(root, node->key());
        }

        static node_ptr prev(node_ptr node, node_ptr root) {
            if (node == NULL)
                return max(root);
            if (node->left)
                return max(node->left);
            return lower(root, node->key());
        }
    };

    template<class K, class V, class C, class A>
    class avl_tree_const_iterator;

    template<class Key, class _Tp, class Compare = ft::less<Key>, class Allocator = std::allocator <ft::pair<const Key, _Tp> > >
    class avl_tree_iterator : public ft::map_iterator<ft::bidirectional_iterator_tag, ft::pair<const Key, _Tp> > {
        friend class avl_tree_const_iterator<Key, _Tp, Compare, Allocator>;

    public :

        typedef ft::pair<const Key, _Tp> value_type;
        typedef std::ptrdiff_t difference_type;
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef value_type *pointer;
        typedef const value_type *const_pointer;
        typedef value_type &reference;
        typedef const value_type &const_reference;

    private :

        typedef avl_node<Key, _Tp, Compare, Allocator> node;
        typedef node *node_ptr;
        typedef ft::pair<const Key, _Tp> const_pair_type;

        node_ptr _root;
        node_ptr _current;

    public :

        avl_tree_iterator() : _root(NULL), _current(NULL) {}

        avl_tree_iterator(node_ptr root, node_ptr current) :
                _root(root),
                _current(current) {}

        avl_tree_iterator(const avl_tree_iterator &other) :
                _root(other._root),
                _current(other._current) {}

        ~avl_tree_iterator() {}

        avl_tree_iterator &operator=(const avl_tree_iterator &other) {
            _root = other._root;
            _current = other._current;
            return *this;
        }

        reference operator*() const {
            return *reinterpret_cast<const_pair_type *>(&_current->key_value_pair());
        }

        pointer operator->() const {
            return &(operator*());
        }

        avl_tree_iterator &operator++() {
            _current = node::next(this->_current, this->_root);
            return *this;
        }

        avl_tree_iterator operator++(int) {
            node_ptr ret = _current;
            _current = node::next(this->_current, this->_root);
            return avl_tree_iterator(this->_root, ret);
        }

        avl_tree_iterator &operator--() {
            _current = node::prev(this->_current, this->_root);
            return *this;
        }

        avl_tree_iterator operator--(int) {
            node_ptr ret = _current;
            _current = node::prev(this->_current, this->_root);
            return avl_tree_iterator(this->_root, ret);
        }

        /* modif */
        avl_tree_iterator operator+(difference_type n) const {
            node_ptr ret = _current;
            while (n-- && ret)
                ret = node::next(ret, this->_root);
            return avl_tree_iterator(this->_root, ret);
        }

        avl_tree_iterator operator-(difference_type n) const {
            node_ptr ret = _current;
            while (n-- && ret)
                ret = node::prev(ret, this->_root);
            return avl_tree_iterator(this->_root, ret);
        }

        /**/
        bool operator==(const avl_tree_iterator &other) const {
            return (this->_root == other._root) && (this->_current == other._current);
        }

        bool operator==(const avl_tree_const_iterator<Key, _Tp, Compare, Allocator> &other) const {
            return (this->_root == other._root) && (this->_current == other._current);
        }

        bool operator!=(const avl_tree_iterator &other) const {
            return (this->_root != other._root) || (this->_current != other._current);
        }

        node_ptr current_node() { return _current; }
    };

    template<class Key, class _Tp, class Compare = ft::less<Key>, class Allocator = std::allocator <ft::pair<const Key, _Tp> > >
    class avl_tree_const_iterator
            : public ft::map_iterator<std::bidirectional_iterator_tag, ft::pair<const Key, _Tp> > {
        friend class avl_tree_iterator<Key, _Tp, Compare, Allocator>;

    public :

        typedef const ft::pair<const Key, _Tp> value_type;
        typedef std::ptrdiff_t difference_type;
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef value_type *pointer;
        typedef const value_type *const_pointer;
        typedef value_type &reference;
        typedef const value_type &const_reference;

    private :

        typedef avl_node<Key, _Tp, Compare, Allocator> node;
        typedef node *node_ptr;
        typedef const ft::pair<const Key, _Tp> const_pair_type;

        node_ptr _root;
        node_ptr _current;

    public :

        avl_tree_const_iterator() : _root(NULL), _current(NULL) {}

        avl_tree_const_iterator(node_ptr root, node_ptr current) :
                _root(root),
                _current(current) {}

        avl_tree_const_iterator(const avl_tree_const_iterator &other) :
                _root(other._root),
                _current(other._current) {}

        avl_tree_const_iterator(const avl_tree_iterator<Key, _Tp, Compare, Allocator> &non_const) : _root(
                non_const._root), _current(non_const._current) {}

        ~avl_tree_const_iterator() {}

        avl_tree_const_iterator &operator=(const avl_tree_const_iterator &other) {
            _root = other._root;
            _current = other._current;
            return *this;
        }

        const_reference operator*() const {
            return *reinterpret_cast<const_pair_type *>(&_current->key_value_pair());
        }

        const_pointer operator->() const {
            return &(operator*());
        }

        avl_tree_const_iterator &operator++() {
            _current = node::next(this->_current, this->_root);
            return *this;
        }

        avl_tree_const_iterator operator++(int) {
            node_ptr ret = _current;
            _current = node::next(this->_current, this->_root);
            return avl_tree_const_iterator(this->_root, ret);
        }

        avl_tree_const_iterator &operator--() {
            _current = node::prev(this->_current, this->_root);
            return *this;
        }

        avl_tree_const_iterator operator--(int) {
            node_ptr ret = _current;
            _current = node::prev(this->_current, this->_root);
            return avl_tree_const_iterator(this->_root, ret);
        }

        bool operator==(const avl_tree_iterator<Key, _Tp, Compare, Allocator> &other) const {
            return (this->_root == other._root) && (this->_current == other._current);
        }

        bool operator==(const avl_tree_const_iterator &other) const {
            return (this->_root == other._root) && (this->_current == other._current);
        }

        bool operator!=(const avl_tree_const_iterator &other) const {
            return (this->_root != other._root) || (this->_current != other._current);
        }

        node_ptr current_node() { return _current; }
    };
}