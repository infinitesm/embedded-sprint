# Embedded Sprint – Day 3 (Aug 13) Overview

## Summary
Day 3 focuses on GPIO fundamentals using STM32CubeIDE: setting up an LED blink and a button toggle with software debouncing. You will master CubeMX pin configuration, HAL-based GPIO control, and timing functions.

## Topics
- **STM32CubeIDE / CubeMX**: Creating a new project, enabling GPIO peripherals  
- **GPIO Modes**: Output push-pull (LED), input with pull-up (button)  
- **HAL Functions**: `HAL_GPIO_Init`, `HAL_GPIO_TogglePin`, `HAL_Delay`, `HAL_GetTick`  
- **Software Debounce**: Implementing time-based filtering using ticks  
- **Project Structure**: `main.c` layout, `SysClock_Config`, error handlers

## Tasks
1. **Environment Setup**  
   - Install STM32CubeIDE (Windows/Linux/Mac).  
   - Create a new project for your STM32F4/Nucleo board in CubeMX.
2. **Pin Configuration**  
   - Set PA5 as GPIO output for LED.  
   - Set PC13 as GPIO input with Pull‑Up for the button.
3. **Code Skeleton**  
   - Generate code; locate `Src/main.c`.  
   - Add prototypes: `Blink_LED_Init()`, `Button_Init()`, `Blink_LED_Task()`, `Button_Task()`.
4. **Documentation**  
   - Draft sections in `README.md`: build & flash steps, pin mappings, code module descriptions.

## Deliverables

### 1. LED Blink Module
- **Prototype**:
  ```c
  /**
   * @brief  Initializes LED GPIO.
   * @param  none
   * @retval none
   */
  void Blink_LED_Init(void);

  /**
   * @brief  Toggles LED at 1 Hz.
   * @param  none
   * @retval none
   * @constraints: Use HAL_Delay(500); no busy loops.
   */
  void Blink_LED_Task(void);
  ```

### 2. Button Toggle Module with Debounce
- **Variables**:
  ```c
  static uint32_t lastDebounceTime;
  static GPIO_PinState lastButtonState;
  ```
- **Prototype**:
  ```c
  /**
   * @brief  Initializes Button GPIO.
   * @param  none
   * @retval none
   */
  void Button_Init(void);

  /**
   * @brief  Reads button with 50 ms debounce and toggles LED on press.
   * @param  none
   * @retval none
   * @constraints: Use HAL_GetTick(); compare time delta >50 ms.
   */
  void Button_Task(void);
  ```

### 3. Git Integration
- `.gitignore` for `Build/`, `*.o`, `*.elf`, `.vs/`.  
- Commit and tag:  
  ```bash
  git init
  git add .
  git commit -m "Day 3: GPIO blink & button debounce skeleton"
  git tag day3_blink_button
  ```

### 4. Optional CLI Build Makefile
Include a Makefile skeleton for `arm-none-eabi-gcc` similar to previous days.

## Learning Resources
- [STM32CubeIDE Quickstart (YouTube)](https://www.youtube.com/watch?v=9KF-62JhQ6c)  
- [STM32 HAL GPIO Tutorial (YouTube)](https://www.youtube.com/watch?v=G7VEU1qN6uA)  
- [Debouncing Techniques (Embedded.com)](https://www.embedded.com/software-debouncing-techniques/)  
- [STM32 HAL API Reference (ST)](https://www.st.com/content/st_com/en/support.html)  
- [GPIO Input Pull‑Up/Pull‑Down Explanation](https://www.microcontrollerslab.com/stm32-pull-up-pull-down-stm32cube/)  
