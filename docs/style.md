# C++ Code Style Guide

## Compiler extensions

**DO NOT USE ANY INLINE ASSEMBLY WHATSOEVER. WE CANNOT STRESS THIS ENOUGH.**

You should refrain from using any compiler extensions, anonymous structs and unions are exceptions, as msvc, gcc, and clang support them.
Use them only when necessary.

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
A perfect example of these critera is the Unity function `GetComponent<T>()`, even though it is C# code.

## Keywords

`const` should be avoided and instead preprocessor defines should be used.
Classical C bitwise operators should be used instead of the newer ones (`bitand`, `bitor`, etc).

## Standard library use

libc functions don't have any restrictions, they can be used anywhere.
STL functions and classes should not be used at all, as they frequently abuse templates creating overly complicated symbols.
If you need proof of this, just read any of your STL header files and see for yourself.

For multithreading, because we cannot use `threads` and `mutex`, to prvenet issues regarding the Windows API and pthreads, we will create our own wrappers around them.
For replacing `std::vector` and `std::string`, we will create our own solution following a similar interface to the STL version.

Until these versions are created, `std::vector` and `std::string` can be used.

## C++11 and later features

C++11 should be the latest standard used for any engine code.
Most new C++11 keywords like `auto` and lambdas should be avoided.
`constexpr` should be avoided like `const`.
`nullptr` should be avoided and instead the classical `NULL` found in `cstdlib` should be used.
Newer redundant features should be avoided.
`std::shared_ptr`, `std::unique_ptr`, and `std::weak_ptr` should not be used, regular C pointers should be used instead.
