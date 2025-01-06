<!-- omit in toc -->
# Simple C++ Binary Tree

- [Description](#description)
- [How to Build or Integrate](#how-to-build-or-integrate)
  - [Method 1. Build Scripts](#method-1-build-scripts)
    - [Prerequisites](#prerequisites)
    - [Invoking the Scripts](#invoking-the-scripts)
      - [1. Setup Script](#1-setup-script)
      - [2. Launcher Script](#2-launcher-script)
    - [Tests Executable](#tests-executable)
  - [Method 2. CMake](#method-2-cmake)
- [Documentation](#documentation)
  - [Prerequisites](#prerequisites-1)
  - [Generating the Documentation](#generating-the-documentation)


# Description

This repository contains a very simple C++ binary tree class. It was originally developed as a part of the "guess the animal" game, but it can be used for any purpose that requires a simplified binary tree data structure.


# How to Build or Integrate

This binary tree is a header-only library. You can either:
1. Clone this repository and use the provided [build scripts](#method-1-build-scripts) (requires Python, Pip and CMake) to build the [tests](#tests-executable) and see how to use the binary tree.
2. Include this repository as a submodule of your project, and build your project with CMake.

In either case, you can use the binary tree in your source code by including the `binary_tree.h` header file in your project, and creating a binary tree object using the `BinaryTree` class defined in the `ddlib` namespace.


## Method 1. Build Scripts

If you are just interested in building the [tests executable](#tests-executable), you can use the provided Python scripts. The scripts will create a virtual environment, install the required Python modules, compile the test program, and create an executable file under the `build/tests` directory (may vary according to the build system used).

### Prerequisites

The Python scripts require:
- **Python 3.8** or later.
- **Pip** package manager.
- **CMake 3.12** or later.

### Invoking the Scripts

**Note:** The following instructions assume that you are in the **root directory** of the Simple Binary Tree repository.

Follow these steps to build and run the test program using the provided Python scripts:
1. Call the [setup script](#1-setup-script) to create a virtual environment and install the required Python modules.
2. Call the [launcher script](#2-launcher-script) to build and run the test program.

#### 1. Setup Script

Invoke the `setup.py` script from the **root directory** of the Simple Binary Tree repository:
- Linux / MacOS:
  ```
  python3 ./scripts/setup.py
  ```
- Windows:
  ```PowerShell
  python .\scripts\setup.py
  ```

#### 2. Launcher Script

Call the `launcher.py` script from the **root directory** with option `-h` to see the available options. You would typically use the `-p` option to prepare the build files, the `-b` option to build the project, and the `-t` option to run the test program.

When preparing the build files with the `-p` option, the script will autodetect the platform and use the appropriate build system generator. If you want, you can override the auto-detected generator and specify one of your choice by passing the name of the desired generator. For example, if you want to prepare the build files with the Unix Makefiles generator, you can run the following commands:
- Linux / MacOS:
  ```bash
  python3 ./scripts/launcher.py -p -G "Unix Makefiles"
  python3 ./scripts/launcher.py -b
  python3 ./scripts/launcher.py -t
  ```
- Windows (using MinGW as generator):
  ```PowerShell
  python .\scripts\launcher.py -p -G "MinGW Makefiles"
  python .\scripts\launcher.py -b
  python .\scripts\launcher.py -t
  ```

### Tests Executable

The tests are built from a [test source file](tests/test_binary_tree.cpp), based on Google Test, that also demonstrates how to use the binary tree.

- When using [Method 1](#method-1-build-scripts), the test program is built by default when invoking the `launcher.py` script with the `-b` option.
- When using [Method 2](#method-2-cmake), building the test program is disabled, so that it does not automatically download Google Test and create unnecessary artefacts in your project.

You can enable building the test program by setting the `BUILD_TESTS` option to `ON` in your project's `CMakeLists.txt` file, or by passing the `-DBUILD_TESTS=ON` option to the `cmake` command.

The test executable will be created in a subdirectory according to the build system used. For example:
- If you built the project with MSVC, you can find the executable in the `build/tests/Debug` directory.
- If you built the project with MinGW or GCC, you can find the executable in the `build/tests` directory.

Alternatively, you can execute the test program invoking the `launcher.py` script with the `-t` option:

```bash
python3 ./scripts/launcher.py -t
```


## Method 2. CMake

This project includes a `CMakeLists.txt` file that can be used to integrate the binary tree as a dependency in your project.
To use the binary tree in your project, you can clone and add it as a submodule in your project, and include the binary tree's root `CMakeLists.txt` file in your project's `CMakeLists.txt` file with an `add_subdirectory` command. The binary tree's own `CMakeLists.txt` file will automatically make itself available to your project, so that you can include it in your project's target.

```bash
git submodule add https://github.com/The-Developing-Developers/SimpleBinaryTree.git
git submodule update --init --recursive
```

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


# Documentation

The documentation for this project is generated with Doxygen.

## Prerequisites

- [Doxygen](https://www.doxygen.nl/download.html)
- [Graphviz](https://graphviz.org/download/) (required for generating diagrams)

## Generating the Documentation

You can generate the documentation by running the `doxygen Doxyfile` command in the `docs/doxygen` directory of the repository. The generated documentation will be placed in the `output` subdirectory.

```bash
cd docs/doxygen
doxygen Doxyfile
```