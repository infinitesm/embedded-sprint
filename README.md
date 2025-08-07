
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






