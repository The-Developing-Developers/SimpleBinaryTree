/**
 * @file tree_node.h
 * @brief Definition of the `TreeNode` structure. It is the building block of the binary tree.
 **/

#ifndef TREENODE_H
#define TREENODE_H

namespace ddlib
{

/**
 * @brief The `TreeNode` structure represents a node in a binary tree. It can contain a value of type `T` and pointers
 * to the left and right children (if any).
 **/
template <typename T>
struct TreeNode
{
  T m_value;
  TreeNode* m_left;
  TreeNode* m_right;

  TreeNode(T val)
  : m_value(val), m_left(nullptr), m_right(nullptr) {}
};

} // namespace ddlib

#endif // TREENODE_H