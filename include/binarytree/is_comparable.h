/**
 * @file is_comparable.h
 * @brief Custom type trait to check if a type is comparable using the `<` operator.
 *
 * The primary template `is_comparable` takes two template parameters: `T` and a default parameter of type `void`. By
 * default, this template inherits from `std::false_type`, indicating that the type `T` is not comparable.
 *
 * The partial specialization of the `is_comparable` template is used for types `T` that support the `<` operator. The
 * specialization uses `std::void_t` and `decltype` to check if the expression `std::declval<T>() < std::declval<T>()`
 * is valid: `std::declval<T>()` is a utility that provides an rvalue reference to a type `T` without requiring the type
 * to be default-constructible. `decltype(std::declval<T>() < std::declval<T>())` evaluates to the type of the
 * expression `std::declval<T>() < std::declval<T>()`. `std::void_t<...>` is a helper type that evaluates to void if the
 * expression inside it is valid. If the expression is invalid, the specialization is discarded. If the expression
 * `std::declval<T>() < std::declval<T>()` is valid, the specialization is chosen, and `is_comparable` inherits from
 * `std::true_type`, indicating that the type `T` is comparable.
 *
 * The helper variable template `is_comparable_v` is created for easier usage. It evaluates to `true` if `T` is
 * comparable, and `false` otherwise.
 **/

#ifndef IS_COMPARABLE_H
#define IS_COMPARABLE_H

#include <type_traits>

namespace ddlib
{

/**
 * @brief Custom type trait to check if `T` is comparable using the `<` operator
 * @tparam `T` The type to check
 * @tparam `typename` SFINAE parameter
 **/
template <typename T, typename = void>
struct is_comparable : std::false_type {};

/**
 * @brief Specialization of `is_comparable` for types that support the `<` operator
 * @tparam `T` The type to check
 **/
template <typename T>
struct is_comparable<T, std::void_t<decltype(std::declval<T>() < std::declval<T>())>> : std::true_type {};

/**
 * @brief Helper variable template for easier usage
 * @tparam `T` The type to check
 **/
template <typename T>
inline constexpr bool is_comparable_v = is_comparable<T>::value;

} // namespace ddlib

#endif // IS_COMPARABLE_H