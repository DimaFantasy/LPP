/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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

#include "stm32g4xx_ll_dmamux.h" // Обязательно для LL_DMAMUX_SetRequestID
#include "stm32g4xx_ll_dma.h"    // Для приоритетов DMA

// Заглушка для пустых пинов
static volatile uint32_t GPIO_NULL_REG = 0;

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
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

/* USER CODE BEGIN PV */

// ============================================================================
// Сигнатура и версия прошивки (APP)
// ============================================================================
const uint32_t APP_KEY0 __attribute__((section(APP_KEY0_SECTION))) = APP_SIG_KEY0;
const uint32_t APP_KEY1 __attribute__((section(APP_KEY1_SECTION))) = APP_SIG_KEY1;
const uint32_t APP_KEY2 __attribute__((section(APP_KEY2_SECTION))) = APP_SIG_KEY2;
const uint32_t APP_KEY3 __attribute__((section(APP_KEY3_SECTION))) = APP_SIG_KEY3;

const uint32_t APP_VER_F __attribute__((section(APP_VER_F_SECTION))) = APP_VERSION;

// Глобальные определения таймеров и режимов
TIM_HandleTypeDef htim1;  
TIM_HandleTypeDef htim2; 
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM4_Init(void);
/* USER CODE BEGIN PFP */

