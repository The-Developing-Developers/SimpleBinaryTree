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
 * to the left and right children (if any).\n
 * The data members are public for simplicity. If they were private, we would need to provide getters and setters.
 **/
template <typename T>
struct TreeNode
{
  T m_value;
  TreeNode* m_left  = nullptr;
  TreeNode* m_right = nullptr;

  TreeNode(const T &value)
  : m_value(value)
  {}
};

} // namespace ddlib

#endif // TREENODE_H