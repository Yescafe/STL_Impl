#ifndef _STL_IMPL_CONCEPT_HPP__
#define _STL_IMPL_CONCEPT_HPP__

#include <type_traits>
#include <utility>
#include <algorithm>
#include <functional>
#include <cstddef>

namespace nstl {

namespace Concepts {

namespace BinaryConcepts{
    template<typename T, typename U>
    concept EqualityComparable = requires(T t, U u) {
        { t == u } -> bool;
        { u == t } -> bool
    };

    template<typename T, typename U>
    concept LessThanComparable = requires(T t, U u) {
        { t < u } -> bool;
        { u < t } -> bool;
    };

    template<typename T, typename U>
    concept Swappable = requires(T t, U u) {
        { std::swap(t, u) };
        { std::swap(u, t) };
    };

    template<typename T, typename U>
    concept ValueSwappable = requires(T t, U u) {
        { std::iter_swap(t, u) };
        { std::iter_swap(u, t) };
    };

}  // namespace BinaryConcepts

// Basic
template<typename T>
concept DefaultConstructible = requires {
    { new T };  
    { T() };
    { T{} };
};

template<typename T>
concept MoveConstructible = std::is_constructible_v<T, 
    std::add_rvalue_reference_t<T>>;

template<typename T>
concept CopyConstuctible = std::is_constructible_v<T, 
    std::add_lvalue_reference_t<std::add_const_t<T>>>;

template<typename T>
concept MoveAssignable = std::is_assignable_v<std::add_lvalue_reference_t<T>, 
    std::add_rvalue_reference_t<T>>;

template<typename T>
concept CopyAssignable = std::is_copy_assignable_v<T>;

template <typename T>
concept Destructible = requires(T x) {
    { x.~T() };
};

// Layout
template<typename T>
concept TriviallyCopyable = std::is_trivially_copyable_v<T>;

template<typename T>
concept TrivialType = std::is_trivial_v<T>;

template<typename T>
concept StandardLayoutType = std::is_standard_layout_v<T>;

// template<typename T>
// concept PODType = std::is_pod_v<T>;

// Library-wide
template<typename T>template<typename T>
// concept Callable = requires {
//     { T().opertor() };
// };
concept EqualityComparable = BinaryConcepts::EqualityComparable<T, T>;

template<typename T>
concept LessThanComparable = BinaryConcepts::LessThanComparable<T, T>;

template<typename T>
concept Swappable = BinaryConcepts::Swappable<T, T>;

template<typename T>
concept ValueSwappable = BinaryConcepts::ValueSwappable<T, T>;

template<typename T>
concept NullablePointer = 
    DefaultConstructible<T> && 
    CopyConstuctible<T> && 
    CopyAssignable<T> && 
    EqualityComparable<T> && 
    Destructible<T> && 
    requires(T u, T v) {
        { bool(u) };
        { T(nullptr) == nullptr };
        { u != v } -> bool;
        { u == nullptr } -> bool;
        { nullptr == u } -> bool;
        { u != nullptr } -> bool;
        { nullptr != u } -> bool;
        { u = nullptr };
    };

template<typename T>
concept Hash = requires(T u) {
    { std::hash(u) } -> std::size_t;
};

// template<typename T>
// concept Allocator = requires(T u) {
//     // Undefined
// };

template<typename T>
concept FunctionObject = 
    std::is_object_v<T> &&
    std::is_function_v<T>;

// template<typename T>
// concept Callable = requires {
//     { T().opertor() };
// };

// template<typename T>
// concept Predicate = // Undefined;



}  // namespace Concepts

}  // namespace nstl

#endif  // _STL_IMPL_CONCEPT_HPP__