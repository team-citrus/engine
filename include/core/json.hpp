/*
*   name: include/core/json.hpp
*   origin: Citrus Engine
*   purpose: Provide nlohmann/json while hiding internals
*   author: Niels Lohmann
*   license: MIT
*/
#ifndef CITRUS_ENGINE_JSON_PARSER_HPP__
#define CITRUS_ENGINE_JSON_PARSER_HPP__

#include <string>
#include "core/vector.hpp"
#include "core/pair.hpp"

#define NLOHMANN_JSON_NAMESPACE_BEGIN                \
    namespace engine                                 \
    {                                                \
	inline namespace nlohmann								 \
	{												 \
    inline namespace NLOHMANN_JSON_NAMESPACE_CONCAT( \
                NLOHMANN_JSON_ABI_TAGS,              \
                NLOHMANN_JSON_NAMESPACE_VERSION)     \
    {

#define NLOHMANN_JSON_NAMESPACE_END                                     \
    }  /* namespace (inline namespace) NOLINT(readability/namespace) */ \
    }  /* namespace nlohmann */											\
	}  /* namespace engine */

#include <nlohmann/json.hpp>

#undef NLOHMANN_JSON_NAMESPACE_BEGIN
#undef NLOHMANN_JSON_NAMESPACE_END

namespace engine
{
	using namespace nlohmann::literals;

	using JSon = nlohmann::basic_json<Map, Vector, std::string, int64_t, uint64_t, float, std::allocator, adl_serializer, Vector<uint8_t>>;
}

#endif