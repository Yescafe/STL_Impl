#ifndef STL_IMPL_ALGOHEAP_
#define STL_IMPL_ALGOHEAP_

#include "iterator.hpp"
#include "__type_traits.hpp"

namespace stl
{
using namespace __traits;

template<typename RandomAccessIterator, typename Distance, typename T>
inline void __push_heap(RandomAccessIterator first, Distance holeIndex, Distance topIndex, T value)
{
    Distance parent = (holeIndex - 1) / 2;  // parent node index
    // Lightly update head by travel upstairs
    // Compare value with hole's parent repeatedly, to determine the last hole index
    while (holeIndex > topIndex && *(first + parent) < value) {
        // Not reach the top and parent value is less than value
        // STL heap is a max-heap
        *(first + holeIndex) = *(first + parent);  // let hole value be parent value
        holeIndex = parent;    // adjust hole index into parent index
        parent = (holeIndex - 1) / 2;
    }
    *(first + holeIndex) = value;   // set up value at new hole
}

template<typename RandomAccessIterator, typename Distance, typename T>
inline void __push_heap_aux(RandomAccessIterator first, RandomAccessIterator last, Distance*, T*)
{
    stl::__push_heap(first, Distance((last - first) - 1), Distance(0), T(*(last - 1)));
}

template<typename RandomAccessIterator>
inline void push_heap(RandomAccessIterator first, RandomAccessIterator last)
{
    stl::__push_heap_aux(first, last, distance_type(first), value_type(first));
}


template<typename RandomAccessIterator, typename Distance, typename T>
void __adjust_heap(RandomAccessIterator first, Distance holeIndex, Distance len, T value)
{
    Distance topIndex = holeIndex;
    Distance secondChild = 2 * holeIndex + 2;  // right child index
    while (secondChild  < len) {
        if (*(first + secondChild) < *(first + (secondChild - 1)))  // compare right child with left child
            --secondChild;       // switch to the left one
        *(first + holeIndex) = *(first + secondChild);   // move child into hole
        holeIndex = secondChild;   // update hole index to child index
        secondChild = 2 * (secondChild + 1);  // get the next right child index
    }
    if (secondChild == len) {     // the last position's parent only has left child
        *(first + holeIndex) = *(first + (secondChild - 1));   // update child into left child index
        holeIndex = secondChild - 1;   // set hole index to the last child
    }
    stl::__push_heap(first, holeIndex, topIndex, value);
}

template<typename RandomAccessIterator, typename T, typename Distance>
inline void __pop_heap(RandomAccessIterator first, RandomAccessIterator last, RandomAccessIterator result, T value, Distance*)
{
    *result = *first;
    stl::__adjust_heap(first, Distance(0), Distance(last - first), value);
}

template<typename RandomAccessIterator, typename T>
inline void __pop_heap_aux(RandomAccessIterator first, RandomAccessIterator last, T*)
{
    stl::__pop_heap(first, last - 1, last - 1, T(*(last - 1)), distance_type(first));
}

template<typename RandomAccessIterator>
inline void pop_heap(RandomAccessIterator first, RandomAccessIterator last)
{
    stl::__pop_heap_aux(first, last, value_type(first));
}


template<typename RandomAccessIterator>
inline void sort_heap(RandomAccessIterator first, RandomAccessIterator last)
{
    while (last - first > 1)
        stl::pop_heap(first, last--);
}


template<typename RandomAccessIterator, typename T, typename Distance>
void __make_heap(RandomAccessIterator first, RandomAccessIterator last, T*, Distance*)
{
    if (last - first < 2) return ;
    Distance len = last - first;
    Distance parent = (len - 2) / 2;

    while (true) {
        stl::__adjust_heap(first, parent, len, T(*(first + parent)));
        if (parent == 0) return ;
        --parent;
    }
}

template<typename RandomAccessIterator>
inline void make_heap(RandomAccessIterator first, RandomAccessIterator last)
{
    stl::__make_heap(first, last, value_type(first), distance_type(first));
}


template<typename RandomAccessIterator, typename Distance, typename T, typename Compare>
inline void __push_heap(RandomAccessIterator first, Distance holeIndex, Distance topIndex, T value, Compare comp)
{
    Distance parent = (holeIndex - 1) / 2;
    while (holeIndex > topIndex && comp(*(first + parent), value)) {
        *(first + holeIndex) = *(first + parent);
        holeIndex = parent;
        parent = (holeIndex - 1) / 2;
    }
    *(first + holeIndex) = value;
}

template<typename RandomAccessIterator, typename Compare, typename Distance, typename T>
inline void __push_heap_aux(RandomAccessIterator first, RandomAccessIterator last, Compare comp, Distance*, T*)
{
    stl::__push_heap(first, Distance((last - first) - 1), Distance(0), T(*(last - 1)), comp);
}

template<typename RandomAccessIterator, typename Compare>
inline void push_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
{
    stl::__push_heap_aux(first, last, comp, distance_type(first), value_type(first));
}


template<typename RandomAccessIterator, typename Distance, typename T, typename Compare>
void __adjust_heap(RandomAccessIterator first, Distance holeIndex, Distance len, T value, Compare comp)
{
    Distance topIndex = holeIndex;
    Distance secondChild = 2 * holeIndex + 2;
    while (secondChild  < len) {
        if (comp(*(first + secondChild), *(first + (secondChild - 1))))
            --secondChild;
        *(first + holeIndex) = *(first + secondChild);
        holeIndex = secondChild;
        secondChild = 2 * (secondChild + 1);
    }
    if (secondChild == len) {
        *(first + holeIndex) = *(first + (secondChild - 1));
        holeIndex = secondChild - 1;
    }
    stl::__push_heap(first, holeIndex, topIndex, value);
}

template<typename RandomAccessIterator, typename T, typename Compare, typename Distance>
inline void __pop_heap(RandomAccessIterator first, RandomAccessIterator last, RandomAccessIterator result, T value, Compare comp, Distance*)
{
    *result = *first;
    stl::__adjust_heap(first, Distance(0), Distance(last - first), value, comp);
}

template<typename RandomAccessIterator, typename Compare, typename T>
inline void __pop_heap_aux(RandomAccessIterator first, RandomAccessIterator last, Compare comp, T*)
{
    stl::__pop_heap(first, last - 1, last - 1, T(*(last - 1)), comp, distance_type(first));
}

template<typename RandomAccessIterator, typename Compare>
inline void pop_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
{
    stl::__pop_heap_aux(first, last, comp, value_type(first));
}


template<typename RandomAccessIterator, typename Compare>
inline void sort_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
{
    while (last - first > 1)
        stl::pop_heap(first, last--, comp);
}


template<typename RandomAccessIterator, typename Compare, typename T, typename Distance>
void __make_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp, T*, Distance*)
{
    if (last - first < 2) return ;
    Distance len = last - first;
    Distance parent = (len - 2) / 2;

    while (true) {
        stl::__adjust_heap(first, parent, len, T(*(first + parent)), comp);
        if (parent == 0) return ;
        --parent;
    }
}

template<typename RandomAccessIterator, typename Compare>
inline void make_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
{
    stl::__make_heap(first, last, comp, value_type(first), distance_type(first));
}


}  // end of namespace stl

#endif /* STL_IMPL_ALGOHEAP_ */