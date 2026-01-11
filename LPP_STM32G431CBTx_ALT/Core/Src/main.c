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

#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include <math.h>
#include <stdbool.h>

#include "counter.h"
#include "lpp_sdk.h"
#include "stdio.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

DMA_HandleTypeDef hdma_memtomem_dma1_channel1;
/* USER CODE BEGIN PV */

void XferCpltCallback(DMA_HandleTypeDef* hdma);

// ============================================================================
// Сигнатура и версия прошивки (APP)
// ============================================================================
const uint32_t APP_KEY0 __attribute__((section(APP_KEY0_SECTION))) = APP_SIG_KEY0;
const uint32_t APP_KEY1 __attribute__((section(APP_KEY1_SECTION))) = APP_SIG_KEY1;
const uint32_t APP_KEY2 __attribute__((section(APP_KEY2_SECTION))) = APP_SIG_KEY2;
const uint32_t APP_KEY3 __attribute__((section(APP_KEY3_SECTION))) = APP_SIG_KEY3;

const uint32_t APP_VER_F __attribute__((section(APP_VER_F_SECTION))) = APP_VERSION;

// ---------------------------------------------------------------------------
// Глобальные переменные
// ---------------------------------------------------------------------------

// Пины H-моста
// Порт
#define HBRIDGE_PORT GPIOB
// H-мост (4 ключа)
#define MOS_HO_L GPIO_PIN_9  // Верхний левый
#define MOS_HO_R GPIO_PIN_6  // Верхний правый
#define MOS_LO_L GPIO_PIN_5  // Нижний левый
#define MOS_LO_R GPIO_PIN_3  // Нижний правый

// Глобальные переменные
TIM_HandleTypeDef htim1;
volatile int32_t pwm_value = 0;  // -5000 ... +5000

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
int main(void) {
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
    MX_USB_Device_Init();
    MX_TIM2_Init();
    MX_TIM3_Init();
    MX_TIM4_Init();
    /* USER CODE BEGIN 2 */
    // Инициализация

    Lpp_Init();

    // Запуск таймеров
    HAL_TIM_Base_Start_IT(&htim4);
    // Запуск ШИМ Лазера PA1
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);  // Лазер

    // Инициализация USB
    USB->BCDR &= ~USB_BCDR_DPPU; // DPPU = 0 → подтяжка DP отключена
//    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);  // Выключение USB
    HAL_Delay(2000);
//    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);  // Включение USB
    USB->BCDR |= USB_BCDR_DPPU; // DPPU = 1 → подтяжка DP включена 


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
void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage
     */
    HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48 | RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
    RCC_OscInitStruct.PLL.PLLN = 42;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
    RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType =
        RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK) {
        Error_Handler();
    }
}

/**
 * @brief TIM2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM2_Init(void) {
    /* USER CODE BEGIN TIM2_Init 0 */

    /* USER CODE END TIM2_Init 0 */

    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_OC_InitTypeDef sConfigOC = {0};

    /* USER CODE BEGIN TIM2_Init 1 */

    /* USER CODE END TIM2_Init 1 */
    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 0;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 100;
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim2) != HAL_OK) {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK) {
        Error_Handler();
    }
    if (HAL_TIM_PWM_Init(&htim2) != HAL_OK) {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK) {
        Error_Handler();
    }
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK) {
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
static void MX_TIM3_Init(void) {
    /* USER CODE BEGIN TIM3_Init 0 */

    /* USER CODE END TIM3_Init 0 */

    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};

    /* USER CODE BEGIN TIM3_Init 1 */

    /* USER CODE END TIM3_Init 1 */
    htim3.Instance = TIM3;
    htim3.Init.Prescaler = 160;
    htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim3.Init.Period = 65535;
    htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim3) != HAL_OK) {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK) {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK) {
        Error_Handler();
    }
    /* USER CODE BEGIN TIM3_Init 2 */

    /* USER CODE END TIM3_Init 2 */
}

