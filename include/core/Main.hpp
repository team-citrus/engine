/*
*	name: include/core/Main.hpp
*	origin: Citrus Engine
*	purpose: Provide the main engine functions
*	author: https://github.com/ComradeYellowCitrusFruit
*	license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_MAIN_FUNCTIONS_HPP__
#define CITRUS_ENGINE_MAIN_FUNCTIONS_HPP__

#include <thread>
#include <ctime>
#include <csetjmp>

namespace engine
{
    namespace internals
    {
        extern bool usingVulkan;
        extern int frameRate;
        extern jmp_buf buf

        extern std::thread render;
        extern std::thread phys;
        extern std::thread mix;
        extern std::thread gameplay;

        // Render the scene, and draw the UI
        int draw();
        // Step the physics simulation, and call all physics triggered functions
        int physmain();
        // Perform audio operations
        int mix();
        // Run the gameplay code
        int gameplayMain();
    };
};

#endif