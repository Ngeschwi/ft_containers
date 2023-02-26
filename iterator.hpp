#pragma once

#include <iostream>
#include "iterator_traits.hpp"

namespace ft {
    template<class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T *, class Reference = T &>
    struct map_iterator {
        typedef T value_type;
        typedef Distance difference_type;
        typedef Category iterator_category;
        typedef Pointer pointer;
        typedef Reference reference;
    };

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

    template<class IteratorL, class IteratorR>
    typename random_access_iterator<IteratorL>::difference_type
    operator-(const random_access_iterator<IteratorL> &lhs, const random_access_iterator<IteratorR> &rhs) {
        return lhs.base() - rhs.base();
    }

    template<class Iterator>
    random_access_iterator<Iterator> operator-(const typename random_access_iterator<Iterator>::difference_type &n,
                                               const random_access_iterator<Iterator> &it) {
        return it - n;
    }

    template<class IteratorL, class IteratorR>
    typename random_access_iterator<IteratorL>::difference_type
    operator+(const random_access_iterator<IteratorL> &lhs, const random_access_iterator<IteratorR> &rhs) {
        return lhs.base() + rhs.base();
    }

    template<class Iterator>
    random_access_iterator<Iterator> operator+(const typename random_access_iterator<Iterator>::difference_type &n,
                                               const random_access_iterator<Iterator> &it) { return it + n; }

    template<class IteratorL, class IteratorR>
    bool operator==(const random_access_iterator<IteratorL> &lhs, const random_access_iterator<IteratorR> &rhs) {
        return lhs.base() == rhs.base();
    }

    template<class IteratorL, class IteratorR>
    bool operator!=(const random_access_iterator<IteratorL> &lhs, const random_access_iterator<IteratorR> &rhs) {
        return lhs.base() != rhs.base();
    }

    template<class IteratorL, class IteratorR>
    bool operator<(const random_access_iterator<IteratorL> &lhs, const random_access_iterator<IteratorR> &rhs) {
        return lhs.base() < rhs.base();
    }

    template<class IteratorL, class IteratorR>
    bool operator>(const random_access_iterator<IteratorL> &lhs, const random_access_iterator<IteratorR> &rhs) {
        return lhs.base() > rhs.base();
    }

    template<class IteratorL, class IteratorR>
    bool operator<=(const random_access_iterator<IteratorL> &lhs, const random_access_iterator<IteratorR> &rhs) {
        return lhs.base() <= rhs.base();
    }

    template<class IteratorL, class IteratorR>
    bool operator>=(const random_access_iterator<IteratorL> &lhs, const random_access_iterator<IteratorR> &rhs) {
        return lhs.base() >= rhs.base();
    }

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

        T base() const { return _ptr; }

        reference operator*() const {
            T tmp = _ptr;
            return *--tmp;
        }

        pointer operator->() const { return &(operator*()); }

        reference operator[](difference_type n) const { return _ptr[-n - 1]; }

        iterator &operator++() {
            --_ptr;
            return *this;
        }

        iterator operator++(int) { return reverse_iterator(_ptr--); }

        iterator &operator--() {
            ++_ptr;
            return *this;
        }

        iterator operator--(int) { return reverse_iterator(_ptr++); }

        iterator &operator+=(difference_type n) {
            _ptr -= n;
            return *this;
        }

        iterator &operator-=(difference_type n) {
            _ptr += n;
            return *this;
        }

        iterator operator+(difference_type n) const { return reverse_iterator(_ptr - n); }

        iterator operator-(difference_type n) const { return reverse_iterator(_ptr + n); }

    };

    template<class IteratorL, class IteratorR>
    typename reverse_iterator<IteratorL>::difference_type
    operator-(const reverse_iterator<IteratorL> &lhs, const reverse_iterator<IteratorR> &rhs) {
        return rhs.base() - lhs.base();
    }

    template<class Iterator>
    reverse_iterator<Iterator> operator-(const typename reverse_iterator<Iterator>::difference_type &n,
                                         const reverse_iterator<Iterator> &rhs) { return rhs.base() + n; }

    template<class IteratorL, class IteratorR>
    typename reverse_iterator<IteratorL>::difference_type
    operator+(const reverse_iterator<IteratorL> &lhs, const reverse_iterator<IteratorR> &rhs) {
        return rhs.base() + lhs.base();
    }

    template<class Iterator>
    reverse_iterator<Iterator> operator+(const typename reverse_iterator<Iterator>::difference_type &n,
                                         const reverse_iterator<Iterator> &rhs) { return rhs.base() - n; }

    template<class IteratorL, class IteratorR>
    bool operator==(const reverse_iterator<IteratorL> &lhs, const reverse_iterator<IteratorR> &rhs) {
        return lhs.base() == rhs.base();
    }

    template<class IteratorL, class IteratorR>
    bool operator!=(const reverse_iterator<IteratorL> &lhs, const reverse_iterator<IteratorR> &rhs) {
        return lhs.base() != rhs.base();
    }

    template<class IteratorL, class IteratorR>
    bool operator>(const reverse_iterator<IteratorL> &lhs, const reverse_iterator<IteratorR> &rhs) {
        return lhs.base() < rhs.base();
    }

    template<class IteratorL, class IteratorR>
    bool operator<(const reverse_iterator<IteratorL> &lhs, const reverse_iterator<IteratorR> &rhs) {
        return lhs.base() > rhs.base();
    }

    template<class IteratorL, class IteratorR>
    bool operator>=(const reverse_iterator<IteratorL> &lhs, const reverse_iterator<IteratorR> &rhs) {
        return lhs.base() <= rhs.base();
    }

    template<class IteratorL, class IteratorR>
    bool operator<=(const reverse_iterator<IteratorL> &lhs, const reverse_iterator<IteratorR> &rhs) {
        return lhs.base() >= rhs.base();
    }
}