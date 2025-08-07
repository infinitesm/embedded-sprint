# Day 2 – Aug 12: Bitwise Operations, Registers, and Circular Buffer

**Summary**  
Deepen your understanding of bitwise operations and memory-efficient C constructs. You’ll practice manipulating hardware-like registers, and implement a generic circular buffer for input buffering—common in embedded applications like UART communication.

---

## Topics
- Set / Clear / Toggle / Test bit operations using macros
- Unions and bitfields to simulate hardware registers
- Enum modes and named flags
- Circular buffer design using arrays and pointer wrap-around

---

## Tasks
- Read [GeeksforGeeks – Set, Clear, and Toggle Bits](https://www.geeksforgeeks.org/dsa/set-clear-and-toggle-a-given-bit-of-a-number-in-c/)
- Write macros and inline helpers for bit operations
- Model an 8-bit register using `union` and bitfields
- Create a generic integer circular buffer library and test all edge cases

---

## Deliverables

### 1. `bitutils.h` and `bitutils.c` – Bit Manipulation Library

**Objective**: Implement bit-level helpers for setting, clearing, toggling, and testing specific bit positions of an integer.

**Functions to Implement:**
```c
// Set bit at pos to 1
void bit_set(uint32_t *val, uint8_t pos);

// Clear bit at pos to 0
void bit_clear(uint32_t *val, uint8_t pos);

// Toggle bit at pos (flip)
void bit_toggle(uint32_t *val, uint8_t pos);

// Test if bit at pos is 1
bool bit_test(uint32_t val, uint8_t pos);
```

**Example Usage**:
```c
uint32_t reg = 0;
bit_set(&reg, 2);     // reg = 0b00000100
bit_toggle(&reg, 2);  // reg = 0b00000000
bool flag = bit_test(reg, 2); // false
```

**What to Do**:
- Use bit shifting and masking logic for all operations.
- Include tests in `main.c` to confirm behavior before/after bit ops.
- Print results with `%#010x` to show 8-bit binary states.

---

### 2. `registers.c` – Union and Bitfield Modeling

**Objective**: Simulate a hardware control register using a `union` of an 8-bit byte and a named `struct` of bitfields.

**Structure Example**:
```c
typedef union {
    uint8_t reg;
    struct {
        uint8_t MODE      : 2;
        uint8_t ENABLE    : 1;
        uint8_t INTERRUPT : 1;
        uint8_t RESERVED  : 4;
    } bits;
} ControlRegister;
```

**What to Do**:
- Implement functions to enable, disable, toggle and read `ENABLE` and `INTERRUPT` flags.
- Write function to set `MODE` to a value from 0–3 (invalid values should be masked or ignored).
- Use `bitutils` helpers to manipulate `reg` directly in alternate versions.
- Test in `main.c`: print full register value and bitfield values side by side.

**Example Test**:
```c
ControlRegister cr = {0};
cr.bits.ENABLE = 1;
cr.bits.MODE = 2;
printf("Register: %#04x (MODE=%d ENABLE=%d)
", cr.reg, cr.bits.MODE, cr.bits.ENABLE);
```

---

### 3. `cbuf.h` and `cbuf.c` – Circular Buffer Library

**Objective**: Build a circular FIFO buffer with constant-time `enqueue` and `dequeue` operations, simulating UART input buffering.

**Structure to Define**:
```c
typedef struct {
    int *buffer;
    size_t head;
    size_t tail;
    size_t capacity;
    size_t size;
} CircularBuffer;
```

**Functions to Implement**:
- `void cb_init(CircularBuffer *cb, size_t cap);`
- `bool cb_is_full(CircularBuffer *cb);`
- `bool cb_is_empty(CircularBuffer *cb);`
- `bool cb_enqueue(CircularBuffer *cb, int val);`
- `bool cb_dequeue(CircularBuffer *cb, int *val);`
- `bool cb_peek(CircularBuffer *cb, int *val);`
- `void cb_free(CircularBuffer *cb);`

**Behavioral Constraints**:
- `enqueue` should fail if full, `dequeue` should fail if empty.
- Maintain `size` correctly during wrap-around conditions.
- Allow wrap-around logic using: `(index + 1) % capacity`

**Test Case Example**:
```c
CircularBuffer cb;
cb_init(&cb, 4);
cb_enqueue(&cb, 10);
cb_enqueue(&cb, 20);
int out;
cb_dequeue(&cb, &out); // out = 10
cb_enqueue(&cb, 30);   // test wrap
cb_peek(&cb, &out);    // out = 20
cb_free(&cb);
```

---

## Tools to Use

- `valgrind` for memory checks.
- `gcc -Wall -Wextra -g` for debug-friendly builds.
- `make` for automated builds.
- Git for version control.

---

## Final Deliverables
- `bitutils.h/.c` – testable helpers for bit manipulation
- `registers.c` – union + bitfield + enums register logic
- `cbuf.h/.c` – circular buffer with wrap-around tests
- `main.c` – test all deliverables with meaningful I/O
- `Makefile` – clean, build, and run all components
