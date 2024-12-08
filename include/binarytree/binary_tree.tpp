/**
 * @file binary_tree.tpp
 * @brief Implementation file for the `BinaryTree` class.
 **/

#include "binary_tree.h"

namespace ddlib
{

template <typename T>
BinaryTree<T>::BinaryTree()
{}

template <typename T>
BinaryTree<T>::~BinaryTree()
{
  destroyTree_pvt(m_root);
}

template <typename T>
void BinaryTree<T>::insert(const T &value)
{
  insert_pvt(m_root, value);
}

template <typename T>
void BinaryTree<T>::insert_pvt(TreeNode<T>* &node, const T &value) const
{
  if (node == nullptr)
  {
    node = new TreeNode<T>(value);
  }
  else if (value < node->m_value)
  {
    insert_pvt(node->m_left, value);
  }
  else
  {
    insert_pvt(node->m_right, value);
  }
}

template <typename T>
bool BinaryTree<T>::search(const T &value)
{
  return search_pvt(m_root, value);
}

template <typename T>
bool BinaryTree<T>::search_pvt(const TreeNode<T>* const node, const T &value) const
{
  if (node == nullptr)
  {
    return false;
  }
  else if (value == node->m_value)
  {
    return true;
  }
  else if (value < node->m_value)
  {
    return search_pvt(node->m_left, value);
  }
  else
  {
    return search_pvt(node->m_right, value);
  }
}

template <typename T>
void BinaryTree<T>::remove(const T &value)
{
  m_root = remove_pvt(m_root, value);
}

template <typename T>
TreeNode<T>* BinaryTree<T>::remove_pvt(TreeNode<T>* node, const T &value) const
{
  if (node == nullptr)
  {
    return nullptr; // Base case: value not found
  }
  else if (value < node->m_value)
  {
    node->m_left = remove_pvt(node->m_left, value);
  }
  else if (value > node->m_value)
  {
    node->m_right = remove_pvt(node->m_right, value);
  }
  else
  {
    // Node to remove found (it contains the searched value)
    if (node->m_left == nullptr && node->m_right == nullptr)
    {
      // Node has no children: just delete it
      delete node;
      node = nullptr;
    }
    else if (node->m_left == nullptr)
    {
      // Node has only right child: replace it with the right child and delete the node
      TreeNode<T>* temp = node;
      node = node->m_right;
      delete temp;
    }
    else if (node->m_right == nullptr)
    {
      // Node has only left child: replace it with the left child and delete the node
      TreeNode<T>* temp = node;
      node = node->m_left;
      delete temp;
    }
    else
    {
      // Node has two children: replace it with the minimum value in the right subtree
      TreeNode<T>* temp = findMin_pvt(node->m_right);
      node->m_value = temp->m_value;
      node->m_right = remove_pvt(node->m_right, temp->m_value);
    }
  }

  return node;
}

template <typename T>
TreeNode<T>* BinaryTree<T>::findMin_pvt(TreeNode<T>* node) const
{
  while (node->m_left != nullptr)
  {
    node = node->m_left;
  }

  return node;
}

template <typename T>
void BinaryTree<T>::destroyTree_pvt(const TreeNode<T>* const node) const
{
  if (node != nullptr)
  {
    destroyTree_pvt(node->m_left);
    destroyTree_pvt(node->m_right);
    delete node;
  }
}

} // namespace ddlib