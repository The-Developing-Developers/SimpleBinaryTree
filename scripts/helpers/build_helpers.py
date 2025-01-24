# Helpers for `build.py` script.

import inspect
import os
import subprocess
import shutil
import sys

from termcolor  import colored
from .utils     import raise_runtime_error, print_successful_event, print_white_on_blue, print_executing_command, print_config_variables
from .config    import Config as cfg

# ---- Functions definitions ---- #

def assign_and_display_project_paths():
  '''
  Assigns and displays the project's paths based on the platform.

  This function assigns the project's variable paths based on the platform (Linux, Darwin, or Windows) and displays
  them. If the platform is not recognized, it quits with an error message.
  '''

  # This project uses the Config class to store all the configuration variables. No project-specific paths are determined at run-time.

  if cfg.PLATFORM_SYSTEM == 'Windows':
    PROJECT_PATH: str = cfg.DIRFUL_REPOSITORY + '\\' # The project's root directory, withouth the trailing backslash
  elif cfg.PLATFORM_SYSTEM in ['Linux', 'Darwin']:
    PROJECT_PATH: str = cfg.DIRFUL_REPOSITORY + '/' # The project's root directory, withouth the trailing slash
  else:
    raise_runtime_error(cfg.PLATFORM_NOT_RECOGNISED_STR)

  print('Project\'s ' + colored('paths', 'yellow') + ' and ' + colored('files', 'cyan') + ':\n')
  print('  - Repository ' + colored('root', 'cyan') +  '                   directory    is: ' + colored(cfg.DIRFUL_REPOSITORY, 'green'))
  print('  - Project    ' + colored('build base', 'cyan') +  '             subdirectory is: ' + colored(cfg.DIRFUL_BUILD_BASE.replace(PROJECT_PATH, ''), 'green'))
  print('  - Project    ' + colored('debug CMakeCache.txt', 'green') + '   file path    is: ' + colored(cfg.FILFUL_CMAKE_CACHE_DEB.replace(PROJECT_PATH, ''), 'cyan'))
  print('  - Project    ' + colored('release CMakeCache.txt', 'green') + ' file path    is: ' + colored(cfg.FILFUL_CMAKE_CACHE_REL.replace(PROJECT_PATH, ''), 'cyan'))
  print('  - Project    ' + colored('testing build output', 'cyan') +  '   subdirectory is: ' + colored(cfg.DIRFUL_TESTS_BUILD.replace(PROJECT_PATH, ''), 'green'))
  print()


def print_args_and_interpreter():
  '''
  Prints the command-line arguments and the Python interpreter information.

  This function prints the command-line arguments passed to the script and the path to the Python interpreter.
  '''

  print('This script has been called with the following arguments:')
  for idx, argument in enumerate(sys.argv):
    print('  - Argument #' + str(idx) + ' is: ' + colored(argument, 'green'))
  print('The Python interpreter is: ' + colored(sys.executable, 'yellow'))
  print()


def print_help():
  '''
  Prints the help message with a list of legal parameters.

  This function prints a help message that lists all the legal parameters and their descriptions.
  '''

  print('List of ' + colored('legal parameters', 'yellow') + ':')
  print('Parameter                     Description')
  print('---------                     -----------')
  print('-h,    --help                 This help')
  print()
  print('-path, --print-all-paths      Prints all the paths used by the project (used for debugging purposes)')
  print()
  print('-bt,    --buildTests           Build the tests')
  print('-bd,    --buildDoc             Build the Doxygen documentation')
  print()
  print('-cc,   --cleanCache           Clean the project\'s Cache (Removes `' + colored('CMakeCache.txt', 'yellow') + '`)')
  print('-cp,   --cleanProject         Clean the project')
  print()
  print('-d,    --doxyDoc              Open the Doxygen documentation in the default browser')
  print()
  print('-p,    --prepareBuildFiles    Prepare build files for the tests. CMake will use the default generator')
  print('-p -G \"Generator\"             Prepare build files for the tests, specifying the generator (for example, \"Unix Makefiles\")')
  print()
  print('-r,    --removeBuildDir       Remove build directory')
  print()
  print('-t,    --test                 Run tests')
  print('-tv,   --testVerbose          Run tests verbosely')
  print('-tf,   --testFailed           Re-run only failed tests')
  print()


