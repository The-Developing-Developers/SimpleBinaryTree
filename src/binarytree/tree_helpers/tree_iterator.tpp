template <Comparable T>
Iterator<T>::Iterator(TreeNode<T>* root)
  : m_current(root)
{}

template <Comparable T>
bool Iterator<T>::moveToLeftChild()
{
  if (m_current && m_current->m_left) // Also check the current node is not null because dereferencing a null pointer is undefined behavior
  {
    m_current = m_current->m_left.get();
    return true;
  }
  return false;
}

template <Comparable T>
bool Iterator<T>::moveToRightChild()
{
  if (m_current && m_current->m_right)
  {
    m_current = m_current->m_right.get();
    return true;
  }
  return false;
}

template <Comparable T>
const T& Iterator<T>::getValue() const
{
  if (m_current)
  {
    return m_current->m_value;
  }
  throw std::runtime_error("Iterator is not at a valid node");
}

template <Comparable T>
void Iterator<T>::setValue(const T& value)
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
bool Iterator<T>::isValid() const
{
  return m_current != nullptr;
}

template <Comparable T>
bool Iterator<T>::isLeaf() const
{
  if (m_current)
  {
    return !m_current->m_left && !m_current->m_right;
  }
  throw std::runtime_error("Iterator is not at a valid node");
}

template <Comparable T>
bool Iterator<T>::createChildren(const T &leftValue, const T &rightValue)
{
  if (m_current && !m_current->m_left && !m_current->m_right)
  {
    m_current->m_left  = std::make_unique<TreeNode<T>>(leftValue);
    m_current->m_right = std::make_unique<TreeNode<T>>(rightValue);
    return true;
  }

  return false;
}