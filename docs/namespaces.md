# A list of the C++ namespaces

- `engine` - The main overarching namespace.
  - `engine::internals` - Internal stuff game code shouldn't touch
    - `engine::internals::Vulkan` - Vulkan internal functions used to provide abstractions over Vulkan for other graphics functions
    - `engine::internals::OpenGL` - OpenGL internal functions used to provide abstractions over OpenGL for other graphics functions
    - `engine::internals::sound` - Low level sound manipulation
    - `engine::internals::core` - Low level core information meant to be accessed from higher level namespaces
    - `engine::internals::physics` - Physics internal functions meant to abstract over box2d and Bullet
  - `engine::physics` - Physics functions to provide physics abstractions for game code
    - `engine::physics::core` - Advanced physics functions, with more direct access to the simulations themselves
  - `engine::render` - Rendering pipeline direct access
  - `engine::sound` - Sound management functions
  - `engine::UI` - UI manipulation
  - `engine::scenes` - Scene loading and manipulation
  - `engine::core` - Advanced engine core manipulation between the levels of `engine` and `engine::internals::core`
