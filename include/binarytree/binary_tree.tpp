/**
 * @file binary_tree.tpp
 * @brief Implementation file for the `BinaryTree` class.
 **/

#include <queue> // Used for level-order traversal

namespace ddlib
{

// ---- Constructor(s) and Destructor ---- //

template <Comparable T>
BinaryTree<T>::BinaryTree()
{}

template <Comparable T>
BinaryTree<T>::~BinaryTree()
{}

// ---- Public Methods ---- //

template <Comparable T>
void BinaryTree<T>::insert(const T &value)
{
  insert_pvt(m_root, value);
}

template <Comparable T>
void BinaryTree<T>::remove(const T &value)
{
  m_root = remove_pvt(std::move(m_root), value);
}

template <Comparable T>
bool BinaryTree<T>::search(const T &value) const
{
  return search_pvt(m_root, value);
}

// ---- Private Helper Methods ---- //

/**
 * @brief Insert a value into the tree.
 * Receives a reference to a `unique_ptr` because the node is modified during the insertion.
 *
 * @param node The node to start the insertion from
 * @param value The value to insert
 **/
template <Comparable T>
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

/**
 * @brief Search for a value in the tree.
 * Receives a reference to a `const` unique pointer to a `TreeNode` because the node is not modified during the search.
 *
 * @param node The node to start the search from
 * @param value The value to search for
 * @return `bool` `true` if the value is found, `false` otherwise
 **/
template <Comparable T>
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

/**
 * @brief Remove a value from the tree.
 * Receives a `unique_ptr` because the node is modified during the search.
 *
 * @param node The node to start the search from
 * @param value The value to remove
 * @return `std::unique_ptr<TreeNode<T>>` The new node after the removal
 **/
template <Comparable T>
std::unique_ptr<TreeNode<T>> BinaryTree<T>::remove_pvt(std::unique_ptr<TreeNode<T>> node, const T& value) const
{
  if (node == nullptr)
  {
    return nullptr; // Base case: value not found
  }
  else if (value < node->m_value)
  {
    node->m_left = remove_pvt(std::move(node->m_left), value); // remove_pvt returns an rvalue, so that node->m_left can release its owned object (if any) and take ownership of the new object
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
      node.reset(nullptr); // Calls the destructor of the node
    }
    else if (node->m_left == nullptr)
    {
      // Node has only right child: replace node with its right child and delete the node
      return std::move(node->m_right);
    }
    else if (node->m_right == nullptr)
    {
      // Node has only left child: replace node with its left child and delete the node
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

  return node; // moves (not copies) the node back to the caller
}

/**
 * @brief Find the minimum node in the tree.
 * Receives a reference to a `const` unique pointer to a `TreeNode` because the node is not modified during the search.
 *
 * @param node the node to start the search from
 * @return `const std::unique_ptr<TreeNode<T>>&` reference to the minimum node in the tree
 **/
template <Comparable T>
const std::unique_ptr<TreeNode<T>>& BinaryTree<T>::findMin_pvt(const std::unique_ptr<TreeNode<T>>& node) const
{
  const std::unique_ptr<TreeNode<T>>* current = &node; // Pointer to the current node. Used to traverse the tree
  while ((*current)->m_left != nullptr)
  {
    current = &((*current)->m_left);
  }

  return *current;
}

// ---- Traversal Methods ---- //

template <Comparable T>
void BinaryTree<T>::inOrderTraversal(const std::function<void(const T&)>& visit_callback) const
{
  inOrderTraversal_pvt(m_root, visit_callback);
}

template <Comparable T>
void BinaryTree<T>::inOrderTraversal_pvt(const std::unique_ptr<TreeNode<T>>& node, const std::function<void(const T&)>& visit_callback) const
{
  if (node != nullptr)
  {
    inOrderTraversal_pvt(node->m_left, visit_callback);
    visit_callback(node->m_value);
    inOrderTraversal_pvt(node->m_right, visit_callback);
  }
}

template <Comparable T>
void BinaryTree<T>::preOrderTraversal(const std::function<void(const T&)>& visit_callback) const
{
  preOrderTraversal_pvt(m_root, visit_callback);
}

template <Comparable T>
void BinaryTree<T>::preOrderTraversal_pvt(const std::unique_ptr<TreeNode<T>>& node, const std::function<void(const T&)>& visit_callback) const
{
  if (node != nullptr)
  {
    visit_callback(node->m_value);
    preOrderTraversal_pvt(node->m_left, visit_callback);
    preOrderTraversal_pvt(node->m_right, visit_callback);
  }
}

template <Comparable T>
void BinaryTree<T>::postOrderTraversal(const std::function<void(const T&)>& visit_callback) const
{
  postOrderTraversal_pvt(m_root, visit_callback);
}

template <Comparable T>
void BinaryTree<T>::postOrderTraversal_pvt(const std::unique_ptr<TreeNode<T>>& node, const std::function<void(const T&)>& visit_callback) const
{
  if (node != nullptr)
  {
    postOrderTraversal_pvt(node->m_left, visit_callback);
    postOrderTraversal_pvt(node->m_right, visit_callback);
    visit_callback(node->m_value);
  }
}

template <Comparable T>
void BinaryTree<T>::levelOrderTraversal(const std::function<void(const T&)>& visit_callback) const
{
  // Does not require a private helper method, because level-order traversal is inherently iterative and uses a queue to
  // manage the nodes to be visited.

  if (!m_root) return;

  std::queue<const TreeNode<T>*> nodeQueue;
  nodeQueue.push(m_root.get());

  while (!nodeQueue.empty())
  {
    const TreeNode<T>* currentNode = nodeQueue.front(); // Get the front element
    nodeQueue.pop(); // Remove the front element

    visit_callback(currentNode->m_value);

    if (currentNode->m_left)
      nodeQueue.push(currentNode->m_left.get());

    if (currentNode->m_right)
      nodeQueue.push(currentNode->m_right.get());
  }
}

// ---- Iterator Methods ---- //

template <Comparable T>
BinaryTree<T>::Iterator::Iterator(TreeNode<T>* root)
  : m_current(root)
{}

template <Comparable T>
typename BinaryTree<T>::Iterator BinaryTree<T>::getIterator() const
{
  return Iterator(m_root.get()); // Calls the constructor of the `Iterator` class
}

template <Comparable T>
bool BinaryTree<T>::Iterator::moveToLeftChild()
{
  if (m_current && m_current->m_left) // Also check the current node is not null because dereferencing a null pointer is undefined behavior
  {
    m_current = m_current->m_left.get();
    return true;
  }
  return false;
}

template <Comparable T>
bool BinaryTree<T>::Iterator::moveToRightChild()
{
  if (m_current && m_current->m_right)
  {
    m_current = m_current->m_right.get();
    return true;
  }
  return false;
}

template <Comparable T>
const T& BinaryTree<T>::Iterator::getValue() const
{
  if (m_current)
  {
    return m_current->m_value;
  }
  throw std::runtime_error("Iterator is not at a valid node");
}

template <Comparable T>
bool BinaryTree<T>::Iterator::isValid() const
{
  return m_current != nullptr;
}

} // namespace ddlib