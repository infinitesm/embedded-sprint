# Embedded Sprint – Day 7 (Aug 17) Overview

## Summary
Practise embedded debugging using CubeIDE debugger, GDB, and logic analyzers to diagnose timing and logical errors.

## Topics
- **Breakpoints, single-stepping, watch expressions**
- **Viewing registers and memory in debugger**
- **Logic analyzer basics for embedded signals**
- **Debugging hardware vs software faults**

## Tasks
- Inject intentional bugs in firmware (e.g., remove buffer wrap-around)
- Use CubeIDE live expressions to monitor variables
- Use arm-none-eabi-gdb command-line for memory inspection
- Capture and annotate logic analyzer timing diagrams

## Deliverables
### Bug report
One-page report describing the bug, misbehavior, diagnostic steps, and resolution. Include screenshots or logs.

### Debugger script
A .gdbinit file with commands to break at key callbacks and print variables each hit.

```bash
# .gdbinit example
break HAL_TIM_PeriodElapsedCallback
break HAL_GPIO_EXTI_Callback
commands
  printf "tickCount = %d\n", tickCount
  continue
end
```

### Logic analyzer capture
Annotated timing diagram for UART or SPI signals showing correct and incorrect behavior.

## Learning Resources
- [CubeIDE Debugging Tutorial](https://www.youtube.com/watch?v=QWV1fB0tN1w)
- [GDB for Embedded Developers](https://www.youtube.com/watch?v=KM8b9MSQvQ8)
- [Using a Logic Analyzer](https://www.youtube.com/watch?v=lads_tYGpO4)
