/*
*   name: src/graphics/vkDraw.cpp
*   origin: Ecosystem Variant of the Citrus Engine
*   purpose: The render function
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/
#include <vulkan.h>
#include <glm/glm.hpp>
#include "core/extensions.h"

struct VertexWeight {
    int index;
    float weight;
};

struct Vertex {
    glm::vec3 pos;
    glm::vec2 uv;
    glm::vec2 normal; // I KNEW IT! NORMALS!
    VertexWeight *boneWeights;
    size_t weightCount;
};

struct Mesh {
    Vertex *verts;
    int *indexBuffer;
    size_t indexBufferLen;

    // TODO: THEM BONES!
};

NOMANGLE NO_INLINE void vk_draw()
{
    // TODO: cosas
}
