#ifndef REGISTERS_H
#define REGISTERS_H
#include <stdint.h>

typedef union {
    uint8_t reg;
    struct {
        uint8_t MODE      : 2;
        uint8_t ENABLE    : 1;
        uint8_t INTERRUPT : 1;
        uint8_t RESERVED  : 4;
    } bits;
} ControlRegister;

// functions to enable/disable/toggle ENABLE and INTERRUPT flags
static inline void toggleEnabledFlag(ControlRegister *reg) { reg->bits.ENABLE ^= 1; }
static inline void toggleInterruptFlag(ControlRegister *reg) { reg->bits.INTERRUPT ^= 1; }
static inline void enableEnabledFlag(ControlRegister *reg) { reg->bits.ENABLE = 1; }
static inline void enableInterruptFlag(ControlRegister *reg) { reg->bits.INTERRUPT = 1; }
static inline void disableEnabledFlag(ControlRegister *reg) { reg->bits.ENABLE = 0; }
static inline void disableInterruptFlag(ControlRegister *reg) { reg->bits.INTERRUPT = 0; }
static inline uint8_t readEnabledFlag(const ControlRegister *reg) { return reg->bits.ENABLE; }
static inline uint8_t readInterruptFlag(const ControlRegister *reg) { return reg->bits.INTERRUPT; }

// function to set mode between 0 and 3 (invalid values ignored)
static inline void setMode(ControlRegister *reg, uint8_t mode) {
    if (mode > 3) return;
    reg->bits.MODE = mode;
}

#endif