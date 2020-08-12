#ifndef STL_IMPL_NUMERIC_
#define STL_IMPL_NUMERIC_

#include "iterator.hpp"
#include <functional>

namespace stl {
// Accumulate
template<typename InputIterator, typename T>
T accumulate(InputIterator first, InputIterator last, T init) {
    for ( ; first != last; ++first)
        init = init + *first;
    return init;
}

template<typename InputIterator, typename T, typename BinaryOperation>
T accumulate(InputIterator first, InputIterator last, T init, 
             BinaryOperation binary_op) {
    for ( ; first != last; ++first)
        init = binary_op(init, *first);
    return init;
}


// Adjacent difference
template<typename InputIterator, typename OutputIterator, typename T>
OutputIterator __adjacent_difference(InputIterator first, InputIterator last,
                                     OutputIterator result, T*) {
    T value = *first;
    while (++first != last) {
        T tmp = *first;
        *++result = tmp - value;
        value = tmp;
    }
    return ++result;
}

template<typename InputIterator, typename OutputIterator>
OutputIterator adjacent_difference(InputIterator first, InputIterator last,
                                   OutputIterator result) {
    if (first == last)
        return result;
    *result = *first;
    return __adjacent_difference(first, last, result, stl::value_type(first));
}

template<typename InputIterator, typename OutputIterator, typename T,
         typename BinaryOperation>
OutputIterator __adjacent_difference(InputIterator first, InputIterator last,
                                     OutputIterator result, T*, BinaryOperation binary_op) {
    T value = *first;
    while (++first != last) {
        T tmp = *first;
        *++result = binary_op(tmp, value);
        value = tmp;
    }
    return ++result;
}

template<typename InputIterator, typename OutputIterator, typename BinaryOperation>
OutputIterator adjacent_difference(InputIterator first, InputIterator last,
                                   OutputIterator result, BinaryOperation binary_op) {
    if (first == last)
        return result;
    *result = *first;
    return __adjacent_difference(first, last, result, stl::value_type(first), binary_op);
}

// Inner product
template<typename InputIterator1, typename InputIterator2, typename T>
T inner_product(InputIterator1 first1, InputIterator1 last1,
                InputIterator2 first2, T init) {
    for ( ; first1 != last1; ++first1, ++first2)
        init = init + (*first1 * *first2);
    return init;
}

template<typename InputIterator1, typename InputIterator2, typename T,
         typename BinaryOperation1, typename BinaryOperation2>
T inner_product(InputIterator1 first1, InputIterator1 last1,
                InputIterator2 first2, T init,
                BinaryOperation1 binary_op1, BinaryOperation2 binary_op2) {
    for ( ; first1 != last1; ++first1, ++first2)
        init = binary_op1(init, binary_op2(*first1, *first2));
    return init;
}

// Partial sum
template<typename InputIterator, typename OutputIterator, typename T>
OutputIterator __partial_sum(InputIterator first, InputIterator last,
                             OutputIterator result, T*) {
    T value = *first;
    while (++first != last) {
        value = *first + value;
        *++result = value;
    }
    return ++result;
}

template<typename InputIterator, typename OutputIterator>
OutputIterator partial_sum(InputIterator first, InputIterator last, OutputIterator result) {
    if (first == last) return result;
    *result = *first;
    return __partial_sum(first, last, result, stl::value_type(first));
}

template<typename InputIterator, typename OutputIterator, typename T,
         typename BinaryOperation>
OutputIterator __partial_sum(InputIterator first, InputIterator last,
                             OutputIterator result, T*, BinaryOperation binary_op) {
    T value = *first;
    while (++first != last) {
        value = binary_op(*first, value);
        *++result = value;
    }
    return ++result;
}

template<typename InputIterator, typename OutputIterator,
         typename BinaryOperation>
OutputIterator partial_sum(InputIterator first, InputIterator last, OutputIterator result,
                       BinaryOperation binary_op) {
    if (first == last) return result;
    *result = *first;
    return __partial_sum(first, last, result, stl::value_type(first), binary_op);
}

// Power
template<typename T, typename Integer, typename MonoidOperation = std::multiplies<T>>
T power(T x, Integer n, MonoidOperation op = std::multiplies<T>()) {
    if (n == 0)
        return 1; // TODO 修改为 stl::identity_element(op)
    else {
        while ((n & 1) == 0) {
            n >>= 1;
            x = op(x, x);
        }

        T result = x;
        n >>= 1;
        while (n != 0) {
            x = op(x, x);
            if ((n & 1) != 0)
                result = op(result, x);
            n >>= 1;
        }
        return result;
    }
}

// Iota
template<typename ForwardIterator, typename T>
void iota(ForwardIterator first, ForwardIterator last, T value) {
    while (first != last)
        *first++ = value++;
}

}  // end of namespace stl

#endif /* STL_IMPL_NUMERIC_ */