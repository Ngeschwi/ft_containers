#pragma once

#include "utils.hpp"
#include "iterators/map_iterator.hpp"
#include "avl/avl_tree.hpp"
#include "vector.hpp"
#include <sstream>
#include <memory>
#include <iostream>

namespace ft {
    template<typename Key, typename _Tp, typename Compare = ft::less<Key>, typename Allocator = std::allocator <ft::pair<const Key, _Tp> > >
    class map {
    public :

        typedef Key key_type;
        typedef _Tp mapped_type;
        typedef ft::pair<const Key, _Tp> value_type;
        typedef Compare key_compare;
        typedef Allocator allocator_type;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef value_type &reference;
        typedef const value_type &const_reference;
        typedef value_type *pointer;
        typedef const value_type *const_pointer;
        typedef typename ft::avl_tree<Key, _Tp, Compare, Allocator>::iterator iterator;
        typedef typename ft::avl_tree<Key, _Tp, Compare, Allocator>::const_iterator const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

        //foncteur
        class value_compare {
            friend class map;

        public :

            typedef bool result_type;
            typedef value_type first_argument_type;
            typedef value_type second_argument_type;

        protected :

            key_compare comp;

        public :

            bool operator()(const value_type &x, const value_type &y) const { return key_compare()(x.first, y.first); }
        };

    private :

        typedef ft::avl_tree<Key, _Tp, Compare, Allocator> tree_type;

        tree_type _tree;

    public :

        map() : _tree(tree_type()) {}

        // construct an empty conatainers
        explicit map(const Compare &comp, const Allocator &alloc = Allocator()) : _tree(
                tree_type(alloc)) { (void) comp; }

        // construct a container with as many elements as the rang [first, last)
        template<class InputIt>
        map(InputIt first, InputIt last, const Compare &comp = Compare(), const Allocator &alloc = Allocator())
                : _tree(tree_type(alloc)) {
            (void) comp;
            while (first != last)
                this->_tree.insert(*first++);
        }

        // constructor by copy
        map(const map &other) : _tree(tree_type()) {
            for (const_iterator it = other.begin(); it != other.end(); ++it)
                this->_tree.insert(*it);
        }

        ~map() {}

        map &operator=(const map &other) {
            this->clear();
            for (const_iterator it = other.begin(); it != other.end(); ++it)
                this->_tree.insert(*it);
            return *this;
        }

        allocator_type get_allocator() const {
            return allocator_type();
        }

        iterator begin() {
            return _tree.begin();
        }

        const_iterator begin() const {
            return _tree.begin();
        }

        iterator end() {
            return _tree.end();
        }

        const_iterator end() const {
            return _tree.end();
        }

        reverse_iterator rbegin() {
            return reverse_iterator(this->end());
        }

        reverse_iterator rend() {
            return reverse_iterator(this->begin());
        }

        mapped_type &at(const Key &key) {
            return this->_tree.find(key).second;
        }

        const mapped_type &at(const Key &key) const {
            return this->_tree.find(key).second;
        }

        bool empty() const {
            return this->size() == 0;
        }

        size_type max_size() const {
            return this->_tree.max_size();
        }

        size_type size() const {
            return this->_tree.size();
        }

        void clear() {
            this->_tree.clear();
        }

        ft::pair<iterator, bool> insert(const value_type &value) {
            bool result = this->_tree.insert(value);
            iterator it = iterator(_tree.root(), this->_tree.find_node(value.first));
            return ft::make_pair(it, result);
        }

        iterator insert(iterator hint, const value_type &value) {
            (void) hint;
            this->_tree.insert(value);
            return iterator(_tree.root(), this->_tree.find_node(value.first));
        }

        template<class InputIt>
        void insert(InputIt first, InputIt last) {
            while (first != last)
                this->_tree.insert(*first++);
        }

        void erase(iterator pos) {
            this->_tree.remove(pos->first);
        }

        void erase(iterator first, iterator last) {
            if (first == begin() && last == end())
                clear();
            ft::vector<iterator> erase_vec;
            for (iterator map_it = first; map_it != last; ++map_it)
                erase_vec.push_back(map_it);
            for (typename ft::vector<iterator>::iterator it = erase_vec.end() - 1; it != erase_vec.begin() - 1; --it)
                erase(*it);
        }

        size_type erase(const Key &key) {
            size_type ret = (_tree.find_node(key) != NULL);
            this->_tree.remove(key);
            return ret;
        }

        mapped_type &operator[](const Key &key) {
            this->_tree.insert(key, mapped_type()); // Will do nothing if key is already mapped
            return this->_tree.find(key).second;
        }

        void swap(map &other) {
            this->_tree.swap(other._tree);
        }

        size_type count(const Key &key) const {
            return this->_tree.find_node(key) ? 1 : 0;
        }

        iterator find(const Key &key) {
            return iterator(this->_tree.root(), this->_tree.find_node(key));
        }

        const_iterator find(const Key &key) const {
            return const_iterator(this->_tree.root(), this->_tree.find_node(key));
        }

        iterator lower_bound(const Key &key) {
            iterator v = this->find(key);
            if (v == this->end())
                return iterator(this->_tree.root(), this->_tree.upper(key));
            return v;
        }

        const_iterator lower_bound(const Key &key) const {
            const_iterator v = this->find(key);
            if (v == this->end())
                return const_iterator(this->_tree.root(), this->_tree.upper(key));
            return v;
        }

        iterator upper_bound(const Key &key) {
            return iterator(this->_tree.root(), this->_tree.upper(key));
        }

        const_iterator upper_bound(const Key &key) const {
            return const_iterator(this->_tree.root(), this->_tree.upper(key));
        }

        ft::pair<iterator, iterator> equal_range(const Key &key) {
            return ft::make_pair(lower_bound(key), upper_bound(key));
        }

        ft::pair<const_iterator, const_iterator> equal_range(const Key &key) const {
            return ft::make_pair(lower_bound(key), upper_bound(key));
        }

        key_compare key_comp() const {
            return key_compare();
        }

        value_compare value_comp() const {
            return value_compare();
        }
    };

    template<class K, class V, class C, class A>
    void swap(ft::map<K, V, C, A> &lhs,
              ft::map<K, V, C, A> &rhs) {
        lhs.swap(rhs);
    }

    template<class K, class V, class C, class A>
    bool operator==(const ft::map<K, V, C, A> &lhs,
                    const ft::map<K, V, C, A> &rhs) {
        if (lhs.size() != rhs.size()) {
            return false;
        }
        return ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template<class K, class V, class C, class A>
    bool operator!=(const ft::map<K, V, C, A> &lhs,
                    const ft::map<K, V, C, A> &rhs) {
        return !(lhs == rhs);
    }

    template<class K, class V, class C, class A>
    bool operator<(const ft::map<K, V, C, A> &lhs,
                   const ft::map<K, V, C, A> &rhs) {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template<class K, class V, class C, class A>
    bool operator<=(const ft::map<K, V, C, A> &lhs,
                    const ft::map<K, V, C, A> &rhs) {
        return !(lhs > rhs);
    }

    template<class K, class V, class C, class A>
    bool operator>(const ft::map<K, V, C, A> &lhs,
                   const ft::map<K, V, C, A> &rhs) {
        return (rhs < lhs);
    }

    template<class K, class V, class C, class A>
    bool operator>=(const ft::map<K, V, C, A> &lhs,
                    const ft::map<K, V, C, A> &rhs) {
        return !(lhs < rhs);
    }
}