/**
 * @brief TIM4 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM4_Init(void) {
    /* USER CODE BEGIN TIM4_Init 0 */

    /* USER CODE END TIM4_Init 0 */

    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};

    /* USER CODE BEGIN TIM4_Init 1 */

    /* USER CODE END TIM4_Init 1 */
    htim4.Instance = TIM4;
    htim4.Init.Prescaler = 160;
    htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim4.Init.Period = 10000;
    htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim4) != HAL_OK) {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK) {
        Error_Handler();
    }
    if (HAL_TIM_OnePulse_Init(&htim4, TIM_OPMODE_SINGLE) != HAL_OK) {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK) {
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
static void MX_DMA_Init(void) {
    /* DMA controller clock enable */
    __HAL_RCC_DMAMUX1_CLK_ENABLE();
    __HAL_RCC_DMA1_CLK_ENABLE();

    /* Configure DMA request hdma_memtomem_dma1_channel1 on DMA1_Channel1 */
    hdma_memtomem_dma1_channel1.Instance = DMA1_Channel1;
    hdma_memtomem_dma1_channel1.Init.Request = DMA_REQUEST_MEM2MEM;
    hdma_memtomem_dma1_channel1.Init.Direction = DMA_MEMORY_TO_MEMORY;
    hdma_memtomem_dma1_channel1.Init.PeriphInc = DMA_PINC_ENABLE;
    hdma_memtomem_dma1_channel1.Init.MemInc = DMA_MINC_ENABLE;
    hdma_memtomem_dma1_channel1.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_memtomem_dma1_channel1.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_memtomem_dma1_channel1.Init.Mode = DMA_NORMAL;
    hdma_memtomem_dma1_channel1.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_memtomem_dma1_channel1) != HAL_OK) {
        Error_Handler();
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
static void MX_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    /* USER CODE BEGIN MX_GPIO_Init_1 */

    /* USER CODE END MX_GPIO_Init_1 */

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10 | GPIO_PIN_15, GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_9,
                      GPIO_PIN_RESET);

    /*Configure GPIO pins : PA8 PA9 */
    GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*Configure GPIO pin : PA10 */
    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*Configure GPIO pin : PA15 */
    GPIO_InitStruct.Pin = GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*Configure GPIO pins : PB3 PB4 PB5 PB6
                             PB7 PB9 */
    GPIO_InitStruct.Pin = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /**/
    __HAL_SYSCFG_FASTMODEPLUS_ENABLE(SYSCFG_FASTMODEPLUS_PB7);

    /* EXTI interrupt init*/
    HAL_NVIC_SetPriority(EXTI9_5_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

    /* USER CODE BEGIN MX_GPIO_Init_2 */

    /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

// ============================================================================
// Отправка 64-байтного пакета хосту (используется SDK)
// ============================================================================
extern uint8_t USBD_CUSTOM_HID_SendReport(USBD_HandleTypeDef* pdev, uint8_t* report, uint16_t len);
extern USBD_HandleTypeDef hUsbDeviceFS;

uint8_t PacketSend(uint8_t* buffer) {
    // Отправка HID отчёта (64 байта)
    return USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, buffer, 64);
}

// ============================================================================
// MotorX_Init — инициализация таймера и GPIO для оси X
// Поддерживаются 3 режима работы двигателя:
//   1) X_MOTOR_MODE_STEP      — Шаговый двигатель (STEP + DIR)
//   2) X_MOTOR_MODE_ONE_PWM   — Один ШИМ + DIR
//   3) X_MOTOR_MODE_TWO_PWM   — Два ШИМ (Dual H-Bridge)
// В любом режиме пин PB15 (ENABLE) используется как выход, активный уровень
// задаётся при настройке, но здесь он просто включается.
// ============================================================================
// void XMotorInit(X_MOTOR_MODE_T mode)
//{
//    // Защита от повторной инициализации
//    static X_MOTOR_MODE_T current_mode = (X_MOTOR_MODE_T)(-1);
//    if (current_mode == mode) return;
//    current_mode = mode;

//    // GPIO
//    __HAL_RCC_GPIOB_CLK_ENABLE();
//    GPIO_InitTypeDef gpio = {0};
//    gpio.Pin = HBRIDGE_PIN_LEFT | HBRIDGE_PIN_RIGHT;
//    gpio.Mode = GPIO_MODE_OUTPUT_PP;
//    gpio.Pull = GPIO_NOPULL;
//    gpio.Speed = GPIO_SPEED_FREQ_HIGH;
//    HAL_GPIO_Init(HBRIDGE_PORT, &gpio);
//    HAL_GPIO_WritePin(HBRIDGE_PORT, HBRIDGE_PIN_LEFT | HBRIDGE_PIN_RIGHT, GPIO_PIN_RESET);

