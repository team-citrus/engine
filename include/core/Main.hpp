/*
*	name: include/core/Main.hpp
*	origin: Citrus Engine
*	purpose: Provide the main engine functions
*	author: https://github.com/ComradeYellowCitrusFruit
*	license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_MAIN_FUNCTIONS_HPP__
#define CITRUS_ENGINE_MAIN_FUNCTIONS_HPP__

namespace engine
{
    namespace internals
    {
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