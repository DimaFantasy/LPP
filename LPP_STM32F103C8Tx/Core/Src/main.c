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

// ============================================================================
// Сигнатура и версия прошивки (APP)
// ============================================================================
const uint32_t APP_KEY0   __attribute__((section(APP_KEY0_SECTION)))   = APP_SIG_KEY0;
const uint32_t APP_KEY1   __attribute__((section(APP_KEY1_SECTION)))   = APP_SIG_KEY1;
const uint32_t APP_KEY2   __attribute__((section(APP_KEY2_SECTION)))   = APP_SIG_KEY2;
const uint32_t APP_KEY3   __attribute__((section(APP_KEY3_SECTION)))   = APP_SIG_KEY3;

const uint32_t APP_VER_F  __attribute__((section(APP_VER_F_SECTION)))  = APP_VERSION;

// Глобальные определения таймеров и режимов
TIM_HandleTypeDef htim1;  
TIM_HandleTypeDef htim2; 

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

/* USER CODE BEGIN PV */

void XferCpltCallback(DMA_HandleTypeDef *hdma);

// ============================================================================
// Внешние объявления
// ============================================================================

extern uint8_t USBD_CUSTOM_HID_SendReport(USBD_HandleTypeDef* pdev, uint8_t* report, uint16_t len);
extern USBD_HandleTypeDef hUsbDeviceFS;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM4_Init(void);
/* USER CODE BEGIN PFP */
static void DMA_M2M_Init();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
static uint8_t enc_b_state = 0;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
	//Приоритет 0: EXTI (Энкодер) — Ловит физический шаг.
	//Приоритет 1: TIM3 (Интерполяция) — Рассчитывает момент внутри шага.
	//Приоритет 2: DMA (PWM Laser) — Тот самый DMA, который «включает порт». Он должен отработать мгновенно, как только интерполятор или таймер дали отшку.
	//Приоритет 3: DMA1_CH1 (M2M Data) — Перекачка данных из буфера. Она может подождать пару тактов, пока лазер выстрелит.
	//Приоритет 4: USB — Связь.
	//Приоритет 5: TIM2, TIM4  (PID) — Моторы Степеры управление.		
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
  MX_USB_DEVICE_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
		DMA_M2M_Init();
		// Инициализация 
		Lpp_Init();		

    // Запуск таймеров
    HAL_TIM_Base_Start_IT(&htim4);

		// Инициализация USB
		#if defined(STM32F401xE) || defined(STM32F401xC) || \
				defined(STM32F411xE)
				// F401, F411: используют OTG_FS_GCCFG для управления PHY и pull-up
				USB_OTG_FS->GCCFG &= ~USB_OTG_GCCFG_PWRDWN;  // Отключаем PHY (и pull-up)
				HAL_Delay(10);
		#elif defined(STM32G431xx)
				// G431: использует регистр BCDR
				USB->BCDR &= ~USB_BCDR_DPPU;
				HAL_Delay(10);
		#endif

				// Выключаем питание USB
				F_RESET_PIN(&g_pins[SYS_PIN_USB_EN]);
				HAL_Delay(2000);  // достаточная задержка
				
				// Включаем питание USB
				F_SET_PIN(&g_pins[SYS_PIN_USB_EN]);
				HAL_Delay(50);   // стабилизация

		#if defined(STM32F401xE) || defined(STM32F401xC) || \
				defined(STM32F411xE)
				// F401, F411: включаем PHY (и pull-up)
				USB_OTG_FS->GCCFG |= USB_OTG_GCCFG_PWRDWN;
		#elif defined(STM32G431xx)
				// G431: включаем pull-up
				USB->BCDR |= USB_BCDR_DPPU;
		#endif
			
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
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /* USER CODE BEGIN MX_GPIO_Init_2 */
  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/**
 ******************************************************************************
 * @file    lpp_sdk_f103.c
 * @brief   Реализация аппаратного уровня LPP для STM32F103 (Blue Pill)
 ******************************************************************************
 */

// Глобальные переменные SDK
volatile uint32_t dma_pwm_masks[3][2] = {0}; // [Laser, LED1, LED2][SET, RESET]
uint32_t raw_pin_masks[3] = {0};             // Маски пинов (1 << N)
uint32_t LAST_LASER_FREQ = 0;
volatile int32_t X_PWM_CURRENT = 0;

