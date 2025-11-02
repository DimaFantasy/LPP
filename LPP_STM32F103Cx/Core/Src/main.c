/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
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
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <math.h>
#include <stdbool.h>
#include "counter.h"
#include "stdio.h"

#include "lpp_sdk.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

// Глобальные определения таймеров и режимов
TIM_HandleTypeDef htim1;  // Основной таймер для управления мотором X

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

DMA_HandleTypeDef hdma_memtomem_dma1_channel1;
/* USER CODE BEGIN PV */

void XferCpltCallback(DMA_HandleTypeDef *hdma);

// ============================================================================
// Сигнатура и версия прошивки (APP)
// ============================================================================
const uint32_t APP_KEY0   __attribute__((section(APP_KEY0_SECTION)))   = APP_SIG_KEY0;
const uint32_t APP_KEY1   __attribute__((section(APP_KEY1_SECTION)))   = APP_SIG_KEY1;
const uint32_t APP_KEY2   __attribute__((section(APP_KEY2_SECTION)))   = APP_SIG_KEY2;
const uint32_t APP_KEY3   __attribute__((section(APP_KEY3_SECTION)))   = APP_SIG_KEY3;

const uint32_t APP_VER_F  __attribute__((section(APP_VER_F_SECTION)))  = APP_VERSION;


// ============================================================================
// Внешние объявления
// ============================================================================

extern uint8_t USBD_CUSTOM_HID_SendReport(USBD_HandleTypeDef* pdev, uint8_t* report, uint16_t len);
extern USBD_HandleTypeDef hUsbDeviceFS;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM4_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_USB_DEVICE_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
		// Инициализация 
		Lpp_Init();		
    // Настройка приоритетов прерываний
    HAL_NVIC_SetPriority(TIM1_UP_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(TIM1_UP_IRQn);
    HAL_NVIC_SetPriority(TIM1_CC_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(TIM1_CC_IRQn);

    // Инициализация мотора X

//    MotorX_Init(MOTORX_MODE_START);

    // Запуск PWM для лазера и подсветки
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);  // Лазер
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);  // Подсветка

    // Запуск таймеров
    HAL_TIM_Base_Start_IT(&htim4);

    // Инициализация задержки и периферии
    HAL_Delay(2000);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);    // Включение USB
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);  // Выключение контроллера Y

    // Настройка DMA callback
    HAL_DMA_RegisterCallback(&hdma_memtomem_dma1_channel1, HAL_DMA_XFER_CPLT_CB_ID, XferCpltCallback);
		

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    while (1) {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
			
			Lpp_MainLoop();
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */
  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */
  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 5;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 100;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */
  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */
  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */
  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 72;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 1;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */
    // Настройка прерываний TIM3 (опционально)
    HAL_NVIC_SetPriority(TIM3_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(TIM3_IRQn);
  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */
  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM4_Init 1 */
  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 72;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 10000;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_OnePulse_Init(&htim4, TIM_OPMODE_SINGLE) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */
  /* USER CODE END TIM4_Init 2 */

}

/**
  * Enable DMA controller clock
  * Configure DMA for memory to memory transfers
  *   hdma_memtomem_dma1_channel1
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* Configure DMA request hdma_memtomem_dma1_channel1 on DMA1_Channel1 */
  hdma_memtomem_dma1_channel1.Instance = DMA1_Channel1;
  hdma_memtomem_dma1_channel1.Init.Direction = DMA_MEMORY_TO_MEMORY;
  hdma_memtomem_dma1_channel1.Init.PeriphInc = DMA_PINC_ENABLE;
  hdma_memtomem_dma1_channel1.Init.MemInc = DMA_MINC_ENABLE;
  hdma_memtomem_dma1_channel1.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
  hdma_memtomem_dma1_channel1.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
  hdma_memtomem_dma1_channel1.Init.Mode = DMA_NORMAL;
  hdma_memtomem_dma1_channel1.Init.Priority = DMA_PRIORITY_LOW;
  if (HAL_DMA_Init(&hdma_memtomem_dma1_channel1) != HAL_OK)
  {
    Error_Handler( );
  }

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7|GPIO_PIN_8, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA7 PA8 */
  GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB6 PB8 */
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  /* USER CODE BEGIN MX_GPIO_Init_2 */
  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

// ============================================================================
// Функции управления мотором X
// ============================================================================

/**
 * @brief Установка мощности мотора X
 * @param power Мощность (-5000 до +5000)
 * @retval None
 */
void MotorX_Set(int power) {
    // Ограничение мощности
    if (power > 5000) power = 5000;
    if (power < -5000) power = -5000;

    // Режим ONE_PWM: один ШИМ + DIR
    if (motorXMode == MOTORX_MODE_ONE_PWM) {
        TIM1->CCR1 = (W_X_POL_PWM == 0) ? abs(power) : (5000 - abs(power));
        
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14,
                          (W_X_POL_DIR == 0) ? ((power >= 0) ? GPIO_PIN_RESET : GPIO_PIN_SET)
                                             : ((power >= 0) ? GPIO_PIN_SET : GPIO_PIN_RESET));
    }

    // Режим TWO_PWM: два ШИМ канала
    if (motorXMode == MOTORX_MODE_TWO_PWM) {
        if (W_X_POL_PWM == 0) {
            TIM1->CCR1 = 5000 + power;
            TIM1->CCR2 = 5000 - power;
        } else {
            TIM1->CCR1 = 5000 - power;
            TIM1->CCR2 = 5000 + power;
        }
    }
}

