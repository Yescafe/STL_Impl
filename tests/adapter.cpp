#include "../iterator.hpp"
#include "../functional.hpp"
#include "../vector.hpp"
#include "../deque.hpp"
#include "../algorithm.hpp"
#include <iostream>
#include <cassert>

template<typename Container>
std::ostream& print(Container& c) {
    // osteram_iterator
    stl::copy(c.begin(), c.end(), stl::ostream_iterator<typename Container::value_type>(std::cout, ", "));
    return std::endl(std::cout);
}

static int negate(int a) {
    return -a;
}

static int plus(int a, int b) {
    return a + b;
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

    struct not1_class : public stl::unary_function<int, bool> {
        bool operator()(int a) { return a % 2 == 0; }
    };
    struct not2_class : public stl::binary_function<int, int, bool> {
        bool operator()(int a, int b) { return a % 2 == 0 && b % 2 == 0; }
    };
    // auto not1_test = stl::not1(not1_class());
    // auto not2_test = stl::not2(not2_class());
    auto bind1st_test = stl::bind1st(stl::multiplies<int>(), 2);
    auto bind2nd_test = stl::bind2nd(stl::plus<int>(), 3);
    auto pointer_to_unary_function_test = stl::ptr_fun(::negate);
    auto pointer_to_binary_function_test = stl::ptr_fun(::plus);
    // assert(not1_test(3) == false);
    // assert(not2_test(2, 3) == true);
    assert(bind1st_test(4) == 8);
    assert(bind2nd_test(3) == 6);
    assert(pointer_to_unary_function_test(2) == -2);
    assert(pointer_to_binary_function_test(2, 3) == 5);

    return 0;
}