def print_paths():
  '''
  Prints all the paths used by the project.

  This function prints a list of all the paths used by the project, including directories and files.
  '''

  print('List of all ' + colored('paths', 'yellow') + ' used by this project:\n')
  print_config_variables()


def execute_user_choice():
  user_choice: str = ''
  generator:   str = None

  if len(sys.argv) > 1:
    user_choice = sys.argv[1]

  if user_choice == '' or user_choice == '--help' or user_choice == '-h':
    print_help()
    return

  if user_choice == '-path' or user_choice == '--print-all-paths':
    print_paths()
    return

  if user_choice == '--buildTests' or user_choice == '-bt':
    build_tests()
  elif user_choice == '--buildDoc' or user_choice == '-bd':
    build_documentation()
  elif user_choice == '--cleanCache' or user_choice == '-cc':
    clean_cache()
  elif user_choice == '--cleanProject' or user_choice == '-cp':
    clean_project()
  elif user_choice == '--doxyDoc' or user_choice == '-d':
    open_documentation()
  elif user_choice == '--prepareBuildFiles' or user_choice == '-p':
    # Check for the -G option to specify the generator
    if '-G' in sys.argv:
      generator_index = sys.argv.index('-G') + 1 # Get the index of the generator string, such as 'Ninja'
      if generator_index < len(sys.argv): # Check if the index is within the bounds of the list
        generator = sys.argv[generator_index] # Get the generator string
    prepare_build_files(generator)
  elif user_choice == '--removeBuildDir' or user_choice == '-r':
    remove_build_dir()
  elif user_choice == '--test' or user_choice == '-t':
    test_project(cfg.TESTING_TYPE_NORMAL)
  elif user_choice == '--testVerbose' or user_choice == '-tv':
    test_project(cfg.TESTING_TYPE_VERBOSE)
  elif user_choice == '--testFailed' or user_choice == '-tf':
    test_project(cfg.TESTING_TYPE_ONLY_FAILED)
  else:
    print(colored('ERROR', 'red') + ': argument ' + colored(user_choice, 'red') + ' not recognised.\n')
    print_help()
    return


def prepare_build_files(generator: str = None):
  print(colored("\nPreparing build files...", 'cyan'))
  COMMAND: list[str] = ['cmake', '-S', '.', '-B', cfg.DIRNAM_BUILD, '-DBUILD_TESTS=ON']
  if generator:
    print('\nUsing the ' + colored('user-specified generator', 'yellow') + ': ' + colored(generator, 'cyan'))
    COMMAND.extend(['-G', generator])
  print("\nExecuting command: " + colored(' '.join(COMMAND), 'yellow'))

  try:
    subprocess.run(COMMAND, check = True)
  except Exception as ex:
    print(ex)
    raise_runtime_error(f'Error preparing configuration files:\n{ex}')

  print()
  print_successful_event('Project build files prepared successfully.')


def build_tests():
  """
  Builds the tests for the project.
  """

  print_white_on_blue('Building tests...')

  if not os.path.exists(cfg.DIRNAM_BUILD):
    raise_runtime_error(f': directory ' + colored(cfg.DIRNAM_BUILD, 'yellow') + ' does not exist. Try preparing build files first.')

  COMMAND: list[str] = ['cmake', '--build', cfg.DIRNAM_BUILD, '-j8']
  print_executing_command(COMMAND, os.getcwd())

  try:
    subprocess.run(COMMAND, check = True)
  except Exception as ex:
    raise_runtime_error(f'Error building tests:\n{ex}. Try preparing build files first.')

  print()
  print_successful_event('Tests built successfully.')


