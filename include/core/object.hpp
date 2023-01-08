/*
*   name: include/core/object.hpp
*   origin: Citrus Engine
*   purpose: Provide the engine::object class
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_OBJECTS_HPP__
#define CITRUS_ENGINE_OBJECTS_HPP__

#include <cstdint>
#include "include/core/extensions.hpp"
#include "include/core/component.hpp"
#include "include/core/mem.hpp"

namespace engine
{
    class object
    {
        public:
            object()
            {
                componentCount = 0;
                components = memalloc(sizeof(component*), MEM_FLAG_UNIT_BYTE);
            }
            // Functions like Unity's AddComponent<T>()
            template<typename T>
            T &addComponent()
            {
                componentCount++;
                components = memrealloc(components, sizeof(component*) * componentCount, MEM_FLAG_UNIT_BYTE);
                components[componentCount - 1]->awake();
                return *components[componentCount - 1];
            }

            // Functions like Unity's GetComponent<T>()
            template<typename T>
            OPERATOR T &getComponent()
            {
                for(int i = 0; i < componentCount; i++)
                {
                    if(components[i]->componentID == typeid(T))
                    {
                        return *components[i];
                    }
                }
            }
        private:
            int componentCount;
            component **components;  
    };
};

#endif