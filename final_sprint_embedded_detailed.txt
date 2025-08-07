
The Final Sprint for an Internship
==================================

### Target internship roles (rated by alignment and competitiveness)

| Role | Alignment score (/10) | Notes |
|---|---|---|
| Embedded Software Engineering Intern | 10.0 | Uses C, MCU programming, protocols – perfect fit for this sprint |
| Firmware Engineer Intern | 9.5 | Similar to embedded SWE but may emphasize RTOS and device drivers |
| Electrical/Embedded Systems Engineer Intern | 8.0 | Broader EE roles; still aligned through MCU and circuit knowledge |
| Robotics Software/Controls Intern | 7.5 | Involves real‑time control and sensors; benefits from embedded skills |
| General SWE Intern (Python/C++) | 6.0 | Secondary option if embedded roles are saturated; leverages Python/Java background |

### Time period

**August 11 – August 24, 2025 (America/Chicago)**  
Each day runs from **8 AM to 5 PM** with a one‑hour lunch break and a one‑hour window at the end for internship applications. Classes begin on August 25, so this schedule provides two full weeks of focussed preparation. The day before (August 10) is reserved for moving into your new house.

### Focus of the sprint

This two‑week sprint aims to transition you from a software‑oriented EE student into a competitive **embedded systems engineer**.  You will:

- **Master embedded C**: practise pointers, memory layout, dynamic memory, structs, bitwise operations and build data structures.  These low‑level skills underpin firmware work and will be tested in interviews.  Reliable sources describe the **stack segment** as where automatic variables and function frames live and show that the **heap segment** grows from the end of the BSS and is used by `malloc`/`realloc`/`free`https://www.geeksforgeeks.org/c/memory-layout-of-c-program/#:~:text=Heap%20%20segment%20is%20where,calls%20to%20adjust%20its%20sizehttps://www.geeksforgeeks.org/c/memory-layout-of-c-program/#:~:text=The%20stack%20is%20a%20region,is%20stored%20in%20this%20segment.  Understanding these segments is critical when allocating memory for buffers or managing static vs dynamic storage.
- **Learn MCU fundamentals**: set up and program an **STM32** microcontroller using the STM32CubeIDE.  Topics include configuring GPIO pins, handling external interrupts (EXTI) and timers, and using communication interfaces (UART, SPI, I²C).  A full‑duplex SPI bus uses MOSI, MISO, SCLK and a chip‑select line (SS); during each clock cycle the master shifts a bit on MOSI and the slave responds on MISOhttps://en.wikipedia.org/wiki/Serial_Peripheral_Interface#:~:text=orchestrates%20communication%20%20with%20one,slave%20roles%20on%20the%20fly.  You will use this knowledge to implement loopback tests and sensor drivers.
- **Practise protocols**: implement bitwise functions to set, clear and toggle register bits (e.g., using `N |= 1 << k`, `N &= ~(1 << k)`, `N ^= 1 << k`https://www.geeksforgeeks.org/dsa/set-clear-and-toggle-a-given-bit-of-a-number-in-c/#:~:text=To%20set%20a%20specific%20bit,bits%20are%20set%20to%200https://www.geeksforgeeks.org/dsa/set-clear-and-toggle-a-given-bit-of-a-number-in-c/#:~:text=Clearing%20a%20Bit%20in%20C).  Mastering bit manipulation and register access is essential for configuring peripherals and will appear in interview questions.
- **Develop debugging and tooling skills**: use **Git** for version control, the **Linux CLI** and **Makefiles** to automate builds, and the **CubeIDE/GDB** debugger to inspect memory, variables and registers.  You will also practise logging over UART, automating firmware flashing, and interpreting logic‑analyzer traces.
- **Experience real‑time and RTOS concepts**: explore FreeRTOS tasks, queues and semaphores; implement pre‑emptive scheduling; and analyse latency and jitter.  Understanding task priorities and context switches will help in more advanced roles.
- **Apply knowledge through coding**: each day includes deliverables requiring you to design and implement firmware or C functions.  These deliverables simulate real embedded tasks and prepare you for technical interviews.  They include constructing data structures, writing drivers, implementing debouncing logic, and integrating peripherals into a cohesive project.

### Daily plan (Aug 11 – Aug 24)

Each day begins with a **summary**, followed by **topics** to be studied, **tasks** to structure your work, and **deliverables** that must be completed.  The deliverables specify constraints and design problems; they emphasise writing code and using tools.  At the end of every day, commit your code to Git with meaningful messages and tags.

#### Day 1 – Aug 11: Memory and pointers mastery

**Summary**: Build a foundation in C memory layout, pointers, arrays and manual memory management.

**Topics**: stack vs heap segmentationhttps://www.geeksforgeeks.org/c/memory-layout-of-c-program/#:~:text=Heap%20%20segment%20is%20where,calls%20to%20adjust%20its%20sizehttps://www.geeksforgeeks.org/c/memory-layout-of-c-program/#:~:text=The%20stack%20is%20a%20region,is%20stored%20in%20this%20segment; pointer arithmetic; arrays vs pointers; structs and typedef; dynamic memory.

**Tasks**:

- Watch Neso Academy’s “Pointers in C” lecture and read GeeksforGeeks’ article on memory layout.  Take notes on how the stack grows toward lower addresses and the heap grows upwardhttps://www.geeksforgeeks.org/c/memory-layout-of-c-program/#:~:text=Heap%20%20segment%20is%20where,calls%20to%20adjust%20its%20sizehttps://www.geeksforgeeks.org/c/memory-layout-of-c-program/#:~:text=The%20stack%20is%20a%20region,is%20stored%20in%20this%20segment.
- Write a `makefile` to build multiple C files (`memlab.c`, `dynarray.c` etc.).
- Practise pointer manipulation: implement `my_strlen`, `my_strcpy`, and `swap` using pointers only.

**Deliverables**:

1. **Memory lab program (`memlab.c`)** – Write a C program that declares local variables and dynamically allocates a large array.  Print the addresses of variables, the heap allocation and functions to illustrate stack and heap growth.  Include comments explaining how addresses differ.  Use `valgrind` (if available) to verify there are no leaks.
2. **String and swap functions** – Implement `int my_strlen(const char *s)`, `void my_strcpy(char *dest, const char *src)` and `void swap_int(int *a, int *b)`.  These functions must not call standard library functions other than `malloc`/`free`.  Write `main()` to test them with corner cases (empty strings, long strings, same pointer for dest and src).  Document pointer arithmetic carefully.
3. **Dynamic array structure** – Create a header `dynarray.h` and source `dynarray.c` for a dynamic integer array struct:

   ```c
   typedef struct {
       int *data;
       size_t size;
       size_t capacity;
   } DynArray;

   void dyn_init(DynArray *a);
   void dyn_push(DynArray *a, int value);
   int  dyn_pop(DynArray *a);
   void dyn_free(DynArray *a);
   ```

   The `push` operation must double the capacity when full using `realloc`.  The `pop` must return the last element and shrink capacity if the size is less than one‑quarter of capacity.  Write tests in `main.c` to demonstrate correct resizing behaviour.

*Resources*: Neso Academy pointers playlist; GeeksforGeeks “Memory layout of C programs”https://www.geeksforgeeks.org/c/memory-layout-of-c-program/#:~:text=Heap%20%20segment%20is%20where,calls%20to%20adjust%20its%20sizehttps://www.geeksforgeeks.org/c/memory-layout-of-c-program/#:~:text=The%20stack%20is%20a%20region,is%20stored%20in%20this%20segment; `valgrind` tutorial.

#### Day 2 – Aug 12: Bitwise operations, registers and circular buffer

**Summary**: Deepen bitwise skills and implement register manipulation and a circular buffer.

**Topics**: set/clear/toggle/test bit operationshttps://www.geeksforgeeks.org/dsa/set-clear-and-toggle-a-given-bit-of-a-number-in-c/#:~:text=To%20set%20a%20specific%20bit,bits%20are%20set%20to%200https://www.geeksforgeeks.org/dsa/set-clear-and-toggle-a-given-bit-of-a-number-in-c/#:~:text=Clearing%20a%20Bit%20in%20Chttps://www.geeksforgeeks.org/dsa/set-clear-and-toggle-a-given-bit-of-a-number-in-c/#:~:text=To%20toggle%20a%20specific%20bit,bits%20are%20set%20to%200; enums and unions for registers; circular buffer design; bitfields.

**Tasks**:

- Read GeeksforGeeks’ “Set, clear and toggle a given bit of a number” article to understand bit manipulation macros and operationshttps://www.geeksforgeeks.org/dsa/set-clear-and-toggle-a-given-bit-of-a-number-in-c/#:~:text=To%20set%20a%20specific%20bit,bits%20are%20set%20to%200https://www.geeksforgeeks.org/dsa/set-clear-and-toggle-a-given-bit-of-a-number-in-c/#:~:text=Clearing%20a%20Bit%20in%20C.
- Write macros for bit operations and practise them on an integer register.
- Design a generic ring buffer for UART input.

**Deliverables**:

1. **Bit‑util library** – Create `bitutils.h/c` with inline functions or macros:

   ```c
   static inline void bit_set(uint32_t *val, uint8_t pos)    { *val |=  (1U << pos); }
   static inline void bit_clear(uint32_t *val, uint8_t pos)  { *val &= ~(1U << pos); }
   static inline void bit_toggle(uint32_t *val, uint8_t pos) { *val ^=  (1U << pos); }
   static inline bool bit_test(uint32_t val, uint8_t pos)    { return (val >> pos) & 1U; }
   ```

   Use these functions to modify a simulated hardware register.  Print the register value before and after each operation to confirm the effect.
2. **Register modelling with unions** – Define a union representing an 8‑bit configuration register with named bitfields (e.g., `MODE`, `ENABLE`, `INTERRUPT`, reserved bits).  Implement functions to set modes using the bit‑util library.
3. **Circular buffer (`cbuf.h/c`)** – Implement a fixed‑size circular buffer for integers with operations `cb_init`, `cb_is_full`, `cb_is_empty`, `cb_enqueue`, `cb_dequeue`, and `cb_peek`.  Use `malloc` for buffer allocation and wrap indices properly (head and tail).  Write tests to cover edge cases (empty/full, wrap‑around, underflow/overflow).  Provide both array indexing and pointer arithmetic versions.

*Resources*: GeeksforGeeks article on bit operationshttps://www.geeksforgeeks.org/dsa/set-clear-and-toggle-a-given-bit-of-a-number-in-c/#:~:text=To%20set%20a%20specific%20bit,bits%20are%20set%20to%200https://www.geeksforgeeks.org/dsa/set-clear-and-toggle-a-given-bit-of-a-number-in-c/#:~:text=Clearing%20a%20Bit%20in%20C; tutorials on implementing ring buffers; the C Programming Language (K&R) for bitfields (optional).

#### Day 3 – Aug 13: STM32CubeIDE setup, GPIO and button handling

**Summary**: Install STM32CubeIDE, create your first project, blink an LED and read a button using HAL drivers.

**Topics**: CubeIDE project creation; CubeMX pin configuration; GPIO modes; debouncing; HAL API vs direct register access.

**Tasks**:

- Install STM32CubeIDE and create a new STM32F4 project (or whichever Nucleo board you own).  Use CubeMX to configure a GPIO pin for LED output and another for button input with pull‑up resistor.
- Learn how to write HAL code in `main.c`, compile and flash the board.
- Write a README explaining how to build and flash the project via CubeIDE and CLI.

**Deliverables**:

1. **Blink and Button project** – Within CubeIDE, generate initial code and modify `main.c` to blink an LED at 1 Hz using `HAL_Delay()`.  Add code to read a button state in the main loop and toggle the LED each time the button is pressed.  Include software debouncing by ignoring subsequent toggles within 50 ms.  Document how the HAL functions work.
2. **Git integration** – Initialise a Git repository in the project directory.  Add `.gitignore` for build artifacts.  Commit the project with an initial tag `day3_blink_button`.  Create a README describing how to configure pins in CubeMX and where the code resides.
3. **Custom Makefile** – Optionally, export the generated project to a Makefile‑based build.  Use `arm-none-eabi-gcc` to compile and link outside CubeIDE.  Document steps in `README.md`.

*Resources*: ST’s official “STM32CubeIDE Getting Started” video; CubeIDE tutorials on YouTube; ST’s HAL API documentation; article on debouncing techniques.

#### Day 4 – Aug 14: Interrupts and timers on STM32

**Summary**: Learn about external interrupts (EXTI) and timer interrupts and implement them for LED blinking and button handling.

**Topics**: NVIC; EXTI lines; timer configuration (TIM); SysTick vs general‑purpose timers; ISR design; clearing interrupt flags.

**Tasks**:

- Use CubeMX to configure an EXTI pin for the button (falling edge).  Set up a timer to generate interrupts at 1 kHz and count ticks to drive a periodic event.
- Write an ISR to toggle an LED every second using the timer interrupt.  Use a global `volatile` counter variable.  Within the button ISR, invert the blinking frequency between 0.5 Hz and 2 Hz.
- Use HAL functions or direct register access to clear interrupt flags.

**Deliverables**:

1. **Timer interrupt project** – Configure TIM2 (or another timer) to trigger an interrupt at 1 kHz.  In the `HAL_TIM_PeriodElapsedCallback()` function, increment a global tick counter.  When the counter reaches 1000, toggle the LED and reset the counter.  Use `volatile` to ensure the compiler doesn’t optimise the variable away.  Show how to enable/disable the timer via HAL.
2. **Button EXTI project** – In `stm32f4xx_it.c`, implement the EXTI ISR for the button.  Use `__HAL_GPIO_EXTI_CLEAR_IT()` to clear the interrupt flag.  Within the ISR, flip a flag that controls the LED blinking period.  Ensure debouncing by reading the button state after a small delay or using a simple software timer.
3. **Cheat sheet** – Create a short document summarising how to configure EXTI lines and timers: register addresses, HAL functions, NVIC priorities.  This cheat sheet will aid in interviews.

*Resources*: ST’s application note on interrupts; blog posts about STM32 timer interrupts; GeeksforGeeks article on `volatile` variables; memory layout article for contexthttps://www.geeksforgeeks.org/c/memory-layout-of-c-program/#:~:text=Heap%20%20segment%20is%20where,calls%20to%20adjust%20its%20sizehttps://www.geeksforgeeks.org/c/memory-layout-of-c-program/#:~:text=The%20stack%20is%20a%20region,is%20stored%20in%20this%20segment.

#### Day 5 – Aug 15: SPI fundamentals and loopback test

**Summary**: Study the SPI protocol and implement a loopback test on the STM32 to verify full‑duplex communication.

**Topics**: SPI signals and modes (MOSI, MISO, SCLK, SS); CPOL/CPHA; data frames; master vs slave; enabling SPI in CubeMX; loopback wiring.

**Tasks**:

- Read the Wikipedia article on the Serial Peripheral Interface (SPI) to understand how the master and slave exchange bits simultaneously via MOSI/MISO and how the SS line selects the slavehttps://en.wikipedia.org/wiki/Serial_Peripheral_Interface#:~:text=orchestrates%20communication%20%20with%20one,slave%20roles%20on%20the%20fly.
- Configure SPI1 as master using CubeMX.  Connect MISO and MOSI pins together externally with a jumper wire to create a loopback.
- Write firmware to send a byte sequence (e.g., `0xA5`, `0x5A`, `0xFF`, `0x00`) and read the response.  Verify that the received bytes match the transmitted ones.

**Deliverables**:

1. **SPI loopback project** – Implement a function `spi_loopback_test()` that transmits an array of bytes via `HAL_SPI_TransmitReceive()` and checks that the received buffer matches the transmitted buffer.  Indicate success by toggling an LED or printing over UART.  Use a manual `CS` GPIO pin: pull it low before starting the transaction and high afterwards.
2. **SPI diagnostics** – Print the transmitted and received bytes via `printf` over UART.  If available, use a logic analyzer or oscilloscope to capture the SPI waveforms.  Save a screenshot of the timing diagram and note the clock polarity and phase settings used.
3. **Protocol summary** – Write a short summary explaining how each SPI signal functions, why loopback verifies full‑duplex operation, and what CPOL and CPHA dohttps://en.wikipedia.org/wiki/Serial_Peripheral_Interface#:~:text=orchestrates%20communication%20%20with%20one,slave%20roles%20on%20the%20fly.

*Resources*: Wikipedia SPI articlehttps://en.wikipedia.org/wiki/Serial_Peripheral_Interface#:~:text=orchestrates%20communication%20%20with%20one,slave%20roles%20on%20the%20fly; CubeMX SPI configuration guide; EEVblog or GreatScott videos on SPI basics.

#### Day 6 – Aug 16: UART logging and ring buffer integration

**Summary**: Set up UART for debugging prints and integrate a ring buffer for incoming data.

**Topics**: UART transmit/receive; baud rate configuration; `printf` retargeting; ring buffers; simple command parser.

**Tasks**:

- Use CubeMX to configure USART2 (or another UART) for 115200 baud, 8‑N‑1.  Enable both TX and RX.
- Write a function `uart_printf()` to redirect `printf` to UART by overriding `_write` (in `syscalls.c`) or using `HAL_UART_Transmit()`.  Use `\r\n` line endings.
- Integrate your `CircularBuffer` from Day 2 to buffer received bytes.  In the UART RX callback, enqueue incoming bytes.  In the main loop, read from the buffer and echo or parse commands.

**Deliverables**:

1. **UART printf project** – Modify the STM32 project to retarget `printf` so that `printf("Hello\n")` transmits over UART.  Write messages when the SPI loopback test passes or fails.  Ensure `printf` is non‑blocking by using either polling or interrupt‑driven transmission.
2. **UART RX ring buffer** – Implement the `HAL_UART_RxCpltCallback()` or `HAL_UART_RxHalfCpltCallback()` to read incoming bytes and enqueue them into the ring buffer.  In the main loop, check the buffer and echo characters back or interpret simple commands (e.g., send 'R' to reset the counter).  Document thread safety: mark the buffer indices as `volatile` or protect with interrupts disabled while reading/writing.
3. **Log parser script** – Write a Bash or Python script that connects via `screen` or `minicom`, logs the UART output to a file, and parses lines containing “ERROR” or “PASS”.  Use Linux CLI tools like `sed`, `awk`, or Python’s `re` module.

*Resources*: ST’s article on retargeting printf; tutorials on UART with STM32; GitHub examples of ring buffer use.

#### Day 7 – Aug 17: Debugging deep dive

**Summary**: Practise embedded debugging using the CubeIDE debugger, GDB, and logic analyzers to diagnose timing and logical errors.

**Topics**: breakpoints, single‑stepping, watch expressions; viewing registers and memory; logic‑analyzer basics; debugging hardware vs software faults.

**Tasks**:

- Introduce intentional bugs: remove the ring‑buffer wrap‑around, misconfigure a timer, or flip a CPHA bit.  Observe misbehaviour and locate the fault using breakpoints and watchpoints.
- Use CubeIDE’s live expressions to monitor `tick_count`, buffer head/tail and register values in real time.  Step through interrupt handlers.
- Use `gdb` (via `arm-none-eabi-gdb`) on the command line to inspect memory addresses, set breakpoints, and print variables.  Practise `layout asm` or `info registers`.

**Deliverables**:

1. **Bug report** – Write a one‑page report describing the injected bug, how the system misbehaved (e.g., LED blink frequency drift, lost UART characters), and the steps taken to diagnose and fix it using breakpoints or register inspection.  Include screenshots or log excerpts.
2. **Debugger script** – Create a `.gdbinit` file or script containing commands to set breakpoints at `HAL_TIM_PeriodElapsedCallback()` and `HAL_GPIO_EXTI_Callback()`, run the program, and print the values of key variables each time.  Document how to run this script.
3. **Logic analyzer capture** – (Optional) If you have access to a logic analyser, capture a UART transmission or SPI loopback session and annotate the timing diagram.  If not, describe how you would use one in a real debugging scenario.

*Resources*: ST debugging docs; blogs on CubeIDE debug features; free YouTube courses on embedded debugging.

#### Day 8 – Aug 18: ADC and PWM

**Summary**: Interface with analog inputs using ADC and control output via PWM, demonstrating real‑time data acquisition and actuator control.

**Topics**: ADC sampling; analog voltage conversion; PWM basics; duty cycle; scaling sensor values.

**Tasks**:

- Configure an ADC channel (e.g., potentiometer or onboard analog input) using CubeMX.  Select continuous conversion mode with interrupt or polling.
- Configure a timer’s PWM output channel to drive an LED or servo.  Adjust duty cycle based on ADC value.
- Write code to read the ADC value, scale it to 0–100 % and update the PWM duty cycle.  Implement both polling (busy‑wait for conversion) and interrupt (use `HAL_ADC_ConvCpltCallback()` and `HAL_ADC_Start_IT()`).

**Deliverables**:

1. **ADC sampling project** – Implement `adc_read()` that returns the latest ADC value and convert it to millivolts given the reference voltage.  Print the raw and converted values over UART.  Plot the values using Python (optional) to visualise sensor behaviour.
2. **PWM control** – Write a function `set_pwm_duty(uint8_t duty)` that sets the CCR register of the timer to adjust duty cycle.  Map the 12‑bit ADC value (0–4095) to 0–100 %.  Show that turning the potentiometer dims or brightens an LED.  Document the relationship between ADC reading and LED brightness.
3. **Interrupt vs polling** – Compare CPU usage and responsiveness between polling (`HAL_ADC_PollForConversion()`) and interrupt‑driven (`HAL_ADC_Start_IT()`).  In a report, discuss which method is more efficient and why, referencing memory and CPU constraints.

*Resources*: ST application notes on ADC and PWM; EEVblog’s ADC videos; examples from STM32CubeMX.

#### Day 9 – Aug 19: System integration

**Summary**: Combine multiple peripherals into a cohesive firmware project that cycles through modes via a button and logs sensor data.

**Topics**: state machines; modular design; global flags; integration testing; code organisation.

**Tasks**:

- Design a simple state machine with three modes: **Monitor** (read ADC and log values), **SPI Loopback** (perform loopback test), **Idle** (blink LED slowly).  Use a button interrupt to cycle through modes.
- Integrate UART logging with ring buffer, ADC reading with PWM output, and SPI loopback test.  Structure your code into modules (`adc.c`, `pwm.c`, `uart.c`, `spi.c`, `main.c`).
- Implement safe transitions: ensure that starting a new mode disables previous interrupts or resets counters.  Use `volatile` flags where appropriate.

**Deliverables**:

1. **Unified firmware** – Build a final project that supports all three modes.  Each mode runs for 10 s then transitions to the next when the button is pressed.  Use UART to print the current mode and relevant data (ADC values, loopback pass/fail).  Clean up resources during transitions.
2. **State machine diagram** – Draw (ASCII or image) and include in the repo a diagram showing the states and transitions.  Explain how the button ISR modifies the global `state` variable.
3. **Integration test script** – Write a Bash or Python script to run and log the firmware output over 30 s, parse the logs to verify that each mode executed correctly, and summarise the results.

*Resources*: Embedded state machine tutorials; examples of modular firmware design; articles on ring buffers and concurrency.

#### Day 10 – Aug 20: Git, Linux CLI, and build automation

**Summary**: Solidify your toolchain by mastering Git workflows, Linux command‑line productivity, Makefiles/CMake, and cross‑compiling.

**Topics**: Git branching, merging, rebasing; Bash scripting; Makefile rules; cross compilation with `arm-none-eabi-gcc`; CLI utilities.

**Tasks**:

- Learn advanced Git: create feature branches, rebase onto main, resolve conflicts and push merges.  Practise interactive rebasing to squash commits.
- Write a Bash script (`build_and_flash.sh`) that builds your STM32 firmware using `make`, then flashes it using `st-flash` or CubeIDE CLI.  Add command‑line arguments for build type (Debug/Release) and board selection.
- Write a script (`log_parser.sh`) that takes a log file and extracts key metrics (e.g., number of state transitions, average ADC value, errors encountered).

**Deliverables**:

1. **Git exercise** – Create a sample repository with two branches implementing separate features (e.g., improved ADC scaling and custom SPI commands).  Merge them into main using rebase or merge and resolve any conflicts.  Document the commands used (`git branch`, `git checkout`, `git merge`, `git rebase`, `git log`), why you chose one method over the other, and push to remote.
2. **Build script** – Provide `build_and_flash.sh` that: (i) calls `make` to build the project; (ii) checks the exit code; (iii) if successful, invokes `st-flash write` or CubeIDE CLI to flash the `.bin` file; (iv) prints success/failure.  Include `make clean` and environment variable support.  Document usage in `README.md`.
3. **Log parser** – Implement `log_parser.sh` or Python script to parse UART logs: count number of mode transitions, average ADC values, and occurrences of “FAIL”.  Output a summary report.  Use standard Unix tools like `grep`, `awk`, or Python `re`.

*Resources*: Atlassian Git tutorials; The Linux Command Line (book) for CLI; ST CLI tools; YouTube tutorials on Makefiles and cross‑compiling.

#### Day 11 – Aug 21: FreeRTOS introduction

**Summary**: Explore FreeRTOS and use tasks and queues to replace polling loops.

**Topics**: tasks and priorities; context switching; semaphores and mutexes; queues; memory allocation in RTOS; avoiding priority inversion.

**Tasks**:

- Read the FreeRTOS Quick Start Guide and watch an introductory video by Richard Barry or similar.  Understand how tasks are created and scheduled, and how to use queues for inter‑task communication.
- Modify your unified firmware to use FreeRTOS: create separate tasks for ADC sampling, SPI loopback, UART logging and mode management.  Use queues to send messages between tasks (e.g., ADC values to the UART task).  Set appropriate priorities so that the logger does not starve the sampler.
- Use semaphores or mutexes to protect shared resources like the ring buffer.

**Deliverables**:

1. **FreeRTOS firmware** – Create a new project or modify the integrated firmware to run under FreeRTOS.  Implement at least three tasks: `Task_ADC`, `Task_SPI`, `Task_UART`.  Use `xQueueSend()` and `xQueueReceive()` to send data.  Use `vTaskDelay()` to pace tasks.  Demonstrate pre‑emptive scheduling by assigning different priorities.
2. **FreeRTOS analysis** – Write a report explaining why an RTOS might improve responsiveness and modularity compared to a superloop.  Discuss context‑switch overhead and memory footprint.  Mention potential pitfalls like priority inversion and how mutexes prevent it.
3. **Stack usage measurement** – Use `uxTaskGetStackHighWaterMark()` or similar to measure how much stack each task uses.  Optimise stack sizes and discuss findings.

*Resources*: FreeRTOS documentation; YouTube lectures on FreeRTOS; blog posts on using RTOS on STM32.

#### Day 12 – Aug 22: Interview practice I – C and firmware questions

**Summary**: Solve C and embedded firmware problems typical of technical interviews.

**Topics**: pointer pitfalls; memory corruption; bitwise puzzles; register configuration problems; concurrency issues.

**Tasks**:

- Select 10–15 C/embedded interview questions from resources such as EmbeddedArtistry, Beningo’s blog or eInfochips.  Solve them by writing C functions and test drivers.  Examples: implementing `memcpy`, reversing bits of a 32‑bit number, reading/writing to a memory‑mapped register with bit‑masks, designing a finite state machine for a traffic light, implementing a debouncer.
- For each question, write your own test harness to verify correctness.  Then attempt to optimise for readability and performance.  Document any trade‑offs.

**Deliverables**:

1. **Interview problems code** – A directory with solutions to selected questions.  Include a brief comment at the top of each file describing the problem and your approach.  Provide `Makefile` to compile and run tests.  Use `assert()` or print statements for verification.
2. **Study notes** – Create a markdown file summarising key points you learned: pointer aliasing, `volatile` usage in ISRs, the difference between `static` and global variables, pitfalls when using bit shifts on signed integers, and examples of writing to memory‑mapped registers using pointer casts.
3. **Self‑reflection** – Identify which problems were difficult and why; schedule follow‑up study if needed.

*Resources*: EmbeddedArtistry and Beningo blogs; eInfochips top embedded questions; GeeksforGeeks bit manipulation articlehttps://www.geeksforgeeks.org/dsa/set-clear-and-toggle-a-given-bit-of-a-number-in-c/#:~:text=To%20set%20a%20specific%20bit,bits%20are%20set%20to%200https://www.geeksforgeeks.org/dsa/set-clear-and-toggle-a-given-bit-of-a-number-in-c/#:~:text=Clearing%20a%20Bit%20in%20Chttps://www.geeksforgeeks.org/dsa/set-clear-and-toggle-a-given-bit-of-a-number-in-c/#:~:text=To%20toggle%20a%20specific%20bit,bits%20are%20set%20to%200; memory layout articlehttps://www.geeksforgeeks.org/c/memory-layout-of-c-program/#:~:text=Heap%20%20segment%20is%20where,calls%20to%20adjust%20its%20size.

#### Day 13 – Aug 23: Interview practice II – system design and optimisation

**Summary**: Practise system‑level and optimisation questions and implement low‑power techniques.

**Topics**: low‑power modes; signal conditioning; real‑time scheduling; latency and jitter; memory/performance trade‑offs.

**Tasks**:

- Solve additional interview questions focusing on system design: design a digital thermometer using an MCU, implement a producer–consumer pattern with semaphores, design an elevator controller state machine, or implement a watchdog timer.
- Study the STM32 power control registers and learn to enter low‑power sleep modes.  Use a timer or EXTI interrupt to wake up and measure current consumption if possible (simulate with debug counters otherwise).
- Optimise your firmware: reduce CPU usage by using DMA for UART or SPI, remove busy‑wait loops, and ensure interrupts do minimal work.

**Deliverables**:

1. **System design write‑ups** – Provide short write‑ups (half a page each) for two system design questions.  Include block diagrams, state machines, or pseudo‑code to show how you would implement them on an MCU.
2. **Low‑power demo** – Modify your unified firmware or FreeRTOS project to enter sleep/stop mode when idle and wake up on a timer or button interrupt.  Toggle an LED or send a UART message after wake‑up.  Document which registers you changed and the effect on responsiveness.  If you have a multimeter or current‑sense resistor, measure current consumption; otherwise, discuss theoretical savings.
3. **Optimisation report** – Identify at least three optimisations you made (e.g., using DMA, reducing polling, minimising ISR time) and document how they improved latency or power usage.

*Resources*: STM32 power management reference manual; low‑power IoT tutorials; interview design questions from Beningo and industry blogs; GeeksforGeeks bit manipulation article for bit‑level efficiencyhttps://www.geeksforgeeks.org/dsa/set-clear-and-toggle-a-given-bit-of-a-number-in-c/#:~:text=To%20set%20a%20specific%20bit,bits%20are%20set%20to%200https://www.geeksforgeeks.org/dsa/set-clear-and-toggle-a-given-bit-of-a-number-in-c/#:~:text=Clearing%20a%20Bit%20in%20Chttps://www.geeksforgeeks.org/dsa/set-clear-and-toggle-a-given-bit-of-a-number-in-c/#:~:text=To%20toggle%20a%20specific%20bit,bits%20are%20set%20to%200.

#### Day 14 – Aug 24: Wrap‑up, portfolio polish and applications

**Summary**: Consolidate your work, finalise documentation and apply to internships.

**Topics**: documentation best practices; resume and portfolio writing; reflection.

**Tasks**:

- Clean up all project directories, ensuring each has a clear `README.md` explaining purpose, build instructions, and usage.  Add comments to your code.
- Create a high‑level summary slide or markdown file describing the sprint, what you learned, major deliverables and outcomes.  Include metrics (e.g., number of commits, lines of code, success rate of loopback tests, maximum ADC frequency achieved).
- Update your resume and LinkedIn: add the “Internship Final Sprint” project entry (see below).  Tailor bullet points to emphasise embedded skills.
- Apply to at least 10 internship postings using your polished resume and portfolio.  Keep track of applications in a spreadsheet.

**Deliverables**:

1. **Project consolidation** – All code and documentation pushed to GitHub.  Create a top‑level `SUMMARY.md` linking to each day’s deliverables.
2. **Reflection document** – Write a one‑page reflection on what went well, what was challenging, and next steps (e.g., deeper RTOS learning, starting a wearable Tinycardia redesign).  Mention how understanding memory segments, bit operations, and SPI internals helped your learninghttps://www.geeksforgeeks.org/c/memory-layout-of-c-program/#:~:text=Heap%20%20segment%20is%20where,calls%20to%20adjust%20its%20sizehttps://www.geeksforgeeks.org/dsa/set-clear-and-toggle-a-given-bit-of-a-number-in-c/#:~:text=To%20set%20a%20specific%20bit,bits%20are%20set%20to%200https://en.wikipedia.org/wiki/Serial_Peripheral_Interface#:~:text=orchestrates%20communication%20%20with%20one,slave%20roles%20on%20the%20fly.
3. **Application log** – Submit applications and document which roles you applied for, along with submission dates.  Use the final hour each day from Aug 11 – 24 for applications.

*Resources*: GitHub docs on README.md best practices; resume writing guides for embedded roles; job boards such as LinkedIn, Handshake and company career pages.

### Resume project entry: Internship Final Sprint

**Internship Final Sprint – Embedded Systems Intensive**  
*Aug 2025 – 2 weeks, Odessa, TX*  
A self‑directed, full‑time project that condensed two months of embedded systems development into 14 days.  I executed daily coding challenges, built and debugged firmware across multiple peripherals, and adopted professional toolchains to prepare for embedded software internships.

**Key accomplishments:**

- Developed **14 mini‑projects** on an STM32 board covering memory management, bitwise operations, interrupt service routines, timers, SPI/I²C/UART communication, ADC/PWM control, UART logging with ring buffers, and simple RTOS tasks.
- Implemented a **dynamic array, ring buffer, and register abstraction** in C to practise pointer arithmetic and dynamic memory allocation; verified correct operation with unit tests and `valgrind`.
- Built and flashed multiple CubeIDE firmware projects using both **HAL** and **direct register** methods; toggled LEDs, handled button EXTI interrupts, and wrote timer‑based ISRs to drive periodic tasks.
- Configured **SPI loopback tests** and verified full‑duplex transfers by manually controlling chip‑select lines; documented how MOSI/MISO bits shift synchronouslyhttps://en.wikipedia.org/wiki/Serial_Peripheral_Interface#:~:text=orchestrates%20communication%20%20with%20one,slave%20roles%20on%20the%20fly.
- Redirected `printf` to UART and integrated a **ring buffer** for non‑blocking receive; wrote Bash scripts to parse logs and summarise performance.
- Integrated ADC sampling with PWM output to control LED brightness; compared polling vs interrupt modes and documented CPU usage differences.
- Created a **unified firmware state machine** combining ADC, SPI and UART tasks; used a button to cycle modes and built a test harness to verify correct transitions.
- Wrote **custom Makefiles** and scripts to automate building and flashing; practised advanced Git workflows (branching, rebasing, merging) and used the **Linux CLI** for build automation and log parsing.
- Explored **FreeRTOS** by partitioning tasks into separate threads with queues and semaphores; measured stack usage and discussed pros/cons of RTOS vs superloop.
- Prepared for interviews by solving **embedded C problems** (bit manipulations, memory‑mapped I/O, state machines) and summarised learnings in comprehensive notes.

Technologies: C, STM32, STM32CubeIDE, STM32 HAL and LL drivers, FreeRTOS, Git, Linux CLI, Makefiles, `arm-none-eabi-gcc`, GDB, Bash, Python, UART, SPI, I²C, ADC, PWM, interrupts, timers, state machines.

### Should this replace an existing resume entry?

Your current resume includes **Contract Software Engineer**, **Freelance Software Engineer**, and projects like **Tinycardia**, **Medusa Anti‑Cheat** and **AimAware**file:///home/oai/share/Resume%20-%20Kyle%20Dudley.pdf.  The Contract Software Engineer role demonstrates professional software experience and should stay.  The Freelance Software Engineer entry spans multiple years and lists Java projects; consider shortening it to 1–2 bullets or moving details into the projects section.  You can then feature **Internship Final Sprint** under the **Projects** section (or create a separate “Embedded Systems” section).  This highlights your intensive embedded work without overcrowding the résumé.  Keep Tinycardia because it aligns strongly with embedded/EE roles.  Condense or remove lesser‑relevant SWE experiences (e.g., generic Minecraft modding) to make room.
