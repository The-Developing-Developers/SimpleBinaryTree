#ifndef SERDES_H
#define SERDES_H

#include "tree_node.h"

namespace ddlib
{

/**
 * @brief Serialisation and deserialisation class for the `BinaryTree` class.
 *
 * The `SerDes` class provides methods to serialise and deserialise a binary tree to/from a file.
 *
 * Don't create an instance of this class. Instead, use the `BinaryTree` class's methods to serialise and deserialise the
 * tree.
 *
 * @tparam T The type of the values stored in the tree. It must support the `<` and `>` operators.
 * @see BinaryTree
 * @see TreeNode
 * @see TreeIterator
 **/
template <Comparable T>
class SerDes
{
private:
  friend class BinaryTree<T>; // Users should use the `BinaryTree` class's methods to serialise and deserialise the tree

  void serialise(const std::string& filename, const std::unique_ptr<TreeNode<T>>& root) const; // Serialise the tree to a file. Use the `BinaryTree` class's public method instead.
  std::unique_ptr<TreeNode<T>> deserialise(const std::string& filename) const; // Deserialise the tree from a file. Use the `BinaryTree` class's public method instead.

  void serialiseNode_pvt(std::ofstream& outFile, const std::unique_ptr<TreeNode<T>>& node) const;
  std::unique_ptr<TreeNode<T>> deserialiseNode_pvt(std::istringstream& inStream) const;
};

} // namespace ddlib

#include "serdes.tpp"

#endif // SERDES_H