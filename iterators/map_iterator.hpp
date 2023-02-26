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
}