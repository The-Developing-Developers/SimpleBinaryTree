/**
 * @file binary_tree.tpp
 * @brief Implementation file for the `BinaryTree` class.
 **/

namespace ddlib
{

template <typename T>
BinaryTree<T>::BinaryTree()
{}

template <typename T>
BinaryTree<T>::~BinaryTree()
{}

template <typename T>
void BinaryTree<T>::insert(const T &value)
{
  insert_pvt(m_root, value);
}

template <typename T>
void BinaryTree<T>::insert_pvt(std::unique_ptr<TreeNode<T>> &node, const T &value) const
{
  if (node == nullptr)
  {
    node = std::make_unique<TreeNode<T>>(value);
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
bool BinaryTree<T>::search(const T &value) const
{
  return search_pvt(m_root, value);
}

/**
 * @brief Search for a value in the tree.
 * Receives a reference to a `const` unique pointer to a `TreeNode` because the node is not modified during the search.
 *
 * @param node The node to start the search from
 * @param value The value to search for
 * @return bool
 **/
template <typename T>
bool BinaryTree<T>::search_pvt(const std::unique_ptr<TreeNode<T>> &node, const T &value) const
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
  m_root = remove_pvt(std::move(m_root), value);
}

template <typename T>
std::unique_ptr<TreeNode<T>> BinaryTree<T>::remove_pvt(std::unique_ptr<TreeNode<T>> node, const T& value) const
{
  if (node == nullptr)
  {
    return nullptr; // Base case: value not found
  }
  else if (value < node->m_value)
  {
    node->m_left = remove_pvt(std::move(node->m_left), value);
  }
  else if (value > node->m_value)
  {
    node->m_right = remove_pvt(std::move(node->m_right), value);
  }
  else
  {
    // Node to remove found (it contains the searched value)
    if (node->m_left == nullptr && node->m_right == nullptr)
    {
      // Node has no children: since `node` is a `unique_ptr`, it will be automatically deleted
      node = nullptr; // Calls the destructor of the node
    }
    else if (node->m_left == nullptr)
    {
      // Node has only right child: replace it with the right child and delete the node
      return std::move(node->m_right);
    }
    else if (node->m_right == nullptr)
    {
      // Node has only left child: replace it with the left child and delete the node
      return std::move(node->m_left);
    }
    else
    {
      // Node has two children: replace its value with the value contained in the minimum node of the right subtree
      const std::unique_ptr<TreeNode<T>>& temp = findMin_pvt(node->m_right); // Find the minimum node in the right subtree
      node->m_value = temp->m_value; // Replace the node's value, effectively "removing" the node
      node->m_right = remove_pvt(std::move(node->m_right), temp->m_value); // Remove the minimum node from the right subtree
    }
  }

  return node;
}

/**
 * @brief Find the minimum node in the tree.
 * Receives a reference to a `const` unique pointer to a `TreeNode` because the node is not modified during the search.
 *
 * @param node the node to start the search from
 * @return `const std::unique_ptr<TreeNode<T>>&` reference to the minimum node in the tree
 **/
template <typename T>
const std::unique_ptr<TreeNode<T>>& BinaryTree<T>::findMin_pvt(const std::unique_ptr<TreeNode<T>>& node) const
{
  const std::unique_ptr<TreeNode<T>>* current = &node; // Pointer to the current node. Used to traverse the tree
  while ((*current)->m_left != nullptr)
  {
    current = &((*current)->m_left);
  }

  return *current;
}

} // namespace ddlib