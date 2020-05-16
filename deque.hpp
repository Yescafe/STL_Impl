#ifndef STL_IMPL_DEQUE_
#define STL_IMPL_DEQUE_

#include <cstddef>
#include <iostream>
#include "memory/alloc.hpp"
#include "iterator.hpp"

namespace stl {

using namespace memory;

inline std::size_t __deque_buf_size(std::size_t n, std::size_t sz)
{
    return n != 0 ? n : (sz < 512 ? std::size_t(512 / sz) : std::size_t(1));
}

template<typename T, typename Ref, typename Ptr, std::size_t BufSiz>
struct __deque_iterator {
    typedef __deque_iterator<T, T&, T*, BufSiz> iterator;
    typedef __deque_iterator<T, const T&, const T*, BufSiz> const_iterator;
    static std::size_t buffer_size() { return __deque_buf_size(BufSiz, sizeof(T)); }

    typedef random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef Ptr pointer;
    typedef Ref reference;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef T** map_pointer;

    typedef __deque_iterator self;

    T* cur;
    T* first;
    T* last;
    map_pointer node;

    void set_node(map_pointer new_node) {
        node = new_node;
        first = *new_node;
        last = first + difference_type(buffer_size());
    }

    reference operator*() const { return *cur; }
    pointer operator->() const { return &(operator*()); }
    difference_type operator-(const self& x) const {
        return difference_type(buffer_size()) * (node - x.node - 1) + 
            (cur - first) + (x.last - x.cur);
    }

    self& operator++() {
        ++cur;
        if (cur == last) {
            set_node(node + 1);
            cur = first;
        }
        return *this;
    }
    self operator++(int) {
        self tmp = *this;
        ++*this;
        return tmp;
    }
    self& operator--() {
        --cur;
        if (cur == first) {
            set_node(node - 1);
            cur = last;
        }
        return *this;
    }
    self operator--(int) {
        self tmp = *this;
        --*this;
        return tmp;
    }

    self& operator+=(difference_type n) {
        difference_type offset = n + (cur - first);
        if (offset >= 0 && offset < difference_type(buffer_size()))
            cur += n;
        else {
            difference_type node_offset = 
                offset > 0 ? offset / difference_type(buffer_size())
                    : -difference_type((-offset - 1) / buffer_size()) - 1;
            set_node(node + node_offset);
            cur = first + (offset - node_offset * difference_type(buffer_size()));
        }
        return *this;
    }
    self operator+(difference_type n) const {
        self tmp = *this;
        return tmp += n;
    }
    self& operator-=(difference_type n) { return *this += -n; }
    self operator-(difference_type n) const {
        self tmp = *this;
        return tmp -= n;
    }

    reference operator[](difference_type n) const { return *(*this + n); }

    bool operator==(const self& x) const { return cur == x.cur; }
    bool operator!=(const self& x) const { return !(*this == x); }
    bool operator<(const self& x) const {
        return (node == x.node) ? (cur < x.cur) : (node < x.node);
    }

};

template<typename T, typename Alloc = alloc, std::size_t BufSiz = 0>
class deque {
public:
    typedef T value_type;
    typedef value_type* pointer;
    typedef value_type& reference;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
protected:
    typedef pointer *map_pointer;

public:
    typedef __deque_iterator<T, T&, T*, BufSiz> iterator;

protected:
    iterator start;
    iterator finish;

    map_pointer map;

    size_type map_size;

public:
    iterator begin() { return start; }
    iterator end() { return finish; };

    reference operator[](size_type n) {
        return start[difference_type(n)];
    }

    reference front() { return *start; }
    reference back() {
        iterator tmp = finish;
        --tmp;
        return tmp;
    }

    size_type size() const { return finish - start; }
    size_type max_size() const { return size_type(-1); }
    bool empty() const { return finish == start; }

protected:
    typedef simple_alloc<value_type, Alloc> data_allocator;
    typedef simple_alloc<pointer, Alloc> map_allocator;

    deque(int n, const value_type& value)
     : start(), finish(), map(0), map_size(0)
    {
        fill_initialize(n, value);
    }
    void fill_initialize(size_type n, const value_type& value);
    void create_map_and_nodes(size_type num_elements);
    size_type buffer_size() {
        return __deque_buf_size(BufSiz, sizeof(value_type));
    }
    size_type initial_map_size() {
        return size_type(8);
    }
    map_pointer allocate_node() {
        return data_allocator::allocate(buffer_size());
    }
};

template<typename T, typename Alloc, std::size_t BufSiz>
void deque<T, Alloc, BufSiz>::fill_initialize(size_type n, const value_type& value)
{
    create_map_and_nodes(n);
    map_pointer cur;
    try {
        for (cur = start.node; cur < finish.node; ++cur)
            uninitialized_fill(*cur, *cur + buffer_size(), value);
        uninitialized_fill(finish.first, finish.cur, value);
    } catch (...) {
        throw;
    }
}

template<typename T, typename Alloc, std::size_t BufSiz>
void deque<T, Alloc, BufSiz>::create_map_and_nodes(size_type num_elements)
{
    size_type num_nodes = num_elements;

    map_size = std::max(initial_map_size(), num_nodes + 2);
    map = map_allocator::allocate(map_size);
    
    map_pointer nstart = map + (map_size - num_nodes) / 2;
    map_pointer nfinish = nstart + num_nodes - 1;

    map_pointer cur;
    try {
        for (cur = nstart; cur <= nfinish; ++cur)
            *cur = allocate_node();
    }
    catch (...) {
        throw;
    }

    start.set_node(nstart);
    finish.set_node(nfinish);
    start.cur = start.first;
    finish.cur = finish.first + num_elements % buffer_size();
}


}

#endif /* STL_IMPL_DEQUE_ */