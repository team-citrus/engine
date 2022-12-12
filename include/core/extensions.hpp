/*
*	This file is part of the Citrus Engine.
*
*	The Citrus Engine is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
*
*	The Citrus Engine is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
*
*	You should have received a copy of the GNU Lesser General Public License along with the Citrus Engine. If not, see <https://www.gnu.org/licenses/>	
*/

#ifndef CITRUS_ENGINE_COMPILER_EXTENSIONS_HPP__
#define CITRUS_ENGINE_COMPILER_EXTENSIONS_HPP__

#ifdef __GNUC__

#define _GNU_ __GNUC__

#define _ALWAYS_INLINE_ __attribute__((always_inline))
#define _DEPRECATED_ __attribute__((deprecated))
#define _NORETURN_ __attribute__((noreturn))
#define _PACKED_(...) __attribute__((__packed__)) __VA_ARGS__

#elif defined(_MSC_VER)

#define _MSVC_ _MSC_VER

#define _ALWAYS_INLINE_ __forceinline
#define _DEPRECATED_ __declspec(deprecated)
#define _NORETURN_ __declspec(noreturn)
#define _PACKED_(...) __pragma(pack(push, 1)) __VA_ARGS__ __pragma(pack(pop))

#endif

#define _FORCE_INLINE_ _ALWAYS_INLINE_
#define OPERATOR _ALWAYS_INLINE_

#define _STRINGIFY_(...) __STRINGIFY__(##__VA_ARGS__)
#define __STRINGIFY__(...) #__VA_ARGS__

#endif
