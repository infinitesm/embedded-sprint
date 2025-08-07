# Embedded Sprint – Day 9 (Aug 19) Overview

## Summary
Combine multiple peripherals into a cohesive firmware project with mode cycling, state machines, and logging.

## Topics
- **Finite state machines for mode management**
- **Modular firmware design and code organisation**
- **Integration testing methodologies**
- **Global flags and safe transitions**

## Tasks
- Design 3-mode state machine: Monitor, SPI Loopback, Idle
- Integrate ADC, PWM, UART, SPI modules into main.c
- Use EXTI button to cycle modes
- Ensure resource cleanup on transitions

## Deliverables
### Unified firmware
Final project supporting all three modes. Logs mode and data over UART. Button cycles modes with safe teardown.

### State machine diagram
ASCII or image diagram of states and transitions with button press event.

### Integration test script
Bash/Python script to log firmware output for 30s, parse mode transitions, and summarise results.

```bash
#!/usr/bin/env python3
# test_integration.py
import serial, time
ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)
start = time.time()
while time.time() - start < 30:
    line = ser.readline().decode()
    print(line.strip())
# parse results...
```

## Learning Resources
- [Embedded State Machine Tutorial](https://www.youtube.com/watch?v=7Qg0pI_vXjY)
- [Modular Firmware Design](https://www.youtube.com/watch?v=LUtS2uh0Aq4)
- [Integration Testing Embedded](https://www.youtube.com/watch?v=Zi1msX3eKQk)
