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
    
}