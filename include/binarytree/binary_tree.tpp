/**
 * @file binary_tree.tpp
 * @brief Implementation file for the `BinaryTree` class.
 **/

#include <queue>   // Used for level-order traversal
#include <fstream> // Used for serialisation / deserialisation
#include <sstream> // Used for deserialisation

namespace ddlib
{

// ---- Constructor(s) and Destructor ---- //

template <Comparable T>
BinaryTree<T>::BinaryTree()
{}

template <Comparable T>
BinaryTree<T>::~BinaryTree()
{}

// ---- Tree Management Methods ---- //

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
bool BinaryTree<T>::isEmpty() const
{
  return m_root == nullptr;
}

template <Comparable T>
bool BinaryTree<T>::search(const T &value) const
{
  return search_pvt(m_root, value);
}

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
void BinaryTree<T>::preOrderTraversal(const std::function<void(const T&)>& visit_callback) const
{
  preOrderTraversal_pvt(m_root, visit_callback);
}

template <Comparable T>
void BinaryTree<T>::postOrderTraversal(const std::function<void(const T&)>& visit_callback) const
{
  postOrderTraversal_pvt(m_root, visit_callback);
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
void BinaryTree<T>::postOrderTraversal_pvt(const std::unique_ptr<TreeNode<T>>& node, const std::function<void(const T&)>& visit_callback) const
{
  if (node != nullptr)
  {
    postOrderTraversal_pvt(node->m_left, visit_callback);
    postOrderTraversal_pvt(node->m_right, visit_callback);
    visit_callback(node->m_value);
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
void BinaryTree<T>::Iterator::setValue(const T& value)
{
  if (m_current)
  {
    m_current->m_value = value;
  }
  else
  {
    throw std::runtime_error("Iterator is not at a valid node");
  }
}

template <Comparable T>
bool BinaryTree<T>::Iterator::isValid() const
{
  return m_current != nullptr;
}

template <Comparable T>
bool BinaryTree<T>::Iterator::isLeaf() const
{
  if (m_current)
  {
    return !m_current->m_left && !m_current->m_right;
  }
  throw std::runtime_error("Iterator is not at a valid node");
}

template <Comparable T>
bool BinaryTree<T>::Iterator::createChildren(const T &leftValue, const T &rightValue)
{
  if (m_current && !m_current->m_left && !m_current->m_right)
  {
    m_current->m_left  = std::make_unique<TreeNode<T>>(leftValue);
    m_current->m_right = std::make_unique<TreeNode<T>>(rightValue);
    return true;
  }

  return false;
}

// ---- Serialisation and Deserialisation Methods ---- //

template <Comparable T>
void BinaryTree<T>::serialise(const std::string& filename) const
{
  std::ofstream outFile(filename);
  if (!outFile)
    throw std::runtime_error("Cannot open file for writing");

  serialiseNode_pvt(outFile, m_root);
  outFile.close();
}

template <Comparable T>
void BinaryTree<T>::deserialise(const std::string& filename)
{
  std::ifstream inFile(filename);
  if (!inFile)
    throw std::runtime_error("Cannot open file for reading");

  std::stringstream buffer;
  buffer << inFile.rdbuf(); // Read the binary file into a stringstream
  std::string dataString = buffer.str(); // Extract the string from the stringstream
  std::istringstream dataStream(dataString); // Create an input string stream from the string
  m_root = deserialiseNode_pvt(dataStream);
  inFile.close();
}

template <Comparable T>
void BinaryTree<T>::serialiseNode_pvt(std::ofstream& outFile, const std::unique_ptr<TreeNode<T>>& node) const
{
  if (node)
  {
    if constexpr (std::is_same_v<T, std::string>)
      outFile << "\"" << node->m_value << "\" "; // Use double quotes to denote string values
    else
      outFile << node->m_value << " "; // Use a space to separate values

    serialiseNode_pvt(outFile, node->m_left);
    serialiseNode_pvt(outFile, node->m_right);
  }
  else
  {
    outFile << "# "; // Use '#' to denote null nodes. The space is used to separate values
  }
}

template <Comparable T>
std::unique_ptr<TreeNode<T>> BinaryTree<T>::deserialiseNode_pvt(std::istringstream& inStream)
{
  std::string valueFromStream;
  inStream >> valueFromStream; // Read the next value from the stream up to the next space. The binary file has been converted to an istringstream by the caller

  if (valueFromStream == "#")
  {
    return nullptr; // Base case: null node
  }
  else
  {
    T nodeValue; // The value to store in the node. Can be a `std::string` or a primitive type

    if constexpr (std::is_same_v<T, std::string>)
    {
      // `T` is a string type
      if (valueFromStream.front() == '"')
      {
        // Start of a quoted string
        std::string restOfString;
        if (valueFromStream.back() != '"')
        {
          // The string contains spaces, and must be read until the closing double quote
          std::getline(inStream, restOfString, '"'); // Read the rest of the string until the closing double quote
          nodeValue = valueFromStream.substr(1) + restOfString; // Combine the parts without adding an extra space
        }
        else
        {
          // The string does not contain spaces, and can be read directly
          nodeValue = valueFromStream.substr(1, valueFromStream.size() - 2); // Remove the double quotes
        }
      }
      else
      {
        throw std::runtime_error("Malformed string in serialised data");
      }
    }
    else
    {
      std::istringstream(valueFromStream) >> nodeValue; // `T` is a primitive type
    }
    auto node = std::make_unique<TreeNode<T>>(nodeValue);
    node->m_left  = deserialiseNode_pvt(inStream);
    node->m_right = deserialiseNode_pvt(inStream);
    return node;
  }
}

} // namespace ddlib