#include <stdio.h>
#include <stdlib.h>

// Global variable stored in initialized data segment
int global_var = 10;

void helper() {
    int helper_local = 2; // On deeper stack
    // print address of helper_local
    printf("Helper function local variable memory address: %p\n", (void*)&helper_local);
}

int main() {
    int main_local = 1; // Stack
    int *heap_var = malloc(10 * sizeof(int)); // Dynamic memory allocation, stored in the heap
    void (*func_ptr)() = &helper; // Pointer to function call stack

    printf("Global variable memory address: %p\n", (void*)&global_var);
    printf("Local variable memory address: %p\n", (void*)&main_local);
    printf("Heap variable memory address: %p\n", (void*)heap_var);
    printf("Helper function call stack memory address %p\n", (void*)&func_ptr);

    // freeing allocated memory for hea    // freeing allocated memory for heap_varp_var to prevent a memory leak
    free(heap_var);
    helper();

    return 0;
}