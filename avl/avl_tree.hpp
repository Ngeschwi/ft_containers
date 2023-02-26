#pragma once

#include "avl_node.hpp"
#include <limits>

namespace ft {
    template<class Key, class _Tp, class Compare = ft::less<Key>, class Allocator = std::allocator <ft::pair<const Key, _Tp> > >
    class avl_tree {
    public :

        typedef avl_node<Key, _Tp, Compare, Allocator> node;
        typedef node *node_ptr;
        typedef Key key_type;
        typedef _Tp value_type;
        typedef ft::pair<Key, _Tp> pair_type;
        typedef ft::pair<const Key, _Tp> const_pair_type;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef Allocator allocator_type;
        typedef ft::avl_tree_iterator<Key, _Tp, Compare, Allocator> iterator;
        typedef ft::avl_tree_const_iterator<Key, _Tp, Compare, Allocator> const_iterator;

    private :

        typedef typename allocator_type::template rebind<node>::other node_allocator;

        node_allocator _allocator;
        node_ptr _root;
        size_type _size;

    public :

        avl_tree(allocator_type alloc = allocator_type()) :
                _allocator(alloc),
                _root(NULL),
                _size(0) {}

        ~avl_tree() {
            this->clear();
        }

        void swap(avl_tree &other) {
            ft::swap(this->_allocator, other._allocator);
            ft::swap(this->_root, other._root);
            ft::swap(this->_size, other._size);
        }

        iterator begin() {
            if (this->_size == 0)
                return this->end();
            return iterator(this->_root, this->min());
        }

        const_iterator begin() const {
            if (this->_size == 0)
                return this->end();
            return const_iterator(this->_root, this->min());
        }

        iterator end() {
            return iterator(this->_root, NULL);
        }

        const_iterator end() const {
            return const_iterator(this->_root, NULL);
        }

        node_ptr root() const {
            return _root;
        }

        bool insert(pair_type data) {
            if (node::find(this->_root, data.first) != NULL) {
                return false;
            }
            this->_root = node::insert(this->_root, data, _allocator);
            this->_size++;
            return true;
        }

        bool insert(key_type key, value_type value) {
            return insert(ft::make_pair(key, value));
        }

        void remove(const key_type &key) {
            if (node::find(this->_root, key) == NULL)
                return;
            this->_root = node::del_node(this->_root, key, _allocator);
            this->_size--;
        }

        size_type size() const { return this->_size; }

        node_ptr min() const {
            if (this->_root == NULL)
                throw std::out_of_range("Map is empty");
            return node::min(this->_root);
        }

        node_ptr max() const {
            if (this->_root == NULL)
                throw std::out_of_range("Map is empty");
            return node::max(this->_root);
        }

        node_ptr upper(const key_type &key) const {
            return node::upper(this->_root, key);
        }

        const_pair_type &find(const key_type &key) const {
            node_ptr node = node::find(this->_root, key);
            if (node == NULL)
                throw std::out_of_range("Key not found in map");
            return reinterpret_cast<const_pair_type &>(node->key_value_pair());
        }

        node_ptr find_node(const key_type &key) const {
            node_ptr node = node::find(this->_root, key);
            return node;
        }

        void clear() {
            size_type size_before = _size;
            for (size_type i = 0; i < size_before; ++i)
                remove(_root->key());
        }

        node_ptr next(node_ptr node) {
            return node::next(node, _root);
        }

        size_type max_size() const {
            size_type t = static_cast<size_type>(std::numeric_limits<difference_type>::max());
            return ft::min(_allocator.max_size(), t);
        }
    };
}