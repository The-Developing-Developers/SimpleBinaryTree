message("\n*** Configuring tests for ${PROJECT_NAME} library ***\n")

include(FetchContent) # Include the `FetchContent` module, used to download and unpack external projects at configure time.

# Download and unpack Google Test at configure time, only if needed.
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.15.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE) # Prevent overriding the parent project's compiler/linker settings on Windows

FetchContent_MakeAvailable(googletest) # Fetch the content

add_executable(test_binary_tree test_binary_tree.cpp) # Create an executable target called `test_binary_tree` from the source file `test_binary_tree.cpp`

target_link_libraries(test_binary_tree gtest_main SimpleBinaryTree) # Link the executable target to the Google Test library and the SimpleBinaryTree library

add_test(NAME test_binary_tree COMMAND test_binary_tree) # Add a test called `test_binary_tree` that runs the `test_binary_tree` executable