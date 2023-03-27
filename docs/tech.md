# Technologies in use

- For graphics, Vulkan is the primary API.
- For math, GLM to make all of our lives easier.
- For physics, things are split.
- For 2D physics, box2d.
- For 3D physics, bullet.
- For sound, soloud.
- Rendering will be handled in house.

## File formats in use

Technically, this is more of a job for an editor/SDK to handle, however, I don't care.

- For audio, we prefer the OGG VORBIS format.
- For models, we prefer the FBX format, or glTF (.glb version).
- For sprites/textures, we prefer the PNG format.
- For shaders, they should be stored somewhere outside of the main executable, however we don't care where.
- For configuration files, we prefer TOML.

For everything else, we don't care how the data gets there as long as it does.
You can pack and compress everything however you want, and as long as we can get everything when we need it, it's fine.
