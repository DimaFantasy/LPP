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
#include "lpp_sdk.h"
#include "counter.h"
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

static void DMA_M2M_Init();

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
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
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
  htim3.Init.Prescaler = 96;
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
  htim4.Init.Prescaler = 96;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 65535;
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

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
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

volatile int32_t X_PWM_CURRENT = 0; // Уставка мощности/тока для ШИМ-контроллера

/**
 * @brief Инициализация таймера TIM2 для управления мотором X
 */
void XMotorInit(X_MOTOR_MODE_T mode) {
    if (X_MOTOR_MODE == mode) return;

    // Полный сброс и включение тактирования
    __HAL_RCC_TIM2_FORCE_RESET();
    __HAL_RCC_TIM2_RELEASE_RESET();
    __HAL_RCC_TIM2_CLK_ENABLE();

    htim2.Instance = TIM2;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.RepetitionCounter = 0;
    
    // Включаем Preload (теневые регистры) для стабильности без джиттера
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;

    if (mode == X_MOTOR_MODE_STEP) {
        // --- РЕЖИМ STEP (Шаг) ---
        htim2.Init.Prescaler = 83; // 1 тик = 1 мкс (при 84МГц APB1)
        htim2.Init.Period = 10000;
        
        // Режим одного импульса
        HAL_TIM_OnePulse_Init(&htim2, TIM_OPMODE_SINGLE); 
        
        HAL_NVIC_SetPriority(TIM2_IRQn, 5, 0);
        HAL_NVIC_EnableIRQ(TIM2_IRQn);
        __HAL_TIM_ENABLE_IT(&htim2, TIM_IT_UPDATE);
        
        TIM2->EGR |= TIM_EGR_UG;
        TIM2->SR = 0;
        TIM2->CR1 |= TIM_CR1_CEN;
    } 
    else {
        // --- РЕЖИМ PWM (Программный, по прерываниям) ---
        
        // Настройка частоты (96МГц / 19 = ~5МГц шаг таймера)
        htim2.Init.Prescaler = 18;  
        htim2.Init.Period = 5001;   
        HAL_TIM_Base_Init(&htim2);
        
        // Постоянная работа (не One Pulse)
        TIM2->CR1 &= ~TIM_CR1_OPM; 

        // Конфигурируем канал 1 как "Timing" (просто для генерации прерывания CC1)
        TIM_OC_InitTypeDef sConfigOC = {0};
        sConfigOC.OCMode = TIM_OCMODE_TIMING;
        sConfigOC.Pulse = 2500; // 50% заполнение для старта
        HAL_TIM_OC_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1);

        // Включаем буферизацию (чтобы изменения Duty Cycle были синхронными)
        TIM2->CR1 |= TIM_CR1_ARPE;
        TIM2->CCMR1 |= TIM_CCMR1_OC1PE;

        // NVIC: Приоритет ШИМ
        HAL_NVIC_SetPriority(TIM2_IRQn, 5, 0); 
        HAL_NVIC_EnableIRQ(TIM2_IRQn);
        
        // Прерывания: UPDATE (начало периода) и CC1 (момент спада импульса)
        __HAL_TIM_ENABLE_IT(&htim2, TIM_IT_UPDATE | TIM_IT_CC1);
        
        // Синхронизация и запуск
        TIM2->EGR |= TIM_EGR_UG; 
        TIM2->SR = 0;
        TIM2->CR1 |= TIM_CR1_CEN; 
    }
    
    X_MOTOR_MODE = mode;
}

/**
 * @brief Программная задержка для защиты силовых ключей (DeadTime)
 * Предотвращает сквозной ток при переключении плеч моста.
 * @note F411: ~1 мкс при 100 МГц 
 */
__STATIC_INLINE void XMotorDeadTime(void) {
    // Примерно 1 мкс при 100 МГц (зависит от оптимизации компилятора)
    for (volatile int i = 0; i < 60; i++) { __NOP(); } 
}

