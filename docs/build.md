# The Build system

Following in the footsteps of a similar project, Godot, we will be using SCons for our build system.

## Arguments

In order to pass arguments to the build system, you do it in key value pairs, ex: `scons foo=bar`.
SCons has it's own arguments, the most notable of which is `-j {INT}`, which sets the number of threads to run on to be `{INT}`.
The exceptable arguments are:

- `config-file` - sets the config file to load (see config file section), default `build/config.json`
- `ARCH` - sets the targeted microarch, exceptable values are any valid GCC microarchitectures, default `haswell`
- `TUNE` - sets the microarch to tune for, exceptable values are any valid GCC `-mtune` values, default `cannonlake`
- `BUILD_TYPE` - sets the build type, exceptable values are `FINAL`, `DEBUG`, and `QUICK`, default `FINAL`
- `VULKAN` - tells the build system to build with Vulkan if set to `TRUE`, and not if set to `FALSE`, default `TRUE`
- `OPENGL` - tells the build system to build with Vulkan if set to `TRUE`, and not if set to `FALSE`, default `FALSE`

## Config file

A config file for our purposes is a json file, by default located at `build/config.json`.
A config file has to contain an object variable called `define`, which contains a list of things to define at build type.
The names of which are the names of the json variables, and the values being the values of the variables.
