#pragma once

namespace ft {

    //MAPS:

    /* min max */
    template<class T>
    const T &max(const T &a, const T &b) { return (a < b) ? b : a; }

    template<class T, class Compare>
    const T &max(const T &a, const T &b, Compare comp) { return (comp()(a, b)) ? b : a; }

    template<class T>
    const T &min(const T &a, const T &b) { return (b < a) ? b : a; }

    template<class T, class Compare>
    const T &min(const T &a, const T &b, Compare comp) { return (comp()(b, a)) ? b : a; }

    /* less */
    template<class T>
    struct less {
        typedef bool result_type;
        typedef T first_argument_type;
        typedef T second_argument_type;

        bool operator()(const T &lhs, const T &rhs) const { return lhs < rhs; }
    };

    /* pair */
    template<class T1, class T2>
    struct pair {
        T1 first;
        T2 second;

        pair() : first(), second() {}

        pair(const T1 &a, const T2 &b) : first(a), second(b) {}

        template<class U1, class U2>
        pair(const pair<U1, U2> &src)        : first(src.first), second(src.second) {}

        ~pair() {}

        pair &operator=(const pair &rhs) {
            first = rhs.first;
            second = rhs.second;
            return *this;
        }
    };

    template<class T1, class T2>
    bool operator==(const pair<T1, T2> &a, const pair<T1, T2> &b) { return a.first == b.first && a.second == b.second; }

    template<class T1, class T2>
    bool operator!=(const pair<T1, T2> &a, const pair<T1, T2> &b) { return !(a == b); }

    template<class T1, class T2>
    bool operator<(const pair<T1, T2> &a, const pair<T1, T2> &b) {
        return a.first < b.first || (!(b.first < a.first) && a.second < b.second);
    }

    template<class T1, class T2>
    bool operator>(const pair<T1, T2> &a, const pair<T1, T2> &b) { return b < a; }

    template<class T1, class T2>
    bool operator<=(const pair<T1, T2> &a, const pair<T1, T2> &b) { return !(b < a); }

    template<class T1, class T2>
    bool operator>=(const pair<T1, T2> &a, const pair<T1, T2> &b) { return !(a < b); }

    /* make_pair */
    template<class T1, class T2>
    pair<T1, T2> make_pair(const T1 &a, const T2 &b) { return pair<T1, T2>(a, b); }




    ////////////////////////////////////////////////////////

    /* enable_if */
    template<bool Cond, class T = void>
    struct enable_if {
    };

    template<class T>
    struct enable_if<true, T> {
        typedef T type;
    };

    /* is_integral */
    template<class T>
    struct remove_c {
        typedef T type;
    };
    template<class T>
    struct remove_c<const T> {
        typedef T type;
    };

    template<class T, T v>
    struct integral_constant {
        const static T value = v;
        typedef T value_type;
        typedef integral_constant<T, v> type;

        operator value_type() const { return value; }

        value_type operator()() const { return value; }
    };

    typedef integral_constant<bool, true> true_type;
    typedef integral_constant<bool, false> false_type;

    template<class T>
    struct is_integral_base : public false_type {
    };

    template<>
    struct is_integral_base<bool> : public true_type {
    };
    template<>
    struct is_integral_base<char> : public true_type {
    };
    template<>
    struct is_integral_base<signed char> : public true_type {
    };
    template<>
    struct is_integral_base<short> : public true_type {
    };
    template<>
    struct is_integral_base<int> : public true_type {
    };
    template<>
    struct is_integral_base<long> : public true_type {
    };
    template<>
    struct is_integral_base<long long> : public true_type {
    };
    template<>
    struct is_integral_base<unsigned char> : public true_type {
    };
    template<>
    struct is_integral_base<unsigned short> : public true_type {
    };
    template<>
    struct is_integral_base<unsigned int> : public true_type {
    };
    template<>
    struct is_integral_base<unsigned long> : public true_type {
    };
    template<>
    struct is_integral_base<unsigned long long> : public true_type {
    };

    template<class T>
    struct is_integral : public is_integral_base<typename remove_c<T>::type> {
    };

    /* equal */
    template<class InputIterator1, class InputIterator2>
    bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2) {
        while (first1 != last1 && first2 != last2)
            if (*first1++ != *first2++)
                return false;
        return first1 == last1 && first2 == last2;
    }

    template<class InputIterator1, class InputIterator2, class BinaryPredicate>
    bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2,
               BinaryPredicate binary_pred) {
        while (first1 != last1 && first2 != last2)
            if (!binary_pred(*first1++, *first2++))
                return false;
        return first1 == last1 && first2 == last2;
    }

    /* lexicographical_compare */
    template<class InputIterator1, class InputIterator2>
    bool
    lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2) {
        while (first1 != last1) {
            if (first2 == last2 || *first2 < *first1)
                return false;
            else if (*first1 < *first2)
                return true;
            ++first1;
            ++first2;
        }
        return (first2 != last2);
    }

    template<class InputIterator1, class InputIterator2, class Compare>
    bool
    lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2,
                            Compare comp) {
        while (first1 != last1) {
            if (first2 == last2 || comp(*first2, *first1))
                return false;
            else if (comp(*first1, *first2))
                return true;
            ++first1;
            ++first2;
        }
        return (first2 != last2);
    }


    /* swap */

    template<class T>
    void swap(T &a, T &b) {
        T tmp = a;
        a = b;
        b = tmp;
    }
}