//// Надёжный вариант через DWT (если включен)
///**
// * @brief Универсальный DeadTime на базе тактов ядра (DWT)
// * Работает на F103 (72MHz), F411 (100MHz), G431 (170MHz)
// */
//__STATIC_INLINE void XMotorDeadTime(void) {
//    // 1. Рассчитываем количество тактов для 1 мкс.
//    // SystemCoreClock / 1000000 дает количество тактов в 1 мкс.
//    uint32_t ticks = (SystemCoreClock / 1000000) * 1; // *1 = 1 мкс.

//    // 2. Ждем завершения отсчета тактов
//    uint32_t start = DWT->CYCCNT;
//    while ((DWT->CYCCNT - start) < ticks);
//}

/**
 * @brief Единый обработчик прерываний TIM2
 * Обрабатывает и начало периода (UIF), и момент выключения импульса (CC1IF).
 */
void TIM2_IRQHandler(void) {
    // Читаем регистр статуса один раз для скорости
    uint32_t sr = TIM2->SR;

    // --- ОБРАБОТКА НАЧАЛА ТАКТА (Update Event) ---
    if (sr & TIM_SR_UIF) {
        TIM2->SR = ~TIM_SR_UIF; // Сбрасываем флаг прерывания
        
        // Вызов основной логики планировщика шагов (важно для режима STEP)
        XTimerCallback(); 
        
        // Если мы в режиме ШИМ (не шаговик), управляем ключами
        if (X_MOTOR_MODE != X_MOTOR_MODE_STEP) {
            // БЕЗОПАСНОСТЬ: В начале каждого такта принудительно закрываем все ключи
            F_RESET_PIN(&g_pins[PIN_X_MO_L]);   
            F_RESET_PIN(&g_pins[PIN_X_MO_R]);
            F_RESET_PIN(&g_pins[PIN_X_MO_L_H]); 
            F_RESET_PIN(&g_pins[PIN_X_MO_R_H]);

            // Если задана мощность (мотор должен вращаться)
            if (X_PWM_CURRENT != 0) {
                // Ждем закрытия транзисторов перед открытием противоположных
                XMotorDeadTime();
                
                // Учет полярности ШИМ из настроек
                int32_t raw_pwr = (W_X_POL_PWM == 0) ? X_PWM_CURRENT : -X_PWM_CURRENT;
                uint32_t abs_pwr = abs(raw_pwr);
                
                // Программное ограничение (не более Period)
                if (abs_pwr > 5000) abs_pwr = 5000;
                
                // Установка точки "спада" импульса в регистр сравнения
                TIM2->CCR1 = abs_pwr; 

                // Выбор схемы активации пинов в зависимости от железа
                if (X_MOTOR_MODE == X_MOTOR_MODE_TWO_PWM) { 
                    // Режим полного H-моста (переключение диагоналей)
                    if (raw_pwr > 0) { 
                        F_SET_PIN(&g_pins[PIN_X_MO_L]);   
                        F_SET_PIN(&g_pins[PIN_X_MO_R_H]); 
                    } else { 
                        F_SET_PIN(&g_pins[PIN_X_MO_R]);   
                        F_SET_PIN(&g_pins[PIN_X_MO_L_H]); 
                    }
                } 
                else if (X_MOTOR_MODE == X_MOTOR_MODE_ONE_PWM) { 
                    // Режим PWM + DIR (один пин шимит, второй задает направление)
                    F_SET_PIN(&g_pins[PIN_X_MO_L]); // Силовой выход
                    uint8_t dir = (raw_pwr >= 0) ? 0 : 1;
                    if (W_X_POL_DIR) dir = !dir; // Инверсия DIR если нужно
                    
                    if (dir) F_SET_PIN(&g_pins[PIN_X_MO_R]); 
                    else     F_RESET_PIN(&g_pins[PIN_X_MO_R]);
                }
            }
        }
    }

    // --- ОБРАБОТКА КОНЦА ИМПУЛЬСА (Compare Event 1) ---
    // Срабатывает, когда счетчик CNT достигает значения CCR1
    if (sr & TIM_SR_CC1IF) {
        TIM2->SR = ~TIM_SR_CC1IF; // Сбрасываем флаг
        
        // Если мы в режиме ШИМ — гасим все силовые выходы
        if (X_MOTOR_MODE != X_MOTOR_MODE_STEP) {
            F_RESET_PIN(&g_pins[PIN_X_MO_L]);   
            F_RESET_PIN(&g_pins[PIN_X_MO_R]);
            F_RESET_PIN(&g_pins[PIN_X_MO_L_H]); 
            F_RESET_PIN(&g_pins[PIN_X_MO_R_H]);
        }
    }
}

