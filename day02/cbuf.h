//
// Created by kyle-dudley on 2025-08-12.
//

#ifndef CBUF_H
#define CBUF_H
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct {
    // FIFO: First In, First Out
    // Circular: When you reach the end of the array you "wrap around" to the start, hence "circular"
    // Wrap-around logic implemented with (index + 1) % capacity
    // Fixed size, does not grow or shrink dynamically (makes most sense for buffers)
    // Used for real-time applications like UART input buffering, where data arrives continuously and must be processed in order.
    int *buffer;
    size_t head; // where new data is written (enqueue)
    size_t tail; // where data is read (dequeue)
    size_t capacity;
    size_t size;
} CircularBuffer;

// initialize the circular buffer
static inline void cb_init(CircularBuffer *cb, size_t cap) {
    // should be careful to assume cap is valid input
    // here we're just focused on ring buffer implementation so it doesn't matter
    // again I fully control the environment, so I can make shortcuts for my code
    cb->buffer = malloc(cap * sizeof *cb->buffer);
    if (!cb->buffer) {
        cb->capacity = 0;
        cb->size = 0;
        cb->head = 0;
        cb->tail = 0;
        // The void return type would lead a user to think initialization is correct
        // The user won't have any indication if something went wrong
        // We just assume it works fine
        return;
    }
    cb->capacity = cap;
    cb->size = 0;
    cb->head = 0;
    cb->tail = 0;
}

// Check if the circular buffer is full
static inline bool cb_is_full(CircularBuffer *cb) {
    return cb->size == cb->capacity;
}

// Check if the circular buffer is empty
static inline bool cb_is_empty(CircularBuffer *cb) {
    return cb->size == 0;
}

// Write (enqueue) a data point to the circular buffer (at the head)
static inline bool cb_enqueue(CircularBuffer *cb, int val) {
    // Should fail if full
    if (cb_is_full(cb)) {
        return false; // This will prevent the buffer from overwriting old data if the buffer overflows.
    }

    // wrap-around logic
    cb->buffer[cb->head] = val;
    cb->head = (cb->head + 1) % cb->capacity;
    cb->size++;
    return true;
}

// Read a data point (dequeue) from the circular buffer (at the tail)
static inline bool cb_dequeue(CircularBuffer *cb, int *val) {
    // Should fail if empty
    if (cb_is_empty(cb)) {
        return false; // Can't dequeue data if there isn't any :)
    }

    *val = cb->buffer[cb->tail];
    cb->tail = (cb->tail + 1) % cb->capacity;
    cb->size--;
    return true;
}

// Read a data point without removing, no movement of head or tail here
static inline bool cb_peek(CircularBuffer *cb, int *val) {
    if (cb_is_empty(cb)) {
        return false; // Can't read data if there isn't any :)
    }

    *val = cb->buffer[cb->tail];
    return true;
}

// Free allocated memory for the buffer
static inline void cb_free(CircularBuffer *cb) {
    free(cb->buffer);
    cb->buffer = NULL;
    cb->size = 0;
    cb->capacity = 0;
    cb->head = 0;
    cb->tail = 0;
}

#endif