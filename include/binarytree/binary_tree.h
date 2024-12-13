/**
 * @file binary_tree.h
 * @brief Include this file to use the `BinaryTree` class.
 **/

#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "is_comparable.h" // custom type trait to check if a type is comparable
#include "tree_node.h"
#include <memory>

namespace ddlib
{

/**
 * @brief A simple binary tree implementation.
 * @tparam T The type of the values stored in the tree. It must support the `<` operator.
 **/
template <typename T>
class BinaryTree
{
  static_assert(is_comparable_v<T>, "Type T must be comparable using < operator");
public:
   BinaryTree();
  ~BinaryTree();

  void insert(const T &value);
  bool search(const T &value) const;
  void remove(const T &value);

private:
  std::unique_ptr<TreeNode<T>> m_root;

  // ---- Helper methods ---- //

  void insert_pvt(std::unique_ptr<TreeNode<T>>& node, const T &value) const;
  bool search_pvt(const TreeNode<T>* const node, const T &value) const;
  std::unique_ptr<TreeNode<T>> remove_pvt(std::unique_ptr<TreeNode<T>> node, const T &value) const;
  TreeNode<T>* findMin_pvt(TreeNode<T>* node) const;
};

} // namespace ddlib

#include "binary_tree.tpp"

#endif // BINARYTREE_H