/**
 * @brief Установка длительности шага для шагового двигателя
 * @param period: Значение ARR (длительность в микросекундах)
 */
void XTimerSet(uint16_t period) {
    if (X_MOTOR_MODE == X_MOTOR_MODE_STEP) {
        // Устанавливаем новое значение автоперезагрузки (частота шагов)
        __HAL_TIM_SET_AUTORELOAD(&htim2, period);
        // Запускаем таймер (бит CEN в CR1)
        __HAL_TIM_ENABLE(&htim2);
    }
}

/**
 * @brief Установка мощности мотора X
 * @param power: Значение от -5000 до 5000
 */
void XMotorSet(int power) {
    if (X_MOTOR_MODE == X_MOTOR_MODE_STEP) return;

    // 1. Ограничение и Deadband
    // if (abs(power) < 10) power = 0;
    if (power > 5000)  power = 5000;
    if (power < -5000) power = -5000;

    // 2. Сохраняем для программного ШИМ в прерывании
    X_PWM_CURRENT = power;

    // 3. СИНХРОНИЗИРУЕМ АППАРАТНЫЙ ЭТАЛОН (PA0)
    // Теперь PA0 будет менять ширину импульса мгновенно по команде
    TIM2->CCR1 = abs(power);

    if (power == 0) {
        // Мгновенный сброс всех ключей (безопасность)
        F_RESET_PIN(&g_pins[PIN_X_MO_L]);
        F_RESET_PIN(&g_pins[PIN_X_MO_R]);
        F_RESET_PIN(&g_pins[PIN_X_MO_L_H]);
        F_RESET_PIN(&g_pins[PIN_X_MO_R_H]);
    }
}


// ============================================================================
// ПОДСИСТЕМА PWM LASER & LIGHT (DMA-BASED)
// ============================================================================
// Глобальные переменные
volatile uint32_t dma_pwm_masks[3][2] = {0}; // [Laser, LED1, LED2][SET, RESET]
uint32_t raw_pin_masks[3] = {0};             // Маски пинов (1 << N)
uint32_t LAST_LASER_FREQ = 0;                // Защита от повторной инициализации
static const uint32_t GPIO_NULL_REG = 0;

/**
 * @brief Привязка потоков DMA к портам и маскам
 */
