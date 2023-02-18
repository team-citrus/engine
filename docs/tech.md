# Technologies in use

For graphics, Vulkan is the primary API.
OpenGL should be supported for systems without Vulkan support, specifically OpenGL ES2
Both will also use GLM to make all of our lives easier.

For physics, things are split.
For 2D physics, box2d.
For 3D physics, bullet.

Rendering will be handled in house.

SoLoud for sound.
