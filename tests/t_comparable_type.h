/**
 * @file t_comparable_type.h
 * @brief Header file for the `TComparableType` and `TNotComparableType` classes.\n
 *
 * These classes are used in the tests to demonstrate the usage of the `BinaryTree` class with a comparable and
 * non-comparable type. Type `T` used in Simple Binary Tree must be comparable, i.e., it must implement the `<` and `>`
 * operators.
 *
 * The `T` prefix is used to indicate that the class is testable, i.e. a custom class created for testing purposes.
 **/

#ifndef T_COMPARABLE_TYPE_H
#define T_COMPARABLE_TYPE_H

/**
 * @brief Used to demonstrate the usage of the `BinaryTree` class with a comparable type.
 **/
class TComparableType
{
public:
  TComparableType(int value) : m_value(value) {}
  bool  operator<(const TComparableType& other) const { return m_value <  other.m_value; }
  bool  operator>(const TComparableType& other) const { return m_value >  other.m_value; }
  bool operator==(const TComparableType& other) const { return m_value == other.m_value; } // Only used for testing purposes by Google Test

private:
  int m_value;
};

/**
 * @brief Used to demonstrate the impossibility of using the `BinaryTree` class with a non-comparable type.
 *  **/
class TNotComparableType {};

#endif // T_COMPARABLE_TYPE_H