// ============================================================================
// MotorX_Init — инициализация таймера и GPIO для оси X
// Поддерживаются 3 режима работы двигателя:
//   1) MOTORX_MODE_STEP      — Шаговый двигатель (STEP + DIR)
//   2) MOTORX_MODE_ONE_PWM   — Один ШИМ + DIR
//   3) MOTORX_MODE_TWO_PWM   — Два ШИМ (Dual H-Bridge)
// В любом режиме пин PB15 (ENABLE) используется как выход, активный уровень
// задаётся при настройке, но здесь он просто включается.
// ============================================================================

void MotorX_Init(MotorXMode_t mode)
{
    if (motorXMode == mode) return; // если режим уже установлен — выходим

    // ------------------------------------------------------------------------
    // Режим START — отключаем таймер и переводим пины в безопасное состояние
    // ------------------------------------------------------------------------
    if (mode == MOTORX_MODE_START)
    {
        __HAL_RCC_TIM1_FORCE_RESET();     // сброс таймера
        __HAL_RCC_TIM1_RELEASE_RESET();

        GPIO_InitTypeDef GPIO_InitStruct = {0};
        GPIO_InitStruct.Pin = GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        motorXMode = mode;
        return;
    }

    // ------------------------------------------------------------------------
    // Включаем тактирование портов и TIM1
    // ------------------------------------------------------------------------
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_TIM1_CLK_ENABLE();
    __HAL_RCC_AFIO_CLK_ENABLE();

    // ------------------------------------------------------------------------
    // Настройка ENABLE (PB15) — всегда как выход push-pull
    // ------------------------------------------------------------------------
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET); // включаем драйвер

    // ------------------------------------------------------------------------
    // Режим STEP + DIR (шаговый двигатель, без энкодера)
    // ------------------------------------------------------------------------
    if (mode == MOTORX_MODE_STEP)
    {
        // Настройка GPIO: PB13 = STEP, PB14 = DIR
        GPIO_InitStruct.Pin = GPIO_PIN_13 | GPIO_PIN_14;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        // Начальные уровни
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);

        // --- Настройка TIM1 для генерации коротких STEP-импульсов ---
        TIM_ClockConfigTypeDef sClockSourceConfig = {0};
        TIM_MasterConfigTypeDef sMasterConfig = {0};

        htim1.Instance = TIM1;
        htim1.Init.Prescaler = 72;               // 72 MHz / 72 = 1 MHz (1 мкс)
        htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
        htim1.Init.Period = 10000;               // 1 мкс — длина импульса
        htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
        htim1.Init.RepetitionCounter = 0;
        htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

        HAL_TIM_Base_Init(&htim1);
        sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
        HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig);

        // Включаем One Pulse Mode
        HAL_TIM_OnePulse_Init(&htim1, TIM_OPMODE_SINGLE);

        sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
        sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
        HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig);

        // Прерывание TIM1_UP (срабатывает по завершению импульса)
        HAL_NVIC_SetPriority(TIM1_UP_IRQn, 1, 0);
        HAL_NVIC_EnableIRQ(TIM1_UP_IRQn);
				
				// Обнуляем счётчик таймера
				__HAL_TIM_SET_COUNTER(&htim1, 0);  
				// Запускаем таймер в режиме One Pulse (вызовет колбэк один раз)
				HAL_TIM_Base_Start_IT(&htim1);				
    }

    // ------------------------------------------------------------------------
    // PWM-режимы (1PWM + DIR) и (2PWM — Dual Bridge)
    // ------------------------------------------------------------------------
    else
    {
        // PB13 — PWM выход, PB14 — либо PWM2, либо DIR
        GPIO_InitStruct.Pin = GPIO_PIN_13;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        if (mode == MOTORX_MODE_TWO_PWM) {
            GPIO_InitStruct.Pin = GPIO_PIN_14;
            GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
            HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
        } else {
            GPIO_InitStruct.Pin = GPIO_PIN_14;
            GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
            HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
        }

        // Настройка TIM1 под PWM
        htim1.Instance = TIM1;
        if (mode == MOTORX_MODE_ONE_PWM) {
            htim1.Init.Prescaler = 15;
            htim1.Init.Period = 4999;
        } else {
            htim1.Init.Prescaler = 7;
            htim1.Init.Period = 9999;
        }

        htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
        htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
        htim1.Init.RepetitionCounter = 0;
        htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

        HAL_TIM_Base_Init(&htim1);

        TIM_ClockConfigTypeDef sClockSourceConfig = {0};
        sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
        HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig);

        HAL_TIM_PWM_Init(&htim1);

        // Конфигурация PWM-каналов
        TIM_OC_InitTypeDef sConfigOC = {0};
        sConfigOC.OCMode = TIM_OCMODE_PWM1;
        sConfigOC.Pulse = 0;
        sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
        sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
        sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
        sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
        sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;

        HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1);
        HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2);

        // Настройка DeadTime и Break-функций
        TIM_BreakDeadTimeConfigTypeDef sBDT = {0};
        sBDT.OffStateRunMode = TIM_OSSR_DISABLE;
        sBDT.OffStateIDLEMode = TIM_OSSI_DISABLE;
        sBDT.LockLevel = TIM_LOCKLEVEL_OFF;
        sBDT.DeadTime = 0;
        sBDT.BreakState = TIM_BREAK_DISABLE;
        sBDT.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
        sBDT.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
        HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBDT);

        HAL_NVIC_SetPriority(TIM1_UP_IRQn, 2, 0);
        HAL_NVIC_EnableIRQ(TIM1_UP_IRQn);

        // Запуск таймера и каналов PWM
        HAL_TIM_Base_Start_IT(&htim1);
        HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
        TIM1->BDTR |= TIM_BDTR_MOE;
        TIM1->CCER |= TIM_CCER_CC1NE;

        if (mode == MOTORX_MODE_TWO_PWM) {
            HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
            TIM1->CCER |= TIM_CCER_CC2NE;
        }
    }

    // Сохраняем текущий режим
    motorXMode = mode;
}



