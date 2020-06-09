#ifndef STL_IMPL__RB_TREE_
#define STL_IMPL__RB_TREE_

#include "iterator.hpp"
#include <cstddef>
#include "./memory/alloc.hpp"

namespace stl
{

typedef bool __rb_tree_color_type;
const __rb_tree_color_type __rb_tree_red = false;
const __rb_tree_color_type __rb_tree_black = true;

struct __rb_tree_node_base {
    typedef __rb_tree_color_type color_type;
    typedef __rb_tree_node_base* base_ptr;

    color_type color;
    base_ptr parent;
    base_ptr left;
    base_ptr right;
    
    static base_ptr minimum(base_ptr x) {
        while (x->left != nullptr)
            x = x->left;
        return x;
    }

    static base_ptr maximum(base_ptr x) {
        while (x->right != nullptr)
            x = x->right;
        return x;
    }
};

template<typename Value>
struct __rb_tree_node : public __rb_tree_node_base {
    typedef __rb_tree_node<Value>* link_type;
    Value value_field;
};

struct __rb_tree_base_iterator {
    typedef __rb_tree_node_base::base_ptr base_ptr;
    typedef bidirectional_iterator_tag iterator_category;
    typedef std::ptrdiff_t difference_type;

    base_ptr node;

    void increment()
    {
        if (node->right != nullptr) {
            node = node->right;
            while (node->left != nullptr)
                node = node->left;
        } else {
            base_ptr y = node->parent;
            while (node == y->right) {
                node = y;
                y = y->parent;
            }
            if (node->right != y)
                node = y;
        }
    }

    void decrement()
    {
        if (node->color == __rb_tree_red && node->parent->parent == node) {
            node = node->right;
        } else if (node->left != nullptr) {
            base_ptr y = node->left;
            while (y->right != nullptr)
                y = y->right;
            node = y;
        } else {
            base_ptr y = node->parent;
            while (node == y->left) {
                node = y;
                y = y->parent;
            }
            node = y;
        }
    }

};

template<typename Value, typename Ref, typename Ptr>
struct __rb_tree_iterator : public __rb_tree_base_iterator {
    typedef Value value_type;
    typedef Ref reference;
    typedef Ptr pointer;
    typedef __rb_tree_iterator<Value, Value&, Value*> iterator;
    typedef __rb_tree_iterator<Value, const Value&, const Value*> const_iterator;
    typedef __rb_tree_iterator<Value, Ref, Ptr> self;
    typedef __rb_tree_node<Value>* link_type;

    __rb_tree_iterator() {}
    __rb_tree_iterator(link_type x) { node = x; }
    __rb_tree_iterator(const iterator& itr) { node = itr.node; }

    reference operator*() const { return link_type(node)->value_field; }
    pointer operator->() const { return &(operator*()); }

    self& operator++() {
        increment();
        return *this;
    }
    self operator++(int) {
        self tmp = *this;
        increment();
        return tmp;
    }

    self& operator--() {
        decrement();
        return *this;
    }
    self operator--(int) {
        self tmp = *this;
        decrement();
        return tmp;
    }
};

using namespace memory;
template<typename Key, typename Value, typename KeyOfValue, typename Compare, typename Alloc = alloc>
class rb_tree {
protected:
    typedef void* void_pointer;
    typedef __rb_tree_node_base* base_ptr;
    typedef __rb_tree_node<Value> rb_tree_node;
    typedef simple_alloc<rb_tree_node, Alloc> rb_tree_node_allocator;
    typedef __rb_tree_color_type color_type;

public:
    typedef Key key_type;
    typedef Value value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef rb_tree_node* link_type;
    typedef std::size_t size_type;
    typedef ptrdiff_t difference_type;

protected:
    link_type get_node() {
        return rb_tree_node_allocator::allocate();
    }
    void put_node(link_type p) {
        rb_tree_node_allocator::deallocate(p);
    }

    link_type create_node(const value_type& x) {
        link_type tmp = get_node();
        try {
            construct(&tmp->value_field, x);
        } catch (...) {
            put_node(tmp);
        }
        return tmp;
    }

    link_type clone_node(link_type x) {
        link_type tmp = create_node(x->value_field);
        tmp->color = x->color;
        tmp->left = nullptr;
        tmp->right = nullptr;
        return tmp;
    }

    void destroy_node(link_type p) {
        destroy(&p->value_field);
        put_node(p);
    }

protected:
    size_type node_count;
    link_type header;
    Compare key_compare;

    link_type& root() const {
        return (link_type&) header->parent;
    }
    link_type& leftmost() const {
        return (link_type&) header->left;
    }
    link_type& rightmost() const {
        return (link_type&) header->right;
    }

    static link_type& left(link_type x)
      { return (link_type&)(x->left); }
    static link_type& right(link_type x)
      { return (link_type&)(x->right); }
    static link_type& parent(link_type x)
      { return (link_type&)(x->parent); }
    static reference value(link_type x)
      { return x->value_field; }
    static const Key& key(link_type x)
      { return KeyOfValue()(value(x)); }
    static color_type& color(link_type x)
      { return (color_type&)(x->color); }
    
    static link_type& left(base_ptr x)
      { return (link_type&)(x->left); }
    static link_type& right(base_ptr x)
      { return (link_type&)(x->right); }
    static link_type& parent(base_ptr x)
      { return (link_type&)(x->parent); }
    static reference value(base_ptr x)
      { return (link_type(x))->value_field; }
    static const Key& key(base_ptr x)
      { return KeyOfValue()(value(link_type(x))); }
    static color_type& color(base_ptr x)
      { return (color_type&)(link_type(x)->color); }

    static link_type minimum(link_type x) {
        return (link_type) __rb_tree_node_base::minimum(x);
    }
    static link_type maximum(link_type x) {
        return (link_type) __rb_tree_node_base::maximum(x);
    }

public:
    typedef __rb_tree_iterator<value_type, reference, pointer> iterator;

private:
    iterator __insert(base_ptr x, base_ptr y, const value_type& v);
    link_type __copy(link_type x, link_type p);
    void __erase(link_type x);
    void init() {
        header = get_node();
        color(header) = __rb_tree_red;
        root() = nullptr;
        leftmost() = header;
        rightmost() = header;
    }

};

}

#endif /* STL_IMPL__RB_TREE_ */