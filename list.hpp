#ifndef STL_IMPL_LIST_
#define STL_IMPL_LIST_

#include "./iterator.hpp"
#include "memory/alloc.hpp"
#include <iterator>
namespace stl {

template<typename T>
struct __list_node {
    typedef void *void_pointer;
    void_pointer prev;
    void_pointer next;
    T data;
};

template<typename T, typename Ref, typename Ptr>
struct __list_iterator {
    typedef __list_iterator<T, T&, T*>     iterator;
    typedef __list_iterator<T, Ref, Ptr>   self;

    typedef bidirectional_iterator_tag iterator_category;
    typedef T                          value_type;
    typedef Ptr                        pointer;
    typedef Ref                        reference;
    typedef __list_node<T>*            link_type;
    typedef std::size_t                size_type;
    typedef std::ptrdiff_t             difference_type;

    link_type node;

    __list_iterator(link_type x) : node(x) {}
    __list_iterator() {}
    __list_iterator(const iterator& x) : node(x.node) {}

    bool operator==(const self& x) const { return node == x.node; }
    bool operator!=(const self& x) const { return node != x.node; }
    reference operator*() const { return node->data; }
    pointer operator->() const { return &(operator*()); }

    self& operator++() {
        node = (link_type)(node->next);
        return *this;
    }
    self& operator++(int) {
        self tmp = *this;
        ++*this;
        return tmp;
    }
    self& operator--() {
        node = (link_type)(node->prev);
        return *this;
    }
    self& operator--(int) {
        self tmp = *this;
        --*this;
        return tmp;
    }

    self operator+(int idx) {
        if (idx == 0) return *this;
        auto result = *this;
        while (idx < 0) {
            ++idx;
            result.node = (link_type)(result.node->prev);
        }
        while (idx > 0) {
            --idx;
            result.node = (link_type)(result.node->next);
        }
        return result;
    }
    self operator-(int idx) {
        return operator+(-idx);
    }
};

using namespace memory;

template<typename T, typename Alloc = alloc>
class list {
protected:
    typedef __list_node<T> list_node;
    typedef simple_alloc<list_node, Alloc> list_node_allocator;
public:
    typedef list_node* link_type;
    typedef __list_iterator<T, T&, T*> iterator;
    typedef T                          value_type;
    typedef T*                         pointer;
    typedef T&                         reference;
    typedef std::size_t                size_type;
    typedef std::ptrdiff_t             difference_type;
protected:
    link_type node;

protected:
    link_type get_node() { return list_node_allocator::allocate(); }
    void put_node(link_type p) { list_node_allocator::deallocate(p); }
    link_type create_node(const T& x) {
        link_type p = get_node();
        construct(&p->data, x);
        return p;
    }
    void destroy_node(link_type p) {
        destroy(&p->data);
        put_node(p);
    }

public:
    iterator begin() const { return (link_type)(node->next); }
    iterator end() const   { return node; }
    bool empty() const { return node->next == node; }
    size_type size() const {
        return distance(begin(), end());
    }
    reference front() { return *begin(); }
    reference back()  { return *(--end()); }

    list() { empty_initialize(); }
    template<typename InputIterator>
    list(InputIterator first, InputIterator last) : list() {
        for (; first != last; ++first) {
            push_back(*first);
        }
    }
    explicit list(size_type n) : list() {
        for ( ; n > 0; --n) {
            push_back(T());
        }
    }

protected:
    void empty_initialize() {
        node = get_node();
        node->next = node;
        node->prev = node;
    }

public:
    void push_front(const T& x) { insert(begin(), x); }
    void push_back(const T& x) { insert(end(), x); }

    iterator insert(iterator position, const T& x) {
        link_type tmp = create_node(x);
        tmp->next = position.node;
        tmp->prev = position.node->prev;
        (link_type(position.node->prev))->next = tmp;
        position.node->prev = tmp;
        return tmp;
    }
    void insert(iterator position, size_type n, const T& x) {
        while (n--) {
            insert(position, x);
        }
    }

    iterator erase(iterator position) {
        link_type next_node = link_type(position.node->next);
        link_type prev_node = link_type(position.node->prev);
        prev_node->next = next_node;
        next_node->prev = prev_node;
        destroy_node(position.node);
        return iterator(next_node);
    }
    void pop_front() { erase(begin()); }
    void pop_back() {
        erase(--end());
    }
    void clear();
    void remove(const T& value);
    void unique();

protected:
    void transfer(iterator position, iterator first, iterator last) {
        if (position != last) {
            link_type(last.node->prev)->next = position.node;
            link_type(first.node->prev)->next = last.node;
            link_type(position.node->prev)->next = first.node;
            link_type tmp = link_type(position.node->prev);
            position.node->prev = last.node->prev;
            last.node->prev = first.node->prev;
            first.node->prev = tmp;
        }
    }

public:
    void swap(list<T, Alloc>& x) {
        auto tmp = node;
        node = x.node;
        x.node = tmp;
    }

    void splice(iterator position, list& x) {
        if (!x.empty())
            transfer(position, x.begin(), x.end());
    }
    void splice(iterator position, list&, iterator i) {
        iterator j = i;
        ++j;
        if (position == i || position == j) return ;
        transfer(position, i, j);
    }
    void splice(iterator position, list&, iterator first, iterator last) {
        if (first != last) 
            transfer(position, first, last);
    }

    void merge(list<T, Alloc>& x);
    void reverse();
    void sort() {
        sort([](const T& a, const T& b) { return a < b; });
    }
    template<typename Pred>
    void sort(Pred pred) {
        // bubble sort?
        for (auto i = begin(); i != end(); ++i) {
            for (auto j = i + 1; j != end(); ++j) {
                if (!pred(*i, *j)) {
                    auto tmp = *i;
                    *i = *j;
                    *j = tmp;
                }
            }
        }
    }
};

template<typename T, typename Alloc>
void list<T, Alloc>::clear()
{
    link_type cur = (link_type) node->next;
    while (cur != node) {
        link_type tmp = cur;
        cur = (link_type) cur->next;
        destroy_node(tmp);
    }
    node->next = node->prev = node;
}

template<typename T, typename Alloc>
void list<T, Alloc>::remove(const T& value)
{
    iterator first = begin();
    iterator last  = end();
    while (first != last) {
        iterator next = first;
        ++next;
        if (*first == value) erase(first);
        first = next;
    }
}

template<typename T, typename Alloc>
void list<T, Alloc>::unique() {
    iterator first = begin();
    iterator last  = end();
    if (first == last) return ;
    iterator next = first;
    while (++next != last) {
        if (*first == *next)
            erase(next);
        else
            first = next;
        next = first;
    }
}

template<typename T, typename Alloc>
void list<T, Alloc>::merge(list<T, Alloc>& x) {
    iterator first1 = begin();
    iterator last1  = end();
    iterator first2 = x.begin();
    iterator last2  = x.end();

    while (first1 != last1 && first2 != last2) {
        if (*first2 < *first1) {
            iterator next = first2;
            transfer(first1, first2, ++next);
            first2 = next;
        } 
        else {
            ++first1;
        }
        if (first2 != last2) transfer(last1, first2, last2);
    }
}

template<typename T, typename Alloc>
void list<T, Alloc>::reverse()
{
    if (node->next == node || link_type(node->next)->next == node)
        return ;
    iterator first = begin();
    ++first;
    while (first != end()) {
        iterator old = first;
        ++first;
        transfer(begin(), old, first);
    }
}

}  // end of namespace stl


#endif /* STL_IMPL_LIST_ */