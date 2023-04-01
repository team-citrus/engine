/*
*	name: include/core/toml.hpp
*	origin: Citrus Engine
*	purpose: Simple TOML parser
*	author: https://github.com/ComradeYellowCitrusFruit
*	license: LGPL-3.0-only
*/

#include <toml.hpp>
#include "core/extensions.h"

#ifndef CITRUS_ENGINE_TOML_PARSER_HPP__
#define CITRUS_ENGINE_TOML_PARSER_HPP__

namespace engine
{
	using toml = engine::internals::toml;
	using namespace engine::toml;
}

#endif