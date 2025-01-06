# Helpers for `build.py` script.

import inspect
import os
import subprocess
import shutil
import sys

from   termcolor import cprint, colored
from .           import utils  as utl
from .           import config as cfg

# ---- Functions definitions ---- #

def assign_and_display_project_paths():
  print('Project\'s '     + colored('paths', 'yellow') + ':')
  print('  - Repository ' + colored('root', 'cyan') + '                 directory    is: ' + colored(cfg.PROJECT_FULLDIR, 'green'))
  print('  - Project    '    + colored('build base', 'cyan') + '           subdirectory is: ' + colored(cfg.BUILD_FULLDIR.replace(cfg.PROJECT_FULLDIR, ''), 'green'))
  print('  - Project    '    + colored('CMakeCache.txt', 'cyan') + '       path         is: ' + colored(cfg.CMAKECACHE_TXT_FILE.replace(cfg.PROJECT_FULLDIR, ''), 'green'))
  print('  - Project    '    + colored('testing build output', 'cyan') + ' subdirectory is: ' + colored(cfg.TESTS_FULLDIR.replace(cfg.PROJECT_FULLDIR, ''), 'green'))
  print()


def print_args_and_interpreter():
  print('This script has been called with the following arguments:')
  for idx, argument in enumerate(sys.argv):
    print('  - Argument #' + str(idx) + ' is: ' + colored(argument, 'green'))
  print('The Python interpreter is: ' + colored(sys.executable, 'yellow'))
  print()


def print_help():
  print('List of ' + colored('legal parameters', 'yellow') + ':')
  print('Parameter                     Description')
  print('---------                     -----------')
  print('-h,    --help                 This help')
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
  return


def print_paths():
  print('List of all ' + colored('paths', 'yellow') + ' used by this project:')
  print(colored('PROJECT_NAME        ', 'cyan') + ': ' + cfg.PROJECT_NAME)
  print(colored('INCLUDE_FILES_SUBDIR', 'cyan') + ': ' + cfg.INCLUDE_FILES_SUBDIR)
  print(colored('SOURCE_FILES_SUBDIR ', 'cyan') + ': ' + cfg.SOURCE_FILES_SUBDIR)
  print(colored('BUILD_SUBDIR        ', 'cyan') + ': ' + cfg.BUILD_SUBDIR)
  print(colored('TESTS_SUBDIR        ', 'cyan') + ': ' + cfg.TESTS_SUBDIR)
  print(colored('PROJECT_FULLDIR     ', 'cyan') + ': ' + cfg.PROJECT_FULLDIR)
  print(colored('BUILD_FULLDIR       ', 'cyan') + ': ' + cfg.BUILD_FULLDIR)
  print(colored('TESTS_FULLDIR       ', 'cyan') + ': ' + cfg.TESTS_FULLDIR)
  print(colored('CMAKECACHE_TXT_FILE ', 'cyan') + ': ' + cfg.CMAKECACHE_TXT_FILE)
  return


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
    build_doc()
  elif user_choice == '--cleanCache' or user_choice == '-cc':
    clean_cache()
  elif user_choice == '--cleanProject' or user_choice == '-cp':
    clean_project()
  elif user_choice == '--doxyDoc' or user_choice == '-d':
    open_doc()
  elif user_choice == '--prepareBuildFiles' or user_choice == '-p':
    # Check for the -G option to specify the generator
    if '-G' in sys.argv:
      generator_index = sys.argv.index('-G') + 1
      if generator_index < len(sys.argv):
        generator = sys.argv[generator_index]
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
  command = ['cmake', '-S', '.', '-B', cfg.BUILD_SUBDIR, '-DBUILD_TESTS=ON']
  if generator:
    print('\nUsing the ' + colored('user-specified generator', 'yellow') + ': ' + colored(generator, 'cyan'))
    command.extend(['-G', generator])
  print("\nExecuting command: " + colored(' '.join(command), 'yellow'))

  try:
    subprocess.run(command, check = True)
  except Exception as ex:
    print(ex)
    utl.quit_with_error_message(inspect.currentframe().f_code.co_name + ': Error preparing configuration files.')
  else:
    print()
    utl.print_successful_event("Project build files prepared successfully.")


