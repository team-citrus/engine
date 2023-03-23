# The Citrus Engine

The Citrus Engine, a game engine originally created for the Team Citrus project.

For this game engine, we have a simple goal in mind, **we want to create a simple, extendable, well documented, game engine**.
We also intend to use this game engine in our future projects, and hope others adopt it as well.
As well, by making the engine free software, we hope to set a precident in the game development world.

***If you are looking to contribute, the style guide can be found at docs/style.md, and the contributing guide can be found at docs/contrib.md.***

## Compiling requirements

- Python
- SCons
- Vulkan SDK
- OpenGL SDK
- GLM
- box2d
- Bullet3
- G++, or compatible C++ compiler (ie. clang, icc)

## TODOs

### High priority - ASAP

- [x] Integrate the Soloud sources into the engine
- [ ] Write the graphics API
  - [ ] Write the UI API
- [ ] Write the phyics API
- [ ] Write the core API
  - [ ] Write the input system
  - [ ] Meshes, verts, etc
    - [ ] Write or otherwise adopt a FBX loader
    - [ ] Write or otherwise adopt a binary format glTF loader
- [x] Write replacement functions and classes for some standard library functions and classes
  - [x] `engine::Vector<T>`
  - [x] `engine::pair<A, B>`
  - [x] `engine::map<A, B>`
  - [x] `engine::hash()`
  - [x] `engine::hashMap<K, T>`
- [ ] Create the rendering pipeline for Vulkan
- [ ] Create the rendering pipeline for OpenGL
- [ ] Create the main loop
  - [x] main()
  - [ ] gameplayMain()
  - [ ] physmain()
  - [ ] draw()
  - [ ] mix()

### Medium priority - Before the next full release

- [ ] Write a proper readme
- [ ] Multi-arch support/Portability (Should be considered between medium and high priority)
  - [ ] Generic implementations of CPU specific code
  - [ ] More detailed build options for different platforms
  - [ ] Optimization headers/APIs for different platforms and extensions
    - [x] SSE4.2
    - [x] AVX
    - [x] AVX2
    - [ ] AVX512
    - [ ] SVE
    - [ ] SVE2
    - [x] Neon
  - [ ] AArch64 optimizations
  - [x] AMD64 optimizations
- [ ] Mult-platoform support/Portability
  - [x] Linux support
  - [x] Windows support
  - [ ] Generic BSD/*nix support
  - [ ] MacOS Support (low prority, just here for organizational purposes)
- [ ] Rust suport (Should be considered between medium and high priority)

### Low priority (within the next few releases)

- [ ] Raytracing rendering for Vulkan (Should be considered between medium and low priority)
- [ ] Mobile support
  - [ ] iOS (after MacOS support in terms of prority)
  - [ ] Android (between *nix support and MacOS support in terms of prority)
- [ ] VR support
- [ ] IR support
- [ ] C# support

## Disclaimers

All of the files located in soloud/ and include/sys/soloud are modified versions of files orginially created for the [SoLoud audio engine](https://github.com/jarikomppa/soloud).
