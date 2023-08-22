# The Citrus Engine

The Citrus Engine, a game engine originally created for the Team Citrus project.

For this game engine, we have a simple goal in mind, **we want to create a simple, extendable, well documented, game engine**.
We also intend to use this game engine in our future projects, and hope others adopt it as well.
As well, by making the engine free software, we hope to set a precident in the game development world.

***If you are looking to contribute, the style guide can be found at docs/style.md, and the contributing guide can be found at docs/contrib.md.***

## Compiling requirements

- Vulkan SDK
- g++, or compatible C++ compiler (ie. clang, icc)
- gcc, or compatible C compiler (ie. clang, icc)
- cargo
- cmake

## TODOs

### High priority - ASAP

- [ ] Convert the remaining C++ to C
- [ ] Document stuff
  - [ ] Doxygen comments in the source code
  - [ ] Documenetation of design choices and functionality.
- [ ] Write the graphics API
  - [ ] Write the UI API
- [ ] Write the phyics API
  - [ ] Box2d
  - [ ] Bullet3
  - [ ] Restore `physmain()`
- [ ] Write the core API
  - [ ] Write the input system
    - [ ] Keyboard
    - [ ] Mouse
    - [ ] Controller
  - [ ] Meshes, verts, etc
    - [ ] Write or otherwise adopt a FBX loader
    - [ ] Write or otherwise adopt a binary format glTF loader
    - [ ] `mesh`
      - [ ] Vertex groups
      - [ ] Bones
    - [ ] `mesh_renderer`
- [ ] Create the rendering pipeline
- [ ] Create the main loop
  - [x] `main()`
  - [x] `ecs_execute()`
  - [x] `physmain()`
  - [ ] `draw()`/`Vulkan::vkDraw()`
  - [ ] `mix()`

### Medium priority - Before the next full release

- [ ] Write a proper readme
- [ ] Multi-arch support/Portability (Should be considered between medium and high priority)
  - [ ] Generic implementations of CPU specific code (except AES)
  - [ ] More detailed build options for different platforms
  - [ ] AArch64 optimizations
  - [x] AMD64 optimizations
- [ ] Mult-platoform support/Portability
  - [x] Linux support
  - [x] Windows support
  - [ ] Generic BSD/*nix support
  - [ ] MacOS Support (low prority, just here for organizational purposes)

### Low priority - within the next few releases

- [ ] Raytracing rendering for Vulkan (Should be considered between medium and low priority)
- [ ] Mobile support
  - [ ] iOS (after MacOS support in terms of prority)
  - [ ] Android (between *nix support and MacOS support in terms of prority)
- [ ] VR support
- [ ] IR support
- [ ] C# support

### Should we somehow get the chance

- [ ] Console support
