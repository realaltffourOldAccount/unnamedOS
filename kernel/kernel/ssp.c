#include <stdint.h>
#include <stdlib.h>

// TODO: Add Panic Support.
#include <stdio.h>

#if UINT32_MAX == UINTPTR_MAX
#define STACK_CHK_GUARD 0xe2dee396
#else
#define STACK_CHK_GUARD 0x595e9fbd94fda766
#endif

uintptr_t __stack_chk_guard = STACK_CHK_GUARD;

__attribute__((noreturn))
void __stack_chk_fail(void) {
    // This is kernel, do panic.
    // TODO: Add Panic Support.
    printf("Kernel: Stack Smashing detected.");

    while (1) { }
    __builtin_unreachable();
}
