#ifndef SERDES_H
#define SERDES_H

#include "tree_node.h"

namespace ddlib
{

template <Comparable T>
class SerDes
{
public:
  void serialise(const std::string& filename, const std::unique_ptr<TreeNode<T>>& root) const;
  std::unique_ptr<TreeNode<T>> deserialise(const std::string& filename) const;

private:
  void serialiseNode_pvt(std::ofstream& outFile, const std::unique_ptr<TreeNode<T>>& node) const;
  std::unique_ptr<TreeNode<T>> deserialiseNode_pvt(std::istringstream& inStream) const;
};

} // namespace ddlib

#include "serdes.tpp"

#endif // SERDES_H