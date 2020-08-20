#define _TESTS_ALGORITHM
#include "../algorithm.hpp"
#include <iostream>
#include "../vector.hpp"
#include <algorithm>
#include <iterator>
#include <functional>
#include "../list.hpp"
#include <vector>

#include "algobase.cpp"
#include "algoheap.cpp"

template<typename Container>
void print(Container& c) {
    // Foreach
    stl::for_each(c.begin(), c.end(), [](int a) { std::cout << a << ", "; });
    std::endl(std::cout);
}

int main()
{
    // Tests for algoheap
    tests_algoheap();
    std::endl(std::cout);

    // Tests for algobase
    tests_algobase();
    std::endl(std::cout);

    // Adjacent find
    stl::vector<int> ivec;
    for (int i = 0; i < 6; ++i) {
        ivec.push_back(i + 1);
    }
    ivec[4] = 4;
    std::cout << "ivec: ";
    ::print(ivec);

    {
        std::cout << "adjacent_find(ivec);" << std::endl;
        auto fnd = ivec.begin();
        if ((fnd = stl::adjacent_find(ivec.begin(), ivec.end())) != ivec.end()) {
            std::cout << "found the " << *fnd;
        } else {
            std::cout << "not found";
        }
        std::endl(std::cout);
    }
    {
        std::cout << "adjacent_find(ivec, <lambda>);" << std::endl;
        auto fnd = ivec.begin();
        if ((fnd = stl::adjacent_find(ivec.begin(), ivec.end(), [](int a, int b) { return a > b; })) != ivec.end()) {
            std::cout << "found the " << *fnd;
        } else {
            std::cout << "not found";
        }
        std::endl(std::cout);
    }
    std::endl(std::cout);

    // Count
    std::cout << "count(ivec, 4);" << std::endl;
    std::cout << stl::count(ivec.begin(), ivec.end(), 4) << std::endl;
    std::cout << "count_if(ivec, <lambda(int)>);" << std::endl;
    std::cout << stl::count_if(ivec.begin(), ivec.end(), [](int a) { return a > 3; })
              << std::endl << std::endl;
    
    // Find
    {
        std::cout << "find(ivec, 2);" << std::endl;
        auto fnd = ivec.begin();
        if ((fnd = stl::find(ivec.begin(), ivec.end(), 2)) != ivec.end()) {
            std::cout << *fnd;
        } else {
            std::cout << "not found";
        }
        std::endl(std::cout);
    }
    {
        std::cout << "find_if(ivec, <lambda<int>>);" << std::endl;
        auto fnd = ivec.begin();
        if ((fnd = stl::find_if(ivec.begin(), ivec.end(), [](int a) { return a > 6; })) != ivec.end()) {
            std::cout << *fnd;
        } else {
            std::cout << "not found";
        }
        std::cout << std::endl << std::endl;
    }
    {
        stl::vector<int> subvec;
        subvec.push_back(4);
        subvec.push_back(4);
        std::cout << "subvec: ";
        ::print(subvec);
        std::cout << "find_end(ivec, subvec);" << std::endl;
        auto fnd = stl::find_end(ivec.begin(), ivec.end(), subvec.begin(), subvec.end());
        if (fnd != ivec.end()) {
            std::cout << *fnd;
        } else {
            std::cout << "#not found";
        }
        std::cout << std::endl << std::endl;
    }
    {
        stl::vector<int> targets;
        targets.push_back(4);
        targets.push_back(3);
        std::cout << "targets: ";
        ::print(targets);
        std::cout << "find_first_of(ivec, targets);" << std::endl;
        auto fnd = stl::find_first_of(ivec.begin(), ivec.end(), targets.begin(), targets.end());
        if (fnd != ivec.end()) {
            std::cout << *fnd;
        } else {
            std::cout << "not found";
        }
        std::cout << std::endl << std::endl;
    }

    // Generate
    {
        std::vector<int> ivec;

        std::cout << "generate_n((std::vector<int>)ivec, 7, <lambda>);" << std::endl;
        stl::generate_n(std::back_inserter(ivec), 7, []() { return 0; });
        ::print(ivec);
        
        std::cout << "generate((...)ivec, <lambda>);" << std::endl;
        stl::generate(std::begin(ivec), std::end(ivec), [i = 0]() mutable { return i++; });
        ::print(ivec);
        std::endl(std::cout);
    }

    // Includes
    {
        std::cout << "ivec: ";
        ::print(ivec);
        stl::vector<int> sub_discontiguous_vec;
        sub_discontiguous_vec.push_back(2);
        sub_discontiguous_vec.push_back(4);
        std::cout << "sub_discontiguous_vec: ";
        ::print(sub_discontiguous_vec);
        std::cout << "includes(ivec, sub_discontiguous_vec);" << std::endl;
        std::cout << std::boolalpha << stl::includes(ivec.begin(), ivec.end(), sub_discontiguous_vec.begin(), sub_discontiguous_vec.end())
                  << std::endl;

        stl::vector<int> non_sub_discontiguous_vec;
        non_sub_discontiguous_vec.push_back(2);
        non_sub_discontiguous_vec.push_back(1);
        std::cout << "non_sub_discontiguous_vec: ";
        ::print(non_sub_discontiguous_vec);
        std::cout << "includes(ivec, non_sub_discontiguous_vec);" << std::endl;
        std::cout << std::boolalpha << stl::includes(ivec.begin(), ivec.end(), non_sub_discontiguous_vec.begin(), non_sub_discontiguous_vec.end())
                  << std::endl << std::endl;
    }

    // Max or min element
    auto [minIter, maxIter] = stl::minmax_element(ivec.begin(), ivec.end());
    std::cout << "The min element of ivec: " << *minIter << std::endl;
    std::cout << "The max element of ivec: " << *maxIter << std::endl << std::endl;
    
    // Merge
    {
        stl::vector<int> ivec1, ivec2;
        ivec1.push_back(1);
        ivec1.push_back(2);
        ivec2.push_back(3);
        ivec1.push_back(4);
        ivec2.push_back(5);
        ivec2.push_back(6);
        std::cout << "ivec1: ";
        ::print(ivec1);
        std::cout << std::endl << "ivec2: ";
        ::print(ivec2);
        std::cout << std::endl << "merge: ";
        stl::vector<int> merged(ivec1.size() + ivec2.size());
        ::print(merged);
        stl::copy(merged.begin(), merged.end(), std::ostream_iterator<int>(std::cout, ", "));
        std::cout << std::endl << std::endl;
    }

    // Partition
    std::cout << "ivec: ";
    ::print(ivec);
    std::cout << "partition(ivec, <lambda>);" << std::endl;
    stl::partition(ivec.begin(), ivec.end(), [](int a) -> bool { return a & 1; });
    std::cout << "ivec: ";
    ::print(ivec);

    // Remove
    std::cout << "remove(ivec, 4);" << std::endl;
    ivec.erase(stl::remove(ivec.begin(), ivec.end(), 4), ivec.end());
    std::cout << "ivec: ";
    ::print(ivec);

    // Replace
    std::cout << "replace(ivec, <lambda>);" << std::endl;
    stl::replace_if(ivec.begin(), ivec.end(), [](int a) { return a & 1; }, -1);
    std::cout << "ivec: ";
    ::print(ivec);

    // Reverse
    std::cout << "reverse(ivec);" << std::endl;
    stl::reverse(ivec.begin(), ivec.end());
    std::cout << "ivec: ";
    ::print(ivec);
    std::endl(std::cout);

    // Rotate
    {
        stl::vector<int> ivec;
        for (int i = 0; i < 8; ++i) {
            ivec.push_back(i + 1);
        }
        std::cout << "Before rotate:\nivec: ";
        ::print(ivec);
        auto first = ivec.begin();
        auto middle = ivec.begin() + 3;
        auto last = ivec.end();
        stl::rotate(first, middle, last);
        std::cout << "After rotate 3:\nivec: ";
        ::print(ivec);
    }
    {
        stl::vector<int> ivec;
        for (int i = 0; i < 8; ++i) {
            ivec.push_back(i + 1);
        }
        std::cout << "Before rotate:\nivec: ";
        ::print(ivec);
        auto first = ivec.begin();
        auto middle = ivec.begin() + 4;
        auto last = ivec.end();
        stl::rotate(first, middle, last);
        std::cout << "After rotate 4:\nivec: ";
        ::print(ivec);
    }
    {
        stl::vector<int> ivec;
        for (int i = 0; i < 8; ++i) {
            ivec.push_back(i + 1);
        }
        std::cout << "Before rotate:\nivec: ";
        ::print(ivec);
        auto first = ivec.begin();
        auto middle = ivec.begin() + 6;
        auto last = ivec.end();
        stl::rotate(first, middle, last);
        std::cout << "After rotate 6:\nivec: ";
        ::print(ivec);
        std::endl(std::cout);
    }

    // Search
    {
        stl::vector<int> ivec;
        for (int i = 0; i < 6; ++i) {
            ivec.push_back(i + 1);
        }
        stl::vector<int> svec;
        for (int i = 0; i < 3; ++i) {
            svec.push_back(i + 3);
        }
        std::cout << "ivec: ";
        ::print(ivec);
        std::cout << "svec: ";
        ::print(svec);
        std::cout << "search(ivec, svec);" << std::endl;
        auto fnd = ivec.begin();
        if ((fnd = stl::search(ivec.begin(), ivec.end(), svec.begin(), svec.end())) != ivec.end())
            std::cout << *fnd << std::endl;
        else
            std::cout << "not found" << std::endl;
        
        std::cout << "search_n(ivec, 3, 3);" << std::endl;
        if ((fnd = stl::search_n(ivec.begin(), ivec.end(), 3, 3)) != ivec.end())
            std::cout << *fnd << std::endl;
        else
            std::cout << "not found" << std::endl;

        std::cout << "search_n(ivec, 3, 3, <lambda>);" << std::endl;
        if ((fnd = stl::search_n(ivec.begin(), ivec.end(), 3, 3, [](int a, int b) { return a > b; })) != ivec.end())
            std::cout << *fnd << std::endl;
        else
            std::cout << "not found" << std::endl;
    }

    // Swap Ranges
    {
        stl::vector<int> ivec;
        for (int i = 0; i < 6; ++i) {
            ivec.push_back(i);
        }
        stl::vector<int> svec;
        for (int i = 0; i < 3; ++i) {
            svec.push_back(i + 1);
        }
        std::cout << "Before swap: " << std::endl;
        std::cout << "ivec: ";
        ::print(ivec);
        std::cout << "svec: ";
        ::print(svec);
        stl::swap_ranges(ivec.begin(), ivec.begin() + 3, svec.begin());
        std::cout << "After swap: " << std::endl;
        std::cout << "ivec: ";
        ::print(ivec);
        std::cout << "svec: ";
        ::print(svec);
        std::endl(std::cout);
    }

    // Transform
    {
        stl::vector<int> ivec;
        for (int i = 0; i < 6; ++i) {
            ivec.push_back(i);
        }
        std::cout << "ivec: ";
        ::print(ivec);
        std::cout << "transform(ivec, <lambda>);" << std::endl;
        stl::transform(ivec.begin(), ivec.end(), ivec.begin(), [](int a) { return a + 2; });
        std::cout << "ivec: ";
        ::print(ivec);
        std::endl(std::cout);
    }
    
    // Unique
    {
        int arr[] = {1, 2, 2, 3, 3, 4, 4, 4, 5};
        stl::vector<int> ivec(arr, arr + sizeof(arr) / sizeof(int));
        std::cout << "arr: ";
        std::copy(std::begin(arr), std::end(arr), std::ostream_iterator<int>(std::cout, ", "));
        std::endl(std::cout);
        std::cout << "ivec: ";
        ::print(ivec);
        std::cout << "unique(ivec);" << std::endl;
        ivec.erase(stl::unique(ivec.begin(), ivec.end()), ivec.end());
        std::cout << "ivec: ";
        ::print(ivec);
        std::endl(std::cout);
    }

    // Lower bound
    // Upper bound
    // Binary search
    {
        int arr[] = {1, 1, 2, 4, 5, 6, 6, 7, 7};
        stl::vector<int> ivec(arr, arr + sizeof(arr) / sizeof(int));
        std::cout << "ivec: ";
        ::print(ivec);
        std::cout << "binary_search(ivec, 6);" << std::endl;
        if (stl::binary_search(ivec.begin(), ivec.end(), 6)) {
            std::cout << "found";
        } else {
            std::cout << "not found";
        }
        std::endl(std::cout);
        
        std::cout << "binary_search(ivec, 10);" << std::endl;
        if (stl::binary_search(ivec.begin(), ivec.end(), 10)) {
            std::cout << "found";
        } else {
            std::cout << "not found";
        }
        std::endl(std::cout);

        std::cout << "binary_search(ivec, 3);" << std::endl;
        if (stl::binary_search(ivec.begin(), ivec.end(), 3)) {
            std::cout << "found";
        } else {
            std::cout << "not found";
        }
        std::endl(std::cout);

        std::cout << "binary_search(ivec, -1);" << std::endl;
        if (stl::binary_search(ivec.begin(), ivec.end(), -1)) {
            std::cout << "found";
        } else {
            std::cout << "not found";
        }
        std::cout << std::endl << std::endl;
    }

    // Permutation
    {
        int arr[] = {1, 2, 3};
        const std::size_t size = sizeof(arr) / sizeof(arr[0]);
        std::cout << "Next permutation sequence:" << std::endl;
        stl::copy(arr, arr + size, std::ostream_iterator<int>(std::cout, ", "));
        std::endl(std::cout);
        while (stl::next_permutation(arr, arr + size)) {
            stl::copy(arr, arr + size, std::ostream_iterator<int>(std::cout, ", "));
            std::endl(std::cout);
        }
    }
    {
        int arr[] = {3, 2, 1};
        const std::size_t size = sizeof(arr) / sizeof(arr[0]);
        std::cout << "Previous permutation sequence:" << std::endl;
        stl::copy(arr, arr + size, std::ostream_iterator<int>(std::cout, ", "));
        std::endl(std::cout);
        while (stl::prev_permutation(arr, arr + size)) {
            stl::copy(arr, arr + size, std::ostream_iterator<int>(std::cout, ", "));
            std::endl(std::cout);
        }
        std::endl(std::cout);
    }
}
