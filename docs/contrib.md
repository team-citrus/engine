# A Brief Guide to Contributing

## Before you write a line of code

**Before writing any C++ code, you must read the style guide (found at docs/style.md).**
You should also read the namespace documentation (found at docs/namespaces.md) and the technology documentation (found at docs/tech.md), however it isn't manditory.

## Git configuration

We prefer the use of rebasing over merging when performing pulls, however merging isn't a crime.
If you want to make the use of rebasing default instead of having to run `git pull --rebase`, run the command `git config pull.rebase true`.

## Styling

**For the majority of styling information, you should refer to the style guide (found at docs/style.md).**
Your code should be easy to read, it shouldn't be rocket science to figure out what a function does.
Your code should also be well commented, to save all of us time figuring out what each line of code does later.
Inline assembly is discouraged, but not illegal.
If you ever use inline assembly, make sure it is well commented to make any future translations easier, and use gcc inline assembly with constraints for clarity and to prevent the use of black magic.

This project is meant to use [RAII](https://en.wikipedia.org/wiki/Resource_acquisition_is_initialization) for managing data.
Keep that in mind with your code.
Small, contained breaks of RAII are fine, however, they should not largely effect the rest of the project.

## Documentation

All you need to do is write readable code, use some comments to make it clear what is going on, and add descriptions in comment form above declarations for classes, methods, macros, and functions.
This should be sufficient for most programmers to understand what is going on, and make documentaion unnecessary.

If documentation is necessary, someone else will handle it.
You don't need to write your own documentation.
Most of docs/ is used for design stuff, anyway.
If you want to write your own documentation anyway, you are free to do so.