// ============================================================================
// СЕКЦИЯ: СВЯЗЬ (USB HID)
// ============================================================================

/**
 * @brief Отправка 64-байтного пакета хосту
 */
uint8_t PacketSend(uint8_t* buffer) {
    // На F103 используется стандартная функция HID-класса
    return USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, buffer, 64);	
}

// ============================================================================
// СЕКЦИЯ: МОТОР ОСИ X (TIM2) — STM32F103 @ 72МГц
// ============================================================================

// Активировать ШИМ-пин (PIN_X_MO_L) с учётом полярности
// W_X_POL_PWM = 0: стоп=LOW,  активен=HIGH
// W_X_POL_PWM = 1: стоп=HIGH, активен=LOW  (BLDC с инвертированным входом)
__STATIC_INLINE void X_PWM_SET(void) {
    if (W_X_POL_PWM == 0) F_SET_PIN(&g_pins[PIN_X_MO_L]);
    else                   F_RESET_PIN(&g_pins[PIN_X_MO_L]);
}

// Деактивировать ШИМ-пин (PIN_X_MO_L) с учётом полярности
__STATIC_INLINE void X_PWM_CLR(void) {
    if (W_X_POL_PWM == 0) F_RESET_PIN(&g_pins[PIN_X_MO_L]);
    else                   F_SET_PIN(&g_pins[PIN_X_MO_L]);
}

// Активировать DIR-пин (PIN_X_MO_R) с учётом полярности
// W_X_POL_DIR = 0: прямая полярность
// W_X_POL_DIR = 1: инвертированная полярность
// Используется только в режиме ONE_PWM
__STATIC_INLINE void X_DIR_SET(void) {
    if (W_X_POL_DIR == 0) F_SET_PIN(&g_pins[PIN_X_MO_R]);
    else                   F_RESET_PIN(&g_pins[PIN_X_MO_R]);
}

// Деактивировать DIR-пин (PIN_X_MO_R) с учётом полярности
__STATIC_INLINE void X_DIR_CLR(void) {
    if (W_X_POL_DIR == 0) F_RESET_PIN(&g_pins[PIN_X_MO_R]);
    else                   F_SET_PIN(&g_pins[PIN_X_MO_R]);
}

void XMotorInit(X_MOTOR_MODE_T mode) {
    if (X_MOTOR_MODE == mode) return;

    HAL_NVIC_DisableIRQ(TIM2_IRQn);
    HAL_NVIC_ClearPendingIRQ(TIM2_IRQn);

    __HAL_RCC_TIM2_FORCE_RESET();
    __HAL_RCC_TIM2_RELEASE_RESET();
    __HAL_RCC_TIM2_CLK_ENABLE();

    TIM2->CR1  = 0;
    TIM2->CR2  = 0;
    TIM2->DIER = 0;
    TIM2->SR   = 0;
    TIM2->CCER = 0;
    X_PWM_CURRENT = 0;

    htim2.Instance               = TIM2;
    htim2.Init.CounterMode       = TIM_COUNTERMODE_UP;
    htim2.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;

    if (mode == X_MOTOR_MODE_STEP) {
        // 72МГц / 72 = 1МГц → 1 тик = 1 мкс
        htim2.Init.Prescaler = 71;
        htim2.Init.Period    = 10000;

        HAL_TIM_OnePulse_Init(&htim2, TIM_OPMODE_SINGLE);

        // Порядок важен: сначала EGR сброс, потом UIE
        TIM2->DIER = 0;
        TIM2->EGR |= TIM_EGR_UG;   // применить Prescaler в железо
        TIM2->SR   = 0;             // сбросить UIF от EGR
        TIM2->DIER |= TIM_DIER_UIE;

        HAL_NVIC_SetPriority(TIM2_IRQn, 5, 0);
        HAL_NVIC_EnableIRQ(TIM2_IRQn);

        // Тестовый толчок
        TIM2->ARR  = 100;           // 100 мкс
        TIM2->CNT  = 0;
        TIM2->SR   = 0;
        TIM2->CR1 |= TIM_CR1_CEN;
    }
    else {
        // 72МГц / 14 ≈ 5.14МГц, период 5001 тик ≈ ~1кГц ШИМ
        htim2.Init.Prescaler = 13;
        htim2.Init.Period    = 5001;
        HAL_TIM_Base_Init(&htim2);

        TIM2->CR1 &= ~TIM_CR1_OPM; // Непрерывный режим

        TIM_OC_InitTypeDef sConfigOC = {0};
        sConfigOC.OCMode = TIM_OCMODE_TIMING;
        sConfigOC.Pulse  = 2500;
        HAL_TIM_OC_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1);

        TIM2->CR1   |= TIM_CR1_ARPE;
        TIM2->CCMR1 |= TIM_CCMR1_OC1PE;

        // Порядок важен: сначала EGR сброс, потом прерывания
        TIM2->DIER = 0;
        TIM2->EGR |= TIM_EGR_UG;
        TIM2->SR   = 0;
        TIM2->DIER |= TIM_DIER_UIE | TIM_DIER_CC1IE;

        HAL_NVIC_SetPriority(TIM2_IRQn, 5, 0);
        HAL_NVIC_EnableIRQ(TIM2_IRQn);

        TIM2->CR1 |= TIM_CR1_CEN;
    }

    X_MOTOR_MODE = mode;
}

