/*
*	This file is part of the Citrus Engine.
*
*	The Citrus Engine is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
*
*	The Citrus Engine is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
*
*	You should have received a copy of the GNU Lesser General Public License along with the Citrus Engine. If not, see <https://www.gnu.org/licenses/>	
*/

#ifndef CITRUS_ENGINE_OBJECTS_HPP__
#define CITRUS_ENGINE_OBJECTS_HPP__

#include <cstdint>
#include "include/core/extensions.hpp"
#include "include/core/component.hpp"

namespace engine
{
    class object
    {
        public:
            // Functions like Unity's AddComponent<T>()
            template<typename T>
            T &addComponent();

            // Functions like Unity's GetComponent<T>()
            template<typename T>
            OPERATOR T &getComponent()
            {
                component *cur = components;
                for(int i = 0; i < componentCount; i++)
                {
                    if(cur->componentID == typeid(T))
                        return *cur;
                    cur = (component*)((uintptr_t)cur + cur->size);
                }
            }
        private:
            int componentCount;
            component *components;  
    };
};

#endif