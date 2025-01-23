"""
Setup Script for SimpleBinaryTree Project

This script is intended to be run from the root of the project.
It creates a Python virtual environment, updates Pip, and installs the required dependencies.
The script's only prerequisite is Python 3.8 or higher and Pip 22.0 or higher.

Modules:
    os: Provides a way of using operating system dependent functionality.
    subprocess: Allows you to spawn new processes, connect to their input/output/error pipes, and obtain their return codes.
    sys: Provides access to some variables used or maintained by the interpreter and to functions that interact strongly with the interpreter.
    helpers.config: Contains platform-specific configuration variables.

Functions:
    print_welcome_message(): Prints a welcome message and prompts the user to continue.
    recognise_platform_or_quit_ANSI(): Checks the current platform and prints a message indicating the platform.
    main(): Main function that creates the virtual environment, updates Pip, and installs the required dependencies.

Usage:
    Run this script from the root of the project directory:
    $ python scripts/setup.py
"""

import os
import subprocess
import sys

from helpers.config import Config as cfg
from helpers.utils  import recognise_platform_or_quit, raise_runtime_error, print_executing_command, ColourCodes as cc


# ---- Functions definitions ---- #

def print_welcome_message():
  '''
  Prints a welcome message and prompts the user to continue.

  This function prints a welcome message for the setup script, describing its purpose.
  If the script is running in a CI environment, it skips the user prompt. Otherwise,
  it prompts the user to continue with the setup. If the user does not agree to continue,
  the script exits.

  Raises:
      SystemExit: If the user chooses not to continue with the setup.
  '''
  print(f'\nWelcome to the setup script for {cc.GREEN_BRIGHT}{cfg.PROJECT_NAME}{cc.RESET}.')
  print(f'This script will create a {cc.CYAN_BRIGHT}Python{cc.RESET} virtual environment, update {cc.CYAN_BRIGHT}Pip{cc.RESET}, and install the required dependencies.')

  if os.getenv('CI'):
    print(f'{cc.YELLOW_BRIGHT}Running in CI environment. Skipping user prompt.{cc.RESET}')
    return

  response = input(f'{cc.YELLOW_BRIGHT}Do you want to continue? (yes / no): {cc.RESET}').strip().lower()

  if response not in ['yes', 'y']:
    print(f'{cc.WHITE_ON_RED}Setup aborted.{cc.RESET}\n')
    sys.exit(0)

# ---- Main function ---- #

def main():
  # Define paths
  if cfg.PLATFORM_SYSTEM == 'Windows':
    REQUIREMENTS_FILE: str = cfg.FILFUL_REQUIREMENTS_TXT_WIN
  elif cfg.PLATFORM_SYSTEM in ['Linux', 'Darwin']:
    REQUIREMENTS_FILE: str = cfg.FILFUL_REQUIREMENTS_TXT_LIN

  # Check if the requirements file exists
  if not os.path.isfile(REQUIREMENTS_FILE):
    raise_runtime_error(f'The requirements file {cc.CYAN_BRIGHT}{REQUIREMENTS_FILE}{cc.RESET} does not exist.')

  # Check if the virtual environment exists
  if not os.path.isdir(cfg.DIRFUL_VENV):
    # Create the virtual environment
    print(f"\n{cc.YELLOW_BRIGHT}Python virtual environment not found.{cc.RESET} Creating one...")
    COMMAND: list[str] = [sys.executable, '-m', 'venv', cfg.DIRFUL_VENV ]
    print_executing_command(COMMAND, os.getcwd())
    try:
      subprocess.run(COMMAND, check = True)
    except Exception as ex:
      raise_runtime_error(f'Failed to create virtual environment:\n{ex}')
  else:
    print(f"\n{cc.GREEN_BRIGHT}Python virtual environment found.{cc.RESET} Skipping creation...")

  # Path to script to activate the virtual environment
  if cfg.PLATFORM_SYSTEM == 'Windows':
    VENV_PYTHON_EXE: str = os.path.join(cfg.DIRFUL_VENV, 'Scripts', 'python')
  elif cfg.PLATFORM_SYSTEM in ['Linux', 'Darwin']:
    VENV_PYTHON_EXE: str = os.path.join(cfg.DIRFUL_VENV, 'bin', 'python')

  # Update Pip and install the requirements in the virtual environment
  try:
    COMMAND: list[str] = [VENV_PYTHON_EXE, '-m', 'pip', 'install', '--upgrade', 'pip']
    print_executing_command(COMMAND, os.getcwd())
    subprocess.run(COMMAND)
    COMMAND: list[str] = [VENV_PYTHON_EXE, '-m', 'pip', 'install', '-r', REQUIREMENTS_FILE]
    print_executing_command(COMMAND, os.getcwd())
    subprocess.run(COMMAND)
  except Exception as ex:
    raise_runtime_error(f'Failed to install dependencies:\n{ex}')

# ---- Main guard ---- #

if __name__ == '__main__': # only execute the script if it is run directly
  print_welcome_message()
  try:
    recognise_platform_or_quit()
    main()
    print(f'\n{cc.WHITE_ON_GREEN}Setup completed successfully!{cc.RESET}\n')
  except Exception as ex: # catch any exceptions raised by the main function
    print(f'\n{cc.WHITE_ON_RED}An error occurred during the execution of the setup script:{cc.RESET}\n\n{ex}\n')
    sys.exit(1)