void DMA_M2M_Init();

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
	// 16 уровней вытеснения (без субприоритетов) для гарантии жесткого Real-time	
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USB_Device_Init();
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
  while (1)
  {
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

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
  RCC_OscInitStruct.PLL.PLLN = 42;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
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
  htim3.Init.Prescaler = 168;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 65535;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
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
  htim4.Init.Prescaler = 168;
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
  __HAL_RCC_SYSCFG_CLK_ENABLE();  // КРИТИЧНО: включает мультиплексор прерываний EXTI
  __HAL_RCC_PWR_CLK_ENABLE();     // Тактирование модуля питания (для G4)
  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

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
// СЕКЦИЯ: МОТОР ОСИ X
// ============================================================================

volatile int32_t X_PWM_CURRENT = 0;

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

    htim2.Instance               = TIM2;
    htim2.Init.CounterMode       = TIM_COUNTERMODE_UP;
    htim2.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.RepetitionCounter = 0;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

    if (mode == X_MOTOR_MODE_STEP) {
        // 170МГц / 170 = 1МГц → 1 тик = 1 мкс
        htim2.Init.Prescaler = 169;
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
        if (mode == X_MOTOR_MODE_ONE_PWM) {
            htim2.Init.Prescaler = 18;
            htim2.Init.Period    = 4940;
        } else { // TWO_PWM
            htim2.Init.Prescaler = 9;
            htim2.Init.Period    = 9880;
        }

        HAL_TIM_Base_Init(&htim2);

        TIM2->CR1 &= ~TIM_CR1_OPM; // Непрерывный режим

        TIM_OC_InitTypeDef sConfigOC = {0};
        sConfigOC.OCMode = TIM_OCMODE_TIMING;
        HAL_TIM_OC_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1);

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
 * ~1 мкс при 170МГц. Подобрать осциллографом!
 */
__STATIC_INLINE void XMotorDeadTime(void) {
    for (volatile int i = 0; i < 100; i++) { __NOP(); }
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

                    // ШИМ активен (с учётом полярности через макрос)
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
 * @param period: длительность в мкс (при PSC=169, 1 тик = 1 мкс)
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
// ПОДСИСТЕМА PWM LASER & LIGHT (DMA-BASED)
// ============================================================================

// Глобальные переменные для работы DMA лазер
volatile uint32_t dma_pwm_masks[3][2] = {0}; // [Laser, LED1, LED2][SET, RESET]
uint32_t raw_pin_masks[3] = {0};             // Маски пинов (1 << N)
uint32_t LAST_LASER_FREQ = 0;                // Для защиты от повторной инициализации

/**
 * @brief Привязка физических портов к каналам DMA.
 */
void PWM_LaserLight_LinkHardware(void) {
    uint8_t target_ids[3] = { PIN_PWM_LASER, PIN_PWM_LED1, PIN_PWM_LED2 };

    for (int i = 0; i < 3; i++) {
        PIN_CFG_T *cfg = &g_pins[target_ids[i]];
        
        // Канал ON:  1, 2, 3 (соответствуют i = 0, 1, 2)
        // Канал OFF: 4, 5, 6 (соответствуют i+3)
        DMA_Channel_TypeDef* ch_on  = (DMA_Channel_TypeDef*)((uint32_t)DMA1_Channel1 + (i * 0x14));
        DMA_Channel_TypeDef* ch_off = (DMA_Channel_TypeDef*)((uint32_t)DMA1_Channel1 + ((i + 3) * 0x14));

        if (!cfg->used || cfg->bsrr == (uint32_t*)&GPIO_NULL_REG) {
            ch_on->CCR &= ~DMA_CCR_EN;
            ch_off->CCR &= ~DMA_CCR_EN;
            continue;
        }

        raw_pin_masks[i] = cfg->pin;

        // Настройка ON
        ch_on->CCR &= ~DMA_CCR_EN;
        ch_on->CPAR = (uint32_t)cfg->bsrr;
        ch_on->CMAR = (uint32_t)&dma_pwm_masks[i][0];
        ch_on->CCR |= DMA_CCR_EN;

        // Настройка OFF
        ch_off->CCR &= ~DMA_CCR_EN;
        ch_off->CPAR = (uint32_t)cfg->bsrr;
        ch_off->CMAR = (uint32_t)&dma_pwm_masks[i][1];
        ch_off->CCR |= DMA_CCR_EN;
    }
}

/**
 * @brief Инициализация таймера и DMA для лазера
 */
void SetLaserLightPWMFrequency(uint32_t freq_hz) {
    if (freq_hz == LAST_LASER_FREQ && freq_hz != 0) return;
    
    if (freq_hz == 0) { 
        TIM1->CR1 &= ~TIM_CR1_CEN; 
        LAST_LASER_FREQ = 0; 
        return; 
    }

    // 1. Включение тактирования
    __HAL_RCC_TIM1_CLK_ENABLE();
    __HAL_RCC_DMA1_CLK_ENABLE();
    __HAL_RCC_DMAMUX1_CLK_ENABLE();

    // 2. ИСПРАВЛЕННЫЙ РАСЧЕТ ЧАСТОТЫ ТАЙМЕРА (TIM1 на APB2)
    uint32_t pclk2 = HAL_RCC_GetPCLK2Freq();
    uint32_t tim_clk = pclk2;

    // Если делитель APB2 не 1, частота таймера удваивается автоматически
    if ((RCC->CFGR & RCC_CFGR_PPRE2) != RCC_CFGR_PPRE2_DIV1) {
        tim_clk = pclk2 * 2;
    }

    uint32_t arr = 100;
    // PSC = (F_clk / (F_target * (ARR + 1)))
    uint32_t psc_val = tim_clk / (freq_hz * (arr + 1));
    
    TIM1->PSC = (psc_val > 0) ? psc_val - 1 : 0;
    TIM1->ARR = arr;
    
    // Остальной код без изменений
    TIM1->CCMR1 = 0; 
    TIM1->CCMR2 = 0;
    TIM1->DIER = TIM_DIER_UDE | TIM_DIER_CC1DE | TIM_DIER_CC2DE | TIM_DIER_CC3DE;

		// 3. Настройка каналов DMA (1-6). 
		for (int i = 0; i < 6; i++) {
				uint8_t ch_num = i + 1; // Теперь: 1, 2, 3, 4, 5, 6
				
				uint32_t req;
				// Логика запросов DMAMUX (TIM1 UP для включения, CHx для выключения)
				if (i < 3)       req = LL_DMAMUX_REQ_TIM1_UP;
				else if (i == 3) req = LL_DMAMUX_REQ_TIM1_CH1;
				else if (i == 4) req = LL_DMAMUX_REQ_TIM1_CH2;
				else             req = LL_DMAMUX_REQ_TIM1_CH3;

				// Настройка DMAMUX (каналы мукса 0..5 соответствуют DMA каналам 1..6)
				LL_DMAMUX_SetRequestID(DMAMUX1, ch_num - 1, req); 

				// Расчет адреса канала (смещение 0x14 на каждый канал)
				DMA_Channel_TypeDef* DMA_Ch = (DMA_Channel_TypeDef*)((uint32_t)DMA1_Channel1 + ((ch_num - 1) * 0x14));
				
				DMA_Ch->CCR &= ~DMA_CCR_EN;
				DMA1->IFCR = (0x0F << ((ch_num - 1) * 4)); // Сброс флагов

				DMA_Ch->CCR = DMA_CCR_DIR | DMA_CCR_CIRC | DMA_CCR_MINC | 
											(0x02 << DMA_CCR_PSIZE_Pos) | (0x02 << DMA_CCR_MSIZE_Pos) | 
											LL_DMA_PRIORITY_VERYHIGH; // Максимальный приоритет для лазера
				
				DMA_Ch->CNDTR = 1;

				// Приоритеты прерываний (хотя для лазера они почти не нужны в CIRC режиме)
				IRQn_Type irq = (IRQn_Type)(DMA1_Channel1_IRQn + (ch_num - 1));
				HAL_NVIC_SetPriority(irq, 2, 0); 
				HAL_NVIC_EnableIRQ(irq);
		}

    for(int i=0; i<3; i++) { 
        dma_pwm_masks[i][0] = 0; 
        dma_pwm_masks[i][1] = 0; 
    }

    PWM_LaserLight_LinkHardware();

    TIM1->BDTR |= TIM_BDTR_MOE; 
    TIM1->SR = 0;               
    TIM1->EGR |= TIM_EGR_UG;    
    TIM1->CR1 |= TIM_CR1_CEN;   
    
    LAST_LASER_FREQ = freq_hz;
}

/**
 * @brief Сверхбыстрое управление мощностью лазера (Branchless)
 */
void Laser_Off(void) {
    LASER_SAFETY_LOCK = 1;
    HAL_TIM_Base_Stop_IT(&htim3); 
    SetLaserPWM(0);
    TIM1->EGR |= TIM_EGR_UG;      // Мгновенная очистка регистров
    F_RESET_PIN(&g_pins[PIN_PWM_LASER]); // Физическая гарантия нуля
}

void Laser_Ready(void) {
    TIM3->CNT = 0;                // Обнуляем интерполяцию
    interp_counter = 0; 
    TIM1->CNT = 0;                // Фазируем ШИМ
    TIM1->EGR |= TIM_EGR_UG;      // Пропихиваем нули    
    LASER_SAFETY_LOCK = 0;        // Разрешаем работу
}


inline void SetLaserPWM(uint16_t val) {
    // Если включена блокировка, любое значение превращается в 0
    if (LASER_SAFETY_LOCK) val = 0;

    dma_pwm_masks[0][0] = (uint32_t)(val != 0) * raw_pin_masks[0];
    dma_pwm_masks[0][1] = (uint32_t)(val < 100) * (raw_pin_masks[0] << 16);
    TIM1->CCR1 = val;

    if (val == 0) {
        F_RESET_PIN(&g_pins[PIN_PWM_LASER]);
        dma_pwm_masks[0][0] = 0; // Чистим память для DMA
    }
}


/**
 * @brief Сверхбыстрое управление мощностью подсветки 1
 */
inline void SetLight1PWM(uint16_t val) {    
    dma_pwm_masks[1][0] = (uint32_t)(val != 0) * raw_pin_masks[1];
    dma_pwm_masks[1][1] = (uint32_t)(val < 100) * (raw_pin_masks[1] << 16);
		// Обновляем порог срабатывания таймера	
    TIM1->CCR2 = val;
}

/**
 * @brief Сверхбыстрое управление мощностью подсветки 2
 */
inline void SetLight2PWM(uint16_t val) {  
    dma_pwm_masks[2][0] = (uint32_t)(val != 0) * raw_pin_masks[2];
    dma_pwm_masks[2][1] = (uint32_t)(val < 100) * (raw_pin_masks[2] << 16);
		// Обновляем порог срабатывания таймера    
    TIM1->CCR3 = val;
}



// HAL callback
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
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

// установка периода и запуск таймера YTimer
void YTimerSet(uint16_t period)
{
    __HAL_TIM_SET_AUTORELOAD(&htim4, period);
    __HAL_TIM_ENABLE(&htim4);
}



void XInterpTimerStart(uint32_t period) {
    // Старт интерполяционого таймера
    TIM3->ARR = period;          // Установка периода
    TIM3->SR &= ~TIM_SR_UIF;     // Сброс флага прерывания
    TIM3->DIER |= TIM_DIER_UIE;  // Разрешение прерывания
    TIM3->CR1 |= TIM_CR1_CEN;    // Запуск таймера
}

/**
 * @brief Наш собственный быстрый обработчик прерываний
 * @param pin_mask Битовая маска сработавших пинов (например, 0x0020 для Pin 5)
 */
void LPP_GPIO_EXTI_Handler(uint16_t pin_mask) {
    // Здесь мы просто пробрасываем маску в логику энкодера
    // или делаем что-то еще. Пин нам не важен, важен сам факт.
    XEncoderCallback(pin_mask); 
}

// Одиночные линии (0-4)
void EXTI0_IRQHandler(void) { EXTI->PR1 = (1U << 0); LPP_GPIO_EXTI_Handler(1U << 0); }
void EXTI1_IRQHandler(void) { EXTI->PR1 = (1U << 1); LPP_GPIO_EXTI_Handler(1U << 1); }
void EXTI2_IRQHandler(void) { EXTI->PR1 = (1U << 2); LPP_GPIO_EXTI_Handler(1U << 2); }
void EXTI3_IRQHandler(void) { EXTI->PR1 = (1U << 3); LPP_GPIO_EXTI_Handler(1U << 3); }
void EXTI4_IRQHandler(void) { EXTI->PR1 = (1U << 4); LPP_GPIO_EXTI_Handler(1U << 4); }

// Групповые линии (5-9)
void EXTI9_5_IRQHandler(void) {
    uint32_t pr = EXTI->PR1 & 0x03E0; 
    if (pr) {
        EXTI->PR1 = pr; // Сбрасываем флаги
        LPP_GPIO_EXTI_Handler(pr); 
    }
}

// Групповые линии (10-15)
void EXTI15_10_IRQHandler(void) {
    uint32_t pr = EXTI->PR1 & 0xFC00; 
    if (pr) {
        EXTI->PR1 = pr; 
        LPP_GPIO_EXTI_Handler(pr);
    }
}

// ============================================================================
// Инициализация DMA для Memory-to-Memory
// ============================================================================

// Глобальные переменные для работы DMA MemToMem
DMA_HandleTypeDef hdma_m2m_dma2_ch1; 

volatile uint8_t LPP_DataReady = 0;

void DMA_M2M_Init(void) {
    __HAL_RCC_DMA2_CLK_ENABLE(); 
    __HAL_RCC_DMAMUX1_CLK_ENABLE();
    __DSB(); 

    DMA2_Channel1->CCR = 0;
    while(DMA2_Channel1->CCR & DMA_CCR_EN);
    
    // Очистка флагов
    DMA2->IFCR = DMA_IFCR_CGIF1;
    
    // Настройка: 8-бит ИСТОЧНИК -> 8-бит ПРИЕМНИК
    DMA2_Channel1->CCR = DMA_CCR_MEM2MEM |             
                         DMA_CCR_TCIE |                
                         DMA_CCR_TEIE |                
                         (0x01 << DMA_CCR_PL_Pos) |    
                         (0x00 << DMA_CCR_MSIZE_Pos) | // 0x00 = 8-bit
                         (0x00 << DMA_CCR_PSIZE_Pos) | // 0x00 = 8-bit
                         DMA_CCR_MINC |                
                         DMA_CCR_PINC;

    HAL_NVIC_SetPriority(DMA2_Channel1_IRQn, 3, 0); 
    HAL_NVIC_EnableIRQ(DMA2_Channel1_IRQn);
}

void FIFO_DATA_StartDma(uint32_t src, uint32_t dst, uint16_t count) {
    // В 8-битном режиме проверка (src & 0x3) больше НЕ НУЖНА.
    
    LPP_DataReady = 0; 
    
    // 1. Принудительно выключаем
    DMA2_Channel1->CCR &= ~DMA_CCR_EN;
    
    // 2. Ждем готовности (защита от перегрузки канала)
    // Если DMA зависнет, здесь может быть вечный цикл. 
    // В идеале добавить счетчик попыток, но для лазера оставим так.
    while(DMA2_Channel1->CCR & DMA_CCR_EN);
    
    // 3. Сброс флагов (обязательно перед новым запуском)
    DMA2->IFCR = DMA_IFCR_CGIF1;
    
    // 4. Загрузка параметров
    DMA2_Channel1->CPAR = src;    // Откуда (адрес байта в памяти)
    DMA2_Channel1->CMAR = dst;    // Куда (адрес байта в памяти)
    DMA2_Channel1->CNDTR = count; // Сколько БАЙТ (в нашем случае 44)
    
    // 5. Поехали
    DMA2_Channel1->CCR |= DMA_CCR_EN;
}

void DMA2_Channel1_IRQHandler(void) 
{
    uint32_t isr = DMA2->ISR;
    
    // Завершение передачи
    if (isr & DMA_ISR_TCIF1) {
        DMA2->IFCR = DMA_IFCR_CTCIF1;
        LPP_DataReady = 1;
        FIFO_DATA_EndDma(); // Если эта функция существует
    }
    
    // Ошибка передачи
    if (isr & DMA_ISR_TEIF1) {
        DMA2->IFCR = DMA_IFCR_CTEIF1;
        LPP_DataReady = 1; // Или специальный код ошибки
        // TODO: логирование ошибки
    }
}

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
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
