#include "../algorithm.hpp"
#include <iostream>
#include "../vector.hpp"
#include <iterator>

template<typename Iterator>
void print_sequence(Iterator first, Iterator last)
{
    std::cout << "{";
    for (auto itr = first; itr != last; ++itr) {
        std::cout << ", " << *itr;
    }
    std::cout << "}" << std::endl;
}

int main()
{
    int ia[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    stl::vector<int> ivec;
    for (auto c: ia) {
        ivec.push_back(c);
    }

    std::cout << "Before make_heap, ia = ";
    print_sequence(std::begin(ia), std::end(ia));
    stl::make_heap(std::begin(ia), std::end(ia));
    std::cout << "After make_heap, ia = ";
    print_sequence(std::begin(ia), std::end(ia));

    std::cout << "Before make_heap, ivec = ";
    print_sequence(ivec.begin(), ivec.end());
    stl::make_heap(ivec.begin(), ivec.end());
    std::cout << "After make_heap, ivec = ";
    print_sequence(ivec.begin(), ivec.end());
}