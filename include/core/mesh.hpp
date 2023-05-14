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
#include "../core/pair.hpp"
#include "../core/rustints.h"
#include "../core/transform.hpp"
#include "../core/component.hpp"

namespace engine
{   
	using IndexBuffer = Vector<size_t>;

	class Vertex
	{
		public:
		Float3 pos;
		Float2 uv;
	};

	class Face
	{
		public:
		Vertex *a;
		Vertex *b;
		Vertex *c;
		Face(Vertex &va, Vertex &vb, Vertex &vc)
		{
			a = &va;
			b = &vb;
			c = &vc;
		}
	};

	class Mesh
	{
		uintptr_t buf; // Secretly a pointer
		public:

		

		Face &indexFace(size_t i);// Creates an uninitalized mesh
		Mesh(); 
		// Loads mesh, and returns this class.
		Mesh(const char *name);
		Vertex &operator[](size_t i);

		// TODO: Stuff
	};

	class MeshRenderer : Component
	{
		public:
		Mesh mesh;

		// TODO: settings and materials and shaders
		// TODO: Skeletons
	};

	using Tri = Face;
	using Vert = Vertex;
	using Model = Mesh;

	// TODO: iterators
}

#endif