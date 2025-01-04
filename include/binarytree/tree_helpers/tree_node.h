/**
 * @file tree_node.h
 * @brief Definition of the `TreeNode` structure. It is the building block of the binary tree.
 **/

#ifndef TREENODE_H
#define TREENODE_H

#include "concepts/comparable.h"
#include <memory>

namespace ddlib
{

/**
 * @brief A node in a binary tree.
 *
 * This structure represents a node in a binary tree. It can contain a value of type `T` and pointers to the left and
 * right children (if any). \n
 * The data members are public for simplicity. If they were private, we would need to provide getters and setters.
 **/
template <Comparable T>
struct TreeNode
{
  /**
   * @brief The value stored in the node.
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

  TreeNode(const T &value)
  : m_value(value)
  {}
};

} // namespace ddlib

#endif // TREENODE_H
