#include <fstream>
#include <sstream>

namespace ddlib
{

template <Comparable T>
void SerDes<T>::serialise(const std::string& filename, const std::unique_ptr<TreeNode<T>>& root) const
{
  std::ofstream outFile(filename);
  if (!outFile)
    throw std::runtime_error("Cannot open file for writing");

  serialiseNode_pvt(outFile, root);
  outFile.close();
}

template <Comparable T>
std::unique_ptr<TreeNode<T>> SerDes<T>::deserialise(const std::string& filename) const
{
  std::ifstream inFile(filename);
  if (!inFile)
    throw std::runtime_error("Cannot open file for reading");

  std::stringstream buffer;
  buffer << inFile.rdbuf();
  std::string dataString = buffer.str();
  std::istringstream dataStream(dataString);
  auto root = deserialiseNode_pvt(dataStream);
  inFile.close();
  return root;
}

template <Comparable T>
void SerDes<T>::serialiseNode_pvt(std::ofstream& outFile, const std::unique_ptr<TreeNode<T>>& node) const
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
std::unique_ptr<TreeNode<T>> SerDes<T>::deserialiseNode_pvt(std::istringstream& inStream) const
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
