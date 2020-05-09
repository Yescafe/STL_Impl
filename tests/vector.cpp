#include "../vector.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
#include "../memory/utils.hpp"

template<typename T>
static void print_vec(const stl::vector<T>& vec) {
    std::cout << "  content: ";
    for (auto itr = vec.begin(); itr != vec.end(); ++itr)
        std::cout << *itr << ' ';
    std::cout << std::endl;
}

template<typename T>
static void print_vec_info(const stl::vector<T>& vec) {
    std::cout << "  size=" << vec.size() << std::endl;
    std::cout << "  capacity=" << vec.capacity() << std::endl;
    print_vec(vec);
}

int main()
{
    stl::vector<int> iv(2, 9);
    std::cout << "ctor:\n";
    print_vec_info(iv);

    iv.push_back(1);
    std::cout << "iv.push_back(1);\n";
    print_vec_info(iv);

    iv.push_back(2);
    std::cout << "iv.push_back(2);\n";
    print_vec_info(iv);

    iv.push_back(3);
    std::cout << "iv.push_back(3);\n";
    print_vec_info(iv);

    iv.push_back(4);
    std::cout << "iv.push_back(4);\n";
    print_vec_info(iv);

    iv.push_back(5);
    std::cout << "iv.push_back(5);\n";
    print_vec_info(iv);

    iv.insert(iv.begin() + 2, 10);
    std::cout << "iv.insert(iv.begin() + 2, 10);\n";
    print_vec_info(iv);

    iv.insert(iv.begin() + 4, 4, 11);
    std::cout << "iv.insert(iv.begin() + 4, 4, 11);\n";
    print_vec_info(iv);
    
    iv.pop_back();
    iv.pop_back();
    std::cout << "iv.pop_back();\n"
                 "iv.pop_back();\n";
    print_vec_info(iv);

    iv.pop_back();
    std::cout << "iv.pop_back();\n";
    print_vec_info(iv);

    iv.erase(iv.begin() + 4);
    std::cout << "iv.erase(iv.begin() + 4);\n";
    print_vec_info(iv);

    iv.erase(iv.begin(), iv.begin() + 3);
    std::cout << "iv.erase(iv.begin(), iv.begin() + 3);\n";
    print_vec_info(iv);

    iv.clear();
    std::cout << "iv.clear();\n";
    print_vec_info(iv);

#if 0   // bug here
    {
        std::vector<int> tmp {1, 2, 3, 4, 5};
        stl::uninitialized_copy(tmp.begin(), tmp.end(), iv.begin());
    }
    print_vec_info(iv);
#endif 

    for (int d = 1; d <= 5; ++d) {
        iv.push_back(d);
    }
    std::cout << "loop 1...5 push_back\n";
    print_vec_info(iv);

    auto ivite = std::find(iv.begin(), iv.end(), 1);
    if (ivite)
        iv.erase(ivite);
    std::cout << "find 1 and erase there\n";
    print_vec_info(iv);

    auto ite = std::find(iv.begin(), iv.end(), 2);
    if (ite)
        iv.insert(ite, 3, 7);
    std::cout << "find 2 and insert 7 7 7\n";
    print_vec_info(iv);

    return 0;
}
