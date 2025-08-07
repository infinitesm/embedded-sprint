# Embedded Sprint – Day 5 (Aug 15) Overview

## Summary
Day 5 covers SPI fundamentals on STM32. You will configure SPI1 as master, set up a loopback test (MOSI→MISO), and verify full‑duplex communication using HAL.

## Topics
- **SPI Signals**: MOSI, MISO, SCLK, SS  
- **SPI Modes**: CPOL/CPHA configurations  
- **Frame Size & Order**: MSB‑first vs LSB‑first  
- **CubeMX SPI Config**: Master mode, baud rate, clock settings  
- **Loopback Testing**: External wiring, HAL transmit/receive

## Tasks
1. **Study**  
   - Review SPI concepts on Wikipedia and a YouTube tutorial.  
2. **Hardware Setup**  
   - Configure SPI1 master in CubeMX.  
   - Connect SPI1_MOSI to SPI1_MISO with a jumper.
3. **Code Skeleton**  
   - In `spi.c/spi.h`, prototypes: `spi_loopback_test()`, `SPI_Print_Buffers()`.  
   - Initialize SPI1 and CS GPIO manually.

## Deliverables

### 1. SPI Loopback Module
- **Prototype**:
  ```c
  /**
   * @brief  Performs SPI loopback transaction.
   * @param  txBuf: transmit buffer pointer
   * @param  rxBuf: receive buffer pointer
   * @param  len: number of bytes
   * @retval HAL_StatusTypeDef (HAL_OK on match)
   * @constraints: Manual CS control, timeout = 1000 ms
   */
  HAL_StatusTypeDef spi_loopback_test(uint8_t *txBuf, uint8_t *rxBuf, uint16_t len);
  ```

### 2. SPI Diagnostics Module
- **Prototype**:
  ```c
  /**
   * @brief  Prints TX and RX buffers over UART.
   * @param  txBuf: transmit buffer
   * @param  rxBuf: receive buffer
   * @param  len: buffer length
   * @retval none
   * @constraints: UART initialized, use printf
   */
  void SPI_Print_Buffers(uint8_t *txBuf, uint8_t *rxBuf, uint16_t len);
  ```

### 3. Protocol Summary
Short document explaining:
- Roles of MOSI, MISO, SCLK, SS  
- CPOL/CPHA effects on clock idle state and sampling edge  
- Why loopback confirms full‑duplex

### 4. Git Workflow
```bash
git add .
git commit -m "Day 5: SPI loopback & diagnostics skeleton"
git tag day5_spi_loopback
```

## Learning Resources
- [SPI Protocol Explained (YouTube)](https://www.youtube.com/watch?v=_dRy-lTqsHc)  
- [STM32 SPI Loopback Tutorial (YouTube)](https://www.youtube.com/watch?v=GnS3XeHrFNI)  
- [SPI Wikipedia Article](https://en.wikipedia.org/wiki/Serial_Peripheral_Interface)  
- [STM32CubeMX SPI Configuration Guide](https://community.st.com/s/article/CubeMX-SPI-Configuration)  
