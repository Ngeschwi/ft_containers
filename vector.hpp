#pragma once

#include <iterator>
#include "iterators/random_access_iterator.hpp"
#include "iterators/reverse_iterator.hpp"
#include "utils.hpp"

namespace ft {

    template<class T, class Alloc = std::allocator <T> >
    class vector {
    public :

        typedef T value_type;
        typedef Alloc allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef ft::random_access_iterator<pointer> iterator;
        typedef ft::random_access_iterator<const_pointer> const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef std::ptrdiff_t difference_type;
        typedef std::size_t size_type;

    private :

        pointer _data;
        size_type _size;
        size_type _capacity;
        allocator_type _alloc;

        // return the new capacity
        // multiply by 2 if capacity is not enough
        size_type _adjust_capacity(size_type capacity) {
            if (capacity > _capacity * 2)
                return capacity;
            else
                return _capacity * 2;
        }

        // delete and deallocate all elements
        void _destroy_array() {
            for (size_type i = 0; i < _size; ++i)
                _alloc.destroy(_data + i);
        }

        //check the capacity and reallocate if needed
        void _check_capacity(size_type count) {
            if (count > _capacity) {
                //check if count is bigger than max size of the allocator
                if (count > max_size())
                    throw std::length_error("vector::assign: max_size exceeded");
                else
                    reserve(count);
            }
        }

    public :

        //Default constructor ft::vector<T> value in <> is the type of the elements
        //ft::vector<int> v; => v = []
        explicit vector(const allocator_type &alloc = allocator_type()) :
                _size(0),
                _capacity(0),
                _alloc(alloc) {
            _data = _alloc.allocate(_capacity);
        };

        // 2 parameter constructor
        // size_type size: the number of elements to initialize
        // value_type value: the value to initialize the elements with
        //ft::vector<int>(4, 100) v; => v = [100, 100, 100, 100]
        explicit vector(size_type size, const value_type &value = value_type(),
                        const allocator_type &alloc = allocator_type()) :
                _size(size),
                _capacity(size),
                _alloc(alloc) {
            _data = _alloc.allocate(_capacity);

            for (size_type i = 0; i < _capacity; i++)
                _alloc.construct(&_data[i], value);
        }

        // 2 parameter constructor
        // InputIterator first: the first element of the range to initialize the vector with
        // InputIterator last: the last element of the range to initialize the vector with
        //ft::vector<int>(first, last) v; => v = [values from first to last]
        template<class InputIterator>
        vector(InputIterator first,
               InputIterator last,
               const allocator_type &alloc = allocator_type(),
               typename ft::enable_if<!ft::is_integral<InputIterator>::value, void *>::type = NULL) :
                _data(NULL),
                _size(0),
                _capacity(0),
                _alloc(alloc) {

            assign(first, last);
        }

        // Copy constructor
        //ft::vector<int>(v) v2; => v2 = [values from v]
        vector(const vector<T> &src) :
                _data(NULL),
                _size(0),
                _capacity(0),
                _alloc(src._alloc) {
            assign(src.begin(), src.end());
        }

        // Destructor
        // delete all elements and deallocate memory
        ~vector() {
            clear();

//            if (_capacity)
            _alloc.deallocate(_data, _capacity);
        };

        // Assign operator
        //ft::vector<int> v; v2 = v; => v2 = [values from v]
        vector<T> &operator=(const vector<T> &rhs) {
            assign(rhs.begin(), rhs.end());
            return *this;
        };

        /* resize the vector to n elements and allocate memory if needed */
        void resize(size_type n, value_type val = value_type()) {

            //reallocate memory if needed
            if (n > _capacity)
                reserve(_adjust_capacity(n));

            if (n < _size) {
                for (size_type i = n; i < _size; ++i)
                    _alloc.destroy(&_data[i]);
                _size = n;
//                _capacity = n;
            } else if (n > _size) {
                for (size_type i = _size; i < n; ++i)
                    _alloc.construct(&_data[i], val);
                _size = n;
                _capacity = n;
            }
        }

        // reserve memory for n elements
        // if n is bigger than the max size of the allocator, throw an exception
        // if n is bigger than the current capacity, reallocate memory
        void reserve(size_type n) {
            //catch if n is bigger than allocator max size
            if (n > max_size())
                throw (std::length_error("vector::reserve: max_size exceeded"));

            //reallocate memory if needed
            if (n > _capacity) {

                //recreate allocated memory
                pointer newData = _alloc.allocate(n);// <-- tmp allocator

                for (size_type i = 0; i < _size; ++i)
                    _alloc.construct(newData + i, _data[i]);

                _destroy_array();

                //deallocate old memory
//                if (_capacity)
                    _alloc.deallocate(_data, _capacity);

                _data = newData;
                _capacity = n;
            }
        }

