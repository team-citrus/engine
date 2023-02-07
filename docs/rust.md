#  Rust interoperability

Rust is a powerful language, and is only ever going to become more popular.
Rust support is an obvious choice to make, however, writing both APIs will be very difficult.

## Name convientions, case, etc.

C++ abides by the style guide and programmer's guide.
Rust abides by the Rust style guide.

## Interoperability internals

### **C++**

From C++, we define special functions to serve as bridges.
We provide types for easier interoperability (ie. `typedef int i32`).

### **Rust**

From Rust we employ `#[cxx::bridge]`s to allow us to import some functions from C++.

## Components

With Rust components, there are two possible avenues of attack we can take:
1. A queue of functions to call from `engine::internals::gameplayMain()` that Rust code can add to
2. A trait based system implemented in Rust that can be called from `engine::internals::gameplayMain()`