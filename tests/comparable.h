/**
 * @file comparable.h
 * @brief Header file for the `ComparableType` and `NotComparableType` classes.\n
 *
 * These classes are used in the tests to demonstrate the usage of the `BinaryTree` class with a comparable and
 * non-comparable type. Type `T` used in Simple Binary Tree must be comparable, i.e., it must implement the `<` and `>`
 * operators.
 **/

#ifndef COMPARABLE_H
#define COMPARABLE_H

/**
 * @brief Used to demonstrate the usage of the `BinaryTree` class with a comparable type.
 **/
class ComparableType
{
public:
  ComparableType(int value) : m_value(value) {}
  bool  operator<(const ComparableType& other) const { return m_value <  other.m_value; }
  bool  operator>(const ComparableType& other) const { return m_value >  other.m_value; }
  bool operator==(const ComparableType& other) const { return m_value == other.m_value; } // Only used for testing purposes by Google Test

private:
  int m_value;
};

/**
 * @brief Used to demonstrate the impossibility of using the `BinaryTree` class with a non-comparable type.
 *  **/
class NotComparableType {};

#endif // COMPARABLE_H