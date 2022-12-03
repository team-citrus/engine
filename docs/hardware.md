# Hardware targets

Currently, the plan is to target amd64 CPUs starting with Intel Sandy Bridge CPUs.
Ideally, we should be able to utilize AVX for optimization via compiler optimizations.
We should also use Vulkan to improve rendering performance as well.

## Target minimums

The current target minimum CPU is an Intel i3-8100, however, support for 4-threaded systems will be difficult to implement.
The current target minimum GPU is an GeForce GTX 1050, however, this may be updated at any time.
The current target minimum RAM is 1gb.

## Target ideals

The current target ideal CPU is any Intel i5 with support for 8 or more logical threads.
The current target ideal GPU is a GeForce GTX 1660, however, this might be a bit overkill.
The current target ideal RAM is 4gb, however many games might require 8gb.
