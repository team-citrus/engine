/*
*   name: include/core/mesh_int.hpp
*   origin: Citrus Engine
*   purpose: Provide internals for meshes
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_INTERNALS_MESH_HPP__
#define CITRUS_ENGINE_INTERNALS_MESH_HPP__

#include <cstddef>
#include "core/pair.hpp"
#include "core/rustints.h"
#include "core/transform.hpp"
#include "core/component.hpp"

#define ENGINE_MESH_MEM (1 << 0) // Should be in addressable memory, not accessed via IO, MMIO is still on the table
#define ENGINE_MESH_RENDER (1 << 1) // Used in the render process, insures it will be stored in RAM, and not stored as MMIO 
#define ENGINE_MESH_RAM ENGINE_MESH_RENDER // Should be stored in RAM
#define ENGINE_MESH_MMIO (1 << 2) // Access using MMIO
#define ENGINE_MESH_MMIO_BIG_PAGES ((1 << 3) | MESH_MMIO) // Access using MMIO + big pages
#define ENGINE_MESH_WILL_BE_EDITED (1 << 4) // Will be edited, allocates new memory regardless of if a version of the mesh is currently in RAM
#define ENGINE_MESH_NEW_MESH ((1 << 5) | MESH_WILL_BE_EDITED) // Creates a completely new mesh, entails MESH_WILL_BE_EDITED

namespace engine
{
	namespace internals
	{
		class Mesh : engine::Mesh
		{
			public:
			// Creates an uninitalized mesh
			Mesh(); 
			// Loads mesh, and returns this class.
			Mesh(const char *name);
			// Loads mesh, and returns this class.
			Mesh(const char *name, int flags);

			Vertex *GetVertexBuffer();

			// TODO: Stuff
		};

		class MeshBufferHandle
		{
			size_t refs;
			// TODO: stuff
			public:
			MeshBufferHandle(const char *meshName, int flags);
			~MeshBufferHandle();

			Vector<Vertex> verts;
			Vector<int> indexBuffer;

			// TODO: Bones, Vertex Groups, etc.
			
			static MeshBufferHandle *getNew(const char *meshName);
			static MeshBufferHandle *getNew(const char *meshName, int flags);

			Vector<Tri> constructFaceBuffer()
			{
				Vector<Tri> ret;
				for(size_t i = 0; i < indexBuffer.getCount()/3; i++)
				{
					ret.push(Tri(verts[indexBuffer[i * 3]], verts[indexBuffer[(i * 3) + 1]], verts[indexBuffer[(i * 3) + 2]]));
				}
				return ret;
			}

			void removeRef()
			{
				refs--;
				if(refs == 0)
				{

					delete this;
				}
			}
		};
	}

	#ifdef CITRUS_ENGINE_FINE_TUNE

	using CoreMesh = internals::Mesh;

	#endif

	// TODO: mesh.cpp
}

#endif