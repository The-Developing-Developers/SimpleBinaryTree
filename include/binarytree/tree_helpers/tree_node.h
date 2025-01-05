/**
 * @file tree_node.h
 * @brief Definition of the `TreeNode` class. It is the building block of the binary tree.
 **/

#ifndef TREENODE_H
#define TREENODE_H

#include "binarytree/concepts/comparable.h"
#include <memory>

namespace ddlib
{

// Forward declarations. Necessary to declare the `BinaryTree` and `Iterator` classes as friends.
template <Comparable T> class BinaryTree;
template <Comparable T> class Iterator;

/**
 * @brief A node in a binary tree.
 *
 * This class represents a node in a binary tree. It can contain a value of type `T` and pointers to the left and
 * right children (if any).
 **/
template <Comparable T>
class TreeNode
{
public:
  TreeNode(const T &value)
    : m_value(value)
  {}

private:

  // Allow access to private members
  friend class BinaryTree<T>;
  friend class Iterator<T>;

  /**
   * @brief The value stored in the node. Can be any type that supports the `<` and `>` operators.
   **/
  T m_value;

  /**
   * @brief Pointer to the left child.
   **/
  std::unique_ptr<TreeNode> m_left  = nullptr;

  /**
   * @brief Pointer to the right child.
   **/
  std::unique_ptr<TreeNode> m_right = nullptr;

};

} // namespace ddlib

#endif // TREENODE_H
