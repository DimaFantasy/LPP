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

// Заглушка для пустых пинов
static volatile uint32_t GPIO_NULL_REG = 0;

/* USER CODE END Includes */

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

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM4_Init(void);
/* USER CODE BEGIN PFP */

static void DMA_M2M_Init();

/* USER CODE END PFP */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  // Приоритет 0: EXTI (Энкодер)
  // Приоритет 1: TIM3 (Интерполяция)
  // Приоритет 2: DMA (PWM Laser)
  // Приоритет 3: DMA2_Stream0 (M2M Data)
  // Приоритет 4: USB
  // Приоритет 5: TIM2, TIM4 (PID)
  /* USER CODE END 1 */

  HAL_Init();

  /* USER CODE BEGIN Init */
  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
  /* USER CODE END Init */

  SystemClock_Config();

  MX_GPIO_Init();
  MX_USB_DEVICE_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();

  /* USER CODE BEGIN 2 */
  DMA_M2M_Init();

  // ============================================================
  // ЯВНАЯ РАССТАНОВКА ПРИОРИТЕТОВ ПРЕРЫВАНИЙ
  // Меньше число = выше приоритет
  // ============================================================

  // 0: EXTI (энкодер)
  HAL_NVIC_SetPriority(EXTI0_IRQn,     0, 0);
  HAL_NVIC_SetPriority(EXTI1_IRQn,     0, 0);
  HAL_NVIC_SetPriority(EXTI2_IRQn,     0, 0);
  HAL_NVIC_SetPriority(EXTI3_IRQn,     0, 0);
  HAL_NVIC_SetPriority(EXTI4_IRQn,     0, 0);
  HAL_NVIC_SetPriority(EXTI9_5_IRQn,   0, 0);
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);

  // 1: TIM3 (интерполяция лазера)
  HAL_NVIC_SetPriority(TIM3_IRQn, 1, 0);

  // 2: DMA лазера — DMA2_Stream5 (ON) и DMA2_Stream1 (OFF)
  HAL_NVIC_SetPriority(DMA2_Stream5_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream5_IRQn);
  HAL_NVIC_SetPriority(DMA2_Stream1_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream1_IRQn);

  // 3: DMA2_Stream0 (M2M копирование данных)
  HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 3, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);

  // 4: USB OTG FS
  HAL_NVIC_SetPriority(OTG_FS_IRQn, 4, 0);

  // 5: TIM2, TIM4
  HAL_NVIC_SetPriority(TIM2_IRQn, 5, 0);
  HAL_NVIC_SetPriority(TIM4_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(TIM4_IRQn);

  Lpp_Init();

  HAL_TIM_Base_Start_IT(&htim4);

  // Инициализация USB (F411: OTG FS)
  USB_OTG_FS->GCCFG &= ~USB_OTG_GCCFG_PWRDWN;
  HAL_Delay(10);

  F_RESET_PIN(&g_pins[SYS_PIN_USB_EN]);
  HAL_Delay(2000);
  F_SET_PIN(&g_pins[SYS_PIN_USB_EN]);
  HAL_Delay(50);

  USB_OTG_FS->GCCFG |= USB_OTG_GCCFG_PWRDWN;
  /* USER CODE END 2 */

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
  * F411: HSE 25MHz → PLL → 96MHz, PLLQ=4 → USB 48MHz
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState       = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState   = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource  = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM      = 25;
  RCC_OscInitStruct.PLL.PLLN      = 192;
  RCC_OscInitStruct.PLL.PLLP      = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ      = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) Error_Handler();

  RCC_ClkInitStruct.ClockType      = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                   | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;  // APB1 max 50MHz
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;  // APB2 = 96MHz
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK) Error_Handler();
}

/**
  * @brief TIM3 Initialization Function
  * F411 @ 96MHz: Prescaler=96 → 96MHz/97 ≈ 1МГц тик (APB1*2=96MHz)
  */
static void MX_TIM3_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 96;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 65535;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK) Error_Handler();
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK) Error_Handler();
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK) Error_Handler();

  // Приоритет задаётся централизованно в main(), EnableIRQ — в XInterpTimerStart()
}

/**
  * @brief TIM4 Initialization Function
  */
static void MX_TIM4_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 96;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 10000;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK) Error_Handler();
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK) Error_Handler();
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK) Error_Handler();
}

/**
  * @brief GPIO Initialization Function
  */
static void MX_GPIO_Init(void)
{
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
}

/* USER CODE BEGIN 4 */
// ============================================================================
// Отправка 64-байтного пакета хосту
// ============================================================================
extern uint8_t USBD_CUSTOM_HID_SendReport(USBD_HandleTypeDef* pdev, uint8_t* report, uint16_t len);
extern USBD_HandleTypeDef hUsbDeviceFS;

