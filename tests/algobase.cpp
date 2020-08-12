#include "../algobase.hpp"
#include <iostream>
#include "../vector.hpp"
#include <vector>
#include <iterator>
#include <functional>
#include <algorithm>
#include <cassert>
#include "../numeric.hpp"
#include <string>

int main()
{
    std::vector<int> std_vec;
    stl::vector<int> stl_vec;
    for (int i = 0; i < 6; ++i) {
        std_vec.push_back(i+1);
        stl_vec.push_back(i+1);
    }

    // Equal
    std::cout << "assert equal(std_vec, stl_vec);" << std::endl;
    assert(equal(std::begin(std_vec), std::end(std_vec), stl_vec.begin()));
    std::cout << "assertion succeed." << std::endl;

    stl::iota(stl_vec.begin(), stl_vec.end(), 2);
    std::cout << "assert equal(std_vec, stl_vec, std::less<int>);" << std::endl;
    assert(equal(std::begin(std_vec), std::end(std_vec), stl_vec.begin(), std::less<int>()));
    std::cout << "assertion succeed." << std::endl << std::endl;
    stl::iota(stl_vec.begin(), stl_vec.end(), 1);

    // Fill
    std::cout << "Before filling value in std_vec: ";
    std::copy(std::begin(std_vec), std::end(std_vec), std::ostream_iterator<int>(std::cout, ", "));
    std::endl(std::cout);
    std::cout << "After filling: ";
    stl::fill(std::begin(std_vec), std::end(std_vec), 0);
    std::copy(std::begin(std_vec), std::end(std_vec), std::ostream_iterator<int>(std::cout, ", "));
    std::cout << std::endl << std::endl;
    stl::iota(std::begin(std_vec), std::end(std_vec), 1);

    // Iterator swap
    std::cout << "Before iterator swap: ";
    std::copy(std::begin(std_vec), std::end(std_vec), std::ostream_iterator<int>(std::cout, ", "));
    std::endl(std::cout);
    std::cout << "After iterator swap: ";
    for (auto itr1 = std::begin(std_vec), itr2 = std::end(std_vec) - 1;
         itr1 < itr2; ++itr1, --itr2) {
        stl::iter_swap(itr1, itr2);
    }
    std::copy(std::begin(std_vec), std::end(std_vec), std::ostream_iterator<int>(std::cout, ", "));
    std::cout << std::endl << std::endl;

    // Lexicographical compare
    std::string str1("hello");
    std::string str2("holle");
    std::cout << "\"hello\" < \"holle\": ";
    std::cout << std::boolalpha
              << stl::lexicographical_compare(std::begin(str1), std::end(str1), std::begin(str2), std::end(str2))
              << std::endl;
    std::cout << "\"hello\" > \"holle\": ";
    std::cout << std::boolalpha
              << stl::lexicographical_compare(std::begin(str1), std::end(str1), std::begin(str2), std::end(str2), std::greater<char>())
              << std::endl << std::endl;

    // Min and max
    int a = 1, b = 2;
    auto [m, M] = stl::min_max(a, b);
    std::cout << "min of 1 and 2: " << m << std::endl
              << "max of 1 and 2: " << M << std::endl << std::endl;

    // Mismatch
    stl::iota(std::begin(std_vec), std::end(std_vec), 1);
    stl::iota(stl_vec.begin(), stl_vec.end(), 1);
    std_vec.at(3) = 3;
    std::cout << "std_vec: ";
    std::copy(std::begin(std_vec), std::end(std_vec), std::ostream_iterator<int>(std::cout, ", "));
    std::endl(std::cout);
    std::cout << "stl_vec: ";
    for (auto itr = stl_vec.begin(); itr != stl_vec.end(); ++itr) {
        std::cout << *itr << ", ";
    }
    std::endl(std::cout);
    auto [pos1, pos2] = stl::mismatch(std::begin(std_vec), std::end(std_vec), stl_vec.begin());
    std::cout << "Mismatch between " << *pos1 << " and " << *pos2
              << std::endl << std::endl;

    // Swap
    std::cout << "Before swaping, a = " << a << ", b = " << b << std::endl;
    stl::swap(a, b);
    std::cout << "After swaping, a = " << a << ", b = " << b << std::endl;
}