void PWM_LaserLight_LinkHardware(void) {
    uint8_t target_ids[3] = { PIN_PWM_LASER, PIN_PWM_LED1, PIN_PWM_LED2 };

    // МАППИНГ ДЛЯ F411 (DMA2):
    // Laser: ON = TIM1_UP  (Str 5), OFF = TIM1_CH1 (Str 1)
    // LED1:  ON = TIM1_CH4 (Str 4), OFF = TIM1_CH2 (Str 2)
    // LED2:  ON = TIM1_CH4 (Str 3), OFF = TIM1_CH3 (Str 6)
    // РЕЗУЛЬТАТ: Stream 0, Stream 7 — ПОЛНОСТЬЮ СВОБОДНЫ.
    
    DMA_Stream_TypeDef* streams_on[3]  = { DMA2_Stream5, DMA2_Stream4, DMA2_Stream3 };
    DMA_Stream_TypeDef* streams_off[3] = { DMA2_Stream1, DMA2_Stream2, DMA2_Stream6 };
    
    uint32_t ch_idx = 6; 

    for (int i = 0; i < 3; i++) {
        PIN_CFG_T *cfg = &g_pins[target_ids[i]];
        DMA_Stream_TypeDef* s_on  = streams_on[i];
        DMA_Stream_TypeDef* s_off = streams_off[i];

        if (!cfg->used || cfg->bsrr == (uint32_t*)&GPIO_NULL_REG) {
            s_on->CR &= ~DMA_SxCR_EN;
            s_off->CR &= ~DMA_SxCR_EN;
            continue;
        }

        raw_pin_masks[i] = cfg->pin;

        // Настройка ON
        s_on->CR &= ~DMA_SxCR_EN;
        while(s_on->CR & DMA_SxCR_EN);
        s_on->PAR = (uint32_t)cfg->bsrr;
        s_on->M0AR = (uint32_t)&dma_pwm_masks[i][0];
        s_on->NDTR = 1;
        s_on->CR = (ch_idx << DMA_SxCR_CHSEL_Pos) | DMA_SxCR_DIR_0 | DMA_SxCR_CIRC | 
                   (0x02 << DMA_SxCR_PSIZE_Pos) | (0x02 << DMA_SxCR_MSIZE_Pos) | (0x03 << DMA_SxCR_PL_Pos);
        s_on->CR |= DMA_SxCR_EN;

        // Настройка OFF
        s_off->CR &= ~DMA_SxCR_EN;
        while(s_off->CR & DMA_SxCR_EN);
        s_off->PAR = (uint32_t)cfg->bsrr;
        s_off->M0AR = (uint32_t)&dma_pwm_masks[i][1];
        s_off->NDTR = 1;
        s_off->CR = (ch_idx << DMA_SxCR_CHSEL_Pos) | DMA_SxCR_DIR_0 | DMA_SxCR_CIRC | 
                    (0x02 << DMA_SxCR_PSIZE_Pos) | (0x02 << DMA_SxCR_MSIZE_Pos) | (0x03 << DMA_SxCR_PL_Pos);
        s_off->CR |= DMA_SxCR_EN;
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
    __HAL_RCC_DMA2_CLK_ENABLE();

    uint32_t pclk2 = HAL_RCC_GetPCLK2Freq();
    uint32_t tim_clk = ((RCC->CFGR & RCC_CFGR_PPRE2) != RCC_CFGR_PPRE2_DIV1) ? pclk2 * 2 : pclk2;

    uint32_t arr = 100;
    uint32_t psc_val = tim_clk / (freq_hz * (arr + 1));
    
    TIM1->PSC = (psc_val > 0) ? psc_val - 1 : 0;
    TIM1->ARR = arr;
    TIM1->CCR4 = 0; // Триггер для одновременного включения светодиодов

    // Включаем 5 запросов DMA на TIM1
    TIM1->DIER = TIM_DIER_UDE | TIM_DIER_CC1DE | TIM_DIER_CC2DE | 
                 TIM_DIER_CC3DE | TIM_DIER_CC4DE;

		// Сброс флагов DMA
		DMA2->LIFCR = (0x3F << 6) | (0x3F << 16) | (0x3F << 22);
		DMA2->HIFCR = (0x3F << 0) | (0x3F << 6)  | (0x3F << 16);

    PWM_LaserLight_LinkHardware();

    TIM1->BDTR |= TIM_BDTR_MOE;
    TIM1->EGR |= TIM_EGR_UG; // Прогружаем настройки
    TIM1->SR = 0; 
    TIM1->CR1 |= TIM_CR1_CEN; 
    
    LAST_LASER_FREQ = freq_hz;
}

/**
 * @brief Отключение лазера с блокировкой
 */
void Laser_Off(void) {
    LASER_SAFETY_LOCK = 1;
    HAL_TIM_Base_Stop_IT(&htim3); 
    SetLaserPWM(0);
    TIM1->EGR |= TIM_EGR_UG;
    F_RESET_PIN(&g_pins[PIN_PWM_LASER]);
}

/**
 * @brief Подготовка лазера к работе
 */
void Laser_Ready(void) {
    TIM3->CNT = 0;
    interp_counter = 0; 
    TIM1->CNT = 0;
    TIM1->EGR |= TIM_EGR_UG;
    LASER_SAFETY_LOCK = 0;
}

/**
 * @brief Сверхбыстрое управление мощностью лазера (Branchless)
 */
inline void SetLaserPWM(uint16_t val) {
    if (LASER_SAFETY_LOCK) val = 0;
    if (val > 100) val = 100;

    dma_pwm_masks[0][0] = (val > 0) ? raw_pin_masks[0] : 0;
    dma_pwm_masks[0][1] = (val < 100) ? (raw_pin_masks[0] << 16) : 0;
    TIM1->CCR1 = val;

    if (val == 0) F_RESET_PIN(&g_pins[PIN_PWM_LASER]);
}

inline void SetLight1PWM(uint16_t val) {  
    if (val > 100) val = 100;
    dma_pwm_masks[1][0] = (val > 0) ? raw_pin_masks[1] : 0;
    dma_pwm_masks[1][1] = (val < 100) ? (raw_pin_masks[1] << 16) : 0;
    TIM1->CCR2 = val;
    if (val == 0) F_RESET_PIN(&g_pins[PIN_PWM_LED1]);
}

inline void SetLight2PWM(uint16_t val) {  
    if (val > 100) val = 100;
    dma_pwm_masks[2][0] = (val > 0) ? raw_pin_masks[2] : 0;
    dma_pwm_masks[2][1] = (val < 100) ? (raw_pin_masks[2] << 16) : 0;
    TIM1->CCR3 = val;
    if (val == 0) F_RESET_PIN(&g_pins[PIN_PWM_LED2]);
}

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

    HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);
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