uint8_t PacketSend(uint8_t* buffer) {
    return USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, buffer, 64);
}

// ============================================================================
// СЕКЦИЯ: МОТОР ОСИ X (TIM2) — STM32F411 @ 96МГц
// ============================================================================

volatile int32_t X_PWM_CURRENT = 0;

__STATIC_INLINE void X_PWM_SET(void) {
    if (W_X_POL_PWM == 0) F_SET_PIN(&g_pins[PIN_X_MO_L]);
    else                   F_RESET_PIN(&g_pins[PIN_X_MO_L]);
}

__STATIC_INLINE void X_PWM_CLR(void) {
    if (W_X_POL_PWM == 0) F_RESET_PIN(&g_pins[PIN_X_MO_L]);
    else                   F_SET_PIN(&g_pins[PIN_X_MO_L]);
}

__STATIC_INLINE void X_DIR_SET(void) {
    if (W_X_POL_DIR == 0) F_SET_PIN(&g_pins[PIN_X_MO_R]);
    else                   F_RESET_PIN(&g_pins[PIN_X_MO_R]);
}

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
    htim2.Init.RepetitionCounter = 0;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;

    if (mode == X_MOTOR_MODE_STEP) {
        htim2.Init.Prescaler = 83; // 96МГц / 84 ≈ 1МГц → 1 тик ≈ 1 мкс
        htim2.Init.Period    = 10000;

        HAL_TIM_OnePulse_Init(&htim2, TIM_OPMODE_SINGLE);

        TIM2->DIER = 0;
        TIM2->EGR |= TIM_EGR_UG;
        TIM2->SR   = 0;
        TIM2->DIER |= TIM_DIER_UIE;

        HAL_NVIC_SetPriority(TIM2_IRQn, 5, 0);
        HAL_NVIC_EnableIRQ(TIM2_IRQn);

        TIM2->ARR  = 100;
        TIM2->CNT  = 0;
        TIM2->SR   = 0;
        TIM2->CR1 |= TIM_CR1_CEN;
    }
    else {
        htim2.Init.Prescaler = 18;
        htim2.Init.Period    = 5001;
        HAL_TIM_Base_Init(&htim2);

        TIM2->CR1 &= ~TIM_CR1_OPM;

        TIM_OC_InitTypeDef sConfigOC = {0};
        sConfigOC.OCMode = TIM_OCMODE_TIMING;
        sConfigOC.Pulse  = 2500;
        HAL_TIM_OC_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1);

        TIM2->CR1   |= TIM_CR1_ARPE;
        TIM2->CCMR1 |= TIM_CCMR1_OC1PE;

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

__STATIC_INLINE void XMotorDeadTime(void) {
    for (volatile int i = 0; i < 100; i++) { __NOP(); }
}

static volatile uint8_t X_DIR_NEXT = 0;

void TIM2_IRQHandler(void) {
    uint32_t sr = TIM2->SR;

    if (sr & TIM_SR_UIF) {
        TIM2->SR = ~TIM_SR_UIF;

        XTimerCallback();

        if (X_MOTOR_MODE != X_MOTOR_MODE_STEP) {
            F_RESET_PIN(&g_pins[PIN_X_MO_L]);
            F_RESET_PIN(&g_pins[PIN_X_MO_L_H]);
            F_RESET_PIN(&g_pins[PIN_X_MO_R_H]);
            if (X_MOTOR_MODE == X_MOTOR_MODE_TWO_PWM) {
                F_RESET_PIN(&g_pins[PIN_X_MO_R]);
            }

            if (X_PWM_CURRENT != 0) {
                XMotorDeadTime();

                if (X_MOTOR_MODE == X_MOTOR_MODE_TWO_PWM) {
                    uint32_t abs_pwr = (uint32_t)abs(X_PWM_CURRENT);
                    if (abs_pwr > 4900) abs_pwr = 4900;
                    TIM2->CCR1 = abs_pwr;

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
                    uint32_t abs_pwr = (uint32_t)abs(X_PWM_CURRENT);
                    if (abs_pwr > 4900) abs_pwr = 4900;
                    TIM2->CCR1 = abs_pwr;
                    X_PWM_SET();
                }
            }
        }
    }

    if (sr & TIM_SR_CC1IF) {
        TIM2->SR = ~TIM_SR_CC1IF;

        if (X_MOTOR_MODE == X_MOTOR_MODE_TWO_PWM) {
            F_RESET_PIN(&g_pins[PIN_X_MO_L]);
            F_RESET_PIN(&g_pins[PIN_X_MO_R]);
            F_RESET_PIN(&g_pins[PIN_X_MO_L_H]);
            F_RESET_PIN(&g_pins[PIN_X_MO_R_H]);
        }
        else if (X_MOTOR_MODE == X_MOTOR_MODE_ONE_PWM) {
            X_PWM_CLR();
            X_DIR_NEXT = (X_PWM_CURRENT >= 0) ? 0 : 1;
            if (X_DIR_NEXT) X_DIR_SET();
            else            X_DIR_CLR();
        }
    }
}

