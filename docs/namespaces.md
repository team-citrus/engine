# A list of the C++ namespaces

- `engine` - The main overarching namespace.
  - `engine::internals` - Internal stuff game code shouldn't touch
    - `engine::internals::Vulkan` - Vulkan internal functions used to provide abstractions over Vulkan for other graphics functions
    - `engine::internals::OpenGL` - OpenGL internal functions used to provide abstractions over OpenGL for other graphics functions
    - `engine::internals::sound` - Low level sound manipulation
    - `engine::internals::physics` - Physics internal functions meant to abstract over box2d and Bullet
  - `engine::physics` - Physics functions to provide physics abstractions for game code
    - `engine::physics::core` - Advanced physics functions, with more direct access to the simulations themselves
  - `engine::render` - Rendering pipeline direct access
  - `engine::sound` - Sound management functions
  - `engine::UI` - UI manipulation
  - `engine::scenes` - Scene loading and manipulation
  - `engine::core` - Advanced engine core manipulation between the levels of `engine` and `engine::internals`

## Some additional details about namespaces

Anything from `engine::internals` shouldn't be used in any non-`engine::internals` header.
If a public facing header needs something from `engine::internals`, they should be moved up a level into a public facing namespace, unless absolutely necessary (ie including `box2d/box2d.h` in a header for rigidbodies).
They can however, be included in any source file that needs them.

`engine::internals` level things can include anything they need.
