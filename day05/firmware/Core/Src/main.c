/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define LEN 256
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
extern SPI_HandleTypeDef hspi2; // master
extern SPI_HandleTypeDef hspi3; // slave
extern UART_HandleTypeDef huart2; // UART for debugging

static uint8_t m_tx[LEN], m_rx[LEN];
static uint8_t s_tx[LEN], s_rx[LEN];

static volatile uint8_t m_done = 0, s_done = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

// debug over UART
static void debug(const char *fmt, ...) {
    char buf[160]; // temp buffer on the stack to hold formatted message before sendeing
    va_list ap; // va_list is a special type to traverse variable args
    va_start(ap, fmt); // initializes ap so it points to the first var arg after fmt;

    // works like snprintf, taking va_list instead of direct args
    // it writes a formatted string into buf using fmt and ap
    // and also ensures no more than sizeof(buf) chars are written (160 here)
    int n = vsnprintf(buf, sizeof(buf), fmt, ap);

    // mandatory after calling va_start
    va_end(ap);

    if (n < 0) return; // indicates some sort of formatting error or failure with vsnprintf
    if (n > (int)sizeof(buf)) n = sizeof(buf); // truncates the string as to not overflow the buffer

    // uses HALs blocking transmit function to transmit over UART
    // &huart2 is the UART handle (goes out onto USART2)
    // (uint8_t*)buf os casing the message string into bytes
    // (uint16_t)n represents how many characters to send.
    // HAL_MAX_DELAY means "wait forever until the transmission finishes"
    HAL_UART_Transmit(&huart2, (uint8_t*)buf, (uint16_t)n, HAL_MAX_DELAY);
}


// puts the slave in "ready and waiting" state so it is ready for first master clock pulse.
static void slave_arm_dma(void) {
	// fill the slave tx buffer with a known XOR index pattern
	// question: why do we use this pattern?
	// answer: using this pattern gives high-variation testing data (alternating bits, all bits are different)
	// allows us to catch any minor mistakes we made in MCU configuration, wiring, or code.
    for (uint16_t i = 0; i < LEN; i++) {
    	s_tx[i] = (uint8_t)(0x55 ^ i);
    }

    // this flag indicate that the transfer is complete, and here it's not.
    // we will set this flag in the DMA complete callback so that we know when the transfer finished.
    s_done = 0;

    // slave peripheral will use DMA both ways
    // read bytes from s_tx and write to SPI3->DR
    // then read received bytes from SPI3->DR and store into s_rx.
    // question: what exactly is SPI3->DR?
    // answer: SPI3->DR is the hardware SPI data register for the peripheral.
    // when using DMA we need an intermediate step of writing into then reading from that data register.
    // DMA never writes directly into the other memory.
    // question: why do we bother writing from s_tx to s_rx?? shouldn't we write to the m_rx
    // answer: we're not writing in that way. 2 DMA streams run on the slave, the tx and rx streams.
    // the tx stream shifts a bit onto MISO toward the master
    // the rx stream takes a bit from MOSI into the data register, and then DMA into s_rx.
    if (HAL_SPI_TransmitReceive_DMA(&hspi3, s_tx, s_rx, LEN) != HAL_OK) {
        Error_Handler();
    }
}

// drives the SPI transaction, we call this after the slave is armed.
static void master_start_dma(void) {
	// prepare master tx buffer with another known pattern
    for (uint16_t i = 0; i < LEN; i++) {
    	m_tx[i] = (uint8_t)(0xA0 + i);
    }

    // clear the master done flag
    m_done = 0;

    // start master transfer using DMA
    // each clock byte from m_tx shifted out to MOSI via DMA, feeding SPI2->DR.
    // then, byte from MISO sampled into SPI2->DR and DMA stores in m_rx.
    if (HAL_SPI_TransmitReceive_DMA(&hspi2, m_tx, m_rx, LEN) != HAL_OK) {
        Error_Handler();
    }
}

// DMA completion callbacks
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi) {
	// When the transaction via DMA is complete, we will set the "done" status to 1.
	// This lets us know the SPI transaction was successful.
    if (hspi->Instance == SPI2) m_done = 1;
    if (hspi->Instance == SPI3) s_done = 1;
}

void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi) {
    // Inspect hspi->ErrorCode if needed
    __NOP(); // do nothing instruction, can set breakpoint here for debugging

    // alternatively we would like some sort of error indicator and handling.
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_SPI2_Init();
  MX_SPI3_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  debug("peripherals initialized\r\n");
  debug("initializing SPI over DMA...\r\n");

  slave_arm_dma();
  master_start_dma();

  uint32_t lastBlink = HAL_GetTick();

  // make sure LED is off to start
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  // save time for timeout checking
  uint32_t watchdog_start = HAL_GetTick();

  // since DMA runs async to the main loop, we need to wait for the DMA actions to complete.
  while (!(m_done && s_done)) {
	  uint32_t now = HAL_GetTick();
	  // bilnk LED every 50ms to indicate we are waiting for the slame & master to be ready.
	  if (now - lastBlink >= 50U) {
		  HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		  lastBlink = now;
	  }

	  // timeout and handle error if takes too long.
	  if (now - watchdog_start > 2000U) {
		  Error_Handler();
	  }
  }

  debug("DMA & SPI test completed\r\n");

  uint32_t errors = 0;

  debug("verifying slave receive\r\n");
  // verify
  for (uint16_t i = 0; i < LEN; i++) {
	  debug("s_rx %u m_tx %u\r\n", s_rx[i], m_tx[i]);
	  if (s_rx[i] != m_tx[i]) errors++;
  }


  debug("verifying master receive\r\n");
  for (uint16_t i = 0; i < LEN; i++) {
	  debug("m_rx %u s_tx %u\r\n", m_rx[i], s_tx[i]);
	  if (m_rx[i] != s_tx[i]) errors++;
  }

  if (errors == 0) {
	  debug("No errors found\r\n");
  } else {
	  debug("%u Errors found.\r\n", errors);
  }

  // indicate success by enabling LED
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