// ============================================================================
// Функции управления осью Y
// ============================================================================

// Установка направления вращения (DIR)
void YTimerSetDir(uint8_t dir_pin_state)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, dir_pin_state);
}

// Импульс STEP (высокий или низкий уровень)
void YTimerStep(uint8_t step_pin_state)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, step_pin_state);
}


// установка периода и запуск таймера YTimer
void YTimerSet(uint16_t period)
{
    __HAL_TIM_SET_AUTORELOAD(&htim4, period);
    __HAL_TIM_ENABLE(&htim4);
}

// ============================================================================
// Управление шаговым двигателем X (в режиме MOTORX_MODE_STEP)
// ============================================================================
// Установка направления DIR для оси X
// @param dir_pin_state: состояние пина (0 или 1)
void XTimerSetDir(uint8_t dir_pin_state)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, dir_pin_state);
}

// Установка состояния STEP для оси X
// step_pin_state: состояние пина (0 или 1)
void XTimerStep(uint8_t step_pin_state)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, (step_pin_state) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

// @brief Установка периода и запуск TIM1 для шагов X
// @param period: период в тактах таймера (микросекунды при Prescaler=71)
void XTimerSet(uint16_t period)
{
    __HAL_TIM_SET_AUTORELOAD(&htim1, period);
    __HAL_TIM_ENABLE(&htim1);
}

// ============================================================================
// Обработчики прерываний таймеров
// ============================================================================

/**
 * @brief Callback обработки переполнения таймера
 * @param htim Указатель на обработчик таймера
 * @retval None
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {
    // TIM1 - Управление мотором X и PID регулятор
    if (htim->Instance == TIM1) {
			XTimerCallback();

    }

    // TIM3 - Интерполяция печати
    if (htim->Instance == TIM3) {
			
        // SDK вариант: один шаг интерполяции
        if (PrintStepInterp() == 0)
        {
            // Возврат 0 означает, что серия интерполяции завершена
            HAL_TIM_Base_Stop_IT(&htim3);
            TIM3->CNT = 0;  // Сброс счетчика
        }						
    }

    // TIM4 - Управление осью Y
    if (htim->Instance == TIM4) {
			YTimerCallback();
    }
}

// ============================================================================
// Обработчики внешних прерываний (энкодер)
// ============================================================================

// Установка мощности лазера (TIM2 CH1)

void SetLaserPWM(uint16_t pwm_value)
{
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, pwm_value);
}

// Установка мощности подсветки (TIM2 CH2)

void SetLightPWM(uint16_t pwm_value)
{
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, pwm_value);
}

// Установка делителя частоты PWM (общий PSC для лазера и подсветки)
//void SetPwmPrescaler(uint16_t prescaler)
//{
//    htim2.Instance->PSC = prescaler;
//    __HAL_TIM_SET_COUNTER(&htim2, 0);
//}

/**
 * @brief  Настраивает частоту PWM по значению в герцах (универсально для разных MCU).
 * @param  freq_hz  Желаемая частота PWM, Гц (например 1000, 5000, 100000).
 * 
 * Функция автоматически вычисляет нужный делитель (PSC) на основе частоты шины таймера.
 * Работает одинаково для разных частот системного тактирования (STM32F1, F4, G4, S3 и т.д.).
 * 
 * Пример: если tim_clk = 72 MHz, freq_hz = 20 kHz, ARR = 999, 
 *         PSC = (72_000_000 / (1000 * 20_000)) = 3,6 → PSC = 3.
 */