void XTimerSet(uint16_t period) {
    if (X_MOTOR_MODE == X_MOTOR_MODE_STEP) {
        TIM2->ARR  = period;
        TIM2->CNT  = 0;
        TIM2->SR   = 0;
        TIM2->CR1 |= TIM_CR1_CEN;
    }
}

// Потолок 4900 вместо ARR=5000: запас ~20мкс нужен, т.к. CCR1
// пишется в конце ISR (после XTimerCallback+DeadTime), и при
// power близком к ARR счётчик CNT успевает обогнать запись CCR1 —
// CC1 не срабатывает, период проходит с выходом в 0.
void XMotorSet(int power) {
    if (X_MOTOR_MODE == X_MOTOR_MODE_STEP) return;
    if (abs(power) < 10) power = 0;

    if (power >  4900) power =  4900;
    if (power < -4900) power = -4900;

    X_PWM_CURRENT = power;

    if (power == 0) {
        TIM2->CCR1 = 0;
        F_RESET_PIN(&g_pins[PIN_X_MO_L_H]);
        F_RESET_PIN(&g_pins[PIN_X_MO_R_H]);
        X_DIR_CLR();
        X_PWM_CLR();
        X_DIR_NEXT = 0;
    } else {
        TIM2->CCR1 = (uint32_t)abs(power);
    }
}

// ============================================================================
// СЕКЦИЯ: ЛАЗЕР (TIM1 + DMA2 Streams)
// ============================================================================
// LASER: Включение по TIM1_UP → DMA2_Stream5 Ch6,
//        выключение по TIM1_CH1 → DMA2_Stream1 Ch6.
// LED1/LED2: программный ШИМ через DWT->CYCCNT в Lpp_MainLoop().
// ============================================================================

// Только лазер — LED управляется программно
volatile uint32_t dma_pwm_masks[1][2] = {0}; // [Laser][SET, RESET]
uint32_t raw_pin_masks[1] = {0};             // Маска пина лазера
uint32_t LAST_LASER_FREQ = 0;

/**
 * @brief Привязка DMA стримов к лазеру
 * F411 (DMA2, фиксированные каналы):
 *   Laser ON  = DMA2_Stream5, Channel 6 (TIM1_UP)
 *   Laser OFF = DMA2_Stream1, Channel 6 (TIM1_CH1)
 */
void PWM_LaserLight_LinkHardware(void) {
    PIN_CFG_T *laser = &g_pins[PIN_PWM_LASER];

    DMA2_Stream5->CR &= ~DMA_SxCR_EN;
    while (DMA2_Stream5->CR & DMA_SxCR_EN);
    DMA2_Stream1->CR &= ~DMA_SxCR_EN;
    while (DMA2_Stream1->CR & DMA_SxCR_EN);

    if (laser->used) F_RESET_PIN(laser);

    DMA2->HIFCR = DMA_HIFCR_CTCIF5 | DMA_HIFCR_CHTIF5 |
                  DMA_HIFCR_CTEIF5 | DMA_HIFCR_CDMEIF5 | DMA_HIFCR_CFEIF5;
    DMA2->LIFCR = DMA_LIFCR_CTCIF1 | DMA_LIFCR_CHTIF1 |
                  DMA_LIFCR_CTEIF1 | DMA_LIFCR_CDMEIF1 | DMA_LIFCR_CFEIF1;

    if (!laser->used || laser->bsrr == (uint32_t*)&GPIO_NULL_REG) return;

    raw_pin_masks[0] = laser->pin;

    uint32_t cr_base = (6U << DMA_SxCR_CHSEL_Pos) | // Channel 6 (TIM1)
                       DMA_SxCR_DIR_0              | // Memory to Peripheral
                       DMA_SxCR_CIRC               | // Circular
                       (0x2U << DMA_SxCR_PSIZE_Pos)| // PSIZE = 32bit
                       (0x2U << DMA_SxCR_MSIZE_Pos)| // MSIZE = 32bit
                       (0x3U << DMA_SxCR_PL_Pos);    // Priority = Very High

    // Laser ON — Stream5
    DMA2_Stream5->PAR  = (uint32_t)laser->bsrr;
    DMA2_Stream5->M0AR = (uint32_t)&dma_pwm_masks[0][0];
    DMA2_Stream5->NDTR = 1;
    DMA2_Stream5->FCR  = 0;
    DMA2_Stream5->CR   = cr_base | DMA_SxCR_EN;

    // Laser OFF — Stream1
    DMA2_Stream1->PAR  = (uint32_t)laser->bsrr;
    DMA2_Stream1->M0AR = (uint32_t)&dma_pwm_masks[0][1];
    DMA2_Stream1->NDTR = 1;
    DMA2_Stream1->FCR  = 0;
    DMA2_Stream1->CR   = cr_base | DMA_SxCR_EN;
}

