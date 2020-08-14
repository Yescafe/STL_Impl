#ifndef STL_IMPL_ALGORITHM_
#define STL_IMPL_ALGORITHM_

#include "algoheap.hpp"
#include "algobase.hpp"

#include "iterator.hpp"
#include "utility.hpp"

namespace stl
{

// Adjacent find
template<typename ForwardIterator>
ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last) {
    if (first == last) return last;
     ForwardIterator next = first;
     while (++next != last) {
         if (*first == *next)
            return first;
        first = next;
     }
     return last;
}

template<typename ForwardIterator, typename BinaryPredicate>
ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last, BinaryPredicate binary_op) {
    if (first == last) return last;
     ForwardIterator next = first;
     while (++next != last) {
         if (binary_op(*first, *next))
            return first;
        first = next;
     }
     return last;
}

// Count
template<typename InputIterator, typename T>
typename stl::iterator_traits<InputIterator>::difference_type
count(InputIterator first, InputIterator last, const T& value) {
    typename stl::iterator_traits<InputIterator>::difference_type n = 0;
    for ( ; first != last; ++first)
        if (*first == value)
            ++n;
    return n;
}

template<typename InputIterator, typename Predicate>
typename stl::iterator_traits<InputIterator>::difference_type
count_if(InputIterator first, InputIterator last, Predicate pred) {
    typename stl::iterator_traits<InputIterator>::difference_type n = 0;
    for ( ; first != last; ++first)
        if (pred(*first))
            ++n;
    return n;
}

// Search
// TODO
template<typename ForwardIterator1, typename ForwardIterator2>
ForwardIterator1 search(ForwardIterator1 first1, ForwardIterator1 last1,
                        ForwardIterator2 first2, ForwardIterator2 last2) {
    return last1;
}

// Find
template<typename InputIterator, typename T>
InputIterator find(InputIterator first, InputIterator last, const T& value) {
    while (first != last && *first != value)
        ++first;
    return first;
}

template<typename InputIterator, typename Predicate>
InputIterator find_if(InputIterator first, InputIterator last, Predicate pred) {
    while (first != last && !pred(*first))
        ++first;
    return first;
}

template<typename ForwardIterator1, typename ForwardIterator2>
inline ForwardIterator1
find_end(ForwardIterator1 first1, ForwardIterator1 last1,
         ForwardIterator2 first2, ForwardIterator2 last2) {
    typedef typename stl::iterator_traits<ForwardIterator1>::iterator_category category1;
    typedef typename stl::iterator_traits<ForwardIterator2>::iterator_category category2;

    return __find_end(first1, last1, first2, last2, category1(), category2());
}

template<typename ForwardIterator1, typename ForwardIterator2>
ForwardIterator1
__find_end(ForwardIterator1 first1, ForwardIterator1 last1,
           ForwardIterator2 first2, ForwardIterator2 last2,
           stl::forward_iterator_tag, stl::forward_iterator_tag) {
    if (first2 == last2)
        return last1;
    else {
        ForwardIterator1 result = last1;
        while (1) {
            ForwardIterator1 new_result = search(first1, last1, first2, last2);
            if (new_result == last1)
                return result;
            else {
                result = new_result;
                first1 = new_result;
                ++first1;
            }
        }
    }
}

template<typename ForwardIterator1, typename ForwardIterator2>
ForwardIterator1
__find_end(ForwardIterator1 first1, ForwardIterator1 last1,
           ForwardIterator2 first2, ForwardIterator2 last2,
           stl::bidirectional_iterator_tag, stl::bidirectional_iterator_tag) {
    return search(first1, last1, first2, last2);    // TODO P347
}

template<typename InputIterator, typename ForwardIterator>
InputIterator find_first_of(InputIterator first1, InputIterator last1,
                            ForwardIterator first2, ForwardIterator last2) {
    for ( ; first1 != last1; ++first1)
        for (auto itr = first2; itr != last2; ++itr)
            if (*first1 == *itr)
                return first1;
    return last1;
}

