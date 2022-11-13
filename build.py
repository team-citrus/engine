import os
import sys

# Variables, lots of them

# Default G++ flags
default_gcc = "-O2 -Wall -pedantic -I./ -Walloca"

# Quick build G++ flags
quick_gcc = "-Ofast -Wall -pedantic -Walloca -I./"

# Debug build G++ flags
debug_gcc = "-Og -Wall -Wextra -Walloca -I./"

def main():
    print("Team citrus build system.")
    # TODO: Add the actual code

if __name__ == "__main__":
    main()
else:
    print("You can't just include the build system where ever")
    exit(0)