def build_tests():
  if not os.path.exists(cfg.BUILD_SUBDIR):
    utl.quit_with_error_message(inspect.currentframe().f_code.co_name + ': directory \"' + cfg.BUILD_SUBDIR + '\" does not exist. Try preparing build files first.')

  print(colored('\nBuilding tests...', 'white', 'on_blue'))
  command = ['cmake', '--build', cfg.BUILD_SUBDIR, '-j8']
  print('\nExecuting command: ' + colored(' '.join(command), 'yellow'))

  try:
    subprocess.run(command, check = True)
  except Exception as ex:
    print(ex)
    utl.quit_with_error_message(inspect.currentframe().f_code.co_name + ': Error calling `CMake --build` for this configuration. Make sure you have run the `--prepareBuildFiles` task first.')
  else:
    print()
    utl.print_successful_event('Project built successfully.')


def build_doc():
  print('\n' + colored('Building Doxygen documentation...', 'white', 'on_blue'))
  command = ['doxygen', 'Doxyfile']
  print('\nExecuting command: ' + colored(' '.join(command), 'yellow'))

  try:
    os.chdir(cfg.DOXYGEN_SUBDIR)
    subprocess.run(command, check = True)
  except Exception as ex:
    print(ex)
    utl.quit_with_error_message(inspect.currentframe().f_code.co_name + ': Error building documentation.')
  else:
    print()
    utl.print_successful_event('Documentation built successfully.')


# Open Doxygen documentation in the default browser
def open_doc():
  if not os.path.exists(cfg.DOXYGEN_INDEX_HTML):
    utl.quit_with_error_message(inspect.currentframe().f_code.co_name + ': file \"' + cfg.DOXYGEN_INDEX_HTML + '\" does not exist. Try building the documentation first.')

  if cfg.PLATFORM_SYSTEM == 'Linux':
    command = ['xdg-open', cfg.DOXYGEN_INDEX_HTML]
  elif cfg.PLATFORM_SYSTEM == 'Darwin':
    command = ['open', cfg.DOXYGEN_INDEX_HTML]
  elif cfg.PLATFORM_SYSTEM == 'Windows':
    command = ['start', cfg.DOXYGEN_INDEX_HTML]
  else:
    utl.quit_with_error_message(inspect.currentframe().f_code.co_name + ': ' + cfg.PLATFORM_NOT_RECOGNISED_STR)

  print('\nExecuting command: ' + colored(' '.join(command), 'yellow'))
  try:
    if cfg.PLATFORM_SYSTEM == 'Windows':
      subprocess.run(command, shell = True, check = True) # `shell = True` is needed for Windows
    else:
      subprocess.run(command, check = True)
  except Exception as ex:
    print(ex)
    utl.quit_with_error_message(inspect.currentframe().f_code.co_name + ': Error opening documentation.')
  else:
    print()
    utl.print_successful_event('Documentation opened successfully.')


def clean_project():
  if not os.path.exists(cfg.BUILD_SUBDIR):
    utl.quit_with_error_message(inspect.currentframe().f_code.co_name + ': directory \"' + cfg.BUILD_SUBDIR + '\" does not exist.')

  command = ['cmake', '--build', cfg.BUILD_SUBDIR, '--target', 'clean']
  print('\nExecuting command: ' + colored(' '.join(command), 'yellow'))
  try:
    subprocess.run(command, check = True)
  except Exception as ex:
    print(ex)
    utl.quit_with_error_message(inspect.currentframe().f_code.co_name + ': Error cleaning project.')
  else:
    print()
    utl.print_information(cfg.BUILD_SUBDIR + ' directory has been cleaned.')


