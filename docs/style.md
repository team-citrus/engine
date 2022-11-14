# C++ Code Style Guide

## Preprocessor defines

Preprocessor defines should be written in all caps.
snake_case should be used as well.

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
Extern inline functions should not be used.

## OOP features

### `new` and `delete`

The `new` and `delete` keywords should only be used when they clearly and obviously improve code readablity.
Otherwise, `malloc` and friends should be used.

### Classes

Classes should essentially be used where ever structs would be used in C.
Classes shouldn't be abused, and should be used sparingly.
Classes should use operators whenever possible in place of methods.

### Namespaces

New namespaces should be added as sparingly as possible.
Namespaces, except in code that defines their function, should be included sparingly.

### Templates

Templates should be used sparingly, only when necessary.
Templates should be kept simple, and clear.

## Keywords

`const` should be avoided and instead preprocessor defines should be used.
Classical C bitwise operators should be used instead of the newer ones.

## C++ standard library features

Use of `chrono` should be avoided.
Use of `thread` and `mutex` is required for any multithreading.
`std::array` should not be used in place of classical C style arrays.
Use of `std::vector` is encouraged, but not required.
The default `malloc` and friends allocator and the `new` allocator should be used, not the ones included in `memory`.
In fact, `memory` should be ignored unless absolutely necessary.

## C++11 and later features

C++11 should be the latest standard used for any engine code.
Most new C++11 keywords like `auto` and lambdas should be avoided.
`constexpr` should be avoided like `const`.
`nullptr` should be avoided and instead the classical `NULL` found in `cstdlib` should be used.
Newer redundant features should be avoided.
`std::shared_ptr`, `std::unique_ptr`, and `std::weak_ptr` should not be used, regular C pointers should be used instead.
