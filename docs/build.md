# The Build system

Instead of using a more traditional buildsystem, we are instead making our own.
The build system will pretty much just be a giant python script.

## Basic function

The build script starts by collecting args and reading a configuration file, `build.conf`, to fill some variables to be used.
Depending on some of the information given, namely the compiler and default system build system (ie make), it then proceds to either query for a compiler and system build system.
If a compiler is not found, execution terminates with a message stating that no compiler was found.
If the compiler was not provided or the one provided was invalid, it probes for another.
Same thing for a system build system.

If a compatible build system is found, based on the arguments provided, and some defaults baked in to the system, a file for it is generated and executed.
If nothing is found, the build system manually executes the commands necessary.

## Advanced function

First the proper compiler and flags are gathered from the configuration file.
Arguments are parsed, and the variables are changed accordingly.
Any unprovided arguments are searched for, and the variables are changed accordingly.
If nothing is found, a termination message is sent stating it.

First, on Linux, gcc is searched for, then clang, then mingw64.
First, on Windows, mingw64 is searched for, then msvc, then clang.

If Visual Studio is found, the latest version found for visual studio is used.
Community is used first, then business, then enterprise.
Then vcvars64.bat is run, unless 32 bit mode is set, then vcvars32.bat is run.
No matter what, from here, msvc (cl.exe) and nmake are used, unless custom cxxflags are set.

The only compatible build systems are make and nmake.

If make is found, a makefile is generated.
If nmake is found, an nmake makefile is generated.
If neither are found, each command is manually generated and executed.
