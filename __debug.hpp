#ifndef STL_IMPL__DEBUG_
#define STL_IMPL__DEBUG_

#include <string>

namespace stl::debug {

std::string warning(const char* info) {
    using std::literals::string_literals::operator""s;
    return "\033[1;31;40m"s + info + "\033[0m"s;
}

}

#endif /* STL_IMPL__DEBUG_ */