def clean_cache():
  if not os.path.exists(cfg.CMAKECACHE_TXT_FILE):
    utl.quit_with_error_message(inspect.currentframe().f_code.co_name + ': file \"' + cfg.CMAKECACHE_TXT_FILE + '\" not found.')

  print('\nAttempting to remove ' + colored(cfg.CMAKECACHE_TXT_FILE, 'yellow') + '...')
  try:
    os.remove(cfg.CMAKECACHE_TXT_FILE)
  except Exception as ex:
    print(ex)
    utl.quit_with_error_message(inspect.currentframe().f_code.co_name + ': Error trying to remove ' + cfg.CMAKECACHE_TXT_FILE + '.')
  else:
    utl.print_information(cfg.CMAKECACHE_TXT_FILE + ' has been removed.\n')


def remove_build_dir():
  if not os.path.exists(cfg.BUILD_SUBDIR):
    utl.quit_with_error_message(inspect.currentframe().f_code.co_name + ': directory \"' + cfg.BUILD_SUBDIR + '\" does not exist.')

  print('\nAttempting to remove ' + colored(cfg.BUILD_SUBDIR, 'yellow') + '...')
  try:
    shutil.rmtree(cfg.BUILD_SUBDIR)
  except Exception as ex1:
    print(ex1)
    print('Error using `' + colored('shutil.rmtree', 'yellow') + '`. Trying with command line instructions...')
    try:
      if cfg.PLATFORM_SYSTEM in ['Linux', 'Darwin']:
        os.system('rm -rf \"{}\"'.format(cfg.BUILD_SUBDIR))
      elif cfg.PLATFORM_SYSTEM == 'Windows':
        os.system('rmdir /S /Q \"{}\"'.format(cfg.BUILD_SUBDIR))
      else:
        utl.quit_with_error_message(inspect.currentframe().f_code.co_name + ': ' + cfg.PLATFORM_NOT_RECOGNISED_STR)
    except Exception as ex2:
      print(ex2)
      cprint('Error using command line instructions.', 'red')
      return
    else:
      print('Directory `' + colored(cfg.BUILD_SUBDIR, 'yellow') + '` has been removed.')
      print()
  else:
    print('Directory `' + colored(cfg.BUILD_SUBDIR, 'yellow') + '` has been removed.')
    print()


def test_project(testing_type: str = cfg.TESTING_TYPE_NORMAL):
  if not os.path.exists(cfg.TESTS_FULLDIR):
    utl.quit_with_error_message(inspect.currentframe().f_code.co_name + ': Testing subdirectory \"' + cfg.TESTS_FULLDIR + '\" does not exist. Try preparing and building first.')

  parameter: list[str] = []
  TESTING_PARAM_VERBOSE:     list[str] = ['-VV']
  TESTING_PARAM_ONLY_FAILED: list[str] = ['--rerun-failed', '--output-on-failure']

  if testing_type == cfg.TESTING_TYPE_VERBOSE:
    parameter = TESTING_PARAM_VERBOSE
  elif testing_type == cfg.TESTING_TYPE_ONLY_FAILED:
    parameter = TESTING_PARAM_ONLY_FAILED

  command: list[str] = ['ctest'] + parameter
  os.chdir(cfg.TESTS_FULLDIR)
  print('\nExecuting command: ' + colored(' '.join(command), 'yellow') + '\n')
  try:
    subprocess.run(command, check = True)
  except subprocess.CalledProcessError as ex:
    print(ex)
    print(colored('\nERROR: initial testing failed.', 'white', 'on_red'))
    print('Re-running failed tests...')
    try:
      parameter = TESTING_PARAM_ONLY_FAILED
      command = ['ctest'] + parameter
      print('\nExecuting command: ' + colored(' '.join(command), 'yellow') + '\n')
      subprocess.run(command, check = True)
    except subprocess.CalledProcessError as ex:
      print(ex)
      utl.print_unsuccessful_event('Some tests failed.')
  else:
    print()
    utl.print_successful_event('Testing was successful.')