def build_documentation():
  """
  Builds the documentation for the project.
  """

  print_white_on_blue('Building documentation...')

  if shutil.which(cfg.DIRNAM_DOXYGEN) is None:
    raise_runtime_error('Doxygen is not installed, or the executable is not in the ' + colored('PATH', 'yellow') + ' environment variable.')

  # Check if the Doxyfile exists
  if not os.path.exists(cfg.FILFUL_DOXYFILE):
    raise_runtime_error('File ' + colored(cfg.FILFUL_DOXYFILE, 'cyan') + ' does not exist.')

  os.chdir(cfg.DIRFUL_DOXYGEN)  # Change directory so that the COMMAND is executed in the correct directory
  COMMAND: list[str] = ['doxygen', 'Doxyfile']

  try:
    print_executing_command(COMMAND, os.getcwd())
    subprocess.run(COMMAND, check = True)
  except Exception as ex:
    raise_runtime_error(f'Error building documentation:\n{ex}')

  print_successful_event('Documentation built successfully.')


# Open Doxygen documentation in the default browser
def open_documentation():
  '''
  Opens the documentation in the default web browser.
  '''

  print_white_on_blue(f'Opening documentation...')

  if not os.path.exists(cfg.FILFUL_DOXYGEN_OUTPUT_HTML):
    raise_runtime_error(f'File {colored(cfg.FILFUL_DOXYGEN_OUTPUT_HTML, "cyan")} does not exist. Try building the documentation first.')

  if cfg.PLATFORM_SYSTEM == 'Linux':
    COMMAND: list[str] = ['xdg-open', cfg.FILFUL_DOXYGEN_OUTPUT_HTML]
  elif cfg.PLATFORM_SYSTEM == 'Darwin':
    COMMAND: list[str] = ['open', cfg.FILFUL_DOXYGEN_OUTPUT_HTML]
  elif cfg.PLATFORM_SYSTEM == 'Windows':
    COMMAND: list[str] = ['start', cfg.FILFUL_DOXYGEN_OUTPUT_HTML]
  else:
    raise_runtime_error(cfg.PLATFORM_NOT_RECOGNISED_STR)

  print_executing_command(COMMAND, os.getcwd())
  try:
    if cfg.PLATFORM_SYSTEM == 'Windows':
      subprocess.run(COMMAND, shell = True, check = True)  # `shell = True` is needed for Windows
    else:
      subprocess.run(COMMAND, check = True)
  except Exception as ex:
    raise_runtime_error(f'Error opening documentation:\n{ex}')

  print()
  print_successful_event(f'Documentation opened successfully.')


def clean_project():
  '''
  Cleans the project by removing build artifacts.
  '''

  print_white_on_blue('Cleaning project...')

  if not os.path.exists(cfg.DIRNAM_BUILD):
    raise_runtime_error(f'Error cleaning project: path {colored(cfg.DIRNAM_BUILD, "yellow")} does not exist.')

  COMMAND: list[str] = ['cmake', '--build', cfg.DIRNAM_BUILD, '--target', 'clean']
  print_executing_command(COMMAND, os.getcwd())

  try:
    subprocess.run(COMMAND, check = True)
  except Exception as ex:
    raise_runtime_error(f'Error cleaning project:\n{ex}')

  print_successful_event(colored(cfg.DIRNAM_BUILD, 'yellow') + ' directory has been cleaned.')


def clean_cache(user_config_choice: str = cfg.BUILD_CONFIG_DEBUG):
  '''
  Cleans the project's cache for the specified configuration.
  '''

  print_white_on_blue('Cleaning project cache...')

  if user_config_choice == cfg.BUILD_CONFIG_DEBUG:
    CMAKE_CACHE_PATH_FINAL: str = cfg.FILFUL_CMAKE_CACHE_DEB
  elif user_config_choice == cfg.BUILD_CONFIG_RELEASE:
    CMAKE_CACHE_PATH_FINAL: str = cfg.FILFUL_CMAKE_CACHE_REL

  print('\nAttempting to remove ' + colored(CMAKE_CACHE_PATH_FINAL, 'cyan') + '...')
  if not os.path.exists(CMAKE_CACHE_PATH_FINAL):
    raise_runtime_error('Error cleaning project cache: file ' + colored(CMAKE_CACHE_PATH_FINAL, 'cyan') + ' does not exist.')

  try:
    os.remove(CMAKE_CACHE_PATH_FINAL)
  except Exception as ex:
    raise_runtime_error(f'Error trying to remove file ' + colored(CMAKE_CACHE_PATH_FINAL, 'cyan') + f':\n{ex}')

  print()
  print_successful_event('File ' + colored(CMAKE_CACHE_PATH_FINAL, 'cyan') + ' has been removed.')


