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