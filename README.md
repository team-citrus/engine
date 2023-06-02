# The Ecosystem Citrus Engine

The Ecosystem Variant of the Citrus Engine, created for the Citrus Engine.
This will be used in the Citrus Game itself, and is highly optimized for it.
As a bonus, it also demonstrates how the Citrus Engine can be adapted for your needs.

***If you are looking for [the main Citrus Engine, it can be found here](https://github.com/team-citrus/engine/)***

## Compiling requirements

- Python
- SCons
- Vulkan SDK
- GLM
- box2d
- Bullet3
- G++, or compatible C++ compiler (ie. clang, icc)

## TODOs

### High priority - ASAP

- [ ] Document stuff
  - [ ] Doxygen comments in the source code
  - [ ] Documenetation of design choices and functionality.
- [ ] Write the graphics API
  - [ ] Write the UI API
- [ ] Write the core API
  - [x] Write the input system
  - [ ] Meshes, verts, etc
    - [ ] Write or otherwise adopt a FBX loader
    - [ ] Write or otherwise adopt a binary format glTF loader
    - [ ] `engine::Mesh`
      - [ ] Vertex groups
      - [ ] Bones
    - [ ] `engine::MeshRenderer`
      - [ ] Possibly `engine::SkinedMeshRenderer`
- [ ] Convert the project into Rust, with memory allocation and render code written in mixed C and C++.
- [ ] Create the rendering pipeline
- [ ] Create the main loop
  - [x] `main()`
  - [x] `gameplayMain()`
  - [ ] `draw()`/`Vulkan::vkDraw()`
  - [ ] `mix()`

### Medium priority - Before the next full release

- [ ] Write a proper readme
- [ ] Mult-platform support/Portability
  - [x] Linux support
  - [x] Windows support
  - [ ] Generic BSD/*nix support
  - [ ] MacOS Support (low prority, just here for organizational purposes)
- [ ] Rust suport (Should be considered between medium and high priority)

### Should we somehow get the chance

- [ ] Console support

## Disclaimers

All of the files located in soloud/ and include/sys/soloud are modified versions of files orginially created for the [SoLoud audio engine](https://github.com/jarikomppa/soloud).
