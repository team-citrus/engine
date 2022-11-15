import os

# Variables, meant for user customization, defaults designed for gcc
flags = ["-O2", "-Wall", "-Wextra"]
include_paths = ["./"]
target = "./bin/target"
library_paths : list
libraries = ["Vulkan", "OpenGL", "box2d", "bullet", "GLFW", "GLM"]

print("Started building...")

# Set up the environment
env = Environment(CPPFLAGS=flags, CCFLAGS=flags, CPPPATH=include_paths, LIBPATH=library_paths, LIBS=libraries)

# Search for files and scripts
files = []
objs = []

for root, directories, file in os.walk("./"):
    for file in file:
        if file.endswith([".cpp", ".cxx", ".c"]):
            # Add file to list
            files.append(os.path.join(root,file))
        elif file.endswith(".py"):
            # Execute the file
            script = open(os.path.join(root,file), "r")
            script_str = script.read()
            script.close()
            exec(script_str)

# Final compilation

# Generate object files
for i in files:
    o = ""
    if i.endswith([".cpp", ".cxx"]):
        o = i[:len(i)-4]
    else:
        o = i[:len(i)-2]
    env.Object(target=o, source=[i])
    o = o + ".o" if os.name == "posix" else o + ".obj"
    objs.append()

# Generate final binary
Default(env.Program(target=target, source=files))