# This script is intended to be run from the root of the project.
# The script creates a Python virtual environment, updates Pip, and installs the required dependencies.
# The script's only prerequisite is Python 3.8 or higher and Pip 22.0 or higher.

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

# ---- Functions definitions ---- #

def print_welcome_message():
  print(f"{GREEN}\nWelcome to the setup script!{RESET}")
  print(f"This script will create a {CYAN}Python{RESET} virtual environment, update {CYAN}Pip{RESET}, and install the required dependencies.")
  response = input(f"{YELLOW}Do you want to continue? (yes / no): {RESET}").strip().lower()

  if response not in ['yes', 'y']:
    print(f"{RED}Setup aborted.{RESET}\n")
    sys.exit(0)

def recognise_platform_or_quit_ANSI():
  """
  Identical to `recognise_platform_or_quit`, but can be used without Python colouring modules.

  This function checks the current platform and prints a message indicating the platform.
  If the platform is not recognised, it prints an error message and raises an exception.
  """

  if PLATFORM_SYSTEM == 'Linux':
    print(f'The platform system  is: {GREEN}Linux{RESET}')
  elif PLATFORM_SYSTEM == 'Darwin':
    print(f'The platform system  is: {GREEN}MacOS{RESET}')
  elif PLATFORM_SYSTEM == 'Windows':
    print(f'The platform system  is: {GREEN}Windows{RESET}')
  else:
    error_message = f'{RED}Error{RESET}: Platform \"{PLATFORM_SYSTEM}\" not recognised.'
    print(error_message)
    raise Exception(error_message)

  print(f'The platform release is: {GREEN}{PLATFORM_RELEASE}{RESET}')
  print(f'The platform version is: {GREEN}{PLATFORM_VERSION}{RESET}')

# ---- Main function ---- #

def main():
  # Define paths
  VENV_DIR:          str = os.path.join('scripts', 'venv')
  REQUIREMENTS_FILE: str = os.path.join('scripts', 'requirements.txt')

  # Check if the virtual environment exists
  if not os.path.isdir(VENV_DIR):
    # Create the virtual environment
    print(f"\n{YELLOW}Python virtual environment not found.{RESET} Creating one...")
    subprocess.check_call([sys.executable, '-m', 'venv', VENV_DIR]) # `sys.executable` is the path to the Python interpreter
  else:
    print(f"\n{GREEN}Python virtual environment found.{RESET} Skipping creation...")

  # Path to script to activate the virtual environment
  if PLATFORM_SYSTEM == 'Windows':
    activate_script = os.path.join(VENV_DIR, 'Scripts', 'activate')
  elif PLATFORM_SYSTEM in ['Linux', 'Darwin']:
    activate_script = os.path.join(VENV_DIR, 'bin', 'activate')

  # Update Pip in the virtual environment
  subprocess.check_call(f'{activate_script} && python -m pip install --upgrade pip', shell = True)

  # Install the requirements in the virtual environment
  subprocess.check_call(f'{activate_script} && pip install -r {REQUIREMENTS_FILE}', shell = True)

# ---- Main guard ---- #

if __name__ == '__main__': # only execute the script if it is run directly
  print_welcome_message()
  try:
    recognise_platform_or_quit_ANSI()
    main()
    print(f"{GREEN}\nSetup completed successfully!{RESET}\n")
  except Exception as e:
    print(f"{RED}\nAn error occurred during setup:{RESET}\n{e}\n")
    sys.exit(1)