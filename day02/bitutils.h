#ifndef BITUTILS_H
#define BITUTILS_H
#include <stdbool.h>
#include <stdint.h>

// Set bit at pos to 1
void bit_set(uint32_t *val, uint8_t pos);

// Clear bit at pos to 0
void bit_clear(uint32_t *val, uint8_t pos);

// Toggle bit at pos (flip)
void bit_toggle(uint32_t *val, uint8_t pos);

// Test if bit at pos is 1
bool bit_test(uint32_t val, uint8_t pos);

#endif