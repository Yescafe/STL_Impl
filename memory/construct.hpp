#ifndef STL_IMPL_MEMORY_CONSTRUCT_
#define STL_IMPL_MEMORY_CONSTRUCT_

#include <new>  // for placement new
#include "../__type_traits.hpp"
using namespace stl::__traits;
#include "../iterator.hpp"

namespace stl::memory {

template<typename T1, typename T2>
inline void construct(T1 *p, const T2 &value) {
    new (p) T1(value);
}

template<typename T>
inline void destroy(T *pointer) {
    pointer->~T();
}

namespace hidden {

template<typename ForwardIterator>
inline void
__destroy_aux(ForwardIterator first, ForwardIterator last, __false_type) {
    for ( ; first < last; ++first)
        destroy(&*first);
}

template<typename ForwardIterator>
inline void
__destroy_aux(ForwardIterator first, ForwardIterator last, __true_type) {}

template<typename ForwardIterator, typename T>
inline void __destroy(ForwardIterator first, ForwardIterator last, T*) {
    typedef typename __type_traits<T>::has_trivial_destructor trivial_destructor;
    __destroy_aux(first, last, trivial_destructor());
}

} /* end of namespace hidden */

template<typename ForwardIterator>
inline void destroy(ForwardIterator first, ForwardIterator last) {
    hidden::__destroy(first, last, value_type(first));
}

inline void destroy(char *,char *) {}
inline void destroy(wchar_t *, wchar_t *) {}

} /* end of namespace stl::memory */

#endif /* STL_IMPL_MEMORY_CONSTRUCT_ */