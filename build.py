import os
import sys
import re

# Variables, lots of them

# Default include path
inc = "./"

# Compatible compilers
compilers = ["gcc", "clang", "msvc"]

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
flags : str

# Compiler
compiler : str

# Level of paralellism
paralellism = int(4)

# Comand template
command_template = "{0} {2} {1} {3}"

# Mode, default = 0, quick = 1, debug = 2, custom = 3
mode = int(0)

def main():
    print("Team citrus build system.") 

    # Open the configuration file
    conf = open("build.conf", "r", encoding="utf-8", newline='\n')
    # Necessary to test for eof
    eof = conf.readline()

    # While not at EOF
    while eof != '':
        ln = eof
        # Check arguments
        if ln == "debug":
            mode = int(2)

        elif ln == "quick":
            mode = int(1)

        elif re.compile("cxxflags=\".+\"", flags=0).match(ln) !=  None:
            mode = int(3)
            # Filter the cxxflags value down to the useful parts
            flags = re.sub("cxxflags=\"", '', ln)
            tmpflags = flags[:len(flags)-1]
            flags = tmpflags

        elif re.compile("compiler=?\"?.+\"?", flags=0).match(ln) != None:
            # Filter the compiler value down to the useful parts
            compiler = re.sub("compiler=?\"?")
            if compiler[len(compiler)-1] == '"':
                tmpcompiler = compiler[:len(flags)-1]
                compiler = tmpcompiler

        elif re.compile("(parellelism)|(threads)=.+", flags=0).match(ln) != None:
            # Filter the paralellism value dow to the useful parts, and convert to an integer
            paralellism_str = re.sub("(parellelism)|(threads)=", '', ln)
            paralellism = int(paralellism_str)

        # Read the next line
        eof = conf.readline()    

if __name__ == "__main__":
    main()
else:
    print("You can't just include the build system where ever")
    exit(0)
