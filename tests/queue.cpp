#include "../queue.hpp"
#include <iostream>
#include <deque>

template<typename T, typename Seq>
static void print_queue_info(stl::queue<T, Seq>& iqueue)
{
    std::cout << "  size=" << iqueue.size() << std::endl;
    std::cout << "  top: ";
    if (iqueue.size())
        std::cout << iqueue.front();
    else
        std::cout << "(null)";
    std::cout << std::endl;
}

int main()
{
    std::cout << "Test for std::deque:" << std::endl;
    {
        stl::queue<int, std::deque<int>> iqueue;
        
        for (int i = 0; i < 10; ++i) {
            iqueue.push(i);
        }
        print_queue_info(iqueue);

        while (!iqueue.empty()) {
            std::cout << " pause here" << std::endl;
            iqueue.pop();
            print_queue_info(iqueue);
        }
    }

    std::cout << "Test for stl::deque:" << std::endl;
    {
        stl::queue<int, stl::deque<int>> iqueue;

        for (int i = 0; i < 10; ++i) {
            iqueue.push(i);
        }
        print_queue_info(iqueue);

        while (!iqueue.empty()) {
            iqueue.pop();
            print_queue_info(iqueue);
        }
    }
}
