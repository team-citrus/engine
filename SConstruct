import json

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

# TODO: Invoke Cargo

SConscript('src/core/SConscript')
SConscript('src/physics/SConscript')
SConscript('src/graphics/SConscript')
SConscript('soloud/src/SConscript')

# TODO: Invoke stuff
# TODO: Link Rust and C++
