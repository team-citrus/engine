# C++ Code Style Guide

## Compiler extensions

You should avoid using compiler extensions too often, however there is nothing wrong with using them.
Common compiler extensions as well as some additional defines can be found in include/core/extensions.hpp, anything defines in that file can be used freely.
Inline assembly is discouraged, but not illegal.
If you ever use inline assembly, make sure it is well commented to make any future translations easier, and use gcc inline assembly with constraints for clarity and to prevent the use of black magic.

## Preprocessor defines

Preprocessor defines should be written in all caps.
SCREAMING_SNAKE_CASE should be used as well.

## Headers

`#pragma once` should be avoided.
Instead traditional `#ifndef ... #define ...` include guards should be used.
Include guard defines should use the following naming scheme:
`CITRUS_ENGINE_{FILENAME}_{EXTRA_STUFF}_HPP__`.

## Function naming

Function names should be conise but descriptive.
Function names should use camelCase.

## Inline functions

Inline functions should be used sparingly.
Heavily used but small static functions should always be inlined.
Large, but rarely used static functions should always be inlined.
Extern inline functions should not be used, except for class methods.

Operators should be defined with `OPERATOR`, which is a macro defined in include/core/extensions.hpp that will set it to always inline.
Although this is not manditory, it is prefered.
Simple method and functions should follow that same rule.

## OOP features

### `new` and `delete`

The `memnew()` and `memdelete()` defines should only be used when they clearly and obviously improve code readablity.
Otherwise, `engine::memalloc` and friends should be used.

### Classes

Classes should essentially be used where ever structs would be used in C.
Classes shouldn't be abused, and should be used sparingly.
Classes should use operators whenever possible in place of methods.

### Namespaces

New namespaces should be added as sparingly as possible.
Namespaces, except in code that defines their function, should be included sparingly.

### Templates

Templates should be used whenever it makes logical sense, and as optimizations.
Templates should not be abused.
A perfect example of these critera is the Unity function `GetComponent<T>()`, even though it is C# code.

## Keywords

`const` should be avoided and instead preprocessor defines should be used.
Classical C bitwise operators should be used instead of the newer ones (`bitand`, `bitor`, etc).

## Standard library use

libc functions don't have any restrictions, they can be used anywhere.
STL functions and classes should not be used, as they frequently abuse templates creating overly complicated symbols.
If you need proof of this, just read any of your STL header files and see for yourself.

STL restrictions have some exceptions, namely, we can use `typeinfo`.

For replacing `std::vector`, `std::map`,  `std::string`, and possibly `std::stringstream`, and `std::fstream` we will create our own solution following a similar interface to the STL version.

Until these versions are created, `std::vector` and `std::string` can be used.

## C++11 and later features

C++17 should be the latest standard used for any engine code.
Most new C++17 keywords/features like `auto` and lambdas should be avoided, however it isn't illegal to use them.
`constexpr` should be avoided like `const`.
`nullptr` should be avoided and instead the classical `NULL` found in `cstdlib` should be used.
Newer redundant features should be avoided.
`std::shared_ptr`, `std::unique_ptr`, and `std::weak_ptr` should not be used, regular C pointers should be used instead.
