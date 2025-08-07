# The Final Sprint for an Internship

**A 14-day intensive embedded systems bootcamp**  
**August 11 – 24, 2025 (America/Chicago)**

---

## Overview

This structured, two-week program simulates the workflow of a junior embedded software engineer. It bridges classroom theory and hands-on firmware development—covering peripheral configuration, driver implementation, data structures, and debugging—so graduates emerge ready for internship challenges.

---

## Objectives

- **Master MCU Fundamentals**  
  Configure STM32CubeIDE projects, GPIO, EXTI interrupts, timers, UART, SPI, ADC, and PWM.  
- **Solidify Protocol Knowledge**  
  Implement full-duplex SPI loopback, UART logging with ring buffers, and register bit-manipulation routines.  
- **Hone Debugging & Toolchain Skills**  
  Leverage Git workflows, Makefiles, Linux CLI, CubeIDE/GDB debugging, and logic-analyzer traces.  
- **Experience Real-Time Concepts**  
  Compare polling vs. interrupts, explore low-power modes, and prototype FreeRTOS tasks, queues, and semaphores.  
- **Automate & Integrate**  
  Build-and-flash scripts, log parsers, state-machine integration, and commit/tag discipline.

---

## Deliverables

This program will produce:

1. **Daily Overviews**  
   Step-by-step guides for each day’s goals, tasks, boilerplate code, and success criteria.

2. **Firmware Modules & Drivers**  
   - GPIO blink & debounced button  
   - EXTI and timer-driven interrupts  
   - SPI loopback test & diagnostics  
   - UART logging with ring buffer & command parser  
   - ADC sampling and PWM control  

3. **Debugging Artifacts**  
   GDB scripts, bug-report write-ups, and logic-analyzer captures illustrating diagnosis and fixes.

4. **Toolchain Automation**  
   Git commits/tags for every milestone, Makefiles, build-and-flash scripts, and log-parser utilities.

5. **RTOS Prototype**  
   FreeRTOS tasks, queues, semaphores, and analysis of scheduling overhead and stack usage.

6. **Integrated Firmware**  
   A cohesive image supporting Monitor, SPI Test, and Idle modes, with safe state-machine transitions.

7. **Documentation & Diagrams**  
   Cheat-sheets, state-machine diagrams, module READMEs, and a final reflection summarizing outcomes.

8. **Application Log**  
   A chronicle of internship submissions made during the sprint, complete with dates and roles.

---

## How to Get Started

1. **Clone the Repo**  
   ```bash
   git clone https://github.com/your-username/embedded-sprint.git
   cd embedded-sprint
   ```

2. **Explore Daily Guides**  
   Open each `dayXX/overview.md` for goals, code skeletons, and validation steps.

3. **Build & Flash**  
   ```bash
   make all
   ./build_and_flash.sh --board NUCLEO-F446RE
   ```

4. **Run Tests & Logs**  
   Employ provided test harnesses and log-parsing scripts to verify functionality.

5. **Commit & Tag**  
   ```bash
   git add .
   git commit -m "day3: GPIO blink & debounce skeleton"
   git tag day3_blink_button
   ```

6. **Reflect & Apply**  
   Review final documentation, polish the resume entry for “Embedded Internship Final Sprint,” and submit applications.

---

## Outcomes & Next Steps

By completion, this bootcamp will have produced:

- A portfolio of **hands-on embedded projects** demonstrating critical skills  
- A disciplined **Git history** reflecting incremental, test-driven development  
- Practical experience with **debugging**, **automation**, and **RTOS** concepts  
- A refined **resume entry** and **application log** ready for internship submissions  

Embark on this sprint to transform theoretical knowledge into deployable firmware—and land that embedded systems internship.  
