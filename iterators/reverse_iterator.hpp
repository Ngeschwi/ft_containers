#pragma once

#include <iostream>
#include "iterator_traits.hpp"

namespace ft {

    template<typename T>
    class reverse_iterator {
    public :

        typedef typename iterator_traits<T>::value_type value_type;
        typedef typename iterator_traits<T>::difference_type difference_type;
        typedef typename iterator_traits<T>::pointer pointer;
        typedef typename iterator_traits<T>::reference reference;
        typedef typename iterator_traits<T>::iterator_category iterator_category;
        typedef reverse_iterator iterator;

    protected :

        T _ptr;

    public :

        reverse_iterator() : _ptr() {}

        reverse_iterator(T x) : _ptr(x) {}

        template<typename U>
        reverse_iterator(const reverse_iterator<U> &x) : _ptr(x.base()) {}

        iterator &operator=(const iterator &other) {
            _ptr = other._ptr;
            return *this;
        }

        T base() const {
            return _ptr;
        }

        reference operator*() const {
            T tmp = _ptr;
            return *--tmp;
        }

        pointer operator->() const {
            return &(operator*());
        }

        reference operator[](difference_type n) const {
            return _ptr[-n - 1];
        }

        iterator &operator++() {
            --_ptr;
            return *this;
        }

        iterator operator++(int) {
            return reverse_iterator(_ptr--);
        }

        iterator &operator--() {
            ++_ptr;
            return *this;
        }

        iterator operator--(int) {
            return reverse_iterator(_ptr++);
        }

        iterator &operator+=(difference_type n) {
            _ptr -= n;
            return *this;
        }

        iterator &operator-=(difference_type n) {
            _ptr += n;
            return *this;
        }

        iterator operator+(difference_type n) const {
            return reverse_iterator(_ptr - n);
        }

        iterator operator-(difference_type n) const {
            return reverse_iterator(_ptr + n);
        }

    };

    template<class Left, class Right>
    typename reverse_iterator<Left>::difference_type
    operator-(const reverse_iterator<Left> &lhs, const reverse_iterator<Right> &rhs) {
        return rhs.base() - lhs.base();
    }

    template<class Iterator>
    reverse_iterator<Iterator> operator-(const typename reverse_iterator<Iterator>::difference_type &n,
                                         const reverse_iterator<Iterator> &rhs) {
        return rhs.base() + n;
    }

    template<class Left, class Right>
    typename reverse_iterator<Left>::difference_type
    operator+(const reverse_iterator<Left> &lhs, const reverse_iterator<Right> &rhs) {
        return rhs.base() + lhs.base();
    }

    template<class Iterator>
    reverse_iterator<Iterator> operator+(const typename reverse_iterator<Iterator>::difference_type &n,
                                         const reverse_iterator<Iterator> &rhs) {
        return rhs.base() - n;
    }

    template<class Left, class Right>
    bool operator==(const reverse_iterator<Left> &lhs, const reverse_iterator<Right> &rhs) {
        return lhs.base() == rhs.base();
    }

    template<class Left, class Right>
    bool operator!=(const reverse_iterator<Left> &lhs, const reverse_iterator<Right> &rhs) {
        return lhs.base() != rhs.base();
    }

    template<class Left, class Right>
    bool operator>(const reverse_iterator<Left> &lhs, const reverse_iterator<Right> &rhs) {
        return lhs.base() < rhs.base();
    }

    template<class Left, class Right>
    bool operator<(const reverse_iterator<Left> &lhs, const reverse_iterator<Right> &rhs) {
        return lhs.base() > rhs.base();
    }

    template<class Left, class Right>
    bool operator>=(const reverse_iterator<Left> &lhs, const reverse_iterator<Right> &rhs) {
        return lhs.base() <= rhs.base();
    }

    template<class Left, class Right>
    bool operator<=(const reverse_iterator<Left> &lhs, const reverse_iterator<Right> &rhs) {
        return lhs.base() >= rhs.base();
    }
}