/**
 * @brief Программная задержка dead-time между переключением ключей моста
 * ~0.7 мкс при 72МГц. Подобрать осциллографом!
 */
__STATIC_INLINE void XMotorDeadTime(void) {
    for (volatile int i = 0; i < 50; i++) { __NOP(); }
}

void TIM2_IRQHandler(void) {
    uint32_t sr = TIM2->SR;

    // --- НАЧАЛО ПЕРИОДА (Update Event) ---
    if (sr & TIM_SR_UIF) {
        TIM2->SR = ~TIM_SR_UIF;

        // Вызов планировщика шагов (для STEP режима)
        XTimerCallback();

        if (X_MOTOR_MODE != X_MOTOR_MODE_STEP) {
            // Безопасный сброс всех ключей в начале периода
            F_RESET_PIN(&g_pins[PIN_X_MO_L]);
            F_RESET_PIN(&g_pins[PIN_X_MO_R]);
            F_RESET_PIN(&g_pins[PIN_X_MO_L_H]);
            F_RESET_PIN(&g_pins[PIN_X_MO_R_H]);

            if (X_PWM_CURRENT != 0) {
                // Пауза перед открытием ключей (защита от сквозного тока)
                XMotorDeadTime();

                if (X_MOTOR_MODE == X_MOTOR_MODE_TWO_PWM) {
                    // TWO_PWM: два пина шимят, W_X_POL_PWM меняет диагонали моста
                    uint32_t abs_pwr = (uint32_t)abs(X_PWM_CURRENT);
                    if (abs_pwr > 5000) abs_pwr = 5000;
                    TIM2->CCR1 = abs_pwr;

                    // Направление с учётом полярности
                    uint8_t fwd = (X_PWM_CURRENT > 0) ? 1 : 0;
                    if (W_X_POL_PWM) fwd = !fwd;

                    if (fwd) {
                        F_SET_PIN(&g_pins[PIN_X_MO_L]);
                        F_SET_PIN(&g_pins[PIN_X_MO_R_H]);
                    } else {
                        F_SET_PIN(&g_pins[PIN_X_MO_R]);
                        F_SET_PIN(&g_pins[PIN_X_MO_L_H]);
                    }
                }
                else if (X_MOTOR_MODE == X_MOTOR_MODE_ONE_PWM) {
                    // ONE_PWM: один пин ШИМ (L), второй DIR (R)
                    // CCR1 всегда положительный — полярность через пины
                    uint32_t abs_pwr = (uint32_t)abs(X_PWM_CURRENT);
                    if (abs_pwr > 5000) abs_pwr = 5000;
                    TIM2->CCR1 = abs_pwr;

                    // DIR выставляем до ШИМ
                    uint8_t dir = (X_PWM_CURRENT >= 0) ? 0 : 1;
                    if (dir) X_DIR_SET();
                    else     X_DIR_CLR();

                    // ШИМ активен (с учётом полярности через функцию)
                    X_PWM_SET();
                }
            }
        }
    }

    // --- КОНЕЦ ИМПУЛЬСА (Compare Event) ---
    // Срабатывает когда CNT достигает CCR1
    if (sr & TIM_SR_CC1IF) {
        TIM2->SR = ~TIM_SR_CC1IF;

        if (X_MOTOR_MODE == X_MOTOR_MODE_TWO_PWM) {
            // Гасим все ключи в середине периода
            F_RESET_PIN(&g_pins[PIN_X_MO_L]);
            F_RESET_PIN(&g_pins[PIN_X_MO_R]);
            F_RESET_PIN(&g_pins[PIN_X_MO_L_H]);
            F_RESET_PIN(&g_pins[PIN_X_MO_R_H]);
        }
        else if (X_MOTOR_MODE == X_MOTOR_MODE_ONE_PWM) {
            // Конец ШИМ-импульса — только ШИМ пин, DIR держится весь период
            X_PWM_CLR();
        }
    }
}

