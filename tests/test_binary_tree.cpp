/**
 * @file test_binary_tree.cpp
 * @brief Unit tests for the `BinaryTree` class.
 **/

#include "binary_tree.h"
#include "t_comparable_type.h"
#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <fstream> // Used for serialisation / deserialisation

// -- Test Environment -- //

/**
 * @brief Test environment for the `BinaryTree` class.
 * This class is used to set up the tree with some initial values and store the results of the traversals.
 **/
class BinaryTreeEnvironment : public ::testing::Environment
{
public:
  static ddlib::BinaryTree<int> tree; // The tree to be used in the tests
  static std::vector<int> result; // Vector to store the results of the traversals

  void SetUp() override
  {
    result.reserve(16); // Reserve space for the 16 nodes in the tree

    // Set up the tree with some initial values
    tree.insert(17); // node #1
    tree.insert(14); // node #2
    tree.insert(26); // node #3
    tree.insert(11); // node #4
    tree.insert(12); // node #5
    tree.insert(15); // node #6
    tree.insert(24); // node #7
    tree.insert(27); // node #8
    tree.insert(10); // node #9
    tree.insert(8);  // node #10
    tree.insert(30); // node #11
    tree.insert(19); // node #12
    tree.insert(32); // node #13
    tree.insert(13); // node #14
    tree.insert(25); // node #15
    tree.insert(23); // node #16
  }

  // Tree structure:
  //                 17
  //            /          \
  //          14            26
  //        /    \        /    \
  //       11     15     24     27
  //      /  \          /  \      \
  //     10   12       19  25      30
  //    /       \        \          \
  //   8        13        23         32

  void TearDown(void) override
  {
    // Clean up if necessary
  }

  // Callback function to store the value of the node in the vector
  static void getNodeValue(const int& node_value)
  {
    result.push_back(node_value);
  }
};

// -- Static member variable definitions -- //

ddlib::BinaryTree<int> BinaryTreeEnvironment::tree;
std::vector<int> BinaryTreeEnvironment::result;

// -- Register the test environment -- //

BinaryTreeEnvironment* env = static_cast<BinaryTreeEnvironment*>(::testing::AddGlobalTestEnvironment(new BinaryTreeEnvironment)); // pointer is automatically deleted by Google Test

// -- Test Insertion and Search -- //

TEST(BinaryTreeTest, InsertAndSearch)
{
  ddlib::BinaryTree<int> tree;
  tree.insert(3);
  tree.insert(5);
  tree.insert(7);

  EXPECT_TRUE(tree.search(5));
  EXPECT_TRUE(tree.search(3));
  EXPECT_TRUE(tree.search(7));
  EXPECT_FALSE(tree.search(10));
}

TEST(BinaryTreeTest, Remove)
{
  ddlib::BinaryTree<int> tree;
  tree.insert(3);
  tree.insert(5);
  tree.insert(7);
  EXPECT_TRUE(tree.search(3));
  EXPECT_TRUE(tree.search(5));
  EXPECT_TRUE(tree.search(7));

  tree.remove(3);

  EXPECT_FALSE(tree.search(3));
  EXPECT_TRUE(tree.search(5));
  EXPECT_TRUE(tree.search(7));
}

// -- Test Comparable and Non-Comparable Types -- //

// Tests the insertion and search of a comparable type
TEST(BinaryTreeTest, InsertAndSearchComparable)
{
  ddlib::BinaryTree<TComparableType> tree;
  tree.insert(TComparableType(3));
  tree.insert(TComparableType(5));
  tree.insert(TComparableType(7));

  EXPECT_TRUE(tree.search(TComparableType(3)));
  EXPECT_TRUE(tree.search(TComparableType(5)));
  EXPECT_TRUE(tree.search(TComparableType(7)));
  EXPECT_FALSE(tree.search(TComparableType(10)));
}

