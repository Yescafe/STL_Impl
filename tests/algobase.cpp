#include "../algobase.hpp"
#include <iostream>
#include "../vector.hpp"
#include <vector>
#include <iterator>
#include <functional>
#include <algorithm>
#include <cassert>
#include "../numeric.hpp"
#include <string>
#include "../list.hpp"
#include "../deque.hpp"

#ifndef _TESTS_ALGORITHM
int main()
#else
void tests_algobase()
#endif
{
    std::vector<int> std_vec;
    stl::vector<int> stl_vec;
    for (int i = 0; i < 6; ++i) {
        std_vec.push_back(i+1);
        stl_vec.push_back(i+1);
    }

    // Equal
    std::cout << "assert equal(std_vec, stl_vec);" << std::endl;
    assert(equal(std::begin(std_vec), std::end(std_vec), stl_vec.begin()));
    std::cout << "assertion succeed." << std::endl;

    stl::iota(stl_vec.begin(), stl_vec.end(), 2);
    std::cout << "assert equal(std_vec, stl_vec, std::less<int>);" << std::endl;
    assert(equal(std::begin(std_vec), std::end(std_vec), stl_vec.begin(), std::less<int>()));
    std::cout << "assertion succeed." << std::endl << std::endl;
    stl::iota(stl_vec.begin(), stl_vec.end(), 1);

    // Fill
    std::cout << "Before filling value in std_vec: ";
    std::copy(std::begin(std_vec), std::end(std_vec), std::ostream_iterator<int>(std::cout, ", "));
    std::endl(std::cout);
    std::cout << "After filling: ";
    stl::fill(std::begin(std_vec), std::end(std_vec), 0);
    std::copy(std::begin(std_vec), std::end(std_vec), std::ostream_iterator<int>(std::cout, ", "));
    std::cout << std::endl << std::endl;
    stl::iota(std::begin(std_vec), std::end(std_vec), 1);

    // Iterator swap
    std::cout << "Before iterator swap: ";
    std::copy(std::begin(std_vec), std::end(std_vec), std::ostream_iterator<int>(std::cout, ", "));
    std::endl(std::cout);
    std::cout << "After iterator swap: ";
    for (auto itr1 = std::begin(std_vec), itr2 = std::end(std_vec) - 1;
         itr1 < itr2; ++itr1, --itr2) {
        stl::iter_swap(itr1, itr2);
    }
    std::copy(std::begin(std_vec), std::end(std_vec), std::ostream_iterator<int>(std::cout, ", "));
    std::cout << std::endl << std::endl;

    // Lexicographical compare
    std::string str1("hello");
    std::string str2("holle");
    std::cout << "\"hello\" < \"holle\": ";
    std::cout << std::boolalpha
              << stl::lexicographical_compare(std::begin(str1), std::end(str1), std::begin(str2), std::end(str2))
              << std::endl;
    std::cout << "\"hello\" > \"holle\": ";
    std::cout << std::boolalpha
              << stl::lexicographical_compare(std::begin(str1), std::end(str1), std::begin(str2), std::end(str2), std::greater<char>())
              << std::endl << std::endl;

    // Min and max
    int a = 1, b = 2;
    auto [m, M] = stl::min_max(a, b);
    std::cout << "min of 1 and 2: " << m << std::endl
              << "max of 1 and 2: " << M << std::endl << std::endl;

    // Mismatch
    stl::iota(std::begin(std_vec), std::end(std_vec), 1);
    stl::iota(stl_vec.begin(), stl_vec.end(), 1);
    std_vec.at(3) = 3;
    std::cout << "std_vec: ";
    std::copy(std::begin(std_vec), std::end(std_vec), std::ostream_iterator<int>(std::cout, ", "));
    std::endl(std::cout);
    std::cout << "stl_vec: ";
    for (auto itr = stl_vec.begin(); itr != stl_vec.end(); ++itr) {
        std::cout << *itr << ", ";
    }
    std::endl(std::cout);
    auto [pos1, pos2] = stl::mismatch(std::begin(std_vec), std::end(std_vec), stl_vec.begin());
    std::cout << "Mismatch between " << *pos1 << " and " << *pos2
              << std::endl << std::endl;

    // Swap
    std::cout << "Before swaping, a = " << a << ", b = " << b << std::endl;
    stl::swap(a, b);
    std::cout << "After swaping, a = " << a << ", b = " << b << std::endl;

    // Copy
    auto print = [](auto& c) {
        for (const auto& i : c)
            std::cout << i << ", ";
        std::endl(std::cout);
    };

    class C {
    public:
        C() : _data(3) { }   // trivial assignment operator
        C(const C&) = default;
        int get() const { return _data; }
    private:
        int _data;
    };
    const char ccs[5] = {'a', 'b', 'c', 'd', 'e'};
    char ccd[5];
    stl::copy(ccs, ccs + 5, ccd);
    std::cout << "Copy 1: ";
    print(ccd);

    const wchar_t cwcs[5] = {'a', 'b', 'c', 'd', 'e'};
    wchar_t cwcd[5];
    stl::copy(cwcs, cwcs + 5, cwcd);
    std::cout << "Copy 2: ";
    print(cwcd);

    int ia[5] = {0, 1, 2, 3, 4};
    stl::copy(ia, ia + 5, ia);
    std::cout << "Copy 3: ";
    print(ia);

    stl::vector<int> ivecs(ia, ia + 5);
    stl::vector<int> ivecd(5);
    stl::copy(ivecs.begin(), ivecs.end(), ivecd.begin());
    std::cout << "Copy 4: ";
    print(ivecd);

    stl::list<int> ilists(ia, ia + 5);
    stl::list<int> ilistd(5);
    stl::copy(ilists.begin(), ilists.end(), ilistd.begin());
    std::cout << "Copy 5: ";
    print(ilistd);

    C c[5];
    stl::deque<C> Cds(c, c + 5);
    stl::deque<C> Cdd(5);
    stl::copy(Cds.begin(), Cds.end(), Cdd.begin());
    std::cout << "Copy 6: ";
    for (auto itr = Cdd.begin(); itr != Cdd.end(); ++itr) {
        std::cout << itr->get() << ", ";
    }
    std::endl(std::cout);
}