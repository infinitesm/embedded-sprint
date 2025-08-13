#ifndef MINITEST_H
#define MINITEST_H

#include <stdio.h>
#include <stdbool.h>

// keeps track of total amount of tests, and # of tests failed
typedef struct { int total, failed; } TState;

// turns off buffering for std out
// means print immediately instead of waiting for newline or buffer to fill
// useful for testing as you see everything that occurred even when the program crashes
static void nobuf(void){ setvbuf(stdout,NULL,_IONBF,0); }

// used internally by the TEST macro, just helps keep the built in testing framework clean
static void test_record(TState *ts, const char *name, bool passed, const char *file, int line) {
    ts->total++;
    if (passed) {
        printf("[ OK ]  %s\n", name);
    } else {
        ts->failed++;
        printf("[FAIL] %s  (%s:%d)\n", name, file, line);
    }
}

#define TEST(ts, name, expr)                   \
    do {                                       \
        bool _passed = (expr);                 \
        test_record((ts), (name), _passed,     \
                    __FILE__, __LINE__);       \
    } while (0)

// define a test function
#define TEST_CASE(name) static void name(TState *ts)

// test descriptor and runner
typedef void (*test_fn)(TState*);
typedef struct { const char *name; test_fn fn; } Test;

static int run_all_tests(const Test *tests, int count) {
    nobuf();
    TState ts = {0, 0};
    for (int i = 0; i < count; i++) {
        printf("==== %s ====\n", tests[i].name);
        tests[i].fn(&ts);
    }
    printf("\nSummary: %d checks, %d failed\n", ts.total, ts.failed);
    return ts.failed ? 1 : 0;
}

#endif /* MINITEST_H */