// Tests the insertion of a non-comparable type
TEST(BinaryTreeTest, InsertNotComparable)
{
  // // This will not compile: type must implement the < operator. Uncomment the following lines to see the compilation error.
  // ddlib::BinaryTree<TNotComparableType> tree;
}

// Same as above, but with comparable type `std::string`
TEST(BinaryTreeTest, InsertAndSearchString)
{
  ddlib::BinaryTree<std::string> tree;
  tree.insert("hello");
  tree.insert("world");

  EXPECT_TRUE(tree.search("hello"));
  EXPECT_TRUE(tree.search("world"));
  EXPECT_FALSE(tree.search("foo"));
}

// -- Test Traversals -- //

// Tests the in-order traversal of the tree, i.e., left-root-right
TEST(BinaryTreeTest, InOrderTraversal)
{
  env->result.clear(); // Clear the vector before the traversal
  env->tree.inOrderTraversal(env->getNodeValue); // Perform the traversal

  std::vector<int> expected = { 8, 10, 11, 12, 13, 14, 15, 17, 19, 23, 24, 25, 26, 27, 30, 32 };
  EXPECT_EQ(env->result, expected);
}

// Tests the pre-order traversal of the tree, i.e., root-left-right
TEST(BinaryTreeTest, PreOrderTraversal)
{
  env->result.clear();
  env->tree.preOrderTraversal(env->getNodeValue);

  std::vector<int> expected = { 17, 14, 11, 10, 8, 12, 13, 15, 26, 24, 19, 23, 25, 27, 30, 32 };
  EXPECT_EQ(env->result, expected);
}

// Tests the post-order traversal of the tree, i.e., left-right-root
TEST(BinaryTreeTest, PostOrderTraversal)
{
  env->result.clear();
  env->tree.postOrderTraversal(env->getNodeValue);

  std::vector<int> expected = { 8, 10, 13, 12, 11, 15, 14, 23, 19, 25, 24, 32, 30, 27, 26, 17 };
  EXPECT_EQ(env->result, expected);
}

// Tests the level-order traversal of the tree, i.e., from top to bottom and from left to right
TEST(BinaryTreeTest, LevelOrderTraversal)
{
  env->result.clear();
  env->tree.levelOrderTraversal(env->getNodeValue);

  std::vector<int> expected = { 17, 14, 26, 11, 15, 24, 27, 10, 12, 19, 25, 30, 8, 13, 23, 32 };
  EXPECT_EQ(env->result, expected);
}

// -- Test Iterator -- //

// Creates an iterator on the root node, and checks if it is valid
TEST(BinaryTreeIteratorTest, IteratorInitialization)
{
  auto it = env->tree.getIterator();
  EXPECT_TRUE(it.isValid());
  EXPECT_EQ(it.getValue(), 17);
}

// Tests the movement of the iterator to the left child
TEST(BinaryTreeIteratorTest, MoveToLeftChild)
{
  auto it = env->tree.getIterator();
  EXPECT_TRUE(it.moveToLeftChild());
  EXPECT_EQ(it.getValue(), 14);
  EXPECT_TRUE(it.moveToLeftChild());
  EXPECT_EQ(it.getValue(), 11);
  EXPECT_TRUE(it.moveToLeftChild());
  EXPECT_EQ(it.getValue(), 10);
  EXPECT_TRUE(it.moveToLeftChild());
  EXPECT_EQ(it.getValue(), 8);
  EXPECT_FALSE(it.moveToLeftChild());
}

// Tests the movement of the iterator to the right child
TEST(BinaryTreeIteratorTest, MoveToRightChild)
{
  auto it = env->tree.getIterator();
  EXPECT_TRUE(it.moveToRightChild());
  EXPECT_EQ(it.getValue(), 26);
  EXPECT_TRUE(it.moveToRightChild());
  EXPECT_EQ(it.getValue(), 27);
  EXPECT_TRUE(it.moveToRightChild());
  EXPECT_EQ(it.getValue(), 30);
  EXPECT_TRUE(it.moveToRightChild());
  EXPECT_EQ(it.getValue(), 32);
  EXPECT_FALSE(it.moveToRightChild());
}

