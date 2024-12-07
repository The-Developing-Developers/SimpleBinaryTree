/**
 * @file binary_tree.tpp
 * @brief Implementation file for the `BinaryTree` class.
 **/

#include "binary_tree.h"

namespace ddlib
{

template <typename T>
BinaryTree<T>::BinaryTree()
: m_root(nullptr) {}

template <typename T>
BinaryTree<T>::~BinaryTree()
{
  destroyTree_pvt(m_root);
}

template <typename T>
void BinaryTree<T>::insert(T value)
{
  insert_pvt(m_root, value);
}

template <typename T>
void BinaryTree<T>::insert_pvt(TreeNode<T>*& node, T value)
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
bool BinaryTree<T>::search(T value)
{
  return search_pvt(m_root, value);
}

template <typename T>
bool BinaryTree<T>::search_pvt(TreeNode<T>* node, T value)
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
void BinaryTree<T>::remove(T value)
{
  m_root = remove_pvt(m_root, value);
}

template <typename T>
TreeNode<T>* BinaryTree<T>::remove_pvt(TreeNode<T>* node, T value)
{
  if (node == nullptr)
  {
    return nullptr;
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
    if (node->m_left == nullptr && node->m_right == nullptr)
    {
      delete node;
      node = nullptr;
    }
    else if (node->m_left == nullptr)
    {
      TreeNode<T>* temp = node;
      node = node->m_right;
      delete temp;
    }
    else if (node->m_right == nullptr)
    {
      TreeNode<T>* temp = node;
      node = node->m_left;
      delete temp;
    }
    else
    {
      TreeNode<T>* temp = findMin_pvt(node->m_right);
      node->m_value = temp->m_value;
      node->m_right = remove_pvt(node->m_right, temp->m_value);
    }
  }
  return node;
}

template <typename T>
TreeNode<T>* BinaryTree<T>::findMin_pvt(TreeNode<T>* node)
{
  while (node->m_left != nullptr)
  {
    node = node->m_left;
  }
  return node;
}

template <typename T>
void BinaryTree<T>::destroyTree_pvt(TreeNode<T>* node)
{
  if (node != nullptr)
  {
    destroyTree_pvt(node->m_left);
    destroyTree_pvt(node->m_right);
    delete node;
  }
}

} // namespace ddlib