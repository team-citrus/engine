# Memory management

Memory management is a critical part of all programs, especially game engines.
We have to make our memory management very efficent, and for this, we need to supply our own memory management system.
`malloc()` and `free()` are very slow, and frequently require system calls when allocating memory.
However, there are to alternative methods we provide `memalloc()`pool allocation.

## Pool Allocation

Pool allocation essentially provides a large pool of memory to use to create smaller allocations.
From this pool, 32 byte blocks are used to allocate memory from the pool.
These blocks are guaranteed to be aligned to a 32 byte boundary.
The pool will lock whenever being allocated to, or memory from it is being freed.
However, the pool is allocated at the start of execution, insuring that it does not require further system calls as well as cutting down on branching, saving lots of overhead inherient to `malloc()` and `free()`.