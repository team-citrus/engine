# Memory management

Memory management is a critical part of all programs, especially game engines.
We have to make our memory management very efficent, including providing multiple simple methods to allocate memory.
We can't use the heap for everything, it can be inefficent for large allocations, being little more than a wrapper for a lower level function like `mmap()`.
The heap is best for arrays, small data that needs to be dynamically allocated.
For larger allocations, we provide two methods, pool allocation, and page allocation.

## Pool Allocation

Pool allocation essentially provides a large pool of memory to use to create smaller allocations.
Pool allocation locks the entire pool whenever an allocation is made, making it inefficent for constant allocation and deallocation, but good for game objects, scene data, and geometry.
The pool can be resized whenever necessary, and is under complete engine control.

## Page allocation

Page allocation is essentially just code for `mmap()`.
Page allocation directly calls operating system calls to create allocations, making it ideal for large things that have to persist in memory across scenes, such as commonly used resources.
Page allocation will likely be used frequently in resource loaders.