void SetLaserLightPWMFrequency(uint32_t freq_hz) {
    if (freq_hz == LAST_LASER_FREQ && freq_hz != 0) return;

    if (freq_hz == 0) {
        TIM1->CR1 &= ~TIM_CR1_CEN;
        LAST_LASER_FREQ = 0;
        return;
    }

    __HAL_RCC_TIM1_CLK_ENABLE();
    __HAL_RCC_DMA2_CLK_ENABLE();

    uint32_t pclk2   = HAL_RCC_GetPCLK2Freq();
    uint32_t tim_clk = ((RCC->CFGR & RCC_CFGR_PPRE2) != RCC_CFGR_PPRE2_DIV1)
                       ? pclk2 * 2 : pclk2;

    uint32_t arr = tim_clk / freq_hz;
    uint32_t psc = 0;

    if (arr > 65535) {
        psc = arr / 65535;
        arr = tim_clk / ((psc + 1) * freq_hz);
    }

    if (arr < 1) arr = 1;
    if (arr > 65535) arr = 65535;

    TIM1->CR1  &= ~TIM_CR1_CEN;
    TIM1->PSC   = psc;
    TIM1->ARR   = arr - 1;
    TIM1->CCR1  = 0;
    TIM1->CCMR1 = 0;
    TIM1->CCMR2 = 0;
    TIM1->DIER  = TIM_DIER_UDE | TIM_DIER_CC1DE;

    dma_pwm_masks[0][0] = 0;
    dma_pwm_masks[0][1] = 0;

    PWM_LaserLight_LinkHardware();

    TIM1->BDTR |= TIM_BDTR_MOE;
    TIM1->SR    = 0;
    TIM1->EGR  |= TIM_EGR_UG;
    TIM1->CR1  |= TIM_CR1_CEN;

    LAST_LASER_FREQ = freq_hz;
}

void Laser_Off(void) {
    LASER_SAFETY_LOCK = 1;
    HAL_TIM_Base_Stop_IT(&htim3);
    SetLaserPWM(0);
    TIM1->EGR |= TIM_EGR_UG;
    F_RESET_PIN(&g_pins[PIN_PWM_LASER]);
}

void Laser_Ready(void) {
    TIM3->CNT = 0;
    interp_counter = 0;
    TIM1->CNT = 0;
    TIM1->EGR |= TIM_EGR_UG;
    LASER_SAFETY_LOCK = 0;
}

inline void SetLaserPWM(uint16_t val) {
    if (LASER_SAFETY_LOCK) val = 0;
    if (val > 1000) val = 1000;
    uint32_t arr = TIM1->ARR;
    uint32_t ccr = ((uint32_t)val * arr) / 1000;

    dma_pwm_masks[0][0] = (val > 0)    ? raw_pin_masks[0]         : 0;
    dma_pwm_masks[0][1] = (val < 1000) ? (raw_pin_masks[0] << 16) : 0;
    TIM1->CCR1 = ccr;

    if (val == 0) F_RESET_PIN(&g_pins[PIN_PWM_LASER]);
}

// SetLight1PWM и SetLight2PWM перенесены в lpp_sdk.c

