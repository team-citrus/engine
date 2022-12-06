# Resource loaders and the like

Resource loaders are a very important part of the game engine, responsible for loading in sprites, textures, models, and what have you.
Since resource loaders must have a good understanding of what resources are allocated to which IDs, which files are used for what, and commonly used resources, their code will primarily generated procedurally by an editor or build script during the build process.

Resource IDs are 64 bit unique values, unique to a resource.
This can be anything from a checksum, a compressed hash, IDOFFILE:IDWITHINFILE sort of thing, etc.
The only requirement is that it be unique.

## Resource loaders and memory

Resource loaders must be heavily optimized, and therefore have to use many memory mangement techniques and tricks to make memory access fast and efficent.
Commonly used resources should have a read-only copy loaded into RAM, using page allocation.
Resource loaders should use memory-mapped files when loading new resources into memory, making use of the large address space of modern 64 bit machines.
Resource loaders should also use page allocated caches for commonly accessed information.

## Resource loaders and game files

***RESOURCE LOADERS MUST BE ABLE TO DESCOVER THE FILE AN ID IS CONTAINED IN QUICKLY, WITHOUT USING DISK READS,*** ideally this can be implemented either through procedural methods.
Ideally, resource loaders should be able to quickly access an ID by mapping that part of the file into memory, however this does not have to be present. 
