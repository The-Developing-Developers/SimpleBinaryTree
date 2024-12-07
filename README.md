<!-- omit in toc -->
# Simple C++ Binary Tree

- [Description](#description)
- [How to Use](#how-to-use)
  - [Method 1. Copy the Files](#method-1-copy-the-files)
  - [Method 2. CMake](#method-2-cmake)
- [Tests Executable](#tests-executable)
  - [Build Script](#build-script)
    - [Invoking the Build Script](#invoking-the-build-script)


# Description

This repository contains a very simple C++ binary tree class. It was originally developed as a part of the "guess the animal" game, but it can be used for any purpose that requires a simplified binary tree data structure.


# How to Use

This binary tree is a header-only library. You can either:
1. Copy the `binarytree` directory (found under `include`) to your project.
2. Include this repository as a submodule of your project, and build with CMake.

In either case, you can use the binary tree in your source code by including the `binary_tree.h` header file in your project, and creating a binary tree object using the `BinaryTree` class defined in the `ddlib` namespace.


## Method 1. Copy the Files

You just need to copy the `binarytree` directory to any directory in your project, and update your build system to include the directory in the include paths. Then, include the `binary_tree.h` header file in your project where you want to use the binary tree. You can find the `binarytree` directory under the `include` directory of this repository.


## Method 2. CMake

This project includes a `CMakeLists.txt` file that can be used to include the binary tree as a dependency in your project.
To use the binary tree in your project, you can clone and add it as a submodule in your project, and include the binary tree's root `CMakeLists.txt` file in your project's `CMakeLists.txt` file with an `add_subdirectory` command. The binary tree's own `CMakeLists.txt` file will automatically make itself available to your project, so that you can include it in your project's target.

For example, supposing you have cloned the Simple Binary Tree repository as a submodule in the `external/binarytree` directory, you just need to add the following lines in your project's `CMakeLists.txt` file:

```CMake
add_subdirectory(external/binarytree)
target_link_libraries(your_project_name PRIVATE SimpleBinaryTree)
```

- The `add_subdirectory(external/binarytree)` line should be added after defining the project and before defining any targets that depend on the binary tree.
- The `target_link_libraries(your_project_name PRIVATE SimpleBinaryTree)` line should be added after defining the target that will use the binary tree.
- Replace `your_project_name` with the name of the target that will use the binary tree.

Here is a minimalistic example of how it should be structured:

```CMake
cmake_minimum_required(VERSION 3.12)
project(your_project_name VERSION 1.0.0 LANGUAGES CXX)

# Add the binary tree subdirectory
add_subdirectory(external/binarytree)

# Define your target
add_executable(${PROJECT_NAME} main.cpp)

# Link the binary tree library to your target
target_link_libraries(${PROJECT_NAME} PRIVATE SimpleBinaryTree)
```

# Tests Executable

This repository includes a [test program](tests/test_binary_tree.cpp), built with Google Test, that also demonstrates how to use the logger.

Building the test program is disabled by default, so that it does not automatically download Google Test and create unnecessary artefacts in your project.

You can enable building the test program by setting the `BUILD_TESTS` option to `ON` in your project's `CMakeLists.txt` file, or by passing the `-DBUILD_TESTS=ON` option to the `cmake` command. As a simpler alternative, consider using the provided [Python build script](#build-script) to build the test program.

The test executable will be created in a subdirectory according to the build system used. For example:
- If you built the project with MSVC, you can find the executable in the `build/tests/Debug` directory.
- If you built the project with MinGW or GCC, you can find the executable in the `build/tests` directory.

Alternatively, you can navigate to the `tests` directory and invoke `ctest` to run the tests.


## Build Script

If you are just interested in building the test program, you can use the provided Python script. The script will compile the program and create an executable file under the `build` directory (may vary according to the build system used).

The build script will autodetect the platform and use the appropriate build system generator. You can also specify the generator to use by passing the name of the generator.

**WARNING**: The Python script requires:
- **Python 3.8** or later.
- **CMake 3.12** or later.


### Invoking the Build Script

Invoke the script from the root directory of the Simple Binary Tree repository:
- Linux / MacOS:
  ```
  python3 ./scripts/build.py
  ```
- Windows:
  ```PowerShell
  python .\scripts\build.py
  ```

For example, if you wish to specify the generator to be used by CMake, you can pass the generator name as an argument to the script:
- Linux / MacOS:
  ```
  python3 ./scripts/build.py "Unix Makefiles"
  ```
- Windows:
  ```PowerShell
  python .\scripts\build.py "Visual Studio 16 2019"
  ```