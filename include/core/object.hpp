#ifndef CITRUS_ENGINE_OBJECTS_HPP__
#define CITRUS_ENGINE_OBJECTS_HPP__

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
            T &getComponent();
        private:
            component *components;  
    };
};

#endif