/**
 * @brief Установка длительности шага (только для STEP режима)
 * @param period: длительность в мкс (при PSC=71, 1 тик = 1 мкс)
 */
void XTimerSet(uint16_t period) {
    if (X_MOTOR_MODE == X_MOTOR_MODE_STEP) {
        TIM2->ARR  = period;
        TIM2->CNT  = 0;
        TIM2->SR   = 0;             // сброс UIF перед стартом
        TIM2->CR1 |= TIM_CR1_CEN;  // старт одного импульса (OPM)
    }
}

/**
 * @brief Установка мощности мотора X
 * @param power: -5000..+5000 (0 = стоп)
 */
void XMotorSet(int power) {
    if (X_MOTOR_MODE == X_MOTOR_MODE_STEP) return;

    if (abs(power) < 10) power = 0;

    X_PWM_CURRENT = power;

    if (power == 0) {
        TIM2->CCR1 = 0;
        // Все ключи выключить
        F_RESET_PIN(&g_pins[PIN_X_MO_L_H]);
        F_RESET_PIN(&g_pins[PIN_X_MO_R_H]);
        X_DIR_CLR();    // DIR в неактивное состояние
        X_PWM_CLR();    // ШИМ в неактивное состояние (HIGH если инвертированный)
    } else {
        if (power >  5000) power =  5000;
        if (power < -5000) power = -5000;
        TIM2->CCR1 = (uint32_t)abs(power);
    }
}

// ============================================================================
// СЕКЦИЯ: ЛАЗЕР И ПОДСВЕТКА (TIM1 + DMA1)
// ============================================================================

// ============================================================================
// Принцип работы:
// 1. LASER: Включение по TIM1_UP (0), выключение по CCR1 (val).
// 2. LED1/LED2: "Инверсная" логика для общего сброса.
//    - Включение: Каждому свой CCR (CCR4 для LED1, CCR3 для LED2).
//    - Точка включения = (100 - val). Чем больше яркость, тем раньше старт.
//    - Выключение: ОБЩЕЕ по CCR2 (всегда 100) через один канал DMA.
//
// Ограничения:
// - LASER: Любой порт, любой пин.
// - LED1 & LED2: Обязательно на одном GPIO порту (используют общий BSRR).
// ============================================================================

