/**
 * @file binary_tree.h
 * @brief Include this file to use the `BinaryTree` class.
 **/

#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "tree_node.h"
#include <memory>
#include <functional> // Used for traversal functions
#include <concepts>

namespace ddlib
{

/**
 * @brief Concept to check if a type is comparable using the `<` operator.
 **/
template <typename T>
concept Comparable = requires(T a, T b)
{
  { a < b } -> std::convertible_to<bool>;
};

/**
 * @brief A simple binary tree implementation.
 * @tparam T The type of the values stored in the tree. It must support the `<` operator.
 **/
template <Comparable T>
class BinaryTree
{
public:
   BinaryTree();
  ~BinaryTree();

  /**
   * @brief Inserts a value into the tree.
   * @param value The value to insert.
   **/
  void insert(const T &value);

  /**
   * @brief Searches for a value in the tree.
   * @param value The value to search for.
   * @return `bool` `true` if the value is found, `false` otherwise.
   **/
  bool search(const T &value) const;

  /**
   * @brief Removes a value from the tree.
   * @param value The value to remove.
   **/
  void remove(const T &value);

  /**
   * @brief In-order traversal of the tree, i.e., left-root-right.
   * @param visit_cbck Function to call for each node's value.
   **/
  void inOrderTraversal(const std::function<void(const T&)>& visit_cbck) const;

  /**
   * @brief Pre-order traversal of the tree, i.e., root-left-right.
   * @param visit_cbck Function to call for each node's value.
   **/
  void preOrderTraversal(const std::function<void(const T&)>& visit_cbck) const;

  /**
   * @brief Post-order traversal of the tree, i.e., left-right-root.
   * @param visit_cbck Function to call for each node's value.
   **/
  void postOrderTraversal(const std::function<void(const T&)>& visit_cbck) const;

  /**
   * @brief Level-order traversal of the tree, i.e., from top to bottom and from left to right.
   * @param visit_cbck Function to call for each node's value.
   **/
  void levelOrderTraversal(const std::function<void(const T&)>& visit_cbck) const;

private:
  std::unique_ptr<TreeNode<T>> m_root;

  // ---- Helper methods ---- //

  void insert_pvt(std::unique_ptr<TreeNode<T>>& node, const T &value) const;
  bool search_pvt(const std::unique_ptr<TreeNode<T>> &node, const T &value) const;
  std::unique_ptr<TreeNode<T>> remove_pvt(std::unique_ptr<TreeNode<T>> node, const T &value) const;
  const std::unique_ptr<TreeNode<T>>& findMin_pvt(const std::unique_ptr<TreeNode<T>>& node) const;

  void inOrderTraversal_pvt(const std::unique_ptr<TreeNode<T>>& node, const std::function<void(const T&)>& visit_cbck) const;
  void preOrderTraversal_pvt(const std::unique_ptr<TreeNode<T>>& node, const std::function<void(const T&)>& visit_cbck) const;
  void postOrderTraversal_pvt(const std::unique_ptr<TreeNode<T>>& node, const std::function<void(const T&)>& visit_cbck) const;
};

} // namespace ddlib

#include "binary_tree.tpp"

#endif // BINARYTREE_H