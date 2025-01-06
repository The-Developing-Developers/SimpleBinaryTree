# This script activates the virtual environment and runs the `main.py` script.
#
# The prerequisite is running the `setup.py` script before executing this script.

import os
import subprocess
import sys

from helpers.config import PLATFORM_SYSTEM, PLATFORM_RELEASE, PLATFORM_VERSION

# ---- ANSI Colour Codes ---- #

RED    = '\033[91m'
CYAN   = '\033[96m'
GREEN  = '\033[92m'
YELLOW = '\033[93m'
RESET  = '\033[0m'

# ---- Main function ---- #

def main():
  # Define the path to the virtual environment and the main script
  VENV_DIR    = os.path.join('scripts', 'venv')
  MAIN_SCRIPT = os.path.join('scripts', 'main.py')

  # Check if the virtual environment exists
  if not os.path.isdir(VENV_DIR):
    raise FileNotFoundError(f'Error: Virtual environment not found at {VENV_DIR}. Please run the setup script first.')

  # Path to script to activate the virtual environment
  if PLATFORM_SYSTEM == 'Windows':
    venv_python_exe = os.path.join(VENV_DIR, 'Scripts', 'python')
  elif PLATFORM_SYSTEM in ['Linux', 'Darwin']:
    venv_python_exe = os.path.join(VENV_DIR, 'bin', 'python')

  # Execute the main script and pass along command-line arguments
  cmd = [venv_python_exe, MAIN_SCRIPT] + sys.argv[1:] # Concatenate the command-line arguments with the command (both are lists)
  result = subprocess.run(cmd, check = True) # subprocess.run() accepts a list of command-line arguments
  if result.returncode != 0:
    raise RuntimeError(f'Error: Command failed with return code {result.returncode}')

if __name__ == '__main__':
  try:
    main()
  except Exception as e:
    print(f'\n{RED}An exception was raised:{RESET}\n{e}')
    sys.exit(1)