# This script contains utility functions that are used by other scripts in this project.

from termcolor import cprint, colored
from . config  import PLATFORM_SYSTEM, PLATFORM_RELEASE, PLATFORM_VERSION, PLATFORM_NOT_RECOGNISED_STR

# ---- Functions definitions ---- #

def print_unsuccessful_event(event_string: str):
  cprint(event_string, 'white', 'on_red')

def print_successful_event(event_string: str):
  cprint(event_string, 'white', 'on_green')

def print_information(event_string: str):
  cprint(event_string, 'white', 'on_grey')

def quit_with_error_message(error_string: str):
  print_unsuccessful_event(error_string)
  raise Exception("*** An error occurred during the execution of this Python script ***")

def recognise_platform_or_quit():
  """
  This function checks the current platform and prints a message indicating the platform.
  If the platform is not recognised, it prints an error message and raises an exception.
  """

  if PLATFORM_SYSTEM == 'Linux':
    print('The platform is: ' + colored('Linux', 'white', 'on_green'))
  elif PLATFORM_SYSTEM == 'Darwin':
    print('The platform is: ' + colored('MacOS', 'white', 'on_green'))
  elif PLATFORM_SYSTEM == 'Windows':
    print('The platform is: ' + colored('Windows', 'white', 'on_green'))
  else:
    quit_with_error_message(PLATFORM_NOT_RECOGNISED_STR)
