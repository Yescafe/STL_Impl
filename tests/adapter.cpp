#include "../iterator.hpp"
#include "../functional.hpp"
#include "../vector.hpp"
#include "../deque.hpp"
#include "../algorithm.hpp"
#include <iostream>

template<typename Container>
std::ostream& print(Container& c) {
    // osteram_iterator
    stl::copy(c.begin(), c.end(), stl::ostream_iterator<typename Container::value_type>(std::cout, ", "));
    return std::endl(std::cout);
}

int main()
{
    stl::vector<int> ivec;
    stl::deque<int> ideq;
    for (int i = 0; i < 5; ++i) {
        ivec.push_back(i + 1);
    }
    std::cout << "ivec: ";
    ::print(ivec);
    std::cout << "ideq: ";
    ::print(ideq);
    std::cout << "copy(ivec.begin(), ivec.end(), back_inserter(ideq));" << std::endl;
    stl::copy(ivec.begin(), ivec.end(), stl::back_inserter(ideq));
    std::cout << "ideq: ";
    ::print(ideq);
    std::cout << "copy(ivec.begin(), ivec.end(), front_inserter(ideq));" << std::endl;
    stl::copy(ivec.begin(), ivec.end(), stl::front_inserter(ideq));
    std::cout << "ideq: ";
    ::print(ideq);
    std::cout << "copy(ivec.begin(), ivec.end(), inserter(ideq, ideq.begin()));" << std::endl;
    stl::copy(ivec.begin(), ivec.end(), stl::inserter(ideq, ideq.begin() + 1));
    std::cout << "ideq: ";
    ::print(ideq);
    std::cout << "copy(ivec.begin(), ivec.end(), reverse_iterator(ideq.end() - 1));" << std::endl;
    stl::copy(ivec.begin(), ivec.end(), stl::reverse_iterator(ideq.end()));
    std::cout << "ideq: ";
    ::print(ideq);

    return 0;
}