/**
 * @file test_binary_tree.cpp
 * @brief Unit tests for the `BinaryTree` class.
 **/

#include "binary_tree.h"
#include "comparable.h"
#include <gtest/gtest.h>

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

TEST(BinaryTreeTest, InsertAndSearchComparable)
{
  ddlib::BinaryTree<Comparable> tree;
  tree.insert(Comparable(3));
  tree.insert(Comparable(5));
  tree.insert(Comparable(7));

  EXPECT_TRUE(tree.search(Comparable(3)));
  EXPECT_TRUE(tree.search(Comparable(5)));
  EXPECT_TRUE(tree.search(Comparable(7)));
  EXPECT_FALSE(tree.search(Comparable(10)));
}

TEST(BinaryTreeTest, InsertNotComparable)
{
  // // This will not compile: type must implement the < operator. Uncomment the following lines to see the compilation error.
  // ddlib::BinaryTree<NotComparable> tree;
}

// // Defining a `main` function in the test source file is optional for the Google Test framework, because it provides
// a default one that can be linked in CMakeLists.txt. A custom `main` function can be defined to run the tests in a
// specific order or to perform additional setup or teardown operations.
// int main(int argc, char **argv)
// {
//   ::testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }