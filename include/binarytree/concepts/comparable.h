/**
 * @file comparable.h
 * @brief Concept used in the binary tree implementation.
 **/

#ifndef CONCEPTS_COMPARABLE_H
#define CONCEPTS_COMPARABLE_H

#include <concepts>

namespace ddlib
{

/**
 * @brief Concept to check if a type is comparable using the `<`, and `>` operators.
 **/
template <typename T>
concept Comparable = requires(T a, T b)
{
  { a < b } -> std::convertible_to<bool>;
  { a > b } -> std::convertible_to<bool>;
};

} // namespace ddlib

#endif // CONCEPTS_COMPARABLE_H
