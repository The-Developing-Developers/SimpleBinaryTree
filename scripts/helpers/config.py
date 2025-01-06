# This script contains the configuration of the project's paths, global variables and various constant strings.

import os
import platform

# ---- Project's paths ---- #

PROJECT_NAME          : str = 'SimpleBinaryTree'
INCLUDE_FILES_SUBDIR  : str = 'include'
SOURCE_FILES_SUBDIR   : str = 'src'
BUILD_SUBDIR          : str = 'build'
TESTS_SUBDIR          : str = 'tests'
DOXYGEN_SUBDIR        : str = os.path.join('docs', 'doxygen')
DOXYGEN_INDEX_HTML    : str = os.path.join(DOXYGEN_SUBDIR, 'output', 'html', 'index.html')
PROJECT_FULLDIR       : str = os.getcwd() # For example, '/home/user/Projects/SimpleBinaryTree'
BUILD_FULLDIR         : str = os.path.join(PROJECT_FULLDIR, BUILD_SUBDIR) # For example, '/home/user/Projects/SimpleBinaryTree/build'
TESTS_FULLDIR         : str = os.path.join(PROJECT_FULLDIR, BUILD_SUBDIR, TESTS_SUBDIR) # For example, '/home/user/Projects/SimpleBinaryTree/build/tests'
CMAKECACHE_TXT_FILE   : str = os.path.join('build', 'CMakeCache.txt')

# ---- Various constant strings ---- #

PLATFORM_SYSTEM             : str = platform.system()
PLATFORM_RELEASE            : str = platform.release()
PLATFORM_VERSION            : str = platform.version()
PLATFORM_NOT_RECOGNISED_STR : str = 'Error: platform not recognised.'
TESTING_TYPE_NORMAL         : str = 'normal'
TESTING_TYPE_VERBOSE        : str = 'verbose'
TESTING_TYPE_ONLY_FAILED    : str = 'onlyFailed'
