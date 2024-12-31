/**
 * @file test_binary_tree.cpp
 * @brief Unit tests for the `BinaryTree` class.
 **/

#include "binary_tree.h"
#include "t_comparable_type.h"
#include <gtest/gtest.h>
#include <vector>
#include <string>

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

  it.moveToLeftChild();
  EXPECT_EQ(it.getValue(), 14);

  it.setValue(99);
  EXPECT_NE(it.getValue(), 14);
  EXPECT_EQ(it.getValue(), 99);

  it.moveToRightChild();
  EXPECT_EQ(it.getValue(), 15);

  it.setValue(100);
  EXPECT_NE(it.getValue(), 15);
  EXPECT_EQ(it.getValue(), 100);
}

// // Defining a `main` function in the test source file is optional for the Google Test framework, because it provides
// a default one that can be linked in CMakeLists.txt. A custom `main` function can be defined to run the tests in a
// specific order or to perform additional setup or teardown operations.
// int main(int argc, char **argv)
// {
//   ::testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }