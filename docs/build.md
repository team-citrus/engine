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
