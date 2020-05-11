#ifndef STL_IMPL_LIST_
#define STL_IMPL_LIST_

#include "./iterator.hpp"
#include "memory/alloc.hpp"

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
    iterator begin() { return (link_type)(node->next); }
    iterator end()   { return node; }
    bool empty() const { return node->next == node; }
    size_type size() const {
        size_type result = 0;
        distance(begin(), end(), result);
        return result;
    }
    reference front() { return *begin(); }
    reference back()  { return *(--end()); }

    list() { empty_initialize(); }

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
            (link_type)(last->node.prev->next = position.node;
            (link_type)(first->node.prev->next = last.node;
            (link_type)(position->node.prev->next = first.node;
            link_type tmp = link_type(position->node.prev);
            position->node.prev = last->node.prev;
            last->node.prev = first->node.prev;
            first->node.prev = tmp;
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

}  // end of namespace stl


#endif /* STL_IMPL_LIST_ */