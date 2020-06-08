#ifndef STL_IMPL_PQUEUE_
#define STL_IMPL_PQUEUE_

#include "vector.hpp"
#include "algorithm.hpp"
#include <functional>

namespace stl
{

template<typename T, typename Sequence = stl::vector<T>, typename Compare = std::less<typename Sequence::value_type>>
class priority_queue {
public:
    typedef typename Sequence::value_type       value_type;
    typedef typename Sequence::size_type        size_type;
    typedef typename Sequence::reference        reference;
    typedef const typename Sequence::reference  const_reference;

protected:
    Sequence c;     // built-in container
    Compare comp;
public:
    priority_queue() : c() {}
    explicit priority_queue(const Compare& x) : c(), comp(x) {}
    template<typename InputIterator>
    priority_queue(InputIterator first, InputIterator last, const Compare& x)
     : c(first, last), comp(x) {
        stl::make_heap(c.begin(), c.end(), comp);
    }
    template<typename InputIterator>
    priority_queue(InputIterator first, InputIterator last)
     : c(first, last) {
        stl::make_heap(c.begin(), c.end(), comp);
    }

    bool empty() const { return c.empty(); }
    size_type size() const { return c.size(); }
    const_reference top() { return c.front(); }
    void push(const value_type& x) {
        try {
            c.push_back(x);
            stl::push_heap(c.begin(), c.end(), comp);
        } catch (...) {
            c.clear();
            throw ;
        }
    }
    void pop() {
        try {
            stl::pop_heap(c.begin(), c.end(), comp);
            c.pop_back();
        } catch (...) {
            c.clear();
            throw ;
        }
    }
};

} // end of namespace stl

#endif /* STL_IMPL_PQUEUE_ */