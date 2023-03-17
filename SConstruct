import json
import os

configFileName = "build/config.json"
ARCH = "haswell"
TUNE = "cannonlake"
BUILD_TYPE = "FINAL"
VULKAN = "TRUE"
OPENGL = "FALSE"
RUST = "FALSE"
AVX = "TRUE"

if "ARCH" in ARGUMENTS:
    ARCH = ARGUMENTS["ARCH"]
if "TUNE" in ARGUMENTS:
    TUNE = ARGUMENTS["TUNE"]
if "VULKAN" in ARGUMENTS:
    ARCH = ARGUMENTS["VULKAN"]
if "OPENGL" in ARGUMENTS:
    ARCH = ARGUMENTS["OPENGL"]
if "config-file" in ARGUMENTS:
    configFileName = ARGUMENTS["config-file"]

# TODO: Rust and AVX

configFile = open(configFileName, "rt")
CONFIG = json.loads(configFile.read())
DEFINES = CONFIG["define"]

Export('ARCH')
Export('BUILD_TYPE')
Export('TUNE')
Export('VULKAN')
Export('OPENGL')
Export('RUST')
Export('AVX')
Export('CONFIG')
Export('DEFINES')

if BUILD_TYPE == "DEBUG" or BUILD_TYPE == "FINAL":
    print("Target CPU (micro)architecture: ", ARCH)
    print("Binary tuned for CPU (micro)architecture: ", TUNE)
    print("Configuration: ", CONFIG)

SConscript('src/core/SConscript')
SConscript('src/physics/SConscript')
SConscript('src/graphics/SConscript')
SConscript('soloud/src/SConscript')

# TODO: Different build types for Rust

if BUILD_TYPE == "DEBUG"
    os.system("cargo build -v --profile dev")
elif BUILD_TYPE == "FINAL":
    os.system("cargo build -v --release")
elif BUILD_TYPE == "QUICK":
    os.system("cargo build --profile quick")
    
# TODO: Link Rust and C++