// ============================================================================
// DMA M2M
// ============================================================================
void DMA_M2M_Init(void) {
    __HAL_RCC_DMA2_CLK_ENABLE();

    // Полностью копируем HAL_DMA_Init:
    DMA2_Stream0->CR = 0;
    while(DMA2_Stream0->CR & DMA_SxCR_EN);

    // Сброс всех флагов Stream0
    DMA2->LIFCR = 0x3F;

    // CR: Channel0, M2M, Priority Low, 8bit->8bit, PINC+MINC, Normal
    DMA2_Stream0->CR = (0 << DMA_SxCR_CHSEL_Pos)  | // Channel 0
                       DMA_SxCR_DIR_1              | // Memory-to-Memory
                       (0 << DMA_SxCR_PL_Pos)      | // Priority Low
                       (0 << DMA_SxCR_MSIZE_Pos)   | // 8-bit Memory
                       (0 << DMA_SxCR_PSIZE_Pos)   | // 8-bit Periph
                       DMA_SxCR_MINC               | // Memory increment
                       DMA_SxCR_PINC;                // Periph increment

    // FCR: FIFO enable, Full threshold, Single burst — ОБЯЗАТЕЛЬНО для M2M
    DMA2_Stream0->FCR = DMA_SxFCR_DMDIS | (0x03 << DMA_SxFCR_FTH_Pos);

}

void FIFO_DATA_StartDma(uint32_t src, uint32_t dst, uint16_t count) {
    // Копируем HAL_DMA_Start_IT:
    
    // 1. Disable
    DMA2_Stream0->CR &= ~DMA_SxCR_EN;
    while(DMA2_Stream0->CR & DMA_SxCR_EN);

    // 2. Сброс флагов
    DMA2->LIFCR = 0x3F;

    // 3. Адреса и размер
    DMA2_Stream0->PAR  = src;
    DMA2_Stream0->M0AR = dst;
    DMA2_Stream0->NDTR = count;

    // 4. FCR заново (сбрасывается при выключении)
    DMA2_Stream0->FCR = DMA_SxFCR_DMDIS | (0x03 << DMA_SxFCR_FTH_Pos);

    // 5. Включаем прерывания и запускаем — всё в одной записи
    DMA2_Stream0->CR |= DMA_SxCR_TCIE | DMA_SxCR_TEIE | DMA_SxCR_DMEIE;
    DMA2_Stream0->CR |= DMA_SxCR_EN;
}

void DMA2_Stream0_IRQHandler(void) {
    uint32_t isr = DMA2->LISR;

    if (isr & DMA_LISR_TCIF0) {
        DMA2->LIFCR = DMA_LIFCR_CTCIF0;
        FIFO_DATA_EndDma();
    }
    if (isr & DMA_LISR_TEIF0) {
        DMA2->LIFCR = DMA_LIFCR_CTEIF0;
        // обработка ошибки
    }
    if (isr & DMA_LISR_DMEIF0) {
        DMA2->LIFCR = DMA_LIFCR_CDMEIF0;
        // direct mode error — не должно быть при FIFO
    }
}

// ============================================================================
// HAL CALLBACKS
// ============================================================================

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
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

void YTimerSet(uint16_t period)
{
    __HAL_TIM_SET_AUTORELOAD(&htim4, period);
    __HAL_TIM_ENABLE(&htim4);
}

void XInterpTimerStart(uint32_t period) {
    HAL_NVIC_EnableIRQ(TIM3_IRQn);
    TIM3->ARR = period;
    TIM3->SR &= ~TIM_SR_UIF;
    TIM3->DIER |= TIM_DIER_UIE;
    TIM3->CR1 |= TIM_CR1_CEN;
}

// ============================================================================
// EXTI HANDLERS (F411: EXTI->PR)
// ============================================================================

void LPP_GPIO_EXTI_Handler(uint16_t pin_mask) {
    XEncoderCallback(pin_mask);
}

void EXTI0_IRQHandler(void)  { __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_0); LPP_GPIO_EXTI_Handler(GPIO_PIN_0); }
void EXTI1_IRQHandler(void)  { __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_1); LPP_GPIO_EXTI_Handler(GPIO_PIN_1); }
void EXTI2_IRQHandler(void)  { __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_2); LPP_GPIO_EXTI_Handler(GPIO_PIN_2); }
void EXTI3_IRQHandler(void)  { __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_3); LPP_GPIO_EXTI_Handler(GPIO_PIN_3); }
void EXTI4_IRQHandler(void)  { __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_4); LPP_GPIO_EXTI_Handler(GPIO_PIN_4); }

void EXTI9_5_IRQHandler(void) {
    uint32_t pin = EXTI->PR & 0x03E0;
    __HAL_GPIO_EXTI_CLEAR_IT(pin);
    LPP_GPIO_EXTI_Handler((uint16_t)pin);
}

void EXTI15_10_IRQHandler(void) {
    uint32_t pin = EXTI->PR & 0xFC00;
    __HAL_GPIO_EXTI_CLEAR_IT(pin);
    LPP_GPIO_EXTI_Handler((uint16_t)pin);
}

/* USER CODE END 4 */

void Error_Handler(void)
{
  __disable_irq();
  while (1) {}
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line) {}
#endif