// F103 маппинг TIM1 → DMA1 (жёстко в железе, не меняется):
void PWM_LaserLight_LinkHardware(void) {
    PIN_CFG_T *laser = &g_pins[PIN_PWM_LASER];
    PIN_CFG_T *led1  = &g_pins[PIN_PWM_LED1];
    PIN_CFG_T *led2  = &g_pins[PIN_PWM_LED2];

    // Останавливаем все каналы DMA перед перенастройкой
    DMA1_Channel5->CCR &= ~DMA_CCR_EN; // Laser ON
    DMA1_Channel2->CCR &= ~DMA_CCR_EN; // Laser OFF
    DMA1_Channel4->CCR &= ~DMA_CCR_EN; // LED1 ON
    DMA1_Channel3->CCR &= ~DMA_CCR_EN; // Common LED OFF (CH2)
    DMA1_Channel6->CCR &= ~DMA_CCR_EN; // LED2 ON
	
		// Перед перенастройкой сбрасывай текущие пины.
		if (laser->used) F_RESET_PIN(laser);
		if (led1->used)  F_RESET_PIN(led1);
		if (led2->used)  F_RESET_PIN(led2);	

    // Сброс флагов
    DMA1->IFCR = DMA_IFCR_CGIF2 | DMA_IFCR_CGIF3 | DMA_IFCR_CGIF4 |
                 DMA_IFCR_CGIF5 | DMA_IFCR_CGIF6;

    uint32_t ccr_base = DMA_CCR_DIR | DMA_CCR_CIRC | DMA_CCR_MSIZE_1 | 
                        DMA_CCR_PSIZE_1 | DMA_CCR_PL_Msk;

    // ----------------------------------------------------------------
    // ЛАЗЕР (Любой порт/пин)
    // ----------------------------------------------------------------
    if (laser->used && laser->bsrr != &GPIO_NULL_REG) {
        raw_pin_masks[0] = laser->pin;
        DMA1_Channel5->CPAR  = (uint32_t)laser->bsrr;
        DMA1_Channel5->CMAR  = (uint32_t)&dma_pwm_masks[0][0];
        DMA1_Channel5->CNDTR = 1;
        DMA1_Channel5->CCR   = ccr_base | DMA_CCR_EN;

        DMA1_Channel2->CPAR  = (uint32_t)laser->bsrr;
        DMA1_Channel2->CMAR  = (uint32_t)&dma_pwm_masks[0][1];
        DMA1_Channel2->CNDTR = 1;
        DMA1_Channel2->CCR   = ccr_base | DMA_CCR_EN;
    }

    // ----------------------------------------------------------------
    // ПОДСВЕТКА (LED1 и LED2)
    // ----------------------------------------------------------------
    
    // Проверка совместимости портов
    bool led1_active = (led1->used && led1->bsrr != &GPIO_NULL_REG);
    bool led2_active = (led2->used && led2->bsrr != &GPIO_NULL_REG);
    
    // Если оба активны, но порты РАЗНЫЕ — блокируем инициализацию подсветки
    if (led1_active && led2_active && (led1->bsrr != led2->bsrr)) {
        return; // Защита: порты не совпадают, ШИМ через общий сброс невозможен
    }

    // Настройка LED1
    if (led1_active) {
        raw_pin_masks[1] = led1->pin;
        // ON: TIM1_CH4
        DMA1_Channel4->CPAR  = (uint32_t)led1->bsrr;
        DMA1_Channel4->CMAR  = (uint32_t)&dma_pwm_masks[1][0];
        DMA1_Channel4->CNDTR = 1;
        DMA1_Channel4->CCR   = ccr_base | DMA_CCR_EN;

        // OFF: TIM1_CH2 (Общий канал выключения)
        DMA1_Channel3->CPAR  = (uint32_t)led1->bsrr;
        DMA1_Channel3->CMAR  = (uint32_t)&dma_pwm_masks[1][1];
        DMA1_Channel3->CNDTR = 1;
        DMA1_Channel3->CCR   = ccr_base | DMA_CCR_EN;
    }

    // Настройка LED2
    if (led2_active) {
        raw_pin_masks[2] = led2->pin;
        // ON: TIM1_CH3
        DMA1_Channel6->CPAR  = (uint32_t)led2->bsrr;
        DMA1_Channel6->CMAR  = (uint32_t)&dma_pwm_masks[2][0];
        DMA1_Channel6->CNDTR = 1;
        DMA1_Channel6->CCR   = ccr_base | DMA_CCR_EN;

        // Если LED1 не используется, настраиваем канал OFF на порт LED2
        if (!led1_active) {
            DMA1_Channel3->CPAR  = (uint32_t)led2->bsrr;
            DMA1_Channel3->CMAR  = (uint32_t)&dma_pwm_masks[1][1];
            DMA1_Channel3->CNDTR = 1;
            DMA1_Channel3->CCR   = ccr_base | DMA_CCR_EN;
        }
    }
}