// Tests the validity of the iterator after moving it around
TEST(BinaryTreeIteratorTest, IteratorValidity)
{
  auto it_1 = env->tree.getIterator();
  EXPECT_TRUE(it_1.isValid());
  it_1.moveToLeftChild();
  it_1.moveToLeftChild();
  it_1.moveToRightChild();
  it_1.moveToRightChild();
  EXPECT_EQ(it_1.getValue(), 13);
  EXPECT_FALSE(it_1.moveToLeftChild());
  EXPECT_EQ(it_1.getValue(), 13);
  EXPECT_TRUE(it_1.isValid());

  auto it_2 = env->tree.getIterator();
  EXPECT_EQ(it_2.getValue(), 17);
  it_2.moveToRightChild();
  EXPECT_EQ(it_2.getValue(), 26);
  it_2.moveToLeftChild();
  EXPECT_EQ(it_2.getValue(), 24);
  it_2.moveToRightChild();
  EXPECT_EQ(it_2.getValue(), 25);
  EXPECT_FALSE(it_2.moveToRightChild());
  EXPECT_EQ(it_2.getValue(), 25);
  EXPECT_TRUE(it_2.isValid());

  auto it_3 = env->tree.getIterator();
  EXPECT_EQ(it_3.getValue(), 17);
  it_3.moveToLeftChild();
  EXPECT_EQ(it_3.getValue(), 14);
  it_3.moveToRightChild();
  EXPECT_EQ(it_3.getValue(), 15);
  EXPECT_FALSE(it_3.moveToLeftChild());
  EXPECT_TRUE(it_3.isValid());
}

// Tests the value of the nodes after moving the iterator around and setting new values
TEST(BinaryTreeIteratorTest, SetValue)
{
  auto it = env->tree.getIterator();
  EXPECT_EQ(it.getValue(), 17);

  it.setValue(42);
  EXPECT_NE(it.getValue(), 17);
  EXPECT_EQ(it.getValue(), 42);
  it.setValue(17); // Restore to the original value
  EXPECT_EQ(it.getValue(), 17);

  it.moveToLeftChild();
  EXPECT_EQ(it.getValue(), 14);

  it.setValue(99);
  EXPECT_NE(it.getValue(), 14);
  EXPECT_EQ(it.getValue(), 99);
  it.setValue(14); // Restore to the original value
  EXPECT_EQ(it.getValue(), 14);

  it.moveToRightChild();
  EXPECT_EQ(it.getValue(), 15);

  it.setValue(100);
  EXPECT_NE(it.getValue(), 15);
  EXPECT_EQ(it.getValue(), 100);
  it.setValue(15); // Restore to the original value
  EXPECT_EQ(it.getValue(), 15);

  // Perform a level-order traversal to check if the values were correctly set
  env->result.clear();
  env->tree.levelOrderTraversal(env->getNodeValue);

  std::vector<int> expected = { 17, 14, 26, 11, 15, 24, 27, 10, 12, 19, 25, 30, 8, 13, 23, 32 };
  EXPECT_EQ(env->result, expected);
}

// Tests if the current node is a leaf node
TEST(BinaryTreeIteratorTest, IsLeaf)
{
  auto it = env->tree.getIterator();
  EXPECT_FALSE(it.isLeaf()); // Root node is not a leaf
  it.moveToLeftChild();
  EXPECT_FALSE(it.isLeaf()); // Node 14 is not a leaf
  it.moveToLeftChild();
  EXPECT_FALSE(it.isLeaf()); // Node 11 is not a leaf
  it.moveToLeftChild();
  EXPECT_FALSE(it.isLeaf()); // Node 10 is not a leaf
  it.moveToLeftChild();
  EXPECT_TRUE(it.isLeaf()); // Node 8 is a leaf

  it = env->tree.getIterator(); // Reset the iterator to the root node
  it.moveToRightChild();
  EXPECT_FALSE(it.isLeaf()); // Node 26 is not a leaf
  it.moveToRightChild();
  EXPECT_FALSE(it.isLeaf()); // Node 27 is not a leaf
  it.moveToRightChild();
  EXPECT_FALSE(it.isLeaf()); // Node 30 is a leaf
  it.moveToRightChild();
  EXPECT_TRUE(it.isLeaf()); // Node 32 is a leaf
}

