#include "../stack.hpp"
#include <iostream>
#include <deque>
#include "../deque.hpp"

template<typename T, typename Seq>
static void print_stack_info(stl::stack<T, Seq>& istack)
{
    std::cout << "  size=" << istack.size() << std::endl;
    std::cout << "  top: ";
    if (istack.size())
        std::cout << istack.top();
    else
        std::cout << "(null)";
    std::cout << std::endl;
}

int main()
{
    std::cout << "Test for std::deque:" << std::endl;
    {
        stl::stack<int, std::deque<int>> istack;
        
        for (int i = 0; i < 6; ++i) {
            istack.push(i);
        }
        print_stack_info(istack);

        while (!istack.empty()) {
            std::cout << " pause here" << std::endl;
            istack.pop();
            print_stack_info(istack);
        }
    }

    std::cout << "Test for stl::deque:" << std::endl;
    {
        stl::stack<int, stl::deque<int>> istack;

        for (int i = 0; i < 6; ++i) {
            istack.push(i);
        }
        print_stack_info(istack);

        while (!istack.empty()) {
            istack.pop();
            print_stack_info(istack);
        }
    }
}
