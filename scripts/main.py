'''
This script builds the project.

It is recommended to run the `launcher.py` script from the root directory instead of running this script directly,
because `launcher.py` activates the virtual environment and then runs this script.

Usage:
  python ./scripts/launcher.py [arguments]

Functions:
  main(): The main function that builds and runs the project.
'''

import sys
import time

from helpers.build_helpers import print_args_and_interpreter, assign_and_display_project_paths, execute_user_choice
from helpers.utils         import recognise_platform_or_quit, raise_runtime_error, print_white_on_blue
from termcolor             import colored


def main():
  '''
  Builds the project.

  This function performs the following steps:
  1. Recognises the platform or quits if the platform is not supported.
  2. Prints the command-line arguments and the Python interpreter information.
  3. Assigns and displays the project paths.
  4. Executes the user's choice of actions.
  5. Measures and prints the time taken for the process.

  Raises:
    Exception: If any error occurs during the execution of the script.
  '''

  START: float = time.time()

  try:
    recognise_platform_or_quit()
    print_args_and_interpreter()
    assign_and_display_project_paths()
    execute_user_choice()
  except Exception as ex:
    raise_runtime_error(f'Error during execution of helper functions\n{ex}')

  END: float = time.time()

  TIME_ELAPSED_MS:        float = (END - START) * 1000
  TIME_ELAPSED_S:         float =  END - START
  TIME_ELAPSED_MS_STR:    str   = format(TIME_ELAPSED_MS, '.3f')
  TIME_ELAPSED_S_STR:     str   = format(TIME_ELAPSED_S,  '.3f')
  TIME_ELAPSED_MM_SS_STR: str   = time.strftime("%M:%S", time.gmtime(TIME_ELAPSED_S))

  print()
  print_white_on_blue('Time taken:')
  print( '  ~ ' + TIME_ELAPSED_MS_STR     + ' milliseconds')
  print( '  ~ ' + TIME_ELAPSED_S_STR      + ' seconds')
  print( '  ~ ' + TIME_ELAPSED_MM_SS_STR  + ' minutes:seconds')
  print()

# ---- Main guard ---- #

if __name__ == '__main__':
  print()
  try:
    main()
  except Exception as ex:
    print(colored('An error occurred during the execution of the main script:', 'white', 'on_red') + '\n\n' + str(ex) + '\n')
    sys.exit(1)