// Tests the creation of children for a leaf node
TEST(BinaryTreeIteratorTest, CreateChildren)
{
  auto it = env->tree.getIterator();
  it.moveToLeftChild(); // Move to node 14
  EXPECT_FALSE(it.isLeaf()); // Node 14 is not a leaf
  EXPECT_FALSE(it.createChildren(5, 9)); // Cannot create children for node 14, because it is not a leaf
  EXPECT_FALSE(env->tree.search(5)); // Value 5 must not be in the tree
  EXPECT_FALSE(env->tree.search(9)); // Value 9 must not be in the tree
  it.moveToLeftChild(); // Move to node 11
  it.moveToLeftChild(); // Move to node 10
  it.moveToLeftChild(); // Move to node 8 (leaf node)
  EXPECT_TRUE(it.isLeaf()); // Node 8 is a leaf
  EXPECT_TRUE(it.createChildren(5, 9)); // Create children for node 8
  EXPECT_FALSE(it.isLeaf()); // Node 8 is no longer a leaf
  it.moveToLeftChild();
  EXPECT_EQ(it.getValue(), 5); // Check left child value

  it = env->tree.getIterator(); // Restart from the root node
  it.moveToLeftChild(); // Move to node 14
  it.moveToLeftChild(); // Move to node 11
  it.moveToLeftChild(); // Move to node 10
  it.moveToLeftChild(); // Move to node 8
  it.moveToRightChild(); // Move to node 9
  EXPECT_EQ(it.getValue(), 9); // Check right child value

  // Check if the children were created
  EXPECT_TRUE(env->tree.search(5));
  EXPECT_TRUE(env->tree.search(9));

  // Remove children
  env->tree.remove(5);
  env->tree.remove(9);
  EXPECT_TRUE(it.isLeaf()); // Node 8 is a leaf again

  // Check if the children were removed
  EXPECT_FALSE(env->tree.search(5));
  EXPECT_FALSE(env->tree.search(9));
}

// Test insertion of children and move value of current node to right child
TEST(BinaryTreeIteratorTest, CreateChildrenAndMoveValue)
{
  auto it = env->tree.getIterator();
  it.moveToLeftChild(); // Move to node 14
  it.moveToLeftChild(); // Move to node 11
  it.moveToLeftChild(); // Move to node 10
  it.moveToLeftChild(); // Move to node 8

  // Create children for node 8. Left child will have value 5; right child will have value 8; current node (8) will be overwritten with value 7
  EXPECT_TRUE(it.createChildren(5, it.getValue()));
  it.setValue(7); // Replace value of node 8 (current node) with 7
  EXPECT_EQ(it.getValue(), 7); // Check current node value
  EXPECT_FALSE(it.isLeaf()); // Node 7 (formerly 8) is no longer a leaf

  auto it_go_left = it; // Copy the iterator, so that we can proceed both with the left and right children
  auto it_restore = it; // Copy the iterator to restore the former "8" node to its original value

  it.moveToRightChild(); // Move to node 8
  EXPECT_EQ(it.getValue(), 8); // Check right child value
  EXPECT_TRUE(it.isLeaf()); // Node 8 is a leaf

  it_go_left.moveToLeftChild(); // Move to node 5
  EXPECT_EQ(it_go_left.getValue(), 5); // Check left child value
  EXPECT_TRUE(it_go_left.isLeaf()); // Node 5 is a leaf

  // Remove children
  env->tree.remove(5);
  env->tree.remove(8);
  EXPECT_TRUE(it.isLeaf()); // Node 7 is a leaf again

  // Check if the children were removed
  EXPECT_FALSE(env->tree.search(5));
  EXPECT_FALSE(env->tree.search(8));

  // Restore the former "8" node to its original value
  it_restore.setValue(8);
  EXPECT_EQ(it_restore.getValue(), 8); // Check current node value
  EXPECT_TRUE(it_restore.isLeaf()); // Node 8 is a leaf again

  // Execute a level-order traversal to check that the tree structure is back to the original state
  env->result.clear();
  env->tree.levelOrderTraversal(env->getNodeValue);

  std::vector<int> expected = { 17, 14, 26, 11, 15, 24, 27, 10, 12, 19, 25, 30, 8, 13, 23, 32 };
  EXPECT_EQ(env->result, expected);
}

