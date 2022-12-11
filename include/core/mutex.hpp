/*
*	This file is part of the Citrus Engine.
*
*	The Citrus Engine is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
*
*	The Citrus Engine is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
*
*	You should have received a copy of the GNU Lesser General Public License along with the Citrus Engine. If not, see <https://www.gnu.org/licenses/>	
*/

#ifndef CITRUS_ENGINE_MUTEXES_HPP__
#define CITRUS_ENGINE_MUTEXES_HPP__

#include "include/core/extensions.hpp"

namespace engine
{
	namespace internals
	{
		class guard
		{
			OPERATOR guard(mutex mtx)
			{
				
			}
		};

		class mutex
		{
			private:
			int mtx

			public:
			OPERATOR mutex()
			{
				mutex = 0;
			}

			OPERATOR void lock()
			{
				mtx = 1;
				return;
			}
		
			OPERATOR void unlock()
			{
				mtx = 0;
				return;
			}
			
			OPERATOR bool isLocked()
			{
				if(mtx)
					return true;
				else
					return false;
			}

			OPERATOR void wait()
			{
				while(mtx);
				return;
			}

			// TODO: Add OPERATOR void wait(uint64_t timeout)
		};
	};
};

#endif
