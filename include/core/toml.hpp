/*
*	name: include/core/toml.hpp
*	origin: Citrus Engine
*	purpose: Simple TOML parser
*	author: https://github.com/ComradeYellowCitrusFruit
*	license: LGPL-3.0-only
*/

// TODO: make this internal
#include <toml.hpp>
#include "core/extensions.h"

#ifndef CITRUS_ENGINE_TOML_PARSER_HPP__
#define CITRUS_ENGINE_TOML_PARSER_HPP__

namespace engine
{
	using TOMLTable = toml::table;
	using TOMLParseError = toml::parse_error;
	
	// TODO: actual wrapper.
}

#endif