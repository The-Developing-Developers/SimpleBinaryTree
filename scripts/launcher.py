# This script activates the virtual environment and runs the `main.py` script.
#
# The prerequisite is running the `setup.py` script before executing this script.

import os
import subprocess
import sys

def main():
  # Define the path to the virtual environment and the main script
  VENV_DIR    = os.path.join('scripts', 'venv')
  MAIN_SCRIPT = os.path.join('scripts', 'main.py')

  # Check if the virtual environment exists
  if not os.path.isdir(VENV_DIR):
    print(f"Error: Virtual environment not found at {VENV_DIR}. Please run the setup script first.")
    sys.exit(1)

  # Path to the script to activate the virtual environment
  if os.name == 'nt':
    activate_script = os.path.join(VENV_DIR, 'Scripts', 'activate')
  else:
    activate_script = os.path.join(VENV_DIR, 'bin', 'activate')

  # Construct the command to activate the virtual environment and run the main script
  command = f'{activate_script} && python {MAIN_SCRIPT} ' + ' '.join(sys.argv[1:])

  # Execute the command
  subprocess.run(command, shell = True, check = True)

if __name__ == '__main__':
  main()