void SetLaserLightPWMFrequency(uint32_t freq_hz) {
    if (freq_hz == LAST_LASER_FREQ && freq_hz != 0) return;

    if (freq_hz == 0) {
        TIM1->CR1 &= ~TIM_CR1_CEN;
        LAST_LASER_FREQ = 0;
        return;
    }

    __HAL_RCC_TIM1_CLK_ENABLE();
    __HAL_RCC_DMA1_CLK_ENABLE();

		uint32_t arr = 100; // Наш диапазон 0-100%
    uint32_t psc_val = 72000000 / (freq_hz * (arr + 1));

    
    TIM1->CR1  &= ~TIM_CR1_CEN; 
    TIM1->PSC   = (psc_val > 0) ? psc_val - 1 : 0;
    TIM1->ARR   = arr;
    
    // Начальные безопасные значения:
    TIM1->CCR1  = 0;   // Laser OFF (управляется в SetLaserPWM)
    TIM1->CCR2  = 100; // Точка ОБЩЕГО СБРОСА для LED1 и LED2 (всегда конец периода)
    TIM1->CCR3  = 100; // Точка включения LED2 (по умолчанию 100 = выключен)
    TIM1->CCR4  = 100; // Точка включения LED1 (по умолчанию 100 = выключен)
		
    // DMA запросы от таймера
    TIM1->DIER = TIM_DIER_UDE    |  // Update  → Ch5 (Laser ON)
                 TIM_DIER_CC1DE  |  // CCR1    → Ch2 (Laser OFF)
                 TIM_DIER_CC2DE  |  // CCR2    → Ch3 (LED1 OFF + LED2 OFF)
                 TIM_DIER_CC3DE  |  // CCR3    → Ch6 (LED2 ON)
                 TIM_DIER_CC4DE;    // CCR4    → Ch4 (LED1 ON)
								 
		PWM_LaserLight_LinkHardware(); 								 

		TIM1->BDTR |= TIM_BDTR_MOE;// Управляет физическими ногами но на всякий бусть будет
    TIM1->EGR  |= TIM_EGR_UG;  // генерируем событие (PSC/ARR защёлкиваются)
    TIM1->SR    = 0;           // сбрасываем флаги ПОСЛЕ UG, иначе смысла нет
    TIM1->CR1  |= TIM_CR1_CEN; // только потом запускаем

    LAST_LASER_FREQ = freq_hz;
}

// ============================================================================
// Управление мощностью
// ============================================================================

void Laser_Off(void) {
    LASER_SAFETY_LOCK = 1;
    HAL_TIM_Base_Stop_IT(&htim3);
    SetLaserPWM(0);
    TIM1->EGR |= TIM_EGR_UG;
    F_RESET_PIN(&g_pins[PIN_PWM_LASER]);
}

void Laser_Ready(void) {
    TIM3->CNT = 0;
    TIM1->CNT = 0;
    TIM1->EGR |= TIM_EGR_UG;
    LASER_SAFETY_LOCK = 0;
}

inline void SetLaserPWM(uint16_t val) {
    if (LASER_SAFETY_LOCK) val = 0;
    if (val > 100) val = 100;

    dma_pwm_masks[0][0] = (val > 0)   ? raw_pin_masks[0]        : 0; // SET
    dma_pwm_masks[0][1] = (val < 100) ? (raw_pin_masks[0] << 16): 0; // RESET

    TIM1->CCR1 = val;
    if (val == 0) F_RESET_PIN(&g_pins[PIN_PWM_LASER]);
}

inline void SetLight1PWM(uint16_t val) {
    if (val > 100) val = 100;
    
    // 1. Устанавливаем точку включения. 
    // Для 100% ставим 1, чтобы не мешать Laser ON в 0-м такте.
    TIM1->CCR4 = (val < 100) ? (100 - val) : 1; 

    // 2. Маска включения (SET)
    dma_pwm_masks[1][0] = (val > 0) ? raw_pin_masks[1] : 0;

    // 3. Маска выключения (RESET) в общем канале (DMA1_Ch3)
    // Для себя: сбрасываем, только если яркость ниже 100%
    uint32_t r1 = (val < 100) ? (raw_pin_masks[1] << 16) : 0;
    
    // Для соседа: сбрасываем, если его CCR3 > 1 (значит его яркость < 100%)
    uint32_t r2 = (TIM1->CCR3 > 1 && raw_pin_masks[2]) ? (raw_pin_masks[2] << 16) : 0;
    
    dma_pwm_masks[1][1] = r1 | r2;

    // Если 0 — гарантированно тушим пин
    if (val == 0) F_RESET_PIN(&g_pins[PIN_PWM_LED1]);
}