        void clear() {
            if (!empty()) {
                _destroy_array();
                _size = 0;
            }
        }

        // assign new content to the vector and destroy old data
        // example: vector<int> v(5, 10); => v = [10, 10, 10, 10, 10]
        //==> v.assign(4, 100); => v = [100, 100, 100, 100]
        void assign(size_type count, const T &value) {

            _check_capacity(count);

            iterator it = begin();

            //destroy old elements and fill with new ones
            for (size_type i = 0; i < _size || i < count; i++) {
                if (it < begin() + _size)
                    _alloc.destroy(&(*it));
                if (it < begin() + count)
                    _alloc.construct(&(*it), value);
                it++;
            }
            _size = count;
        }


        // assign new content to the vector and deallocate old memory
        template<class InputIterator>
        void assign(InputIterator first, InputIterator last,
                    typename ft::enable_if<!ft::is_integral<InputIterator>::value, void *>::type = NULL) {
            size_type count = 0;

            for (InputIterator it = first; it != last; it++)
                count++;

            _check_capacity(count);

            iterator it = begin();
            for (size_type i = 0; i < _size || i < count; i++) {
                if (it < begin() + _size)
                    _alloc.destroy(&(*it));
                if (it < begin() + count) {
                    _alloc.construct(&(*it), *first);
                    first++;
                }
                it++;
            }
            _size = count;
        }

        //Add an element to the end of the vector
        //If the vector is full, reallocate memory
        void push_back(const value_type &val) {
            if (_size == _capacity)
                reserve(_adjust_capacity(_size + 1));
            _alloc.construct(_data + _size, val);
            ++_size;
        }

        //remove the last element of the vector
        //if the vector is empty, do nothing
        void pop_back() {
            if (empty())
                return;

            --_size;
            _alloc.destroy(&_data[_size]);
        }

        //insert an element at the position pos
        //if the vector is full, reallocate memory
        iterator insert(iterator pos, const value_type &val) {
            //if position is the end of the vecto
            if (pos == end() && _size + 1 <= _capacity) {
                _alloc.construct(_data + _size, val);
                ++_size;

                return end() - 1;
            }

            //if the vector is full, reallocate memory
            if (_size + 1 > _capacity) {

                pointer newData = _alloc.allocate(_adjust_capacity(_size + 1)); //<-- tmp pointer to new memory
                size_type beginPos = pos - begin();

                //set the value at the right position
                _alloc.construct(newData + beginPos, val);

                //copy the old values between the new ones
                for (size_type i = 0; i <= _size; ++i) {

                    if (i < beginPos)
                        _alloc.construct(newData + i, _data[i]);
                    else if (i > beginPos)
                        _alloc.construct(newData + i, _data[i - 1]);
                }

                //destroy and deallocate old memory
                _destroy_array();
                _alloc.deallocate(_data, _capacity);

                //update the vector attributes
                _capacity = _adjust_capacity(_size + 1);
                _data = newData;
                ++_size;

                return begin() + beginPos;
            } else {
                size_type beginPos = pos - begin();
                _alloc.construct(_data + _size, *(_data + _size - 1));
                for (size_type i = _size - 1; i > beginPos; --i)
                    _data[i] = _data[i - 1];
                *pos = val;
                ++_size;
                return begin() + beginPos;
            }
        }

        void insert(iterator pos, size_type count, const value_type &val) {
            if (_size + count > _capacity) {
                size_type posIndex = pos - begin();
                pointer newData = _alloc.allocate(_adjust_capacity(_size + count));
                size_type newCapacity = _adjust_capacity(_size + count);
                for (size_type i = 0; i < count; ++i) {
                    _alloc.construct(newData + posIndex + i, val);
                }
                size_t j = 0;
                for (size_type i = 0; i < _size + count; ++i) {
                    if (i >= posIndex && i < posIndex + count)
                        continue;
                    _alloc.construct(newData + i, _data[j]);
                    ++j;
                }
                _destroy_array();
                _alloc.deallocate(_data, _capacity);
                _capacity = newCapacity;
                _data = newData;
                _size += count;
                return;
            }
            for (iterator it = end() + count - 1; it != pos + count - 1; --it) {
                if (it >= end())
                    _alloc.construct(it.base(), *(it - count));
                else
                    *it = *(it - count);
            }
            for (iterator it = pos; it != pos + count; ++it) {
                if (it >= end())
                    _alloc.construct(it.base(), val);
                else
                    *it = val;
            }
            _size += count;
        }

