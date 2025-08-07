# Day 1 – Aug 11: Memory and Pointers Mastery

## Summary
Build a foundation in C memory layout, pointers, arrays, and manual memory management. Focus on writing low-level C code that manipulates memory directly. This will prepare you for embedded systems work where you must manage stack, heap, and hardware-level pointers efficiently.

---

## Topics
- Stack vs Heap Segmentation
- Pointer Arithmetic
- Arrays vs Pointers
- Structs and Typedef
- Dynamic Memory (`malloc`, `realloc`, `free`)

**Resources**:
- [Memory layout of a C program (GeeksforGeeks)](https://www.geeksforgeeks.org/memory-layout-of-c-program/)
- [Neso Academy – Pointers in C (YouTube)](https://www.youtube.com/playlist?list=PLBlnK6fEyqRjoG6aJ4FvFU1tlXbjLBiOP)
- [Valgrind Usage Guide](https://valgrind.org/docs/manual/quick-start.html)

---

## Tasks
- Watch Neso Academy’s pointers playlist and read the memory layout article
- Implement pointer utility functions without using standard libraries (except `malloc`)
- Build a dynamic array struct with auto-resizing
- Visualize memory layout using stack, heap, and static/global segments

---

## Deliverables

### 1. `memlab.c` – Memory Layout Visualizer

Create a C program that:

- Declares **local variables** in `main()` (stack)
- Declares **local variable** in a helper function (deeper stack)
- Uses `malloc()` to allocate a dynamic array (heap)
- Declares at least one **global or static** variable (data or BSS segment)
- Declares a **function pointer** (code/text segment)
- Prints all memory addresses using `printf("%p", ...)`
- Adds **inline comments** describing segment
- Includes sample output as a comment block
- Verifies correctness using `valgrind`

```c
#include <stdio.h>
#include <stdlib.h>

// Example function skeleton with comments — DO NOT IMPLEMENT
int global_var = 42; // Data segment

void helper() {
    int helper_local = 2; // Stack (deeper)
    // Print address of helper_local
}

int main() {
    int main_local = 1; // Stack
    int *heap_var = malloc(sizeof(int) * 10); // Heap
    void (*func_ptr)() = &helper; // Code segment

    // Print addresses of all variables above

    helper();
    free(heap_var);
    return 0;
}
```

**Example Output** (as comment):
```txt
Main stack variable: 0x7ffcdf0
Helper stack variable: 0x7ffcd70
Heap allocation:     0x560b320
Global variable:     0x60104c
Function pointer:    0x4005d6
```

**Valgrind**:
```bash
valgrind --leak-check=full ./memlab
```

---

### 2. `ptrutils.c` – Pointer Utility Functions

Write the following C functions using **only pointer arithmetic** (no indexing). Document all operations with inline comments.

#### Functions to Implement:
```c
int my_strlen(const char *s);
// Iterate until *s == '\0'; return difference between end and start pointer.

void my_strcpy(char *dest, const char *src);
// Copy one character at a time using pointer dereference (*dest++ = *src++)

void swap_int(int *a, int *b);
// If a == b, do nothing. Otherwise, swap values using a temp variable.
```

#### Example Input/Output:

```c
my_strlen("hello")      // → 5
my_strlen("")           // → 0

char dest[10];
my_strcpy(dest, "hi");  // dest → "hi"

int x = 4, y = 9;
swap_int(&x, &y);       // x → 9, y → 4
```

Edge Cases to Test:
- Same pointer for dest and src
- Swapping pointer to same variable (`swap_int(&x, &x)`)

---

### 3. `dynarray.c/.h` – Dynamic Integer Array

Create a C header and source file for a dynamic array that auto-resizes.

#### Header: `dynarray.h`
```c
#ifndef DYNARRAY_H
#define DYNARRAY_H

#include <stddef.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} DynArray;

void dyn_init(DynArray *a);
void dyn_push(DynArray *a, int value);
int  dyn_pop(DynArray *a);
void dyn_free(DynArray *a);

#endif
```

#### Implementation Instructions (`dynarray.c`)
Each function should include **inline comments** explaining behavior.

- `dyn_init`: allocate 4-element array, set size to 0.
- `dyn_push`: double capacity when full using `realloc`.
- `dyn_pop`: return last element and shrink if size < capacity / 4.
- `dyn_free`: free memory, null out pointer, reset size and capacity.

```c
// Example usage in main.c

DynArray a;
dyn_init(&a);
dyn_push(&a, 10);
dyn_push(&a, 20);
printf("%d\n", dyn_pop(&a)); // → 20
dyn_free(&a);
```

Edge Cases:
- Popping from empty array
- Shrinking array to reduce memory usage

---

## Secondary Skills
- Use of `Makefile` to compile all `.c` and `.h` files
- Practice `git add`, `git commit`, `git push` on your repo
- Use `valgrind` to detect leaks, invalid accesses
