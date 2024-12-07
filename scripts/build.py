import subprocess
import sys

def main():
  # ANSI colour codes
  RED = '\033[91m'
  GREEN = '\033[92m'
  YELLOW = '\033[93m'
  CYAN = '\033[96m'
  RESET = '\033[0m'

  # Welcome message
  print(f"\nWelcome to the {GREEN}Simple Binary Tree{RESET} build automation script!")
  print(f"\nThis script will prepare the build files and build the {GREEN}tests executable{RESET} for the project.")
  print(f"{CYAN}CMake{RESET} is required to run this script (minimum version: 3.12). Make sure you have it installed.")
  print(f"{CYAN}CMake{RESET} will automatically detect the C++ compiler on your system, provided it is in the {CYAN}PATH{RESET}.")
  print(f"You can {GREEN}override{RESET} the default generator by providing one as a command line argument. For example: {YELLOW}python ./scripts/build.py \"Visual Studio 16 2019\"{RESET}.")

  response: str = None

  # Check if a generator is specified from the command line
  generator = sys.argv[1] if len(sys.argv) > 1 else None
  if generator:
    response = input(f"{YELLOW}\nYou have specified generator {CYAN}{generator}{RESET}. Do you wish to continue?{RESET} (y/n): ")
  else:
    response = input(f"{YELLOW}\nDo you wish to continue?{RESET} (y/n): ")

  if response.lower() in ['no', 'n']:
    print(f"{RED}ABORTED{RESET}" + ": The build process was aborted by the user.")
  else:
    try:
      # Prepare the build files
      command = ['cmake', '-S', '.', '-B', 'build', '-DBUILD_TESTS=ON']
      if generator:
        print(f"\nUsing the {GREEN}user-specified generator{RESET}: {CYAN}{generator}{RESET}")
        command.extend(['-G', generator])
      print(f"{CYAN}\nPreparing build files...{RESET}")
      print(f"Running command: {YELLOW}{' '.join(command)}{RESET}")
      subprocess.run(command, check=True)

      # Build the project
      command = ['cmake', '--build', 'build']
      print(f"{CYAN}\nBuilding the project...{RESET}")
      print(f"Running command: {YELLOW}{' '.join(command)}{RESET}")
      subprocess.run(command, check=True)

      print(f"{GREEN}\nSUCCESS{RESET}" + ": The project was built successfully!")
      print(f"- If you built the project with {CYAN}MSVC{RESET},         you can find the executable in the {YELLOW}build/tests/Debug{RESET} directory.")
      print(f"- If you built the project with {CYAN}MinGW{RESET} or {CYAN}GCC{RESET}, you can find the executable in the {YELLOW}build/tests{RESET}       directory.")
    except subprocess.CalledProcessError as e:
      print(f"{RED}ERROR{RESET}" + f": The build process failed with error code {e.returncode}.")
  print()

if __name__ == "__main__":
  main()