#pragma once

#include <iostream>
#include "iterator_traits.hpp"

namespace ft {

    template<typename T>
    class random_access_iterator {
    public :

        typedef typename iterator_traits<T>::value_type value_type;
        typedef typename iterator_traits<T>::difference_type difference_type;
        typedef typename iterator_traits<T>::pointer pointer;
        typedef typename iterator_traits<T>::reference reference;
        typedef typename iterator_traits<T>::iterator_category iterator_category;
        typedef random_access_iterator iterator;

    protected :

        T _ptr;

    public :

        random_access_iterator() : _ptr(NULL) {}

        random_access_iterator(pointer ptr) : _ptr(ptr) {}

        template<typename U>
        random_access_iterator(const random_access_iterator<U> &src) : _ptr(src.base()) {}

        iterator &operator=(const iterator &rhs) {
            _ptr = rhs._ptr;
            return *this;
        }

        pointer base() const {
            return _ptr;
        }

        reference operator*() const {
            return *_ptr;
        }

        pointer operator->() const {
            return _ptr;
        }

        reference operator[](difference_type n) const {
            return _ptr[n];
        }

        iterator &operator++() {
            ++_ptr;
            return *this;
        }

        iterator operator++(int) {
            return iterator(_ptr++);
        }

        iterator &operator--() {
            --_ptr;
            return *this;
        }

        iterator operator--(int) {
            return iterator(_ptr--);
        }

        iterator &operator+=(difference_type n) {
            _ptr += n;
            return *this;
        }

        iterator &operator-=(difference_type n) {
            _ptr -= n;
            return *this;
        }

        iterator operator+(difference_type n) const { return iterator(_ptr + n); }

        iterator operator-(difference_type n) const {
            return iterator(_ptr - n);
        }

        bool operator!() const {
            return !_ptr;
        }
    };

    template<class Left, class Right>
    typename random_access_iterator<Left>::difference_type
    operator-(const random_access_iterator<Left> &lhs, const random_access_iterator<Right> &rhs) {
        return lhs.base() - rhs.base();
    }

    template<class Iterator>
    random_access_iterator<Iterator> operator-(const typename random_access_iterator<Iterator>::difference_type &n,
                                               const random_access_iterator<Iterator> &it) {
        return it - n;
    }

    template<class Left, class Right>
    typename random_access_iterator<Left>::difference_type
    operator+(const random_access_iterator<Left> &lhs, const random_access_iterator<Right> &rhs) {
        return lhs.base() + rhs.base();
    }

    template<class Iterator>
    random_access_iterator<Iterator> operator+(const typename random_access_iterator<Iterator>::difference_type &n,
                                               const random_access_iterator<Iterator> &it) { return it + n; }

    template<class Left, class Right>
    bool operator==(const random_access_iterator<Left> &lhs, const random_access_iterator<Right> &rhs) {
        return lhs.base() == rhs.base();
    }

    template<class Left, class Right>
    bool operator!=(const random_access_iterator<Left> &lhs, const random_access_iterator<Right> &rhs) {
        return lhs.base() != rhs.base();
    }

    template<class Left, class Right>
    bool operator<(const random_access_iterator<Left> &lhs, const random_access_iterator<Right> &rhs) {
        return lhs.base() < rhs.base();
    }

    template<class Left, class Right>
    bool operator>(const random_access_iterator<Left> &lhs, const random_access_iterator<Right> &rhs) {
        return lhs.base() > rhs.base();
    }

    template<class Left, class Right>
    bool operator<=(const random_access_iterator<Left> &lhs, const random_access_iterator<Right> &rhs) {
        return lhs.base() <= rhs.base();
    }

    template<class Left, class Right>
    bool operator>=(const random_access_iterator<Left> &lhs, const random_access_iterator<Right> &rhs) {
        return lhs.base() >= rhs.base();
    }
}