template<typename InputIterator, typename ForwardIterator, typename BinaryPredicate>
InputIterator find_first_of(InputIterator first1, InputIterator last1,
                            ForwardIterator first2, ForwardIterator last2, BinaryPredicate comp) {
    for ( ; first1 != last1; ++first1)
        for (auto itr = first2; itr != last2; ++itr)
            if (comp(*first1, *itr))
                return first1;
    return last1;
}

// Foreach
template<typename InputIterator, typename Function>
Function for_each(InputIterator first, InputIterator last, Function f) {
    for ( ; first != last; ++first)
        f(*first);
    return f;
}

// Generate
template<typename ForwardIterator, typename Generator>
void generate(ForwardIterator first, ForwardIterator last, Generator gen) {
    for ( ; first != last; ++first)
        *first = gen();
}

template<typename OutputIterator, typename Size, typename Generator>
OutputIterator generate_n(OutputIterator first, Size n, Generator gen) {
    for ( ; n > 0; --n, ++first)
        *first = gen();
    return first;
}

// Includes
template<typename InputIterator1, typename InputIterator2>
bool includes(InputIterator1 first1, InputIterator1 last1,
              InputIterator2 first2, InputIterator2 last2) {
    while (first1 != last1 && first2 != last2) {
        if (*first2 < *first1)
            return false;
        else if (*first1 < *first2)
            ++first1;
        else
            ++first1, ++first2;
    }

    return first2 == last2;
}

template<typename InputIterator1, typename InputIterator2, typename Compare>
bool includes(InputIterator1 first1, InputIterator1 last1,
              InputIterator2 first2, InputIterator2 last2,
              Compare comp) {
    while (first1 != last1 && first2 != last2) {
        if (comp(*first2, *first1))
            return false;
        else if (comp(*first1, *first2))
            ++first1;
        else
            ++first1, ++first2;
    }

    return first2 == last2;
}

// Max or min element
template<typename ForwardIterator>
ForwardIterator max_element(ForwardIterator first, ForwardIterator last) {
    if (first == last) return first;
    ForwardIterator result = first;
    while (++first != last)
        if (*result < *first)
            result = first;
    return result;
}

template<typename ForwardIterator, typename Compare>
ForwardIterator max_element(ForwardIterator first, ForwardIterator last, Compare comp) {
    if (first == last) return first;
    ForwardIterator result = first;
    while (++first != last)
        if (comp(*result, *first))
            result = first;
    return result;
}

template<typename ForwardIterator>
ForwardIterator min_element(ForwardIterator first, ForwardIterator last) {
    if (first == last) return first;
    ForwardIterator result = first;
    while (++first != last)
        if (*result > *first)
            result = first;
    return result;
}

template<typename ForwardIterator, typename Compare>
ForwardIterator min_element(ForwardIterator first, ForwardIterator last, Compare comp) {
    if (first == last) return first;
    ForwardIterator result = first;
    while (++first != last)
        if (comp(*result, *first))
            result = first;
    return result;
}

template<typename ForwardIterator>
stl::pair<ForwardIterator, ForwardIterator> minmax_element(ForwardIterator first, ForwardIterator last) {
    if (first == last) return { first, first };
    stl::pair<ForwardIterator, ForwardIterator> result (first, first);
    while (++first != last) {
        if (*result.first > *first)
            result.first = first;
        if (*result.second < *first)
            result.second = first;
    }
    return result;
}

template<typename ForwardIterator, typename Compare>
stl::pair<ForwardIterator, ForwardIterator> minmax_element(ForwardIterator first, ForwardIterator last, Compare comp) {
    if (first == last) return { first, first };
    stl::pair<ForwardIterator, ForwardIterator> result = (first, first);
    while (++first != last) {
        if (comp(*result.first, *first))
            result.first = first;
        if (comp(*first, *result.second))
            result.second = first;
    }
    return result;
}

}  // end of namespace stl

#endif /*  STL_IMPL_ALGORITHM_ */