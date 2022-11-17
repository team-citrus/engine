import os

# Variables, meant for user customization, defaults designed for gcc
flags = ["-O2", "-Wall", "-Wextra"]
include_paths = ["./"]
target = "./bin/target"
library_paths = []
libraries = ["Vulkan", "OpenGL", "box2d", "bullet", "GLM"]
file_types = [".cpp", ".cxx", ".c"]

print("Started building...")

# Set up the environment
env = Environment(CPPFLAGS=flags, CCFLAGS=flags, CPPPATH=include_paths, LIBPATH=library_paths, LIBS=libraries)

# Search for files_list and scripts
files_list = []
objs = []

for root, directories, files in os.walk("./"):
    for file in files:
        if file.endswith in file_types:
            # Add file to list
            files_list.append(os.path.join(root,file))
        elif file.endswith(".py"):
            # Execute the file
            script = open(os.path.join(root,file), "r")
            script_str = script.read()
            script.close()
            exec(script_str)

# Final compilation

# Generate object files_list_lis
# We'll probably have to rework all of this later, but this will do for now.
for i in files_list:
    o = ""
    if i.endswith in file_types:
        o = i[:len(i)-4]
    else:
        #TODO: Rewrite this to avoid issues with 2+ character file types.
        o = i[:len(i)-2]
    env.Object(target=o, source=[i])
    o = o + ".o" if os.name == "posix" else o + ".obj"
    objs.append()

# Generate final binary
Default(env.Program(target=target, source=files_list))
