#include "bitutils.h"
#include "registers.h"
#include "../minitest/minitest.h"

static inline void show(const ControlRegister cr) {
    printf("Register: %#04x (MODE=%d ENABLE=%d)\n", cr.reg, cr.bits.MODE, cr.bits.ENABLE);
}

// Test cases
// 1. test initialization, all bits should be == 0
TEST_CASE(test_init) {
    ControlRegister cr = { .reg = 0 };
    show(cr);
    TEST(ts, "reg == 0", cr.reg == 0);
}

// 2. test enable functions
TEST_CASE(test_enable_functions) {
    ControlRegister cr = { .reg = 0 };

    // Enable INTERRUPT flag
    enableInterruptFlag(&cr);
    show(cr);
    TEST(ts, "INTERRUPT flag enabled", cr.bits.INTERRUPT == 1);

    // Enable ENABLE flag
    enableEnabledFlag(&cr);
    show(cr);
    TEST(ts, "ENABLE flag enabled", cr.bits.ENABLE == 1);
}

// 3. test disable functions
TEST_CASE(test_disable_functions) {
    ControlRegister cr = { .reg = 0 };

    // Enable first (without enable function in case it fails)
    cr.bits.ENABLE = 1;
    cr.bits.INTERRUPT = 1;

    // Disable ENABLE flag
    disableEnabledFlag(&cr);
    show(cr);
    TEST(ts, "ENABLE flag disabled", cr.bits.ENABLE == 0);

    // Disable INTERRUPT flag
    disableInterruptFlag(&cr);
    show(cr);
    TEST(ts, "INTERRUPT flag disabled", cr.bits.INTERRUPT == 0);

}
// 4. test toggle functions
TEST_CASE(test_toggle_functions) {
    ControlRegister cr = { .reg = 0 };

    // Toggle both ENABLE & INTERRUPT flags, should be 1 since init to 0.
    toggleEnabledFlag(&cr);
    show(cr);
    TEST(ts, "toggle ENABLE flag", cr.bits.ENABLE == 1);

    toggleInterruptFlag(&cr);
    show(cr);
    TEST(ts, "toggle INTERRUPT flag", cr.bits.INTERRUPT == 1);
}

// 5. test setting mode (valid and invalid inputs)
TEST_CASE(test_set_mode) {
    ControlRegister cr = { .reg = 0 };

    // valid inputs
    setMode(&cr, 1);
    show(cr);
    TEST(ts, "mode == 1", cr.bits.MODE == 1);
    setMode(&cr, 3);
    show(cr);
    TEST(ts, "mode == 3", cr.bits.MODE == 3);

    // invalid input
    setMode(&cr, 4);
    show(cr);
    TEST(ts, "invalid mode input (4) ignored, mode == 3", cr.bits.MODE == 3);
}

// 6. test read functions
TEST_CASE(test_read_functions) {
    ControlRegister cr = { .reg = 0 };

    // set random values
    cr.bits.INTERRUPT = 1;
    cr.bits.ENABLE = 0; // redundant, explicitly written just for clarity.

    show(cr);
    TEST(ts, "(read) interrupt == 1", readInterruptFlag(&cr) == 1);
    TEST(ts, "(read) enable == 0", readEnabledFlag(&cr) == 0);
}

// 7. test field independence (e.g. changing MODE does not affect ENABLE or INTERRUPT)
TEST_CASE(test_field_independence) {
    ControlRegister cr = { .reg = 0 };

    // 1) MODE change shouldn’t affect ENABLE/INTERRUPT
    cr.bits.MODE = 2;
    show(cr);
    TEST(ts, "mode set independence",
         (cr.bits.ENABLE == 0) && (cr.bits.INTERRUPT == 0));

    // 2) INTERRUPT change shouldn’t affect ENABLE/MODE
    cr.reg = 0; // reset
    cr.bits.INTERRUPT = 1;
    TEST(ts, "interrupt flag independence",
         (cr.bits.ENABLE == 0) && (cr.bits.MODE == 0));

    // 3) ENABLE change shouldn’t affect INTERRUPT/MODE
    cr.reg = 0; // reset
    cr.bits.ENABLE = 1;
    TEST(ts, "enable flag independence",
         (cr.bits.INTERRUPT == 0) && (cr.bits.MODE == 0));
}


// 8. test raw register view (modifying flag modifies the correct bit positions)
TEST_CASE(test_bitset_positions) {
    ControlRegister cr = { .reg = 0 };

    cr.bits.MODE = 2;
    cr.bits.ENABLE = 1;
    cr.bits.INTERRUPT = 1;
    show(cr);
    TEST(ts, "combined value == 0x0E", cr.reg == 0x0Eu);
}

int main() {
    const Test tests[] = {
        {"test_init", test_init},
        {"test_enable_functions", test_enable_functions},
        {"test_disable_functions", test_disable_functions},
        {"test_toggle_functions", test_toggle_functions},
        {"test_set_mode", test_set_mode},
        {"test_read_functions", test_read_functions},
        {"test_field_independence", test_field_independence},
        {"test_bitset_positions", test_bitset_positions}
    };
    return run_all_tests(tests, sizeof(tests) / sizeof(tests[0]));
}
