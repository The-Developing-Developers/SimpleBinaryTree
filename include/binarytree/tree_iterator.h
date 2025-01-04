/**
 * @file tree_iterator.h
 * @brief Definition of the `Iterator` class for the `BinaryTree`.
 **/

#ifndef TREE_ITERATOR_H
#define TREE_ITERATOR_H

#include "tree_node.h"

namespace ddlib
{

template <Comparable T> class BinaryTree; // Forward declaration

template <Comparable T>
class Iterator
{
public:
  Iterator(TreeNode<T>* root);

  /**
   * @brief Move to the left child of the current node.
   * @return `bool` `true` if the left child exists and the iterator moved, `false` otherwise.
   **/
  bool moveToLeftChild();

  /**
   * @brief Move to the right child of the current node.
   * @return `bool` `true` if the right child exists and the iterator moved, `false` otherwise.
   **/
  bool moveToRightChild();

  /**
   * @brief Get the value of the current node.
   * @return `const T&` The value of the current node.
   **/
  const T& getValue() const;

  /**
   * @brief Set the value of the current node.
   * @param value The new value to set.
   **/
  void setValue(const T& value);

  /**
   * @brief Check if the iterator is at a valid node.
   * @return `bool` `true` if the iterator is at a valid node, `false` otherwise.
   **/
  bool isValid() const;

  /**
   * @brief Check if the current node is a leaf node.
   * @return `bool` `true` if the current node is a leaf node, `false` otherwise.
   **/
  bool isLeaf() const;

  /**
   * @brief Create left and right children for the current node.
   * @param leftValue The value for the left child.
   * @param rightValue The value for the right child.
   * @return `bool` `true` if the children were successfully created, `false` otherwise.
   **/
  bool createChildren(const T& leftValue, const T& rightValue);

private:
  TreeNode<T>* m_current;
};

#include "tree_iterator.tpp"

} // namespace ddlib

#endif // TREE_ITERATOR_H