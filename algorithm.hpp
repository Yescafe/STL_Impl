#ifndef STL_IMPL_ALGORITHM_
#define STL_IMPL_ALGORITHM_

#include "algoheap.hpp"
#include "algobase.hpp"

#include "iterator.hpp"
#include "utility.hpp"
#include "numeric.hpp"

#include <iostream>
#include <iterator>

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
template<typename ForwardIterator1, typename ForwardIterator2,
         typename Distance1, typename Distance2>
ForwardIterator1 __search(ForwardIterator1 first1, ForwardIterator1 last1,
                        ForwardIterator2 first2, ForwardIterator2 last2,
                        Distance1*, Distance2*) {
    Distance1 d1 = distance(first1, last1);
    Distance2 d2 = distance(first2, last2);

    if (d1 < d2) return last1;
    
    ForwardIterator1 current1 = first1;
    ForwardIterator2 current2 = first2;

    while (current2 != last2) {
        if (*current1 == *current2) {
            ++current1, ++current2;
        } else {
            if (d1 == d2)
                return last1;
            else {
                current1 = ++first1;
                current2 = first2;
                --d1;
            }
        }
    }
    return first1;
}

template<typename ForwardIterator1, typename ForwardIterator2,
         typename Distance1, typename Distance2, typename BinaryOperation>
ForwardIterator1 __search(ForwardIterator1 first1, ForwardIterator1 last1,
                        ForwardIterator2 first2, ForwardIterator2 last2,
                        Distance1*, Distance2*, BinaryOperation binary_op) {
    Distance1 d1 = distance(first1, last1);
    Distance2 d2 = distance(first2, last2);

    if (d1 < d2) return last1;
    
    ForwardIterator1 current1 = first1;
    ForwardIterator2 current2 = first2;

    while (current2 != last2) {
        if (binary_op(*current1, *current2)) {
            ++current1, ++current2;
        } else {
            if (d1 == d2)
                return last1;
            else {
                current1 = ++first1;
                current2 = first2;
                --d1;
            }
        }
    }
    return first1;
}

template<typename ForwardIterator1, typename ForwardIterator2>
ForwardIterator1 search(ForwardIterator1 first1, ForwardIterator1 last1,
                        ForwardIterator2 first2, ForwardIterator2 last2) {
    return __search(first1, last1, first2, last2, distance_type(first1), distance_type(first2));
}

