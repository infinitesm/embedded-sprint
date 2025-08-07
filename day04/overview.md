# Embedded Sprint – Day 4 (Aug 14) Overview

## Summary
Day 4 introduces interrupts and timers on STM32. You will configure EXTI for button presses and use TIM2 interrupts to drive periodic LED toggling, building ISR design and NVIC management skills.

## Topics
- **NVIC Configuration**: Priority, enabling IRQs  
- **External Interrupt (EXTI)**: Edge selection, interrupt flag clearing  
- **General-Purpose Timer (TIM2)**: Prescaler, ARR, update event, interrupts  
- **HAL vs. Registers**: Using HAL callbacks vs direct register access  
- **ISR Best Practices**: `volatile`, minimal processing, flag clearing

## Tasks
1. **CubeMX Setup**  
   - Enable EXTI on PC13 (Falling Edge).  
   - Configure TIM2 for 1 kHz update and enable its global interrupt.
2. **Skeleton Code**  
   - Add in `stm32f4xx_it.h`: `void EXTI15_10_IRQHandler(void);`, `void TIM2_IRQHandler(void);`.  
   - In `main.c`, prototypes: `EXTI_Init()`, `Timer_Init()`.
3. **README Update**  
   - Document CubeMX steps, IRQ mapping, callback flow.

## Deliverables

### 1. Timer Interrupt Module
- **Variable**:
  ```c
  volatile uint32_t tickCount;
  ```
- **Prototype**:
  ```c
  /**
   * @brief  Initializes TIM2 to 1 kHz and enables interrupt.
   * @param  none
   * @retval none
   */
  void Timer_Init(void);

  /**
   * @brief  TIM2 IRQ Handler prototype.
   */
  void TIM2_IRQHandler(void);

  /**
   * @brief  HAL callback on timer update.
   * @param  htim: timer handle
   */
  void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
  ```

### 2. Button EXTI Module
- **Variables**:
  ```c
  volatile uint32_t lastButtonTick;
  volatile uint32_t blinkThreshold;
  ```
- **Prototype**:
  ```c
  /**
   * @brief  Initializes EXTI for button.
   * @param  none
   * @retval none
   */
  void EXTI_Init(void);

  /**
   * @brief  EXTI IRQ Handler for PC13.
   */
  void EXTI15_10_IRQHandler(void);
  ```

### 3. Interrupt Cheat Sheet
One-page summary of:
- EXTI registers: `EXTI->IMR`, `FTSR`, `PR`.  
- TIM2 registers: `PSC`, `ARR`, `DIER`.  
- NVIC calls: `HAL_NVIC_SetPriority`, `HAL_NVIC_EnableIRQ`.

### 4. Git Workflow
```bash
git add .
git commit -m "Day 4: Interrupt & Timer skeleton modules"
git tag day4_interrupts_timers
```

## Learning Resources
- [STM32 Timer Interrupts Tutorial (YouTube)](https://www.youtube.com/watch?v=Y_3MhX1HbfM)  
- [STM32 EXTI Interrupts Guide (YouTube)](https://www.youtube.com/watch?v=YS9P1dj0Uo4)  
- [STM32 NVIC and Interrupts (YouTube)](https://www.youtube.com/watch?v=1k5ffg4dnPE)  
- [STM32 Reference Manual – Interrupts Section (ST)](https://www.st.com/resource/en/reference_manual)  
- [NVIC Introduction (ARM)](https://developer.arm.com/documentation/ddi0439/latest/)  
