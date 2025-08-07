# Embedded Sprint – Day 8 (Aug 18) Overview

## Summary
Interface with analog inputs using ADC and control outputs using PWM, demonstrating real-time data acquisition and actuator control.

## Topics
- **ADC sampling modes, resolution, reference voltage**
- **PWM basics: frequency, duty cycle**
- **Scaling analog values to digital**
- **HAL ADC and PWM APIs: polling vs interrupt**

## Tasks
- Configure ADC channel in CubeMX (continuous conv mode)
- Configure timer PWM channel to drive LED or servo
- Implement adc_read(), set_pwm_duty() functions
- Compare polling vs interrupt performance

## Deliverables
### ADC sampling project
Implement adc_read() returning raw ADC value and converted millivolts. Print results over UART.

```c
/**
 * @brief  Reads ADC channel and returns raw value.
 * @retval 12-bit ADC read (0-4095)
 */
uint16_t adc_read(void);

/**
 * @brief  Converts raw ADC value to millivolts.
 * @param  raw: ADC raw value
 * @retval voltage in mV
 */
uint32_t adc_to_millivolts(uint16_t raw);
```

### PWM control
Implement set_pwm_duty(uint8_t duty) to map 0-100% to CCR register. Dimming LED based on ADC.

```c
/**
 * @brief  Sets PWM duty cycle.
 * @param  duty: percentage 0-100
 * @retval none
 */
void set_pwm_duty(uint8_t duty);
```

### Interrupt vs polling report
Compare CPU usage and responsiveness between polling and interrupt-driven ADC. Discuss efficiency.

## Learning Resources
- [STM32 ADC Tutorial](https://www.youtube.com/watch?v=9x1D5nF6Q8Y)
- [STM32 PWM Tutorial](https://www.youtube.com/watch?v=7X9K1wu_SkQ)
- [ADC vs DMA vs Polling](https://www.youtube.com/watch?v=hX_GN2YQ0v4)
