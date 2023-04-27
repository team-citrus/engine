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
#include "core/pair.hpp"
#include "core/rustints.h"
#include "core/transform.hpp"
#include "core/component.hpp"

namespace engine
{   
	using IndexBuffer = Vector<size_t>;

	namespace internals
	{
		class meshBufferHandle
		{
			int flags;
			size_t refs;
			public:
			meshBufferHandle(const char *meshName);
			~meshBufferHandle();

			Vector<Vertex> verts;
			Vector<int> indexBuffer;

			// TODO: Bones, Vertex Groups, etc.
			
			static meshBufferHandle &getNew(const char *meshName, int flags);
			static meshBufferHandle &getNew(int flags);

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

					this->~meshBufferHandle();
				}
			}
		};
	}

	class Vertex
	{
		public:
		Float3 pos;
		Float2 uv;
	}

	class Face
	{
		public:
		Vertex &a;
		Vertex &b;
		Vertex &c;
		Face(Vertex &va, Vertex &vb, Vertex &vc)
		{
			a = va;
			b = vb;
			c = vc;
		}
	};

	class Mesh
	{
		internals::meshBufferHandle &buf; // Mesh buffers will be used to save memory by pointing them to the same buffer until a write/non-RO access occurs, then creating a new one.
		
		public:

		// Creates an uninitalized mesh
		Mesh(); 
		// Loads mesh, and returns this class.
		Mesh(const char *name); 

		Face &indexFace(size_t i);
		Vertex &operator[](size_t i)
		{
			return buf.verts[i];
		}

		// TODO: Stuff
	};

	class MeshRenderer : Component
	{
		public:
		Mesh mesh;

		// TODO: settings and materials and shaders
		// TODO: Skeletons
	}

	using Tri = Face;
	using Vert = Vertex;
	using Model = Mesh;

	// TODO: iterators
}

#endif