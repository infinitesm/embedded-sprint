# Day 1 – Aug 11: Memory and Pointers Mastery

**Summary**  
Build a foundation in C memory layout, pointer operations, array handling, and manual memory management. Understanding these core concepts is essential for low-level embedded systems work, where you often manage memory directly without the safety of higher-level abstractions.

---

## Topics
- Stack vs Heap segmentation
- Pointer arithmetic
- Arrays vs Pointers
- `typedef` and `struct` usage
- Function pointers
- Dynamic memory with `malloc`, `realloc`, and `free`

---

## Tasks
- Watch Neso Academy’s ["Pointers in C"](https://www.youtube.com/playlist?list=PLBlnK6fEyqRiVhbXDGLXDk_OQAeuVcp2O) playlist.
- Read [GeeksforGeeks – Memory Layout of C Programs](https://www.geeksforgeeks.org/memory-layout-of-c-program/)
- Take notes on memory regions and how stack/heap grows
- Write a `Makefile` to build multiple C files (`memlab.c`, `ptrutils.c`, `main.c`, `dynarray.c`)
- Implement the three deliverables described below in full

---

## Deliverables

### 1. `memlab.c` – Visualizing Memory Segments

**Goal**: Observe the address layout of various memory segments by printing their addresses.

**Requirements**:
- Declare at least one **local variable** in `main()` to represent a **stack** variable.
- Declare a **local variable** in a helper function to show **stack growth**.
- Use `malloc()` to allocate memory on the **heap**.
- Declare one **global or static** variable for `.data` or `.bss`.
- Declare a **function pointer** to visualize the **code segment**.
- Print all addresses using `printf("%p", ...)`.
- Annotate with comments on which segment each address belongs to.
- Include sample output (in comments) to demonstrate stack vs heap direction.
- Validate no memory leaks using:

```sh
valgrind --leak-check=full ./memlab
```

**Example**:

```c
#include <stdio.h>
#include <stdlib.h>

int global_var = 42; // .data segment

void helper() {
    int helper_local = 2; // Stack (deeper)
    printf("Helper stack variable: %p\n", (void*)&helper_local);
}

int main() {
    int main_local = 1; // Stack
    int *heap_var = malloc(sizeof(int) * 10); // Heap
    void (*func_ptr)() = &helper; // Code (text) segment

    printf("Main stack variable: %p\n", (void*)&main_local);
    printf("Heap allocation:     %p\n", (void*)heap_var);
    printf("Global variable:     %p\n", (void*)&global_var);
    printf("Function pointer:    %p\n", (void*)func_ptr);

    helper();
    free(heap_var);
    return 0;
}
```

---

### 2. `ptrutils.c` – Pointer Utility Functions

**Goal**: Implement essential string/pointer utilities using **pointer arithmetic only** (no indexing).

**Functions to implement**:
- `int my_strlen(const char *s)`
- `void my_strcpy(char *dest, const char *src)`
- `void swap_int(int *a, int *b)`

**Constraints**:
- Use only pointer operations (`*p`, `p++`, etc.)
- No array indexing (`[]`)
- Cover corner cases: empty string, `src == dest`, `a == b`

**Examples**:

```c
int my_strlen(const char *s) {
    const char *start = s;
    while (*s) s++;
    return s - start;
}

void my_strcpy(char *dest, const char *src) {
    while ((*dest++ = *src++));
}

void swap_int(int *a, int *b) {
    if (a == b) return;
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
```

**Test cases in `main.c`**:
- `my_strlen("")` → 0
- `my_strcpy(dest, src)` with `src == dest`
- `swap_int(&x, &x)` to ensure no crash

---

### 3. `dynarray.c` and `dynarray.h` – Dynamic Integer Array

**Goal**: Build a dynamic array struct that **auto-resizes** as elements are added/removed.

**Header: `dynarray.h`**

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

**Source: `dynarray.c`**

```c
#include <stdlib.h>
#include "dynarray.h"

void dyn_init(DynArray *a) {
    a->capacity = 4;
    a->size = 0;
    a->data = malloc(sizeof(int) * a->capacity);
}

void dyn_push(DynArray *a, int value) {
    if (a->size == a->capacity) {
        a->capacity *= 2;
        a->data = realloc(a->data, sizeof(int) * a->capacity);
    }
    a->data[a->size++] = value;
}

int dyn_pop(DynArray *a) {
    if (a->size == 0) return -1; // underflow
    int val = a->data[--a->size];
    if (a->size < a->capacity / 4 && a->capacity > 4) {
        a->capacity /= 2;
        a->data = realloc(a->data, sizeof(int) * a->capacity);
    }
    return val;
}

void dyn_free(DynArray *a) {
    free(a->data);
    a->data = NULL;
    a->size = 0;
    a->capacity = 0;
}
```

**Tests in `main.c`**

```c
#include <stdio.h>
#include "dynarray.h"

int main() {
    DynArray a;
    dyn_init(&a);
    for (int i = 0; i < 10; i++) dyn_push(&a, i);
    for (int i = 0; i < 5; i++) printf("%d\n", dyn_pop(&a));
    dyn_free(&a);
    return 0;
}
```

---

## Tools to Use

- `valgrind` to check for memory leaks.
- `make` to manage build process.
- `gcc -Wall -Wextra -g` for debug-friendly builds.
- Git CLI to track your commits.

---

## Final Deliverables

- `memlab.c` – prints out memory segment addresses with annotations
- `ptrutils.c` + `main.c` – pointer utilities fully tested
- `dynarray.h` + `dynarray.c` + `main.c` – dynamic resizing array with shrinking logic
- `Makefile` to build everything with a single command
- All memory leaks verified with `valgrind`
