/*
*   name: include/engine/engine.hpp
*   origin: Citrus Engine
*   purpose: A header including all of the core headers of the main API
*   author: https://github.com/ComradeYellowCitrusFruit
*   license: LGPL-3.0-only
*/

#ifndef CITRUS_ENGINE_MAIN_API_HPP__
#define CITRUS_ENGINE_MAIN_API_HPP__

#define __CITRUS_ENGINE_SOURCE_FILE__

#include "../core/extensions.h"
#include "../core/mem.hpp"
#include "../core/object.hpp"
#include "../core/component.hpp"
#include "../core/vector.hpp"
#include "../core/rustints.h"
#include "../core/pair.hpp"
#include "../core/input.hpp"
#include "../core/scene.hpp"
#include "../core/log.hpp"
#include "../core/option.hpp"
#include "../core/transform.hpp"
#include "../core/time.hpp"
#include "../core/hash.hpp"
#include "../physics/vectors.hpp"

#ifndef CITRUS_ENGINE_FINE_TUNE

#include "../core/mesh.hpp"

#undef __CITRUS_ENGINE_SOURCE_FILE__

#else

#include "../core/mesh_int.hpp"

#endif

#endif