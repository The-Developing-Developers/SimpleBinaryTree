cmake_minimum_required(VERSION 3.12)
project(SimpleBinaryTree VERSION 1.0.0 LANGUAGES CXX)

# Define the header-only library as an INTERFACE target. It does not produce any output. It is used to propagate usage
# requirements (such as include directories, compile options, and link libraries) to other targets that link against it.
add_library(${PROJECT_NAME} INTERFACE)

# Specify the include directory for the library as an INTERFACE target. Any project that links to this library will have this directory
# added to its include path.
target_include_directories(${PROJECT_NAME} INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR}/include/binarytree
)

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_20) # Specify the C++ standard for the target

# Option to build tests is OFF by default. You can override it by passing -DBUILD_TESTS=ON to CMake, or adding
# instruction `set(BUILD_TESTS ON)` in the parent `CMakeLists.txt`.
option(BUILD_TESTS "Build tests" OFF)

if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()