def remove_build_dir():
  '''
  Removes the build directory.
  '''

  print_white_on_blue('Removing build directory...')
  print()

  if not os.path.exists(cfg.DIRFUL_BUILD_BASE):
    raise_runtime_error('Directory ' + colored(cfg.DIRFUL_BUILD_BASE, 'yellow') + ' does not exist.')

  try:
    shutil.rmtree(cfg.DIRFUL_BUILD_BASE) # First attempt: use shutil.rmtree() to remove the build directory recursively
  except Exception as ex1:
    # shutil.rmtree() may unexpectedly fail on Windows due to a file lock. If this happens, try to remove the directory using command line instructions.
    print(colored('Error', 'red') + ' using ' + colored('shutil.rmtree', 'cyan') + f':\n{ex1}')

    try:
      print()
      print_white_on_blue('Now trying with command line instructions...')

      if cfg.PLATFORM_SYSTEM in ['Linux', 'Darwin']:
        COMMAND: list[str] = ['rm', '-rf', cfg.DIRFUL_BUILD_BASE]
      elif cfg.PLATFORM_SYSTEM == 'Windows':
        COMMAND = ['powershell', '-Command', f'Remove-Item -Recurse -Force {cfg.DIRFUL_BUILD_BASE}']
      else:
        raise_runtime_error(cfg.PLATFORM_NOT_RECOGNISED_STR)

      print_executing_command(COMMAND, os.getcwd())
      subprocess.run(COMMAND, check = True)
    except Exception as ex2:
      # Command line instructions also failed
      raise_runtime_error('Error using command line instructions to remove directory ' + colored(cfg.DIRFUL_BUILD_BASE, 'yellow') + f':\n{ex2}')

  print_successful_event('Directory ' + colored(cfg.DIRFUL_BUILD_BASE, 'yellow') + ' has been removed.')


def test_project(testing_type: str = cfg.TESTING_TYPE_NORMAL):
  '''
  Tests the project with the specified testing type TODO: and code coverage option.
  '''

  print_white_on_blue('Testing project...')

  if not os.path.exists(cfg.DIRFUL_TESTS_BUILD):
    raise_runtime_error('Testing subdirectory ' + colored(cfg.DIRFUL_TESTS_BUILD, 'yellow') + ' does not exist. Try preparing and building the debug configuration first.')

  parameter: list[str] = []

  if testing_type == cfg.TESTING_TYPE_VERBOSE:
    parameter.append(cfg.TESTING_PARAM_VERBOSE)
  elif testing_type == cfg.TESTING_TYPE_ONLY_FAILED:
    parameter.append(cfg.TESTING_PARAM_RERUN_FAILED)
    parameter.append(cfg.TESTING_PARAM_OUT_ON_FAILURE)

  if not os.path.exists(cfg.DIRFUL_TESTS_BUILD):
    raise_runtime_error('Testing subdirectory ' + colored(cfg.DIRFUL_TESTS_BUILD, 'yellow') + ' does not exist. Try preparing and building the debug configuration first.')

  os.chdir(cfg.DIRFUL_TESTS_BUILD)

  try:
    COMMAND: list[str] = ['ctest'] + parameter
    print_executing_command(COMMAND, os.getcwd())
    subprocess.run(COMMAND, check = True)
  except Exception as ex:
    print()
    print(colored('ERROR', 'white', 'on_red')+ f': initial testing failed:\n{ex}')
    print()
    print_white_on_blue('Re-running failed tests only...')
    parameter = [cfg.TESTING_PARAM_RERUN_FAILED, cfg.TESTING_PARAM_OUT_ON_FAILURE]
    COMMAND: list[str] = ['ctest'] + parameter
    print_executing_command(COMMAND, os.getcwd())

    try:
      subprocess.run(COMMAND, check = True)
    except Exception as ex:
      print()
      print(colored('ERROR', 'white', 'on_red') + f': some tests failed.')
      return # If the re-run fails, return without raising an exception, to avoid triggering other error messages

  print()
  print_successful_event('Testing was successful.')

  # TODO: Implement code coverage
  # if run_code_coverage:
  #   run_code_coverage_tool()