template<typename ForwardIterator1, typename ForwardIterator2, typename BinaryOperation>
ForwardIterator1 search(ForwardIterator1 first1, ForwardIterator1 last1,
                        ForwardIterator2 first2, ForwardIterator2 last2,
                        BinaryOperation binary_op) {
    return __search(first1, last1, first2, last2, distance_type(first1), distance_type(first2), binary_op);
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

// Search

template<typename ForwardIterator, typename Integer, typename T>
ForwardIterator search_n(ForwardIterator first, ForwardIterator last, Integer count, const T& value) {
    if (count <= 0)
        return first;
    else {
        first = find(first, last, value);
        while (first != last) {
            Integer n = count - 1;
            ForwardIterator i = first;
            ++i;
            while (i != last && n != 0 && *i == value) {
                ++i;
                --n;
            }
            if (n == 0)
                return first;
            else
                first = find(i, last, value);
        }
        return last;
    }
}

template<typename ForwardIterator, typename Integer, typename T, typename BinaryOperation>
ForwardIterator search_n(ForwardIterator first, ForwardIterator last, Integer count,
                         const T& value, BinaryOperation binary_op) {
    if (count <= 0)
        return first;
    else {
        while (first != last) {
            if (binary_op(*first, value)) break;
            ++first;
        }
        while (first != last) {
            Integer n = count - 1;
            ForwardIterator i = first;
            ++i;
            while (i != last && n != 0 && binary_op(*i, value)) {
                ++i;
                --n;
            }
            if (n == 0)
                return first;
            else {
                while (first != last) {
                    if (binary_op(*first, value)) break;
                    ++first;
                }
                first = i;
            }
        }
        return last;
    }
}

// Find

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
    return search(first1, last1, first2, last2);
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

// Merge
template<typename InputIterator1, typename InputIterator2, typename OutputIterator>
OutputIterator merge(InputIterator1 first1, InputIterator1 last1,
                     InputIterator2 first2, InputIterator2 last2,
                     OutputIterator result) {
    while (first1 != last1 && first2 != last2) {
        if (*first2 < *first1) {
            *result = *first2;
            ++first2;
        }
        else {
            *result = *first1;
            ++first1;
        }
        ++result;
    }
    return copy(first2, last2, copy(first1, last1, result));
}

template<typename InputIterator1, typename InputIterator2, typename OutputIterator,
         typename Compare>
OutputIterator merge(InputIterator1 first1, InputIterator1 last1,
                     InputIterator2 first2, InputIterator2 last2,
                     OutputIterator result, Compare comp) {
    while (first1 != last1 && first2 != last2) {
        if (comp(*first2, *first1)) {
            *result = *first2;
            ++first2;
        }
        else {
            *result = *first1;
            ++first1;
        }
        ++result;
    }
    return copy(first2, last2, copy(first1, last1, result));
}

// Partition
template<typename BidirectionalIterator, typename Predicate>
BidirectionalIterator partition(BidirectionalIterator first, BidirectionalIterator last,
                                Predicate pred) {
    while (true) {
        while (true) {
            if (first == last)
                return first;
            else if (pred(*first))
                ++first;
            else
                break;
        }
        --last;
        while (true) {
            if (first == last)
                return first;
            else if (!pred(*last))
                --last;
            else
                break;
        }
        iter_swap(first, last);
        ++first;
    }
}

// Remove
template<typename InputIterator, typename OutputIterator, typename T>
OutputIterator remove_copy(InputIterator first, InputIterator last,
                           OutputIterator result, const T& value) {
    for ( ; first != last; ++first) {
        if (*first != value) {
            *result = *first;
            ++result;
        }
    }
    return result;
}

template<typename InputIterator, typename OutputIterator, typename Predicate>
OutputIterator remove_copy_if(InputIterator first, InputIterator last,
                              OutputIterator result, Predicate pred) {
    for ( ; first != last; ++first) {
        if (!pred(*first)) {
            *result = *first;
            ++result;
        }
    }
    return result;
}

template<typename ForwardIterator, typename T>
ForwardIterator remove(ForwardIterator first, ForwardIterator last, const T& value) {
    first = find(first, last, value);
    ForwardIterator next = first;
    return first == last ? first : remove_copy(++next, last, first, value);
}

template<typename ForwardIterator, typename Predicate>
ForwardIterator remove_if(ForwardIterator first, ForwardIterator last, Predicate pred) {
    first = find(first, last, pred);
    ForwardIterator next = first;
    return first == last ? first : remove_copy(++next, last, first, pred);
}

// Replace
template<typename ForwardIterator, typename T>
void replace(ForwardIterator first, ForwardIterator last,
             const T& old_value, const T& new_value) {
    for ( ; first != last; ++first)
        if (*first == old_value)
            *first = new_value;
}

template<typename InputIterator, typename OutputIterator, typename T>
void replace_copy(InputIterator first, InputIterator last, OutputIterator result,
                  const T& old_value, const T& new_value) {
    for ( ; first != last; ++first, ++result)
        *result = *first == old_value ? new_value : *first;
    return result;
}

template<typename ForwardIterator, typename Predicate, typename T>
void replace_if(ForwardIterator first, ForwardIterator last,
                Predicate pred, const T& new_value) {
    for ( ; first != last; ++first)
        if (pred(*first))
            *first = new_value;
}

template<typename InputIterator, typename OutputIterator, typename Predicate, typename T>
void replace_copy_if(InputIterator first, InputIterator last, OutputIterator result,
                     Predicate pred, const T& new_value) {
    for ( ; first != last; ++first, ++result)
        *result = pred(*first) ? new_value : *first;
    return result;
}

// Reverse
template<typename BidirectionalIterator>
void __reverse(BidirectionalIterator first, BidirectionalIterator last, bidirectional_iterator_tag) {
    while (true) {
        if (first == last || first == --last)
            return ;
        else
            iter_swap(first++, last);
    }
}

template<typename RandomAccessIterator>
void __reverse(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag) {
    while (first < last) iter_swap(first++, --last);
}

template<typename BidirectionalIterator>
void reverse(BidirectionalIterator first, BidirectionalIterator last) {
    __reverse(first, last, iterator_category(first));
}

template<typename BidirectionalIterator, typename OutputIterator>
OutputIterator reverse_copy(BidirectionalIterator first, BidirectionalIterator last,
                            OutputIterator result) {
    while (first != last) {
        --last;
        *result = *last;
        ++result;
    }
    return result;
}

// Rotate
template<typename ForwardIterator, typename Distance>
void __rotate(ForwardIterator first, ForwardIterator middle, ForwardIterator last,
              Distance*, forward_iterator_tag) {
    for (ForwardIterator i = middle; ;) {
        iter_swap(first, i);
        ++first, ++i;
        if (first == middle) {
            if (i == last) return ;
            middle = i;
        } else if (i == last) {
            i = middle;
        }
    }
}

template<typename BidirectionalIterator, typename Distance>
void __rotate(BidirectionalIterator first, BidirectionalIterator middle,
              BidirectionalIterator last, Distance*, bidirectional_iterator_tag) {
    reverse(first, middle);
    reverse(middle, last);
    reverse(first, last);
}

template<typename RandomAccessIterator, typename Distance, typename T>
void __rotate_cycle(RandomAccessIterator first, RandomAccessIterator last,
                    RandomAccessIterator initial, Distance shift, T*) {
    T value = *initial;
    RandomAccessIterator ptr1 = initial;
    RandomAccessIterator ptr2 = ptr1 + shift;
    while (ptr2 != initial) {
        *ptr1 = *ptr2;
        ptr1 = ptr2;
        if (last - ptr2 > shift)
            ptr2 += shift;
        else
            ptr2 = first + (shift - (last - ptr2));
    }
    *ptr1 = value;
}

template<typename RandomAccessIterator, typename Distance>
void __rotate(RandomAccessIterator first, RandomAccessIterator middle,
              RandomAccessIterator last, Distance*, random_access_iterator_tag) {
    Distance n = ::stl::gcd(last - first, middle - first);
    while (n--) {
        __rotate_cycle(first, last, first + n, middle - first, value_type(first));
    }
}

template<typename ForwardIterator>
inline void rotate(ForwardIterator first, ForwardIterator middle, ForwardIterator last) {
    if (first == middle || middle == last) return ;
    __rotate(first, middle, last, distance_type(first), iterator_category(first));
}

template<typename ForwardIterator, typename OutputIterator>
OutputIterator rotate_copy(ForwardIterator first, ForwardIterator middle,
                           ForwardIterator last, OutputIterator result) {
    return ::stl::copy(first, middle, ::stl::copy(middle, last, result));
}

// Swap Ranges
template<typename ForwardIterator1, typename ForwardIterator2>
ForwardIterator1 swap_ranges(ForwardIterator1 first1, ForwardIterator1 last1,
                             ForwardIterator2 first2) {
    for ( ; first1 != last1; ++first1, ++first2)
        iter_swap(first1, first2);
    return first2;
}

// Transform
template<typename InputIterator, typename OutputIterator, typename UnaryOperation>
OutputIterator transform(InputIterator first, InputIterator last,
                         OutputIterator result, UnaryOperation op) {
    for ( ; first != last; ++first, ++result)
        *result = op(*first);
    return result;
}

template<typename InputIterator1, typename InputIterator2, 
         typename OutputIterator, typename BinaryOperation>
OutputIterator transform(InputIterator1 first1, InputIterator1 last1,
                         InputIterator2 first2, OutputIterator result,
                         BinaryOperation binary_op) {
    for ( ; first1 != last1; ++first1, ++first2, ++result)
        *result = binary_op(*first1, *first2);
    return result;
}

// Unique
template<typename InputIterator, typename ForwardIterator>
ForwardIterator __unique_copy(InputIterator first, InputIterator last,
                              ForwardIterator result, forward_iterator_tag) {
    *result = *first;
    while (++first != last)
        if (*result != *first)
            *++result = *first;
    return ++result;
}

template<typename InputIterator, typename OutputIterator, typename T>
OutputIterator __unique_copy(InputIterator first, InputIterator last,
                             OutputIterator result, T*) {
    T value = *first;
    *result = value;
    while (++first != last) {
        if (value != *first) {
            value = *first;
            *++result = value;
        }
    }
    return ++result;
}

template<typename InputIterator, typename OutputIterator>
inline OutputIterator __unique_copy(InputIterator first, InputIterator last,
                                    OutputIterator result, output_iterator_tag) {
    return __unique_copy(first, last, result, value_type(first));
}

template<typename InputIterator, typename OutputIterator>
inline OutputIterator unique_copy(InputIterator first, InputIterator last,
                                  OutputIterator result) {
    if (first == last) return result;
    return __unique_copy(first, last, result, iterator_category(result));
}

template<typename ForwardIterator>
ForwardIterator unique(ForwardIterator first, ForwardIterator last) {
    first = adjacent_find(first, last);
    return unique_copy(first, last, first);
}

}  // end of namespace stl

#endif /*  STL_IMPL_ALGORITHM_ */