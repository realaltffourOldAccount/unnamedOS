#include <stdio.h>

#include <kernel/tty.h>

// TODO: Add Unit Testing
void kernel_main(void) {
    terminal_initialize();
    printf("In kernel!\n");
    printf("Newline test!\n");
}