//    // TIM1: 160 MHz → делитель 31 → ~5.161 MHz, ARR=5000 → ~1.032 кГц
//    __HAL_RCC_TIM1_CLK_ENABLE();
//    htim1.Instance = TIM1;
//    htim1.Init.Prescaler = 30;        // (30 + 1) = 31
//    htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
//    htim1.Init.Period = 5000;         // 0 ... 5000 → 5001 такт
//    htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
//    htim1.Init.RepetitionCounter = 0;
//    htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
//    HAL_TIM_Base_Init(&htim1);

//    // Прерывания (STM32G4)
//    HAL_NVIC_SetPriority(TIM1_UP_TIM16_IRQn, 1, 0);
//    HAL_NVIC_EnableIRQ(TIM1_UP_TIM16_IRQn);

//    HAL_NVIC_SetPriority(TIM1_CC_IRQn, 1, 1);
//    HAL_NVIC_EnableIRQ(TIM1_CC_IRQn);

//    HAL_TIM_Base_Start_IT(&htim1);
//}

void XMotorInit(X_MOTOR_MODE_T mode) {
    static X_MOTOR_MODE_T current_mode = (X_MOTOR_MODE_T)(-1);
    if (current_mode == mode) return;
    current_mode = mode;

    // спад PWM → всё OFF
    HAL_GPIO_WritePin(HBRIDGE_PORT, MOS_HO_L | MOS_HO_R | MOS_LO_L | MOS_LO_R, GPIO_PIN_RESET);

    __HAL_RCC_TIM1_CLK_ENABLE();
    htim1.Instance = TIM1;
    htim1.Init.Prescaler = 30;
    htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim1.Init.Period = 5000;
    htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim1.Init.RepetitionCounter = 0;
    htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    HAL_TIM_Base_Init(&htim1);

    // КЛЮЧЕВАЯ СТРОКА для TIM1:
    TIM1->BDTR |= TIM_BDTR_MOE;

    HAL_NVIC_SetPriority(TIM1_UP_TIM16_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(TIM1_UP_TIM16_IRQn);
    HAL_NVIC_SetPriority(TIM1_CC_IRQn, 1, 1);
    HAL_NVIC_EnableIRQ(TIM1_CC_IRQn);

    // НЕ вызываем HAL_TIM_Base_Start_IT()
    // Вместо этого включаем вручную:
    __HAL_TIM_ENABLE_IT(&htim1, TIM_IT_UPDATE);
    __HAL_TIM_ENABLE_IT(&htim1, TIM_IT_CC1);
    __HAL_TIM_ENABLE(&htim1);
}

void XMotorSet(int power) {
    if (power > 5000) power = 5000;
    if (power < -5000) power = -5000;

    pwm_value = (W_X_POL_PWM == 0) ? power : -power;
}

__STATIC_INLINE void HBridgeDeadTime(void) {
    volatile int i;
    for (i = 0; i < 100; i++)  // ~1 µs
    {
        __NOP();
    }
}

void TIM1_UP_TIM16_IRQHandler(void) {
    if (__HAL_TIM_GET_FLAG(&htim1, TIM_FLAG_UPDATE) && __HAL_TIM_GET_IT_SOURCE(&htim1, TIM_IT_UPDATE)) {
        __HAL_TIM_CLEAR_IT(&htim1, TIM_IT_UPDATE);

        // PID / логика оси
        XTimerCallback();

        // 1) ВСЁ ВЫКЛ
        HAL_GPIO_WritePin(HBRIDGE_PORT, MOS_HO_L | MOS_HO_R | MOS_LO_L | MOS_LO_R, GPIO_PIN_RESET);

        // 2) dead-time
        HBridgeDeadTime();

        // 3) отключаем Compare
        __HAL_TIM_DISABLE_IT(&htim1, TIM_IT_CC1);

        if (pwm_value == 0) {
            return;  // coast
        }

        uint32_t abs_val = (pwm_value > 0) ? (uint32_t)pwm_value : (uint32_t)(-pwm_value);

        TIM1->CCR1 = abs_val;

        // 4) включаем Compare если не 100%
        if (abs_val < 5000) {
            __HAL_TIM_ENABLE_IT(&htim1, TIM_IT_CC1);
        }

        // 5) включаем ТОЛЬКО одну диагональ
        if (pwm_value > 0) {
            // Forward
            HAL_GPIO_WritePin(HBRIDGE_PORT, MOS_LO_L, GPIO_PIN_SET);
            HAL_GPIO_WritePin(HBRIDGE_PORT, MOS_HO_R, GPIO_PIN_SET);
        } else {
            // Reverse
            HAL_GPIO_WritePin(HBRIDGE_PORT, MOS_LO_R, GPIO_PIN_SET);
            HAL_GPIO_WritePin(HBRIDGE_PORT, MOS_HO_L, GPIO_PIN_SET);
        }
    }
}

void TIM1_CC_IRQHandler(void) {
    if (__HAL_TIM_GET_FLAG(&htim1, TIM_FLAG_CC1) && __HAL_TIM_GET_IT_SOURCE(&htim1, TIM_IT_CC1)) {
        __HAL_TIM_CLEAR_IT(&htim1, TIM_IT_CC1);

        // спад PWM → всё OFF
        HAL_GPIO_WritePin(HBRIDGE_PORT, MOS_HO_L | MOS_HO_R | MOS_LO_L | MOS_LO_R, GPIO_PIN_RESET);
    }
}

/**
 * @brief Callback обработки переполнения таймера
 * @param htim Указатель на обработчик таймера
 * @retval None
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {
    // TIM3 - Интерполяция печати
    if (htim->Instance == TIM3) {
        // SDK вариант: один шаг интерполяции
        if (XInterpTimerCallback() == 0) {
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

// Управление ENABLE пином оси X (в этой распиновке нету)
void XTimerSet(uint16_t period) {}
// Степер оси X (в этой распиновке нету)
void XSetDir(uint8_t dir_pin_state) {}
void XSetEnable(uint8_t enabled) {}
void XSetStep(uint8_t step_pin_state) {}

// Двигатели Y

void YSetEnable(uint8_t enabled) {
    GPIO_PinState st = enabled ? GPIO_PIN_SET : GPIO_PIN_RESET;
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, st);  // Ось Y
}

void YSetDir(uint8_t dir_pin_state) {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, dir_pin_state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void YSetStep(uint8_t step_pin_state) {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, step_pin_state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void YTimerSet(uint16_t period) {
    __HAL_TIM_SET_AUTORELOAD(&htim4, period);
    __HAL_TIM_ENABLE(&htim4);
}

// Установка мощности лазера (TIM2 CH1)
void SetLaserPWM(uint16_t pwm_value) { __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, pwm_value); }

// Установка мощности подсветки (в этой распиновке нету)
void SetLightPWM(uint16_t pwm_value) {}

/**
 * @brief  Настраивает частоту PWM по значению в герцах (универсально для всех STM32).
 * @param  freq_hz  Желаемая частота PWM, Гц (например 1000, 5000, 100000).
 *
 * Функция автоматически вычисляет нужный делитель (PSC) на основе частоты шины таймера.
 * Работает одинаково для разных частот системного тактирования и серий MCU
 * (STM32F0, F1, F2, F3, F4, G0, G4, H7, L0, L1, L4, L5, WB, WL и др.).
 *
 * Учитывает важную особенность тактирования таймеров STM32:
 * - Если прескалер APBx = 1, то частота таймера = частота шины APBx
 * - Если прескалер APBx > 1, то частота таймера = частота шины APBx × 2
 *
 * Пример: если SYSCLK = 72 MHz, APB1 prescaler = /2, freq_hz = 20 kHz, ARR = 99:
 *         PCLK1 = 36 MHz, но TIM_CLK = 72 MHz (удвоение!)
 *         PSC = (72_000_000 / (100 × 20_000)) - 1 = 35
 */
void SetLaserLightPWMFrequency(uint32_t freq_hz) {
    // Получаем базовую частоту шины APB1
    uint32_t pclk1 = HAL_RCC_GetPCLK1Freq();

    // Извлекаем биты прескалера APB1 из регистра конфигурации тактирования
    // Расположение битов PPRE1 зависит от серии MCU
    uint32_t ppre1_bits;

    // STM32F0/F1/F2/F3/F4/G0/G4/L0/L1/L4/L5/WB/WL: биты PPRE1 в RCC->CFGR
    ppre1_bits = (RCC->CFGR & RCC_CFGR_PPRE1) >> RCC_CFGR_PPRE1_Pos;

    // Определяем реальную частоту тактирования таймера
    // Кодировка битов PPRE1[2:0]:
    // 0xx (0-3): нет деления (APB prescaler = 1)    → TIM_CLK = PCLK1
    // 100 (4):   деление на 2 (APB prescaler = 2)   → TIM_CLK = PCLK1 × 2
    // 101 (5):   деление на 4 (APB prescaler = 4)   → TIM_CLK = PCLK1 × 2
    // 110 (6):   деление на 8 (APB prescaler = 8)   → TIM_CLK = PCLK1 × 2
    // 111 (7):   деление на 16 (APB prescaler = 16) → TIM_CLK = PCLK1 × 2
    uint32_t tim_clk;
    if (ppre1_bits >= 4) {
        // APB1 prescaler >= 2: таймер получает удвоенную частоту шины
        tim_clk = pclk1 * 2;
    } else {
        // APB1 prescaler = 1: таймер тактируется напрямую от шины
        tim_clk = pclk1;
    }

    // Устанавливаем значение ARR (Auto-Reload Register) — определяет период счёта.
    // ARR = 99 даёт 100 шагов ШИМ (0-99), что удобно для процентного управления (1% = 1 шаг).
    uint32_t arr = 100 - 1;

    // Вычисляем делитель частоты (Prescaler) по формуле:
    // f_PWM = TIM_CLK / ((PSC + 1) × (ARR + 1))
    // Отсюда: PSC = (TIM_CLK / ((ARR + 1) × f_PWM)) - 1
    uint32_t prescaler = (tim_clk / (arr + 1)) / freq_hz;

    // Защита от выхода за допустимые значения 16-битного регистра PSC (0-65535)
    if (prescaler < 1) prescaler = 1;
    if (prescaler > 65535) prescaler = 65535;

    // Применяем вычисленные параметры к таймеру через макросы HAL
    __HAL_TIM_SET_PRESCALER(&htim2, prescaler - 1);  // PSC (вычитаем 1, т.к. регистр работает как (PSC+1))
    __HAL_TIM_SET_AUTORELOAD(&htim2, arr);           // ARR (период счёта)

    // Генерируем событие обновления (Update Event) для немедленного применения новых значений PSC и ARR.
    // Без этого изменения вступят в силу только после переполнения счётчика.
    htim2.Instance->EGR = TIM_EGR_UG;

    // Сбрасываем счётчик таймера в 0 для стабильного старта с новыми параметрами
    __HAL_TIM_SET_COUNTER(&htim2, 0);
}

// Энкодеры
uint16_t ReadEncoderPins(void) {
    // Читаем состояние пинов энкодера на порту B
    return X_ENCODER_PORT->IDR & (ENCODER_A_PIN | ENCODER_B_PIN);
}

void XInterpTimerStart(uint32_t period) {
    // Старт интерполяционого таймера
    TIM3->ARR = period;          // Установка периода
    TIM3->SR &= ~TIM_SR_UIF;     // Сброс флага прерывания
    TIM3->DIER |= TIM_DIER_UIE;  // Разрешение прерывания
    TIM3->CR1 |= TIM_CR1_CEN;    // Запуск таймера
}

// ============================================================================
// Запуск DMA для копирования блока данных FIFO (вызывается из SDK)
// ============================================================================
void FIFO_DATA_StartDma(uint32_t src_addr, uint32_t dst_addr, uint16_t size) {
    HAL_DMA_Start_IT(&hdma_memtomem_dma1_channel1, src_addr, dst_addr,
                     size  // передаём размер извне
    );
}

/**
 * @brief Callback обработки внешних прерываний (энкодер)
 * @param GPIO_Pin Пин, вызвавший прерывание
 * @retval None
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) { XEncoderCallback(GPIO_Pin); }

/**
 * @brief Callback завершения DMA передачи
 * @param hdma Указатель на структуру DMA
 * @retval None
 */
void XferCpltCallback(DMA_HandleTypeDef* hdma) {
    if (hdma == &hdma_memtomem_dma1_channel1) {
        FIFO_DATA_EndDma();
    }
}

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1) {
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
void assert_failed(uint8_t* file, uint32_t line) {
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
