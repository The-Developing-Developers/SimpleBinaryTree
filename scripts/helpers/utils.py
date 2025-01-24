"""
utils.py

This module provides utility functions and classes for terminal text formatting, error handling, and configuration
management. It includes ANSI colour codes for terminal text formatting, functions for printing formatted messages,
and functions for handling errors and platform recognition.

Classes:
    ColourCodes: ANSI colour codes for terminal text formatting.
"""

from traceback import extract_stack
from .config   import Config as cfg

# ---- ANSI Colour Codes ---- #

class ColourCodes:
  '''
  ANSI colour codes for terminal text formatting.

  This class provides ANSI escape codes for colouring terminal text output. These codes are useful for scripts
  that are designed to be run outside of a Python virtual environment, where the `termcolor` module is not available.
  '''

  CYAN_BRIGHT    = '\033[96m'
  CYAN_DARK      = '\033[36m'
  GREEN_DARK     = '\033[32m'
  GREEN_BRIGHT   = '\033[92m'
  MAGENTA_BRIGHT = '\033[95m'
  MAGENTA_DARK   = '\033[35m'
  RED_BRIGHT     = '\033[91m'
  RED_DARK       = '\033[31m'
  YELLOW_DARK    = '\033[33m'
  YELLOW_BRIGHT  = '\033[93m'
  WHITE_BRIGHT   = '\033[97m'
  WHITE_DARK     = '\033[37m'

  WHITE_ON_RED   = '\033[97;41m'
  WHITE_ON_GREEN = '\033[97;42m'
  WHITE_ON_GREY  = '\033[97;100m'
  WHITE_ON_BLUE  = '\033[97;44m'

  RESET          = '\033[0m'

cc = ColourCodes # alias for the ColourCodes class


# ---- Functions definitions ---- #

def print_successful_event(event: str) -> None:
  '''
  Prints a successful event message.

  This function prints a message indicating that an event was successful. The message is coloured using ANSI escape codes.

  Args:
      event (str): The event that was successful.
  '''
  print(f'{cc.WHITE_ON_GREEN}SUCCESS:{cc.RESET} {event}')


def print_white_on_blue(message: str) -> None:
  '''
  Prints a message with white text on a blue background.

  This function prints a message with white text on a blue background. The message is coloured using ANSI escape codes.

  Args:
      message (str): The message to print.
  '''
  print(f'{cc.WHITE_ON_BLUE}{message}{cc.RESET}')


def format_error_message(message):
  '''
  Formats an error message with traceback information.

  This function captures the current stack trace, extracts the relevant frame, and formats an error message that
  includes the line number and filename where the error occurred. The message is also coloured using ANSI escape codes.

  Args:
      message (str): The error message to format.

  Returns:
      str: The formatted error message with traceback information.
  '''
  CALLING_FRAME_INDEX: int = -3 # The index of the calling frame in the stack trace that we are actually interested in
  tb = extract_stack()[CALLING_FRAME_INDEX]
  return f'{cc.RED_BRIGHT}Error{cc.RESET} at line {cc.RED_BRIGHT}{tb.lineno}{cc.RESET}\tin file {cc.YELLOW_BRIGHT}{tb.filename}{cc.RESET}:\n  {message}'


def raise_runtime_error(message: str) -> None:
  '''
  Raises a RuntimeError with the specified message.

  This function raises a RuntimeError with the specified message.

  Args:
      message (str): The message to include in the RuntimeError.

  Raises:
      RuntimeError: The message passed as an argument.
  '''
  ERROR_STRING: str = format_error_message(message)
  raise RuntimeError(ERROR_STRING)


def recognise_platform_or_quit():
  '''
  This function checks the current platform and prints a message indicating the platform.
  If the platform is not recognised, it prints an error message and raises an exception.
  '''

  if cfg.PLATFORM_SYSTEM == 'Linux':
    print(f'The platform is: ' + f'{cc.WHITE_ON_GREEN}Linux{cc.RESET}')
  elif cfg.PLATFORM_SYSTEM == 'Darwin':
    print(f'The platform is: ' + f'{cc.WHITE_ON_GREEN}MacOS{cc.RESET}')
  elif cfg.PLATFORM_SYSTEM == 'Windows':
    print(f'The platform is: ' + f'{cc.WHITE_ON_GREEN}Windows{cc.RESET}')
  else:
    raise_runtime_error(cfg.PLATFORM_NOT_RECOGNISED_STR)

  print(f'The platform release is: {cc.GREEN_BRIGHT}{cfg.PLATFORM_RELEASE}{cc.RESET}')
  print(f'The platform version is: {cc.GREEN_BRIGHT}{cfg.PLATFORM_VERSION}{cc.RESET}')


def print_executing_command(command: list[str], directory: str = None) -> None:
  '''
  Prints the command that is about to be executed.

  This function prints the command that is about to be executed. The command is coloured using ANSI escape codes.

  Args:
    command (list[str]): The command to execute.
    directory (str): The directory in which to execute the command.
  '''
  print(f'\nIn directory:      {cc.YELLOW_BRIGHT}{directory}{cc.RESET}')
  COMMAND_STR: str = ' '.join(command)
  print(f'Executing command: {cc.YELLOW_BRIGHT}{COMMAND_STR}{cc.RESET}\n')


def print_config_variables():
  '''
  Prints all configuration variables and their values from the Config class.
  It would make more sense if defined in the Config class itself, but since it requires colours from the ColourCodes class,
  it is defined here to avoid circular imports.
  '''

  for name, value in cfg.__dict__.items():
    if not name.startswith('__') and not callable(value):
      if 'NEWLINE' in value:
        print()
      else:
        print(f'{cc.CYAN_DARK}{name}{cc.RESET}: {value}')