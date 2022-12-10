# Components

As is common place with modern game engines, we will keep track of the game spaces using scenes/levels/whatever you wanna call em same difference.
Within them, we will objects to represent everything.
Within these objects, we will use components to do the work for each object.
Components will be one of the main ways for game code to execute.
Components will also be used for physics, and materials.
Our components model will be modeled in a similar way to Unity's version, namely copying `awake()`, `start()`, `update()`, `fixedUpdate()`, etc.

All components will be based around a base class, `engine::component`. From there, the rest will be handled by users and some engine devs.
