/*
*   name: include/core/mesh.hpp
*   origin: Citrus Engine
*   purpose: Provide a class for meshes that should work for most things
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_MESH_HPP__
#define CITRUS_ENGINE_MESH_HPP__

#include <cstddef>
#include "core/rustints.h"
#include "core/transform.hpp"

namespace engine
{   
    namespace internals
    {
        typedef struct __MESH_BUFFER_HANDLE meshBufferHandle; // Everyone loves opaque types
    }

    class vertex
    {
        public:
        float3 pos;
        float2 uv;

        // TODO: Vertex normals?
        // TODO: Methods... maybe?
    }

    class face
    {
        public:
        vertex &a;
        vertex &b;
        vertex &c;

        // TODO: Face normals?
        // TODO: Methods... maybe?
    };

    class mesh
    {
        private:
        bool readwrite;
        internals::meshBufferHandle *buf; // Mesh buffers will be used to save memory by pointing them to the same buffer until a write/non-RO access occurs, then creating a new one.
        public:

        // Creates an uninitalized mesh
        mesh(); 
        // Loads mesh, and returns this class.
        mesh(const char *name); 

        face &operator[](size_t i);

        // TODO: Stuff
    };

    using tri = face;
    using vert = vertex;
    using model = mesh;
}

#endif