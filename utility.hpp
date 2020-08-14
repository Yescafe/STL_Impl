#ifndef STL_IMPL_UTILITY_
#define STL_IMPL_UTILITY_

namespace stl
{

template<typename T1, typename T2>
struct pair {
    using first_type = T1;
    using second_type = T2;
    T1 first;
    T2 second;
    pair()
     : first{}, second{} {}
    pair(const T1& x, const T2& y)
     : first(x), second(y) {}
    pair(const pair<T1, T2>& p)
     : first(p.first), second(p.second) {}
    bool operator==(const pair<T1, T2>& rhs)
    {
        return this->first == rhs.first &&
               this->second == rhs.second;
    }
    bool operator<(const pair<T1, T2>& rhs)
    {
        return this->first != rhs.first ?
               this->first < rhs.first : this->second < rhs.second;
    }
    bool operator!=(const pair<T1, T2>& rhs) { return !operator==(rhs); }
    bool operator<=(const pair<T1, T2>& rhs) { return operator==(rhs) || operator<(rhs); }
    bool operator>=(const pair<T1, T2>& rhs) { return !operator<(rhs); }
    bool operator> (const pair<T1, T2>& rhs) { return !operator<=(rhs); }
    pair<T1, T2>& operator=(const pair<T1, T2>& rhs)
    {
        this->first = rhs.first;
        this->second = rhs.second;
        return *this;
    }
};

}  // end of namespace stl

#endif  /* STL_IMPL_UTILITY_ */