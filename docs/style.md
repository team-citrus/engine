# C++ Code Style Guide

For all engine C++ code, the styling specified here should be used above all else.
If there is anything we haven't specfied, the [Linux Kernel Style Guide](https://www.kernel.org/doc/html/v4.10/process/coding-style.html) should be obeyed, especially the part about burning a copy of the GNU Coding Standards.

## Compiler extensions

You should avoid using compiler extensions too often, however there is nothing wrong with using them.
Common compiler extensions as well as some additional defines can be found in include/core/extensions.h, anything defines in that file can be used freely.
Inline assembly is discouraged, but not illegal.
If you ever use inline assembly, make sure it is well commented to make any future translations easier, and use gcc extended assembly for clarity and to prevent the use of black magic.

## Preprocessor defines

SCREAMING_SNAKE_CASE should be used for preprocessor defines, for the most part.
Generally, preprocessor defines should be avoided, however it isn't illegal to use them.

## Headers

`#pragma once` should be avoided.
Instead traditional `#ifndef ... #define ...` include guards should be used.
Include guard defines should use the following naming scheme:
`CITRUS_ENGINE_{FILENAME}_{EXTRA_STUFF}_HPP__`.

## Function naming

Function names should be conise but descriptive.
Function names should use camelCase, as should all variables.

## Inline functions

Inline functions should be used sparingly.
Heavily used but small static functions should always be inlined.
Large, but rarely used static functions should always be inlined.
Extern inline functions should not be used, except for class methods.

Operators should be defined with `OPERATOR`, which is a macro defined in include/core/extensions.h that will set it to always inline.
Although this is not manditory, it is prefered.
Simple method and functions should follow that same rule.

## Nesting

Generally, you should avoid more than three layers of indentation in code.
Practices like early returns can help avoid this.

## Brackets

Brackets should be put on their own lines for functions.
For `if` blocks and the like, we don't care, do as you will.

```c++
void foo()
{
  // Code
}
```

## Indentation

Indentation should be tabs, set as one pleases.

## Conditionals

### `if`

`if`/`else` chains should be kept as short as possible.
`if`/`else` chains should be used as little as possible.

### `?:`/The Ternary Operator

Since we aren't in Rust, the ternary operator should be used instead of an `if` and `else` when using a simple condition to assign to a variable.
Ternary Operators shouldn't be chained, in any scenario where that would happen, use `if`/`else` chains or `switch` instead.

```c++
// good
int a = thingIsHappening ? 0xABCD : 0xCDAB;

// bad
int a;
if(thingIsHappening)
    a = 0xABCD;
else
    a = 0xCDAB;
```

### `switch`

`switch` should be used instead of `if`/`else` whenever applicable.
`case`s should be indented, and code placed at the same indentation level.

```c++
// good
int getTheValue(int param)
{
    switch(param)
    {
        case 0xA:
            return 'a';
        case 0xB:
            return 'b';
        case 0xC:
            return 'c';
        case 0xD:
            return 'd';
        default:
            return -1;
    }
}

// bad
int getTheValue(int param)
{
    if(param == 0xA)
        return 'a';
    else if(param == 0xB)
        return 'b';
    else if(param == 0xC)
        return 'c'; 
    else if(param == 0xD)
        return 'd';
    else
        return -1;
}
```

## OOP features

### `new` and `delete`

Unless you need to use `new`, you should use `engine::memalloc`.

### Classes

Classes should essentially be used where ever structs would be used in C.
Classes shouldn't be abused, and should be used sparingly.
Classes should use operators whenever possible in place of methods.
Classes should use PascalCase.

### Namespaces

New namespaces should be added as sparingly as possible.
Namespaces, except in code that defines their function, should be included sparingly.

### Templates

Templates should be used whenever it makes logical sense, and as optimizations.
Templates should not be abused.
A good example of a good use of templates would be `getComponent<T>()` found in `core/object.hpp`.

## Keywords

`const` should be avoided unless necessary and instead preprocessor defines should be used.
Classical C bitwise operators should be used instead of the newer ones (`bitand`, `bitor`, etc).

## Standard library use

libc functions, except `malloc` and friends don't have any restrictions, they can be used anywhere.
Although the symbols of `malloc` and friends have been overriden, they should still be avoided in engine code.
STL functions and classes should be avoided, but are fine to use.
However, you can not use `std::vector`, `std::map`, or `std::unordered_map`.
For these, we provide our own alternatives.

## C++11 and later features

C++17 should be the latest standard used for any engine code.
Most new C++17 keywords/features like `auto` and lambdas should be avoided, however it isn't illegal to use them.
`nullptr` should be avoided and instead the classical `NULL` found in `cstdlib` should be used.
Newer redundant features should be avoided.
`std::shared_ptr`, `std::unique_ptr`, and `std::weak_ptr` should not be used, regular C pointers should be used instead.
