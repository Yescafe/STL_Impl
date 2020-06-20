#include "../__rb_tree.hpp"
#include <iostream>
#include <functional>

template<typename T>
struct identity {
    constexpr T&& operator()(T&& t) const noexcept {
        return std::forward(t);
    }
};

template<typename RB_TREE>
static void print_rb_tree_info(RB_TREE& itree)
{
    std::cout << "size=" << itree.size() 
              << std::endl << std::endl;
}

int main()
{
    stl::rb_tree<int, int, ::identity<int>, std::less<int>> itree;
    std::cout << "Default ctro: " << std::endl;
    print_rb_tree_info(itree);

    itree.insert_unique(10);
    itree.insert_unique(7);
    itree.insert_unique(8);

    itree.insert_unique(15);
    itree.insert_unique(5);
    itree.insert_unique(6);

    itree.insert_unique(11);

    itree.insert_unique(13);
    itree.insert_unique(12);

    print_rb_tree_info(itree);
    for (auto itr = itree.begin(); itr != itree.end(); ++itr)
        std::cout << *itr << ' ';
    std::endl(std::cout);

    auto ite1 = itree.begin();
    auto ite2 = itree.end();
    stl::__rb_tree_base_iterator rbtite;

    for (; ite1 != ite2; ++ite1) {
        rbtite = __rb_tree_base_iterator(ite1);
        std::cout << *ite1 << '(' << rbtite.node->color << ") ";
    }
    std::endl(std::cout);
}