/**
 * @brief HAL callback для периодических событий таймера
 * @note F411: TIM3 и TIM4 на APB1 (42MHz), с делителем тактируются 84MHz
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
    // TIM3 - Интерполяция печати
    if (htim->Instance == TIM3) {
        if (XInterpTimerCallback() == 0) {
            HAL_TIM_Base_Stop_IT(&htim3);
            TIM3->CNT = 0;
        }
    }
    // TIM4 - Управление осью Y
    if (htim->Instance == TIM4) {
        YTimerCallback();
    }
}

/**
 * @brief Установка периода и запуск таймера YTimer
 */
void YTimerSet(uint16_t period)
{
    __HAL_TIM_SET_AUTORELOAD(&htim4, period);
    __HAL_TIM_ENABLE(&htim4);
}

/**
 * @brief Запуск интерполяционного таймера
 */
void XInterpTimerStart(uint32_t period) {
    TIM3->ARR = period;
    TIM3->SR &= ~TIM_SR_UIF;
    TIM3->DIER |= TIM_DIER_UIE;
    TIM3->CR1 |= TIM_CR1_CEN;
}

// ============================================================================
// EXTI HANDLERS
// ============================================================================

/**
 * @brief Наш собственный быстрый обработчик прерываний
 * @param pin_mask Битовая маска сработавших пинов
 */
void LPP_GPIO_EXTI_Handler(uint16_t pin_mask) {
    XEncoderCallback(pin_mask); 
}

// F411: EXTI handlers идентичны G431
void EXTI0_IRQHandler(void) { EXTI->PR = (1U << 0); LPP_GPIO_EXTI_Handler(1U << 0); }
void EXTI1_IRQHandler(void) { EXTI->PR = (1U << 1); LPP_GPIO_EXTI_Handler(1U << 1); }
void EXTI2_IRQHandler(void) { EXTI->PR = (1U << 2); LPP_GPIO_EXTI_Handler(1U << 2); }
void EXTI3_IRQHandler(void) { EXTI->PR = (1U << 3); LPP_GPIO_EXTI_Handler(1U << 3); }
void EXTI4_IRQHandler(void) { EXTI->PR = (1U << 4); LPP_GPIO_EXTI_Handler(1U << 4); }

void EXTI9_5_IRQHandler(void) {
    uint32_t pr = EXTI->PR & 0x03E0; 
    if (pr) {
        EXTI->PR = pr;
        LPP_GPIO_EXTI_Handler(pr); 
    }
}

void EXTI15_10_IRQHandler(void) {
    uint32_t pr = EXTI->PR & 0xFC00; 
    if (pr) {
        EXTI->PR = pr; 
        LPP_GPIO_EXTI_Handler(pr);
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
