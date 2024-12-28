/**
 * @file comparable.h
 * @brief Header file for the `Comparable` and `NotComparable` classes.\n
 *
 * These classes are used in the tests to demonstrate the usage of the `BinaryTree` class with a comparable and
 * non-comparable type.
 **/

#ifndef COMPARABLE_H
#define COMPARABLE_H

/**
 * @brief Used to demonstrate the usage of the `BinaryTree` class with a comparable type.
 **/
class Comparable
{
public:
  Comparable(int value) : m_value(value) {}
  bool  operator<(const Comparable& other) const { return m_value <  other.m_value; }
  bool operator==(const Comparable& other) const { return m_value == other.m_value; } // Only used for testing purposes by Google Test

private:
  int m_value;
};

/**
 * @brief Used to demonstrate the impossibility of using the `BinaryTree` class with a non-comparable type.
 *  **/
class NotComparable {};

#endif // COMPARABLE_H