"""
Configuration Script for SimpleBinaryTree Project

This script contains the configuration of the project's paths, global variables, and various constant strings.

Modules:
    os: Provides a way of using operating system dependent functionality.
    platform: Provides a way to access underlying platform’s identifying data.

Classes:
    Config: Contains configuration variables for the project.
"""

import os
import platform

class Config:
  """
  This class contains the configuration of the project's paths, global variables and various constant strings.
  They are mostly in alphabetical order, except where some paths are dependent on others.
  """

  # ---- Project's paths ---- #

  PROJECT_NAME                : str = 'SimpleBinaryTree'

  NEWLINE_1                   : str = 'NEWLINE' # This is just a placeholder for a newline when printing the configuration variables
  DIRNAM_BUILD                : str = 'build'
  DIRNAM_DOCS                 : str = 'docs'
  DIRNAM_DOXYGEN              : str = 'doxygen'
  DIRNAM_INCLUDE              : str = 'include'
  DIRNAM_HTML                 : str = 'html'
  DIRNAM_PYTHON_BIN_LIN       : str = 'bin'
  DIRNAM_DEBUG                : str = 'debug'
  DIRNAM_RELEASE              : str = 'release'
  DIRNAM_PYTHON_BIN_WIN       : str = 'Scripts'
  DIRNAM_PYTHON_VENV          : str = 'venv'
  DIRNAM_REQUIREMENTS         : str = 'requirements'
  DIRNAM_SCRIPTS              : str = 'scripts'
  DIRNAM_SOURCE               : str = 'src'
  DIRNAM_TESTS                : str = 'tests'
  FILNAM_CMAKECACHE_TXT       : str = 'CMakeCache.txt'
  FILNAM_DOXYFILE             : str = 'Doxyfile'
  FILNAM_INDEX_HTML           : str = 'index.html'
  FILNAM_MAIN_PY              : str = 'main.py'
  FILNAM_REQUIREMENTS_TXT_LIN : str = DIRNAM_REQUIREMENTS + '_linux.txt'
  FILNAM_REQUIREMENTS_TXT_WIN : str = DIRNAM_REQUIREMENTS + '_win.txt'

  NEWLINE_2                   : str = 'NEWLINE' # This is just a placeholder for a newline when printing the configuration variables
  DIRFUL_REPOSITORY           : str = os.getcwd()
  DIRFUL_BUILD_BASE           : str = os.path.join(DIRFUL_REPOSITORY, DIRNAM_BUILD)
  DIRFUL_DEB_DIR_FINAL        : str = os.path.join(DIRFUL_BUILD_BASE, DIRNAM_DEBUG)
  DIRFUL_DOXYGEN              : str = os.path.join(DIRFUL_REPOSITORY, DIRNAM_DOCS, DIRNAM_DOXYGEN)
  DIRFUL_REL_DIR_FINAL        : str = os.path.join(DIRFUL_BUILD_BASE, DIRNAM_RELEASE)
  DIRFUL_SCRIPTS              : str = os.path.join(DIRFUL_REPOSITORY, DIRNAM_SCRIPTS)
  DIRFUL_REQUIREMENTS         : str = os.path.join(DIRFUL_SCRIPTS, DIRNAM_REQUIREMENTS)
  DIRFUL_TESTS_BUILD                : str = os.path.join(DIRFUL_REPOSITORY, DIRNAM_BUILD, DIRNAM_TESTS) # For example, '/home/user/Projects/SimpleBinaryTree/build/tests'
  DIRFUL_VENV                 : str = os.path.join(DIRFUL_REPOSITORY, DIRNAM_SCRIPTS, DIRNAM_PYTHON_VENV)
  DIRFUL_VENV_BIN_LIN         : str = os.path.join(DIRFUL_VENV, DIRNAM_PYTHON_BIN_LIN)
  DIRFUL_VENV_BIN_WIN         : str = os.path.join(DIRFUL_VENV, DIRNAM_PYTHON_BIN_WIN)
  FILFUL_CMAKE_CACHE_DEB      : str = os.path.join(DIRFUL_DEB_DIR_FINAL, FILNAM_CMAKECACHE_TXT)
  FILFUL_CMAKE_CACHE_REL      : str = os.path.join(DIRFUL_REL_DIR_FINAL, FILNAM_CMAKECACHE_TXT)
  FILFUL_DOXYFILE             : str = os.path.join(DIRFUL_DOXYGEN, FILNAM_DOXYFILE)
  FILFUL_DOXYGEN_OUTPUT_HTML    : str = os.path.join(DIRFUL_DOXYGEN, DIRNAM_BUILD, DIRNAM_HTML, FILNAM_INDEX_HTML)
  FILFUL_MAIN_PY              : str = os.path.join(DIRFUL_SCRIPTS, FILNAM_MAIN_PY)
  FILFUL_PYTHON_EXE_VENV_LIN  : str = os.path.join(DIRFUL_VENV_BIN_LIN, 'python')
  FILFUL_PYTHON_EXE_VENV_WIN  : str = os.path.join(DIRFUL_VENV_BIN_WIN, 'python')
  FILFUL_REQUIREMENTS_TXT_LIN : str = os.path.join(DIRFUL_REQUIREMENTS, FILNAM_REQUIREMENTS_TXT_LIN)
  FILFUL_REQUIREMENTS_TXT_WIN : str = os.path.join(DIRFUL_REQUIREMENTS, FILNAM_REQUIREMENTS_TXT_WIN)

  # ---- Various constant strings ---- #

  NEWLINE_3                   : str = 'NEWLINE' # This is just a placeholder for a newline when printing the configuration variables
  BUILD_CONFIG_DEBUG          : str = 'Debug'
  BUILD_CONFIG_RELEASE        : str = 'Release'
  PLATFORM_SYSTEM             : str = platform.system()
  PLATFORM_RELEASE            : str = platform.release()
  PLATFORM_VERSION            : str = platform.version()
  PLATFORM_NOT_RECOGNISED_STR : str = 'Error: platform not recognised.'
  TESTING_TYPE_NORMAL         : str = 'normal'
  TESTING_TYPE_VERBOSE        : str = 'verbose'
  TESTING_TYPE_ONLY_FAILED    : str = 'onlyFailed'
  TESTING_PARAM_VERBOSE       : str = '-VV'
  TESTING_PARAM_RERUN_FAILED  : str = '--rerun-failed'
  TESTING_PARAM_OUT_ON_FAILURE: str = '--output-on-failure'
