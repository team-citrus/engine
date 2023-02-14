# The Citrus Engine

The Citrus Engine, a game engine originally created for the Team Citrus project.

For this game engine, we have a simple goal in mind, **we want to create a simple, extendable, well documented, game engine**.
We also intend to use this game engine in our future projects, and hope others adopt it as well.
As well, by making the engine free software, we hope to set a precident in the game development world.

***If you are looking to contribute, the style guide can be found at docs/style.md, and the programmer's guide can be found at docs/guide.md.***

## Compiling requirements

- Python
- SCons
- Vulkan SDK
- OpenGL SDK
- GLM
- box2d
- Bullet
- G++, or compatible C++ compiler (ie. clang, icc)

## TODOs

### High priority

- [x] Get a name for the engine
- [ ] Write a proper readme
- [x] Create build system
- [x] Create code structure
- [x] Create formating guide
- [ ] Write headers for the graphics API
- [ ] Write headers for the phyics API
- [ ] Write headers for general engine information
- [ ] Write replacement functions and classes for some standard library functions and classes
- [ ] Create the rendering pipeline
- [ ] Create the main loop
  - [x] main()
  - [ ] gameplayMain()
  - [ ] physmain()
  - [ ] draw()
  - [ ] mix()
