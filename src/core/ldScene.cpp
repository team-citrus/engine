/*
*   name: src/core/ldScene.hpp
*   origin: Citrus Engine
*   purpose: Implement engine::loadScene()
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#include "core/scene.hpp"
#include "core/scene_int.hpp"

using namespace engine;

int engine::loadScene(int ID)
{
    option<internals::scene &> packedScene = internals::scenes.lookup(ID);
    if(packedScene.isNone())
        return -1;

    internals::loadNecesary = true;
    internals::currentScene = ID;
}