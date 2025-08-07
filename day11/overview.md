# Embedded Sprint – Day 11 (Aug 21) Overview

## Summary
Explore FreeRTOS: tasks, queues, semaphores, and migrate from superloop to RTOS architecture.

## Topics
- **Task creation and priorities**
- **Inter-task communication via queues**
- **Mutexes and semaphores for resource protection**
- **Context switching and memory considerations**

## Tasks
- Read FreeRTOS Quick Start Guide and watch intro video
- Create tasks for ADC, SPI, UART, mode manager
- Use xQueueSend/xQueueReceive for data passing
- Protect shared ring buffer with mutex

## Deliverables
### FreeRTOS firmware
Modified firmware with Task_ADC, Task_SPI, Task_UART using queues and vTaskDelay.

### FreeRTOS analysis
Report on RTOS benefits vs superloop: responsiveness, overhead, pitfalls.

### Stack usage measurement
Use uxTaskGetStackHighWaterMark to measure and optimise task stacks.

## Learning Resources
- [FreeRTOS Basics](https://www.youtube.com/watch?v=RltVr8N1R5w)
- [FreeRTOS Documentation](https://www.freertos.org/Documentation/RTOS_book.html)
- [STM32 FreeRTOS Tutorial](https://www.youtube.com/watch?v=I_MMdsGlupE)
