#include "../pqueue.hpp"
#include <iterator>
#include <iostream>

template<typename T, typename Seq, typename Compare>
void print_pqueue_info(stl::priority_queue<T, Seq, Compare>& ipq)
{
    std::cout << "  size=" << ipq.size() << '\t';
    std::cout << "  top: ";
    if (ipq.size())
        std::cout << ipq.top();
    else
        std::cout << "(null)";
    std::cout << std::endl;
}

int main()
{
    int ia[9] = {0, 1, 2, 3, 4, 8, 9, 3, 5};
    stl::priority_queue<int> ipq(std::begin(ia), std::end(ia));
    std::cout << "Construct from an array:" << std::endl;
    print_pqueue_info(ipq);

    while (!ipq.empty()) {
        print_pqueue_info(ipq);
        ipq.pop();
        std::cout << "One pop." << std::endl;
    }
}