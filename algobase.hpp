#ifndef STL_IMPL_ALGOBASE_
#define STL_IMPL_ALGOBASE_

#include "iterator.hpp"
#include <functional>
#include <utility>
#include <cstring>
#include "__type_traits.hpp"

namespace stl {

// Equal
template<typename InputIterator1, typename InputIterator2>
inline bool equal(InputIterator1 first1, InputIterator1 last1,
                  InputIterator2 first2) {
    for ( ; first1 != last1; ++first1, ++first2)
        if (*first1 != *first2)
            return false;
    return true;
}

template<typename InputIterator1, typename InputIterator2, typename BinaryOperation>
inline bool equal(InputIterator1 first1, InputIterator1 last1,
                  InputIterator2 first2, BinaryOperation binary_op) {
    for ( ; first1 != last1; ++first1, ++first2)
        if (!binary_op(*first1, *first2))
            return false;
    return true;
}

// Fill
template<typename ForwardIterator, typename T>
void fill(ForwardIterator first, ForwardIterator last, const T& value) {
    for ( ; first != last; ++first)
        *first = value;
}

template<typename OutputIterator, typename Size, typename T>
void fill_n(OutputIterator first, Size n, const T& value) {
    for ( ; n > 0; --n, ++first)
        *first = value;
    return first;
}

// Iterator swap
template<typename ForwardIterator1, typename ForwardIterator2, typename T>
inline void __iter_swap(ForwardIterator1 a, ForwardIterator2 b, T*) {
    T tmp = *a;
    *a = *b;
    *b = tmp;
}

template<typename ForwardIterator1, typename ForwardIterator2>
inline void iter_swap(ForwardIterator1 a, ForwardIterator2 b) {
    __iter_swap(a, b, stl::value_type(a));
}

// Lexicographical compare
template<typename InputIterator1, typename InputIterator2>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                             InputIterator2 first2, InputIterator2 last2) {
    for ( ; first1 != last1 && first2 != last2; ++first1, ++first2) {
        if (*first1 < *first2)
            return true;
        if (*first2 < *first1)
            return false;
    }
    return first1 == last1 && first2 != last2;
}

template<typename InputIterator1, typename InputIterator2, typename Compare>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                             InputIterator2 first2, InputIterator2 last2,
                             Compare comp) {
    for ( ; first1 != last1 && first2 != last2; ++first1, ++first2) {
        if (comp(*first1, *first2))
            return true;
        if (comp(*first2, *first1))
            return false;
    }
    return first1 == last1 && first2 != last2;
}

// Min and max
template<typename T>
inline const T& min(const T& a, const T& b) {
    return b < a ? b : a;
}

template<typename T, typename Compare>
inline const T& min(const T& a, const T& b, Compare comp) {
    return comp(b, a) ? b : a;
}

template<typename T>
inline const T& max(const T& a, const T& b) {
    return b > a ? b : a;
}

template<typename T, typename Compare>
inline const T& max(const T& a, const T& b, Compare comp) {
    return comp(b, a) ? b : a;
}

template<typename T>
inline std::pair<T, T>
min_max(const T& a, const T& b) {
    return std::make_pair(min(a, b), max(a, b));
}

// Mismatch
template<typename InputIterator1, typename InputIterator2>
std::pair<InputIterator1, InputIterator2>
mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
    while (first1 != last1 && *first1 == *first2) {
        ++first1;
        ++first2;
    }
    return std::make_pair(first1, first2);
}

template<typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
std::pair<InputIterator1, InputIterator2>
mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2,
         BinaryPredicate binary_pred) {
    while (first1 != last1 && binary_pred(first1, *first2)) {
        ++first1;
        ++first2;
    }
    return std::make_pair(first1, first2);
}

// Swap
template<typename T>
inline void swap(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
}

// Copy
template<typename InputIterator, typename OutputIterator>
inline OutputIterator __copy(InputIterator first, InputIterator last,
                             OutputIterator result, stl::input_iterator_tag) {
    for ( ; first != last; ++result, ++first)
        *result = *first;
    return result;
}

template<typename RandomAccessIterator, typename OutputIterator, typename Distance>
inline OutputIterator
__copy_d(RandomAccessIterator first, RandomAccessIterator last,
         OutputIterator result, Distance*) {
    for (Distance n = last - first; n > 0; --n, ++result, ++first)
        *result = *first;
    return result;
}

template<typename RandomAccessIterator, typename OutputIterator>
inline OutputIterator
__copy(RandomAccessIterator first, RandomAccessIterator last,
       OutputIterator result, stl::random_access_iterator_tag) {
    return __copy_d(first, last, result, stl::distance_type(first));
}

template<typename T>
inline T* __copy_t(const T* first, const T* last, T* result, stl::__traits::__true_type) {
    std::memmove(result, first, sizeof(T) * (last - first));
    return result + (last - first);
}

template<typename T>
inline T* __copy_t(const T* first, const T* last, T* result, stl::__traits::__false_type) {
    return __copy_d(first, last, result, (ptrdiff_t*) 0);
}

template<typename InputIterator, typename OutputIterator>
struct __copy_dispatch {
    OutputIterator operator()(InputIterator first, InputIterator last, OutputIterator result) {
        return __copy(first, last, result, stl::iterator_category(first));
    }
};

template<typename T>
struct __copy_dispatch<T*, T*> {
    T* operator()(T* first, T* last, T* result) {
        typedef typename stl::__traits::__type_traits<T>::has_trivial_assignment_operator t;
        return __copy_t(first, last, result, t());
    }
};

template<typename T>
struct __copy_dispatch<const T*, T*> {
    T* operator()(const T* first, const T* last, T* result) {
        typedef typename stl::__traits::__type_traits<T>::has_trivial_assignment_operator t;
        return __copy_t(first, last, result, t());
    }
};

template<typename InputIterator, typename OutputIterator>
inline OutputIterator copy(InputIterator first, InputIterator last,
                           OutputIterator result) {
    return __copy_dispatch<InputIterator, OutputIterator>()
            (first, last, result);
}

inline char* copy(const char* first, const char* last, char* result) {
    std::memmove(result, first, last - first);
    return result + (last - first);
}

inline wchar_t* copy(const wchar_t* first, const wchar_t* last,
                     wchar_t* result) {
    memmove(result, first, sizeof(wchar_t) * (last - first));
    return result + (last - first);
}



}  // end of namespace stl

#endif /* STL_IMPL_ALGOBASE_ */