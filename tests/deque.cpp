#include "../deque.hpp"
#include <algorithm>
#include <iostream>
#include "../memory/alloc.hpp"

template<typename T, typename Alloc, std::size_t BufSiz>
void print_deque_info(stl::deque<T, Alloc, BufSiz>& rhs)
{
    const auto size =  rhs.size();
    std::cout << "  size=" << size << std::endl << "  content:";
    for (auto itr = rhs.begin(); itr != rhs.end(); ++itr)
        std::cout << " " << *itr;
    if (0 == size) std::cout << " (null)";
    std::cout << std::endl << "  addrs:";
    for (auto itr = rhs.begin(); itr != rhs.end(); ++itr)
        std::cout << " " << *itr << "(" << itr.cur << ")";
    if (0 == size) std::cout << " (null)";
    std::cout << std::endl << std::endl;
}


int main()
{
    stl::deque<int, stl::alloc, 32> ideq(20, 9);
    std::cout << "ctor:" << std::endl;
    print_deque_info(ideq);

    for (std::size_t i = 0; i < ideq.size(); ++i)
        ideq[i] = i;
    std::cout << "Update elements\' value by calling `operator[]()`:" << std::endl;
    print_deque_info(ideq);

    for (int cnt = 0; cnt < 3; ++cnt) {
        ideq.push_back(cnt);
    }
    std::cout << "Push 3 elements at back:" << std::endl;
    print_deque_info(ideq);

    ideq.push_back(3);
    std::cout << "Push another element at back:" << std::endl;
    print_deque_info(ideq);

    for (int cnt = 99; cnt > 96; --cnt) {
        ideq.push_front(cnt);
    }
    std::cout << "Push 3 elements at front:" << std::endl;
    print_deque_info(ideq);

#ifdef STL_IMPL_ALGORITHM_
    auto fnd = stl::find(ideq.begin(), ideq.end(), 99);
    std::cout << "Find 99 in `ideq`:" << std::endl;
    std::cout << "*itr = " << *itr << std::endl;
    std::cout << "*(itr.cur) = " << *(itr.cur) << std::endl;

    ideq.erase(itr);
    std::cout << "Erase found one:" << std::endl;
    print_deque_info(ideq);
#endif /* STL_IMPL_ALGORITHM_ */

    {
        auto pos1 = ideq.begin() + 2;
        auto pos2 = pos1 + 5;
        std::cerr << " pos1.cur = " << pos1.cur << ", pos2.cur = " << pos2.cur << std::endl;
        ideq.erase(pos1, pos2);
    }
    std::cout << "Erase a range of elements:" << std::endl;
    print_deque_info(ideq);

    ideq.clear();
    std::cout << "Clear:" << std::endl;
    print_deque_info(ideq); 

    return 0;
}