#ifndef STL_IMPL_STACK_
#define STL_IMPL_STACK_

#include "deque.hpp"

namespace stl {
template<typename T, typename Sequence = stl::deque<T>>
class stack {
public:
    stack() = default;

public:
    typedef typename Sequence::value_type       value_type;
    typedef typename Sequence::size_type        size_type;
    typedef typename Sequence::reference        reference;
    typedef const typename Sequence::reference  const_reference;

public:
    bool operator== [[deprecated]] (const stack<T, Sequence>& rhs) {
        return this->c == rhs.c;
    }
    bool operator< [[deprecated]] (const stack<T, Sequence>& rhs) {
        return this->c < rhs.c;
    }

protected:
    Sequence c;     // built-in container
public:
    bool empty() const { return c.empty(); }
    size_type size() const { return c.size(); }
    reference top() { return c.back(); }
    const_reference top() const { return c.back(); }
    // stack: FILO
    void push(const value_type& x) { c.push_back(x); }
    void pop() { c.pop_back(); }
};

} // end of namespace stl
#endif /* STL_IMPL_STACK_ */