        template<class InputIterator>
        void insert(iterator pos, InputIterator first, InputIterator last,
                    typename ft::enable_if<!ft::is_integral<InputIterator>::value, void *>::type = NULL) {
            size_type count = 0;
            for (InputIterator it = first; it != last; it++)
                count++;
            if (_size + count > _capacity) {
                size_type posIndex = pos - begin();
                pointer newData = _alloc.allocate(_adjust_capacity(_size + count));
                size_type newCapacity = _adjust_capacity(_size + count);
                for (size_type i = 0; i < count; ++i) {
                    _alloc.construct(newData + posIndex + i, *first);
                    ++first;
                }
                size_t j = 0;
                for (size_type i = 0; i < _size + count; ++i) {
                    if (i >= posIndex && i < posIndex + count)
                        continue;
                    _alloc.construct(newData + i, _data[j]);
                    ++j;
                }
                _destroy_array();
                _alloc.deallocate(_data, _capacity);
                _capacity = newCapacity;
                _data = newData;
                _size += count;
                return;
            }
            for (iterator it = end() + count - 1; it != pos + count - 1; --it) {
                if (it >= end())
                    _alloc.construct(it.base(), *(it - count));
                else
                    *it = *(it - count);
            }
            for (iterator it = pos; first != last; ++it) {
                if (it >= end())
                    _alloc.construct(it.base(), *first);
                else
                    *it = *first;
                ++first;
            }
            _size += count;
        }

        void swap(vector &b) {
            ft::swap(_data, b._data);
            ft::swap(_size, b._size);
            ft::swap(_capacity, b._capacity);
            ft::swap(_alloc, b._alloc);
        }

        //destroy element at pos
        //return iterator to the next element
        iterator erase(iterator pos) {
            //if the container is empty
            if (pos == end())
                return end();

            //find the index of the element to be deleted
            for (iterator it = pos; it != end() - 1; ++it)
                *it = *(it + 1);

            _alloc.destroy((end() - 1).base());
            --_size;
            return pos;
        }

        //destroy elements in range [first, last)
        //return iterator to the next element
        iterator erase(iterator first, iterator last) {
            iterator firstp = first;

            //find the index of the element to be deleted
            for (iterator it = last; it != end(); ++it) {
                *firstp = *it;
                ++firstp;
            }

            //destroy the elements in the range [first, last)
            for (reverse_iterator it = rbegin(); it != reverse_iterator(firstp); ++it) {
                _alloc.destroy(it.base().base() - 1);
                --_size;
            }
            return first;
        }

        iterator begin() {
            return iterator(_data);
        }

        const_iterator begin() const {
            return const_iterator(_data);
        }

        iterator end() {
            return iterator(_data + _size);
        }

        const_iterator end() const {
            return const_iterator(_data + _size);
        }

        reverse_iterator rbegin() {
            return reverse_iterator(end());
        }

        const_reverse_iterator rbegin() const {
            return const_reverse_iterator(end());
        }

        reverse_iterator rend() {
            return reverse_iterator(begin());
        }

        const_reverse_iterator rend() const {
            return const_reverse_iterator(begin());
        }

        size_type size() const {
            return _size;
        }

        size_type max_size() const {
            return _alloc.max_size();
        }

        size_type capacity() const {
            return _capacity;
        }

        bool empty() const {
            if (_size)
                return false;

            return true;
        }

        value_type &operator[](const size_t &i) const {
            return _data[i];
        }

        reference front() {
            return _data[0];
        }

        const_reference front() const {
            return _data[0];
        }

        reference back() {
            return _data[_size - 1];
        }

        const_reference back() const {
            return _data[_size - 1];
        }

        pointer data() {
            return _data;
        }

        const_pointer data() const {
            return _data;
        }

        reference at(size_type n) {
            if (n >= _size)
                throw std::out_of_range("ft::vector::at");
            return _data[n];
        }

        const_reference at(size_type n) const {
            if (n >= _size)
                throw std::out_of_range("ft::vector::at");
            return _data[n];
        }


        allocator_type get_allocator() const {
            return _alloc;
        }
    };

    template<class T, class Alloc>
    void swap(vector<T, Alloc> &a, vector<T, Alloc> &b) {
        a.swap(b);
    }

    template<class T, class Alloc>
    bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
        return ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template<class T, class Alloc>
    bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
        return !(lhs == rhs);
    }

    template<class T, class Alloc>
    bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template<class T, class Alloc>
    bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
        return rhs < lhs;
    }

    template<class T, class Alloc>
    bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
        return !(lhs > rhs);
    }

    template<class T, class Alloc>
    bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
        return !(lhs < rhs);
    }
}