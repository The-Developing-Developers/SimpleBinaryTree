'''
This script activates the virtual environment and runs the `main.py` script.

The prerequisite is running the `setup.py` script before executing this script.

Usage:
  python launcher.py [arguments]

Functions:
  main(): The main function that activates the virtual environment and runs the `main.py` script.
'''

import os
import subprocess
import sys

from helpers.config import Config as cfg
from helpers.utils  import raise_runtime_error, print_executing_command, ColourCodes as cc

# ---- Main function ---- #

def main():
  '''
  Activates the virtual environment and runs the `main.py` script.

  This function checks if the virtual environment exists, activates it, and runs the `main.py` script
  with any command-line arguments passed to this script.

  Raises:
    FileNotFoundError: If the virtual environment is not found.
    RuntimeError: If the command to run `main.py` fails.
  '''

  # Check if the virtual environment exists
  if not os.path.isdir(cfg.DIRFUL_VENV):
    raise_runtime_error(f'Virtual environment {cc.RED_BRIGHT}not found{cc.RESET} at {cc.YELLOW_BRIGHT}{cfg.DIRFUL_VENV}{cc.RESET}. Please run the {cc.CYAN_BRIGHT}setup.py{cc.RESET} script first.')

  # Path to script to activate the virtual environment
  if cfg.PLATFORM_SYSTEM == 'Windows':
    FILFUL_PYTHON_EXE_VENV = cfg.FILFUL_PYTHON_EXE_VENV_WIN
  elif cfg.PLATFORM_SYSTEM in ['Linux', 'Darwin']:
    FILFUL_PYTHON_EXE_VENV = cfg.FILFUL_PYTHON_EXE_VENV_LIN

  # Execute the main script and pass along command-line arguments
  COMMAND: list[str] = [FILFUL_PYTHON_EXE_VENV, cfg.FILFUL_MAIN_PY] + sys.argv[1:] # Concatenate the command-line arguments with the command (both are lists)

  try:
    print_executing_command(COMMAND, os.getcwd())
    subprocess.run(COMMAND, check = True) # subprocess.run() accepts a list of command-line arguments
  except Exception as ex:
    raise_runtime_error(f'Failed to run the main script with command-line arguments:\n{ex}')

# ---- Main guard ---- #

if __name__ == '__main__':
  try:
    main()
  except Exception as ex: # catch any exceptions raised by the main function
    print(f'\n{cc.WHITE_ON_RED}An error occurred during the execution of the launcher script:{cc.RESET}\n\n{ex}\n')
    sys.exit(1)