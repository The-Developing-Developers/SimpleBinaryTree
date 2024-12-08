/**
 * @file binary_tree.h
 * @brief Include this file to use the `BinaryTree` class.
 **/

#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "is_comparable.h" // custom type trait to check if a type is comparable
#include "tree_node.h"

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
  bool search(const T &value);
  void remove(const T &value);

private:
  TreeNode<T>* m_root = nullptr;

  // ---- Helper methods ---- //

  void insert_pvt(TreeNode<T>*& node, const T &value) const;
  bool search_pvt(const TreeNode<T>* const node, const T &value) const;
  TreeNode<T>* remove_pvt(TreeNode<T>* node, const T &value) const;
  TreeNode<T>* findMin_pvt(TreeNode<T>* node) const;
  void destroyTree_pvt(const TreeNode<T>* const node) const;
};

} // namespace ddlib

#include "binary_tree.tpp"

#endif // BINARYTREE_H