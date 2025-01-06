# This script builds the tests for the project and runs them.
#
# It is recommended to run the `launcher.py` script instead of running this script directly, because `launcher.py`
# activates the virtual environment and then runs this script.

import sys
import time

from helpers   import build_helpers as bld
from helpers   import utils         as utl
from termcolor import colored

def main():
  start: float = time.time()

  utl.recognise_platform_or_quit()
  bld.print_args_and_interpreter()
  bld.assign_and_display_project_paths()
  bld.execute_user_choice()

  end: float = time.time()

  time_elapsed_ms: float = (end - start) * 1000
  time_elapsed_s:  float =  end - start

  time_elapsed_ms_str   : str = format(time_elapsed_ms, '.3f')
  time_elapsed_s_str    : str = format(time_elapsed_s,  '.3f')
  time_elapsed_mm_ss_str: str = time.strftime("%M:%S", time.gmtime(time_elapsed_s))

  print('\n' + colored('The process took', 'white', 'on_blue') + ':')
  print( '  ~ ' + time_elapsed_ms_str + ' milliseconds')
  print( '  ~ ' + time_elapsed_s_str  + ' seconds')
  print( '  ~ ' + time_elapsed_mm_ss_str  + ' minutes:seconds')

if __name__ == '__main__':
  print()
  try:
    main()
  except Exception as ex:
    utl.print_unsuccessful_event('***** Error during execution of Python script *****')
    print(ex)
    sys.exit("An error occurred.")
  finally:
    pass
