/*
*	This file is part of the Citrus Engine.
*
*	The Citrus Engine is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
*
*	The Citrus Engine is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
*
*	You should have received a copy of the GNU Lesser General Public License along with the Citrus Engine. If not, see <https://www.gnu.org/licenses/>	
*/

#ifndef CITRUS_ENGINE_MEMORY_MANAGEMENT_INTERNALS_HPP__
#define CITRUS_ENGINE_MEMORY_MANAGEMENT_INTERNALS_HPP__

#include <cstdint>
#include "include/core/extensions.hpp"

#define POOL_FREE_BLOCK_MAGIC 0x46534545
#define POOL_ALLOC_BLOCK_MAGIC 0x4E4F474F

namespace engine
{
	namespace internals
	{
		// Pool block
		class poolBlock
		{
			public:
				union
				{
					// Attempt to force compress the structs
					union
					{
						// Header for a contigous free section
						struct
						{
							// Small magic number for a free section
							uint32_t fmagic;
							// Size of section, in blocks
							int fsize;
							// Next contigous section, NULL if last
							poolBlock *next;
							poolBlock *last;
						};
						// Header for an allocated section
						struct
						{
							// Small magic number for an allocated section
							uint32_t amagic;
							// Size of section, in blocks
							int asize;
						};
					};
					// Expand the size to 32 bytes
					uint8_t b[32];
				};
		};

		// The pool, as a class, for convience
		class Pool
		{
			public:
				// Is the pool locked?
				bool locked;
				// The start of the pool
				poolBlock *start;
				// The first free section header block
				poolBlock *head;
				// Size, allocated immediately so as to stay contigous, in blocks
				size_t size;

				// Allocate some blocks
				void *allocate(int blocks);
				// Realloc
				void *reallocate(void *ptr, int blocks);
				// Free some blocks
				void free(engine::internals::poolBlock *bptr);
				
				// Wait
				OPERATOR void wait()
				{
					while(locked);
					return;
				}

				Pool();
				~Pool();
		};

		// Main memory pool
		Pool pool;
	};
};

#endif
