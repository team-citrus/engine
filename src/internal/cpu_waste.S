#include "core/os.h"

#ifdef CITRUS_ENGINE_WIN64

#define GLOBAL_SYMBOL(x) _##x
#define ARGUMENT1 %ecx

#else

#define GLOBAL_SYMBOL(x) x
#define ARGUMENT1 %edi

#endif

.text

.global GLOBAL_SYMBOL(waste_cpu_cycles)

GLOBAL_SYMBOL(waste_cpu_cycles):
    // Stack frames are for losers
    mov ARGUMENT1, %eax

    sub $34, %eax        // should be 38, but subtract 4 to get rid of an add 4
    and $0xffffffb, %eax // round to next multiple of 4
    mov $4, %r10d
    idiv %r10d           // %eax now holds the counter for the main wastage loop.

    .L:
    dec %eax
    cmp %eax, 0
    jne .L

    ret
