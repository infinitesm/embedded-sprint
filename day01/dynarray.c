#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dynarray.h"
#include "../minitest/minitest.h"

TEST_CASE(test_init) {
    DynArray a;
    dyn_init(&a);

    TEST(ts, "init: size=0", a.size == 0);
    TEST(ts, "init: cap=4",  a.capacity == 4);
    TEST(ts, "init: data!=NULL", a.data != NULL);

    dyn_free(&a);
}

TEST_CASE(test_pop_empty) {
    DynArray a;
    dyn_init(&a);

    int r = dyn_pop(&a);
    TEST(ts, "pop empty -> sentinel (-1)", r == -1);
    TEST(ts, "pop empty leaves size=0", a.size == 0);
    TEST(ts, "pop empty leaves cap unchanged (4)", a.capacity == 4);

    dyn_free(&a);
}

TEST_CASE(test_grow_then_shrink) {
    DynArray a;
    dyn_init(&a);

    // push 5 elements to force growth from 4 to at least 8
    for (int i = 0; i < 5; ++i) dyn_push(&a, i + 10);
    TEST(ts, "after 5 pushes: size=5", a.size == 5);
    TEST(ts, "after 5 pushes: capacity doubled to >=8", a.capacity >= 8);

    // pop down to size==1; shrink triggers when size < cap/4 (1 < 2) -> halves to 4
    (void)dyn_pop(&a);
    (void)dyn_pop(&a);
    (void)dyn_pop(&a);
    (void)dyn_pop(&a);
    TEST(ts, "after popping to size=1", a.size == 1);
    TEST(ts, "shrink: capacity halved to 4 when size<cap/4", a.capacity == 4);

    // pop last to size==0; with cap=4, 0 < 1 -> halves to 2
    (void)dyn_pop(&a);
    TEST(ts, "after final pop: size=0", a.size == 0);
    TEST(ts, "shrink again at 0 < 4/4 -> capacity becomes 2", a.capacity == 2);

    dyn_free(&a);
}

TEST_CASE(test_lifo_and_sentinel) {
    DynArray a;
    dyn_init(&a);

    for (int i = 0; i < 3; ++i) dyn_push(&a, i); // 0,1,2
    dyn_push(&a, -1); // store sentinel-like value as real data
    TEST(ts, "push count -> size=4", a.size == 4);

    TEST(ts, "pop returns -1 (real value, not empty)", dyn_pop(&a) == -1);
    TEST(ts, "then 2", dyn_pop(&a) == 2);
    TEST(ts, "then 1", dyn_pop(&a) == 1);
    TEST(ts, "then 0", dyn_pop(&a) == 0);
    TEST(ts, "now empty pop -> sentinel", dyn_pop(&a) == -1);

    dyn_free(&a);
}

TEST_CASE(test_invariants) {
    DynArray a;
    dyn_init(&a);

    for (int i = 0; i < 16; ++i) dyn_push(&a, i);
    for (int i = 0; i < 15; ++i) (void)dyn_pop(&a);

    TEST(ts, "capacity never below size", a.capacity >= a.size);

    dyn_free(&a);
}

int main(void) {
    const Test tests[] = {
        {"test_init",              test_init},
        {"test_pop_empty",         test_pop_empty},
        {"test_grow_then_shrink",  test_grow_then_shrink},
        {"test_lifo_and_sentinel", test_lifo_and_sentinel},
        {"test_invariants",        test_invariants},
    };
    return run_all_tests(tests, sizeof(tests) / sizeof(tests[0]));
}

void dyn_init(DynArray *a) {
    // allocate dynamic array with capacity of 4
    a->size = 0;
    a->capacity = 4;
    a->data = malloc(sizeof *a->data * a->capacity);
}

void dyn_push(DynArray *a, int value) {
    // case 1: size < capacity, no need to allocate new memory, can simply fill allocated memory and increment size
    if (a->size < a->capacity) {
        // push the new value to the dynamic array
        *(a->data + a->size++) = value;
    }
    // case 2: size >= capacity, need to allocate new memory (realloc?), double capacity and increment size
    else {
        // define the new capacity
        // you actually cannot one line this by setting it in realloc
        // doing so would cause behavioral issues if realloc fails due to OOM
        size_t new_capacity = a->capacity * 2;
        // use realloc, this allocates all data from the previous pointer to this new pointer with more memory
        int* new_data = realloc(a->data, sizeof(int) * new_capacity);
        if (!new_data) return; // can handle OOM differently, handling is trivial for this deliverable
        // set the dynamic array pointer to the new pointer
        a->data = new_data;
        // push the new value to the dynamic array
        a->data[a->size++] = value;
        // update the capacity
        a->capacity = new_capacity;
    }
}

int dyn_pop(DynArray *a) {
    // return top element, if exists
    if (a->size == 0) {
        // return a sentinel value here, we have full I/O control so it's not a problem here
        // wouldn't normally do this in production but here it is the simplest way to implement
        return -1;
    }

    // no matter what, we can return the element in the last index
    int res = a->data[--(a->size)];

    // shrink if size < capacity / 4
    // not sure that this is the ideal implementation, but is the simplest
    if (a->size < a->capacity / 4) {
        // define the new capacity
        // again can't one line this incase realloc fails
        size_t new_capacity = a->capacity / 2;
        int* new_data = realloc(a->data, sizeof(int) * new_capacity);
        // even if realloc fails we can still return
        if (new_data) {
            a->data = new_data;
            a->capacity = new_capacity;
        }
    }

    return res;
}

void dyn_free(DynArray *a) {
    // free the allocated memory to prevent memory leak
    free(a->data);

    // null the pointer as it is now unused (good practice)
    a->data = NULL;

    // reset the size and capacity of the now extinct dynamic array
    a->size = 0;
    a->capacity = 0;
}