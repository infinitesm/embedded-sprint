# Embedded Sprint – Day 6 (Aug 16) Overview

## Summary
Set up UART for debugging prints and integrate a ring buffer for incoming data.

## Topics
- **UART transmit/receive; baud rate configuration; 8‑N‑1 framing**
- **printf retargeting via _write or HAL_UART_Transmit**
- **Circular buffers for RX data; thread safety**
- **HAL UART callbacks: HAL_UART_RxCpltCallback, HAL_UART_RxHalfCpltCallback**
- **Simple command parsing from buffered data**

## Tasks
- Configure USART2 at 115200 baud, 8‑N‑1 with TX/RX in CubeMX
- Implement uart_printf() by overriding _write or using HAL_UART_Transmit
- Integrate CircularBuffer: enqueue in RX callback, dequeue in main loop for echo/commands
- Document buffer thread safety and callback integration

## Deliverables
### UART printf project

Retarget printf to UART: printf("Hello\n") sends over USART. Non-blocking via interrupt or polling.

```c
/**
 * @brief  Retargets printf to UART.
 * @param  fmt: format string
 * @param  ...: variadic args
 * @retval number of bytes transmitted
 * @constraints: Non-blocking, CR-LF line endings
 */
int uart_printf(const char *fmt, ...);
```

### UART RX ring buffer

Use HAL_UART_RxCpltCallback to enqueue bytes into CircularBuffer. Main loop dequeues and echoes or parses commands.

```c
/**
 * @brief  UART receive complete callback.
 * @param  huart: UART handle
 * @retval none
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

/**
 * @brief  Processes buffered UART data.
 * @param  none
 * @retval none
 * @constraints: Disable interrupts when accessing head/tail indices or use volatile
 */
void UART_ProcessBuffer(void);
```

### Log parser script

Bash or Python script using screen/minicom to log UART output and parse lines with "ERROR" or "PASS".

```bash
#!/usr/bin/env bash
# log_parser.sh
# Usage: ./log_parser.sh /dev/ttyUSB0 logfile.txt
screen -L -Logfile $2 $1 115200
grep -E "ERROR|PASS" $2 | sed 's/^/LOG: /'
```

## Learning Resources
- [Retarget printf for STM32](https://www.youtube.com/watch?v=0fr_X4Y8Allowed)
- [STM32 UART HAL Tutorial](https://www.youtube.com/watch?v=USJtwVnrMTw)
- [Implementing Circular Buffer in C](https://embeddedartistry.com/blog/2017/6/21/circular-buffers-in-cc)
- [HAL UART Callbacks (ST forum)](https://community.st.com/s/question/0D53W00000JP4cFSAT/uart-rcvcomplete-callback)