inline void SetLight2PWM(uint16_t val) {
    if (val > 100) val = 100;

    // 1. Точка включения
    TIM1->CCR3 = (val < 100) ? (100 - val) : 1; 

    // 2. Маска включения (SET)
    dma_pwm_masks[2][0] = (val > 0) ? raw_pin_masks[2] : 0;

    // 3. Общая маска выключения (RESET)
    // Для соседа (LED1): смотрим на его CCR4
    uint32_t r1 = (TIM1->CCR4 > 1 && raw_pin_masks[1]) ? (raw_pin_masks[1] << 16) : 0;
    
    // Для себя: смотрим на свой val
    uint32_t r2 = (val < 100) ? (raw_pin_masks[2] << 16) : 0;
    
    dma_pwm_masks[1][1] = r1 | r2;

    if (val == 0) F_RESET_PIN(&g_pins[PIN_PWM_LED2]);
}

// ============================================================================
// СЕКЦИЯ: DMA M2M (Копирование пакетов)
// ============================================================================

void DMA_M2M_Init(void) {
    __HAL_RCC_DMA1_CLK_ENABLE();
}

void FIFO_DATA_StartDma(uint32_t src, uint32_t dst, uint16_t count) {
    DMA1_Channel1->CCR &= ~DMA_CCR_EN;
    DMA1->IFCR = DMA_IFCR_CGIF1; // Сброс флагов
    
    DMA1_Channel1->CPAR = src;
    DMA1_Channel1->CMAR = dst;
    DMA1_Channel1->CNDTR = count;
    
    // M2M, Low Priority, 8-bit, MINC, PINC, TCIE
    DMA1_Channel1->CCR = DMA_CCR_MEM2MEM | DMA_CCR_MINC | DMA_CCR_PINC | 
                         DMA_CCR_TCIE | DMA_CCR_TEIE;
    
    HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
    DMA1_Channel1->CCR |= DMA_CCR_EN;
}

void DMA1_Channel1_IRQHandler(void) {
    if (DMA1->ISR & DMA_ISR_TCIF1) {
        DMA1->IFCR = DMA_IFCR_CTCIF1;
        FIFO_DATA_EndDma(); // Callback готовности данных
    }
}

// ============================================================================
// СЕКЦИЯ: ИНТЕРПОЛЯЦИЯ И Y-ОСЬ
// ============================================================================

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {
    if (htim->Instance == TIM3) {
        if (XInterpTimerCallback() == 0) {
            HAL_TIM_Base_Stop_IT(&htim3);
            TIM3->CNT = 0;
        }
    }
    if (htim->Instance == TIM4) {
        YTimerCallback();
    }
}

void YTimerSet(uint16_t period) {
    __HAL_TIM_SET_AUTORELOAD(&htim4, period);
    __HAL_TIM_ENABLE(&htim4);
}

void XInterpTimerStart(uint32_t period) {
    TIM3->ARR = period;
    TIM3->SR &= ~TIM_SR_UIF;
    TIM3->DIER |= TIM_DIER_UIE;
    TIM3->CR1 |= TIM_CR1_CEN;
}

// ============================================================================
// ОБРАБОТЧИКИ ПРЕРЫВАНИЙ EXTI (Энкодер)
// ============================================================================

void LPP_GPIO_EXTI_Handler(uint16_t pin_mask) {
    XEncoderCallback(pin_mask); 
}

void EXTI0_IRQHandler(void) { __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_0); LPP_GPIO_EXTI_Handler(GPIO_PIN_0); }
void EXTI1_IRQHandler(void) { __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_1); LPP_GPIO_EXTI_Handler(GPIO_PIN_1); }
void EXTI2_IRQHandler(void) { __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_2); LPP_GPIO_EXTI_Handler(GPIO_PIN_2); }
void EXTI3_IRQHandler(void) { __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_3); LPP_GPIO_EXTI_Handler(GPIO_PIN_3); }
void EXTI4_IRQHandler(void) { __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_4); LPP_GPIO_EXTI_Handler(GPIO_PIN_4); }
void EXTI9_5_IRQHandler(void) {
    uint32_t pin = EXTI->PR & 0x03E0;
    EXTI->PR = pin; LPP_GPIO_EXTI_Handler(pin);
}
void EXTI15_10_IRQHandler(void) {
    uint32_t pin = EXTI->PR & 0xFC00;
    EXTI->PR = pin; LPP_GPIO_EXTI_Handler(pin);
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
////////////////////////////////////////////////////////////////    __disable_irq();
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
