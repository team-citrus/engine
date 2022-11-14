import os
import sys
import argparse

# Variables, lots of them

# Default G++ flags
default_gcc = "-O2 -Wall -pedantic"

# Quick build G++ flags
quick_gcc = "-Ofast -pedantic"

# Debug build G++ flags
debug_gcc = "-Og -Wall -Wextra"

# Default MSVC flags
default_cl = "-O2 -Wall"

# Quick build MSVC flags
quick_cl = "-Od"

# Debug build MSVC flags
debug_cl = "-Od -GF -Wall"

# Compiler flags
parser = argparse.ArgumentParser()
# TODO: Add all compiler flags using the following format.
#   USE:
#       parser.add_argument("-FLAG", "--FLAGNAME", help="NAME", type=TYPE
#       print(args.FLAGNAME)
#   EXAMPLE: 
#       parser.add_argument("-test", "--test", help="Test", type=str
#       print(args.test)
args = parser.parse_args()
# End Compiler Flags

def main():
    print("Team citrus build system.")
    # TODO: Add the actual code

if __name__ == "__main__":
    main()
else:
    print("You can't just include the build system where ever")
    exit(0)
