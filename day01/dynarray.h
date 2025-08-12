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