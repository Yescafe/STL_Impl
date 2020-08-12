#include "../numeric.hpp"
#include <iostream>
#include <functional>
#include <numeric>
#include <vector>
#include <algorithm>
#include <iterator>
#include "../vector.hpp"

int main()
{
    std::vector<int> std_vec(6);
    stl::vector<int> stl_vec;
    for (int i = 0; i < 6; ++i) {
        stl_vec.push_back(i+1);
    }

    // Iota
    std::cout << "stl::iota(std_vec, 1);" << std::endl;
    stl::iota(std::begin(std_vec), std::end(std_vec), 1);
    std::copy(std::begin(std_vec), std::end(std_vec), std::ostream_iterator<int>(std::cout, ", "));
    std::cout << std::endl << std::endl;

    // Accumulate
    std::cout << "accumulate(std_vec, 0);" << std::endl;
    std::cout << stl::accumulate(std::begin(std_vec), std::end(std_vec), 0) << std::endl;

    std::cout << "accumulate(stl_vec, 0);" << std::endl;
    std::cout << stl::accumulate(stl_vec.begin(), stl_vec.end(), 0) << std::endl;

    std::cout << "accmulate(std_vec, 0, std::multiplies<int>);" << std::endl;
    std::cout << stl::accumulate(std::begin(std_vec), std::end(std_vec), 1, std::multiplies<int>()) << std::endl;

    std::cout << "accmulate(stl_vec, 0, std::multiplies<int>);" << std::endl;
    std::cout << stl::accumulate(stl_vec.begin(), stl_vec.end(), 1, std::multiplies<int>()) << std::endl << std::endl;

    // Adjacent difference and partial sum
    std::vector<int> result_set;
    std::cout << "adjacent_difference(std_vec, result_set);" << std::endl;
    stl::adjacent_difference(std::begin(std_vec), std::end(std_vec), std::back_inserter(result_set));
    std::copy(std::begin(result_set), std::end(result_set), std::ostream_iterator<int>(std::cout, ", "));
    std::cout << std::endl;
    result_set.clear();

    std::cout << "adjacent_difference(stl_vec, result_set);" << std::endl;
    stl::adjacent_difference(stl_vec.begin(), stl_vec.end(), std::back_inserter(result_set));
    std::copy(std::begin(result_set), std::end(result_set), std::ostream_iterator<int>(std::cout, ", "));
    std::cout << std::endl;

    std::cout << "partial_sum(result_set, stl_vec);" << std::endl;
    stl::partial_sum(std::begin(result_set), std::end(result_set), stl_vec.begin());
    for (auto itr = stl_vec.begin(); itr != stl_vec.end(); ++itr) {
        std::cout << *itr << ", ";
    }
    std::endl(std::cout);
    result_set.clear();

    std::cout << "adjacent_difference(std_vec, result_set, std::multiplies<int>);" << std::endl;
    stl::adjacent_difference(std::begin(std_vec), std::end(std_vec), std::back_inserter(result_set), std::multiplies<int>());
    std::copy(std::begin(result_set), std::end(result_set), std::ostream_iterator<int>(std::cout, ", "));
    std::cout << std::endl;
    result_set.clear();

    std::cout << "adjacent_difference(stl_vec, result_set, std::multiplies<int>);" << std::endl;
    stl::adjacent_difference(stl_vec.begin(), stl_vec.end(), std::back_inserter(result_set), std::multiplies<int>());
    std::copy(std::begin(result_set), std::end(result_set), std::ostream_iterator<int>(std::cout, ", "));
    std::cout << std::endl;

    std::cout << "partial_sum(result_set, stl_vec, std::divides<int>);" << std::endl;
    stl::partial_sum(std::begin(result_set), std::end(result_set), stl_vec.begin(), std::divides<int>());
    for (auto itr = stl_vec.begin(); itr != stl_vec.end(); ++itr) {
        std::cout << *itr << ", ";
    }
    std::cout << std::endl << std::endl;
    result_set.clear();

    // Inner product
    std::cout << "inner_product(std_vec, stl_vec);" << std::endl;
    std::cout << stl::inner_product(std::begin(std_vec), std::end(std_vec), stl_vec.begin(), 0) << std::endl;
    
    std::cout << "inner_product(std_vec, stl_vec, std::multiplies<int>, std::plus<int>);" << std::endl;
    std::cout << stl::inner_product(std::begin(std_vec), std::end(std_vec), stl_vec.begin(), 1, std::multiplies<int>(), std::plus<int>())
              << std::endl << std::endl;


    // Power
    std::cout << "power(2, 16);" << std::endl;
    std::cout << stl::power(2, 16) << std::endl;

    std::cout << "power(2, 0);" << std::endl;
    std::cout << stl::power(2, 0) << std::endl;

    std::cout << "power(10, 7);" << std::endl;
    std::cout << stl::power(10, 7) << std::endl;
}