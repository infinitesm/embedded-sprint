#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int  my_strlen(const char *s);
void my_strcpy(char *dest, const char *src);
void swap_int(int *a, int *b);

/* ---- Tiny test harness ---- */
typedef struct { int total, failed; } TestState;

static void set_no_buf(void) { setvbuf(stdout, NULL, _IONBF, 0); }

#define TEST(ts, name, expr) do {                 \
    (ts)->total++;                                \
    if (expr) {                                   \
        printf("[ OK ] %s\n", name);              \
    } else {                                      \
        (ts)->failed++;                           \
        printf("[FAIL] %s\n", name);              \
    }                                             \
} while (0)

int main(void) {
    set_no_buf();

    TestState ts = {0, 0};

    /* my_strlen */
    TEST(&ts, "strlen empty",          my_strlen("") == 0);
    TEST(&ts, "strlen hello",          my_strlen("hello") == 5);
    TEST(&ts, "strlen stops at NUL",   my_strlen("hi\0zzz") == 2);

    /* my_strcpy */
    const char *src = "this string will be copied";
    char *dest = malloc(strlen(src) + 1);
    TEST(&ts, "malloc dest",           dest != NULL);
    if (dest) {
        my_strcpy(dest, src);
        TEST(&ts, "strcpy basic",      strcmp(dest, src) == 0);
        free(dest);
    }

    char d0[1];
    my_strcpy(d0, "");
    TEST(&ts, "strcpy empty",          strcmp(d0, "") == 0);

    /* swap_int */
    int a = 25, b = 52;
    swap_int(&a, &b);
    TEST(&ts, "swap 25<->52",          a == 52 && b == 25);

    int x = 7;
    swap_int(&x, &x);
    TEST(&ts, "swap same pointer",     x == 7);

    /* summary + exit code */
    if (ts.failed) {
        printf("\nSUMMARY: %d/%d failed\n", ts.failed, ts.total);
        return 1;  // non-zero for CI/ctest
    }
    printf("\nSUMMARY: all %d passed\n", ts.total);
    return 0;
}

/* ---- Implementations ---- */
int my_strlen(const char *s) {
    int n = 0;
    while (s[n] != '\0') n++;
    return n;
}

void my_strcpy(char *dest, const char *src) {
    if (!dest || !src) return;
    while ((*dest++ = *src++)) {}
}

void swap_int(int *a, int *b) {
    if (a == b) return;
    const int t = *a; *a = *b; *b = t;
}