// -- Test Serialisation and Deserialisation -- //

TEST(BinaryTreeTestSerialisation, SerialiseAndDeserialise)
{
  ddlib::BinaryTree<int> tree;
  tree.insert(17);
  tree.insert(14);
  tree.insert(26);
  tree.insert(11);
  tree.insert(15);
  tree.insert(24);
  tree.insert(27);

  // Serialise the tree to a file
  std::string filename = "tree_serialised.dat";
  tree.serialise(filename);

  // Create a new tree and deserialise from the file
  ddlib::BinaryTree<int> new_tree;
  new_tree.deserialise(filename);

  // Check if the new tree has the same structure and values
  std::vector<int> original_result;
  std::vector<int> new_result;

  tree.levelOrderTraversal([&original_result](const int& value) { original_result.push_back(value); });
  new_tree.levelOrderTraversal([&new_result](const int& value) { new_result.push_back(value); });

  EXPECT_EQ(original_result, new_result);

  // Clean up the serialised file
  std::remove(filename.c_str());
}

TEST(BinaryTreeTestSerialisation, SerialiseAndDeserialiseStrings)
{
  ddlib::BinaryTree<std::string> tree;
  tree.insert("hello");
  tree.insert("world");
  tree.insert("foo");
  tree.insert("bar");

  // Serialise the tree to a file
  std::string filename = "tree_serialised_strings.dat";
  tree.serialise(filename);

  // Create a new tree and deserialise from the file
  ddlib::BinaryTree<std::string> new_tree;
  new_tree.deserialise(filename);

  // Find the values in the new tree
  EXPECT_TRUE(new_tree.search("hello"));
  EXPECT_TRUE(new_tree.search("world"));
  EXPECT_TRUE(new_tree.search("foo"));
  EXPECT_TRUE(new_tree.search("bar"));

  // Check if the new tree has the same structure and values
  std::vector<std::string> original_result;
  std::vector<std::string> new_result;

  tree.levelOrderTraversal([&original_result](const std::string& value) { original_result.push_back(value); });
  new_tree.levelOrderTraversal([&new_result](const std::string& value) { new_result.push_back(value); });

  EXPECT_EQ(original_result, new_result);

  // Clean up the serialised file
  std::remove(filename.c_str());
}

TEST(BinaryTreeTestSerialisation, SerialiseAndDeserialiseEmptyTree)
{
  ddlib::BinaryTree<int> tree;

  // Serialise the empty tree to a file
  std::string filename = "empty_tree_serialised.dat";
  tree.serialise(filename);

  // Create a new tree and deserialise from the file
  ddlib::BinaryTree<int> new_tree;
  new_tree.deserialise(filename);

  // Check if the new tree is empty
  EXPECT_FALSE(new_tree.search(0)); // Should not find any value
  EXPECT_FALSE(new_tree.search(1));
  EXPECT_TRUE(new_tree.isEmpty()); // Should be empty

  // Clean up the serialised file
  std::remove(filename.c_str());
}


// // Defining a `main` function in the test source file is optional for the Google Test framework, because it provides
// a default one that can be linked in CMakeLists.txt. A custom `main` function can be defined to run the tests in a
// specific order or to perform additional setup or teardown operations.
// int main(int argc, char **argv)
// {
//   ::testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }