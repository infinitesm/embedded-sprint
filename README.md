
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
