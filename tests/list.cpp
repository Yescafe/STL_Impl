#include "../list.hpp"
#include <iostream>
#include <algorithm>

template<typename T, typename Alloc>
void print_list(stl::list<T, Alloc>& x) {
    std::cout << "  content:";
    for (auto itr = x.begin(); itr != x.end(); ++itr)
        std::cout << ' ' << *itr;
    std::cout << std::endl;
}

template<typename T, typename Alloc>
void print_list_info(stl::list<T, Alloc>& x) {
    std::cout << "  size=" << x.size() << std::endl;
    print_list(x);
}

int main()
{
    stl::list<int> ilist;
    std::cout << "ctor" << std::endl;
    print_list_info(ilist);

    for (int i = 0; i <= 5; ++i) {
        ilist.push_back(i);
    }
    std::cout << "loop 0..5 push_back" << std::endl;
    print_list_info(ilist);

#ifdef STL_IMPL_ALGORITHM_
    auto itr = stl::find(ilist.begin(), ilist.end(), 3);
    if (itr != 0) {
        ilist.insert(itr, 99);
    }
    std::cout << "insert at position of find 3" << std::endl;
    print_list_info(ilist);

    itr = stl::find(ilist.begin(), ilist.end(), 1);
    if (itr != 0) {
        std::cout << " after erase, erase position: " 
                  << *(ilist.erase(itr)) << std::endl;
    }
    std::cout << std::endl;
#endif /* STL_IMPL_ALGORITHM_ */

    ilist.erase(ilist.begin() + 2);
    std::cout << "ilist.erase(ilist.begin() + 2);" << std::endl;
    print_list_info(ilist);

    ilist.insert(ilist.begin() + 1, 3, 3);
    std::cout << "ilist.insert(ilist.begin() + 1, 3, 3);" << std::endl;
    print_list_info(ilist);

    ilist.remove(0);
    std::cout << "ilist.remove(3);" << std::endl;
    print_list_info(ilist);

    ilist.unique();   // 3 3 3 -> 3
    std::cout << "ilist.unique();" << std::endl;
    print_list_info(ilist);

    ilist.reverse();
    std::cout << "ilist.reverse();" << std::endl;
    print_list_info(ilist);

    ilist.reverse();
    std::cout << "ilist.reverse();" << std::endl;
    print_list_info(ilist);

    ilist.sort();
    std::cout << "ilist.sort();" << std::endl;
    print_list_info(ilist);

    stl::list<int> ilist2;
    for (int i = 3; i < 7; ++i) ilist2.push_back(i);

    std::cout << "ilist.size()=" << ilist.size() 
              << ", ilist2.size()=" << ilist2.size()
              << std::endl;
    ilist.merge(ilist2);
    std::cout << "ilist.merge(ilist2);" << std::endl;
    print_list_info(ilist);

    ilist.sort(std::greater{});
    std::cout << "ilist.sort(<functor>);" << std::endl;
    print_list_info(ilist);

    ilist.sort([](const auto& a, const auto& b) {
            if (a % 2 == 0 && b % 2 != 0)
                return true;
            return false;
        });
    std::cout << "ilist.sort(<lambda>);" << std::endl;
    print_list_info(ilist);

    ilist.clear();
    std::cout << "ilist.clear(ilist);" << std::endl;
    print_list_info(ilist);

    return 0;
}