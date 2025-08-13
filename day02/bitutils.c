#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "../minitest/minitest.h"
#include "bitutils.h"

/* Helper to show state with the requested format */
static inline void show(const char *label, uint32_t v) {
    // %#010x -> 0x prefix, zero-padded to width 10
    printf("%s = %#010x\n", label, (unsigned)v);
}

/* --- Tests --- */

TEST_CASE(test_set_basic) {
    uint32_t v = 0x00000000;
    show("start", v);

    bit_set(&v, 0);
    show("after set(0)", v);
    TEST(ts, "bit_test(v,0) == true", bit_test(v, 0));
    TEST(ts, "v == (1u<<0)", v == ((uint32_t)1 << 0));

    bit_set(&v, 5);
    show("after set(5)", v);
    TEST(ts, "bit_test(v,5) == true", bit_test(v, 5));
    TEST(ts, "v has bits 0 and 5", v == (((uint32_t)1 << 0) | ((uint32_t)1 << 5)));

    bit_set(&v, 31);
    show("after set(31)", v);
    TEST(ts, "bit_test(v,31) == true", bit_test(v, 31));
    TEST(ts, "v has bits 31,5,0", v == (((uint32_t)1 << 31) | ((uint32_t)1 << 5) | ((uint32_t)1 << 0)));
}

TEST_CASE(test_clear_basic) {
    uint32_t v = 0xFFFFFFFF;
    show("start", v);

    bit_clear(&v, 0);
    show("after clear(0)", v);
    TEST(ts, "bit_test(v,0) == false", !bit_test(v, 0));

    bit_clear(&v, 31);
    show("after clear(31)", v);
    TEST(ts, "bit_test(v,31) == false", !bit_test(v, 31));

    bit_clear(&v, 5);
    show("after clear(5)", v);
    TEST(ts, "bit_test(v,5) == false", !bit_test(v, 5));

    uint32_t expected = 0xFFFFFFFFu;
    expected &= ~((uint32_t)1 << 0);
    expected &= ~((uint32_t)1 << 31);
    expected &= ~((uint32_t)1 << 5);
    TEST(ts, "v matches expected mask after clears", v == expected);
}

TEST_CASE(test_toggle_roundtrip) {
    uint32_t v = 0x00000000;
    show("start", v);

    bit_toggle(&v, 3);
    show("after toggle(3) #1", v);
    TEST(ts, "bit_test(v,3) == true", bit_test(v, 3));
    TEST(ts, "v == (1u<<3)", v == ((uint32_t)1 << 3));

    bit_toggle(&v, 3);
    show("after toggle(3) #2", v);
    TEST(ts, "!bit_test(v,3)", !bit_test(v, 3));
    TEST(ts, "v back to zero", v == 0);

    bit_toggle(&v, 1);
    bit_toggle(&v, 4);
    bit_toggle(&v, 7);
    show("after toggle(1,4,7)", v);
    TEST(ts, "bits 1,4,7 set", v == (((uint32_t)1 << 1) | ((uint32_t)1 << 4) | ((uint32_t)1 << 7)));

    bit_toggle(&v, 4);
    show("after toggle(4) again", v);
    TEST(ts, "bits 1,7 remain", v == (((uint32_t)1 << 1) | ((uint32_t)1 << 7)));
}

TEST_CASE(test_idempotence) {
    uint32_t v = 0;

    // set twice -> same result
    bit_set(&v, 9);
    uint32_t after_first_set = v;
    bit_set(&v, 9);
    show("after set(9) twice", v);
    TEST(ts, "set twice unchanged", v == after_first_set);

    // clear twice -> same result
    bit_clear(&v, 9);
    uint32_t after_first_clear = v;
    bit_clear(&v, 9);
    show("after clear(9) twice", v);
    TEST(ts, "clear twice unchanged", v == after_first_clear);
}

TEST_CASE(test_bounds_guard) {
    // Your functions guard with (pos < 32), so these should be no-ops for pos >= 32.
    uint32_t v = 0xA5A5A5A5u;
    show("start", v);

    bit_set(&v, 32);
    bit_clear(&v, 33);
    bit_toggle(&v, 255);
    show("after out-of-range ops", v);
    TEST(ts, "out-of-range did not change v", v == 0xA5A5A5A5u);

    TEST(ts, "bit_test(v,32) == false", bit_test(v, 32) == false);
    TEST(ts, "bit_test(v,255) == false", bit_test(v, 255) == false);
}

TEST_CASE(test_interactions) {
    uint32_t v = 0;
    show("start", v);

    bit_set(&v, 2);
    bit_set(&v, 6);
    show("after set(2), set(6)", v);
    TEST(ts, "bits 2 and 6 set", bit_test(v, 2) && bit_test(v, 6));

    bit_clear(&v, 2);
    show("after clear(2)", v);
    TEST(ts, "bit 2 cleared, bit 6 remains", !bit_test(v, 2) && bit_test(v, 6));

    bit_toggle(&v, 6);
    show("after toggle(6)", v);
    TEST(ts, "bit 6 cleared", !bit_test(v, 6));

    bit_toggle(&v, 0);
    bit_toggle(&v, 31);
    show("after toggle(0), toggle(31)", v);
    TEST(ts, "bits 0 and 31 set", bit_test(v, 0) && bit_test(v, 31));
}

/* --- Runner --- */
int main(void) {
    const Test tests[] = {
        {"test_set_basic",        test_set_basic},
        {"test_clear_basic",      test_clear_basic},
        {"test_toggle_roundtrip", test_toggle_roundtrip},
        {"test_idempotence",      test_idempotence},
        {"test_bounds_guard",     test_bounds_guard},
        {"test_interactions",     test_interactions},
    };
    return run_all_tests(tests, sizeof(tests) / sizeof(tests[0]));
}


// Set bit at pos to 1
void bit_set(uint32_t *val, uint8_t pos) {
    // behavior would be undefined at anything > 31 (bits are in position 0-31 for unsigned 32-bit integer)
    if (pos < 32) {
        // setting means that either it's already 1 or if not, we set it to 1
        *val |= ((uint32_t) 1 << pos);
    }
}

// Clear bit at pos to 0
void bit_clear(uint32_t *val, uint8_t pos) {
    if (pos < 32) {
        // translate to val = val AND NOT (1 << pos)
        // this would clear anything at the specified position since we are doing 0 & n at pos
        *val &= ~((uint32_t) 1 << pos);
    }
}

// Toggle bit at pos (flip)
void bit_toggle(uint32_t *val, uint8_t pos) {
    if (pos < 32) {
        // ^ is the XOR (exclusive OR operator)
        // At pos, if we have n=0, hence 0 ^ 1, we get 1 as an output
        // And if we have n=1, hence 1 ^ 1, we get 0 as an output
        // This results in toggling the bit at pos
        *val ^= ((uint32_t) 1 << pos);
    }
}

// Test if bit at pos is 1
bool bit_test(uint32_t val, uint8_t pos) {
    if (pos < 32) {
        // this is called masking
        // basically for each bit, returns 1 is both the bit in val and in our bitmask is 1
        // otherwise returns 0
        // since we only define 1 bit in the bitmask to be 1
        // we can just check if the result != 0
        return (val & ((uint32_t) 1 << pos)) != 0;
    }
    // Undefined behavior for invalid position, return false
    return false;
}