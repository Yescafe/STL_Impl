#ifndef STL_IMPL_FUNCTIONAL_
#define STL_IMPL_FUNCTIONAL_

namespace stl
{

// Base classes
template<typename Arg, typename Result>
struct unary_function {
    typedef Arg argument_type;
    typedef Result result_type;
};

template<typename Arg1, typename Arg2, typename Result>
struct binary_function {
    typedef Arg1 first_argument_type;
    typedef Arg2 second_argument_type;
    typedef Result result_type;
};

// Arithmetic functors
template<typename T>
struct plus : public binary_function<T, T, T> {
    T operator()(const T& x, const T& y) const { return x + y; }
};

template<typename T>
struct minus : public binary_function<T, T, T> {
    T operator()(const T& x, const T& y) const { return x - y; }
};

template<typename T>
struct multiplies : public binary_function<T, T, T> {
    T operator()(const T& x, const T& y) const { return x * y; }
};

template<typename T>
struct divides : public binary_function<T, T, T> {
    T operator()(const T& x, const T& y) const { return x / y; }
};

template<typename T>
struct modulus : public binary_function<T, T, T> {
    T operator()(const T& x, const T& y) const { return x % y; }
};

template<typename T>
struct negate : public unary_function<T, T> {
    T operator()(const T& x) const { return -x; }
};

template<typename T>
inline T identity_element(plus<T>) {
    return T(0);
}

template<typename T>
inline T identity_element(multiplies<T>) {
    return T(1);
}

// Relational functors
template<typename T>
struct equal_to : public binary_function<T, T, bool> {
    bool operator()(const T& x, const T& y) const { return x == y; }
};

template<typename T>
struct not_equal_to : public binary_function<T, T, bool> {
    bool operator()(const T& x, const T& y) const { return x != y; }
};

template<typename T>
struct greater : public binary_function<T, T, bool> {
    bool operator()(const T& x, const T& y) const { return x > y; }
};

template<typename T>
struct greater_equal : public binary_function<T, T, bool> {
    bool operator()(const T& x, const T& y) const { return x >= y; }
};

template<typename T>
struct less : public binary_function<T, T, bool> {
    bool operator()(const T& x, const T& y) const { return x < y; }
};

template<typename T>
struct less_equal : public binary_function<T, T, bool> {
    bool operator()(const T& x, const T& y) const { return x <= y; }
};

// Logical functors
template<typename T>
struct logical_and : public binary_function<T, T, bool> {
    bool operator()(const T& x, const T& y) const { return x && y; }
};

template<typename T>
struct logical_or : public binary_function<T, T, bool> {
    bool operator()(const T& x, const T& y) const { return x || y; }
};

template<typename T>
struct logical_not : public unary_function<T, bool> {
    bool operator()(const T& x) const { return !x; }
};

// Maths and functional functors
template<typename T>
struct identity : public unary_function<T, T> {
    const T& operator()(const T& x) const { return x; }
};

template<typename Pair>
struct select1st : public unary_function<Pair, typename Pair::first_type> {
    const typename Pair::first_type& operator()(const Pair& x) const {
        return x.first;
    }
};

template<typename Pair>
struct select2nd : public unary_function<Pair, typename Pair::second_type> {
    const typename Pair::second_type& operator()(const Pair& x) const {
        return x.second;
    }
};

// Function functors
template<typename Predicate>
class unary_negate
 : public unary_function<typename Predicate::argument_type, bool> {
protected:
    Predicate pred;
public:
    explicit unary_negate(const Predicate& x) : pred(x) { }
    bool operator()(const typename Predicate::argument_type& x) const {
        return !pred(x);
    }
};

template<typename Predicate>
inline unary_negate<Predicate> not1(const Predicate& pred) {
    return unary_negate<Predicate>(pred);
}

template<typename Predicate>
class binary_negate
 : public binary_function<typename Predicate::first_argument_type,
                          typename Predicate::second_argument_type,
                          bool> {
protected:
    Predicate pred;
public:
    explicit binary_negate(const Predicate& x) : pred(x) { }
    bool operator()(const typename Predicate::first_argument_type& x,
                    const typename Predicate::second_argument_type& y) const {
        return !pred(x, y);
    }
};

template<typename Predicate>
inline binary_negate<Predicate> not2(const Predicate& pred) {
    return binary_negate<Predicate>(pred);
}
template<typename Operation>
class binder1st
 : public unary_function<typename Operation::second_argument_type,
                         typename Operation::result_type> {
protected:
    Operation op;
    typename Operation::first_argument_type value;
public:
    binder1st(const Operation& x, const typename Operation::first_argument_type& y)
     : op(x), value(y) { }
    typename Operation::result_type
    operator()(const typename Operation::second_argument_type& x) const {
        return op(value, x);
    }
};

template<typename Operation, typename T>
inline binder1st<Operation> bind1st(const Operation& op, const T& x) {
    typedef typename Operation::first_argument_type arg1_type;
    return binder1st<Operation>(op, arg1_type(x));
}

template<typename Operation>
class binder2nd
 : public unary_function<typename Operation::first_argument_type,
                         typename Operation::result_type> {
protected:
    Operation op;
    typename Operation::second_argument_type value;
public:
    binder2nd(const Operation& x, const typename Operation::second_argument_type& y)
     : op(x), value(y) { }
    typename Operation::result_type
    operator()(const typename Operation::first_argument_type& x) const {
        return op(value, x);
    }
};

template<typename Operation, typename T>
inline binder2nd<Operation> bind2nd(const Operation& op, const T& x) {
    typedef typename Operation::second_argument_type arg2_type;
    return binder2nd<Operation>(op, arg2_type(x));
}

template<typename Arg, typename Result>
class pointer_to_unary_function : public unary_function<Arg, Result>
{
protected:
    Result (*ptr)(Arg);
public:
    pointer_to_unary_function() { }
    explicit pointer_to_unary_function(Result (*x)(Arg)) : ptr(x) { }

    Result operator()(Arg x) const { return ptr(x); }
};

template<typename Arg, typename Result>
inline pointer_to_unary_function<Arg, Result>
ptr_fun(Result (*x)(Arg)) {
    return pointer_to_unary_function<Arg, Result>(x);
}

template<typename Arg1, typename Arg2, typename Result>
class pointer_to_binary_function
 : public binary_function<Arg1, Arg2, Result> {
protected:
    Result (*ptr)(Arg1, Arg2);
public:
    pointer_to_binary_function() { }
    explicit pointer_to_binary_function(Result (*x)(Arg1, Arg2)) : ptr(x) { }
    
    Result operator()(Arg1 x, Arg2 y) { return ptr(x, y); }
};

template<typename Arg1, typename Arg2, typename Result>
inline pointer_to_binary_function<Arg1, Arg2, Result>
ptr_fun(Result (*x)(Arg1, Arg2)) {
    return pointer_to_binary_function<Arg1, Arg2, Result>(x);
}


}  // end of namespace stl



#endif  /* STL_IMPL_FUNCTIONAL_ */