void SetLaserLightPWMFrequency(uint32_t freq_hz)
{
    // Получаем частоту шины таймера.
    // Для TIM1/TIM8 это обычно PCLK2, для TIM2–TIM7 — PCLK1.
    uint32_t tim_clk = HAL_RCC_GetPCLK1Freq(); 

    // Устанавливаем значение ARR — диапазон счётчика.
    // Здесь выбран 1000 шагов ШИМ, что удобно для 0.1% точности.
    // Можно сделать параметром, если нужно динамически менять разрешение PWM.
    uint32_t arr = 1000 - 1;                   

    // Вычисляем делитель (PSC) по формуле:
    // f_PWM = tim_clk / ((PSC + 1) * (ARR + 1))
    // → PSC = (tim_clk / ((ARR + 1) * freq_hz)) - 1
    uint32_t prescaler = (tim_clk / (arr + 1)) / freq_hz;

    // Защита от выхода за диапазон 16-битного регистра PSC
    if (prescaler < 1) prescaler = 1;
    if (prescaler > 65535) prescaler = 65535;

    // Применяем настройки в таймер
    htim2.Instance->PSC = prescaler - 1;   // Устанавливаем делитель
    htim2.Instance->ARR = arr;             // Задаём диапазон счётчика
    __HAL_TIM_SET_COUNTER(&htim2, 0);      // Сбрасываем счётчик для стабильного старта
}

void InterpTimerStart(uint32_t period) {
    // Старт интерполяционого таймера
	  TIM3->ARR = period;          // Установка периода
    TIM3->SR &= ~TIM_SR_UIF;     // Сброс флага прерывания
    TIM3->DIER |= TIM_DIER_UIE;  // Разрешение прерывания
    TIM3->CR1 |= TIM_CR1_CEN;    // Запуск таймера
}

uint16_t ReadEncoderPins(void) {
    // Читаем состояние пинов энкодера на порту B
    return GPIOB->IDR & (ENCODER_A_PIN | ENCODER_B_PIN);
}

/**
 * @brief Callback обработки внешних прерываний (энкодер)
 * @param GPIO_Pin Пин, вызвавший прерывание
 * @retval None
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {		
	PrintStep();
};


// ============================================================================
// Отправка 64-байтного пакета хосту (используется SDK)
// ============================================================================
uint8_t PacketSend(uint8_t* buffer)
{
    // Отправка HID отчёта (64 байта)
    return USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, buffer, 64);
}

// ============================================================================
// Запуск DMA для копирования блока данных FIFO (вызывается из SDK)
// ============================================================================
void FIFO_DATA_StartDma(uint32_t src_addr, uint32_t dst_addr, uint16_t size)
{
    HAL_DMA_Start_IT(
        &hdma_memtomem_dma1_channel1,
        src_addr,
        dst_addr,
        size  // передаём размер извне
    );
}

// ============================================================================
// Обработчик завершения DMA передачи
// ============================================================================
/**
 * @brief Callback завершения DMA передачи
 * @param hdma Указатель на структуру DMA
 * @retval None
 */
void XferCpltCallback(DMA_HandleTypeDef* hdma) {
	// Проверяем, что это нужный канал DMA
	if (hdma == &hdma_memtomem_dma1_channel1) {
		FIFO_DATA_EndDma();		
	}
}

// ============================================================================
// Управление сигналом ENABLE для оси Y
// ============================================================================
void YSetEnablePin(uint8_t enabled)
{
    // ENA_Y → GPIOA PIN7
    if (enabled)
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
    else
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
}

// ============================================================================
// Управление сигналом ENABLE для оси X
// ============================================================================
void XSetEnablePin(uint8_t enabled)
{
    // ENA_X → GPIOB PIN15
    if (enabled)
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
    else
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
}


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
    __disable_irq();
    while (1) {
    }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
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
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
