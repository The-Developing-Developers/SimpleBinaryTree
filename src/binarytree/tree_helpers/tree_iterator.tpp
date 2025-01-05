template <Comparable T>
TreeIterator<T>::TreeIterator(TreeNode<T>* root)
  : m_current(root)
{}

template <Comparable T>
bool TreeIterator<T>::moveToLeftChild()
{
  if (m_current && m_current->m_left) // Also check the current node is not null because dereferencing a null pointer is undefined behavior
  {
    m_current = m_current->m_left.get();
    return true;
  }
  return false;
}

template <Comparable T>
bool TreeIterator<T>::moveToRightChild()
{
  if (m_current && m_current->m_right)
  {
    m_current = m_current->m_right.get();
    return true;
  }
  return false;
}

template <Comparable T>
const T& TreeIterator<T>::getValue() const
{
  if (m_current)
  {
    return m_current->m_value;
  }
  throw std::runtime_error("Iterator is not at a valid node");
}

template <Comparable T>
void TreeIterator<T>::setValue(const T& value)
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
bool TreeIterator<T>::isValid() const
{
  return m_current != nullptr;
}

template <Comparable T>
bool TreeIterator<T>::isLeaf() const
{
  if (m_current)
  {
    return !m_current->m_left && !m_current->m_right;
  }
  throw std::runtime_error("Iterator is not at a valid node");
}

template <Comparable T>
bool TreeIterator<T>::createChildren(const T &leftValue, const T &rightValue)
{
  if (m_current && !m_current->m_left && !m_current->m_right)
  {
    m_current->m_left  = std::make_unique<TreeNode<T>>(leftValue);
    m_current->m_right = std::make_unique<TreeNode<T>>(rightValue);
    return true;
  }

  return false;
}