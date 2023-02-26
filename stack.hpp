#pragma once

#include "vector.hpp"

namespace ft {
    template<class T, class Container = ft::vector<T> >
    class stack {
    public :

        typedef Container container_type;
        typedef typename Container::value_type value_type;
        typedef typename Container::size_type size_type;
        typedef typename Container::reference reference;
        typedef typename Container::const_reference const_reference;

    protected :

        Container c;

    public :

        explicit stack(const container_type &ctnr = container_type()) : c(ctnr) {}

        explicit stack(const stack &rhs) : c(rhs.c) {}

        ~stack() {}

        stack &operator=(const stack &rhs) {
            this->c = rhs.c;
            return *this;
        }

        /* Element Access */

        reference top() {
            return c.back();
        }

        const_reference top() const {
            return c.back();
        }

        /* Capacity */

        bool empty() const {
            return c.empty();
        }

        size_type size() const {
            return c.size();
        }

        /* Modifiers */

        void push(const value_type &value) {
            c.push_back(value);
        }

        void pop() {
            c.pop_back();
        }

        /* Overloads proto */
        template<typename _T, typename ctnr>
        friend bool operator==(const stack<_T, ctnr> &lhs, const stack<_T, ctnr> &rhs);

        template<typename _T, typename ctnr>
        friend bool operator!=(const stack<_T, ctnr> &lhs, const stack<_T, ctnr> &rhs);

        template<typename _T, typename ctnr>
        friend bool operator>=(const stack<_T, ctnr> &lhs, const stack<_T, ctnr> &rhs);

        template<typename _T, typename ctnr>
        friend bool operator<=(const stack<_T, ctnr> &lhs, const stack<_T, ctnr> &rhs);

        template<typename _T, typename ctnr>
        friend bool operator>(const stack<_T, ctnr> &lhs, const stack<_T, ctnr> &rhs);

        template<typename _T, typename ctnr>
        friend bool operator<(const stack<_T, ctnr> &lhs, const stack<_T, ctnr> &rhs);
    };

    /* Non member function */

    template<typename T, typename Container>
    bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
        return lhs.c == rhs.c;
    }

    template<typename T, typename Container>
    bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
        return lhs.c != rhs.c;
    }

    template<typename T, typename Container>
    bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
        return lhs.c >= rhs.c;
    }

    template<typename T, typename Container>
    bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
        return lhs.c <= rhs.c;
    }

    template<typename T, typename Container>
    bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
        return lhs.c > rhs.c;
    }

    template<typename T, typename Container>
    bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
        return lhs.c < rhs.c;
    }
}