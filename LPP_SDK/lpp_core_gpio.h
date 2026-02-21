#ifndef LPP_CORE_GPIO_H
#define LPP_CORE_GPIO_H

#include <stdbool.h>
#include <stdint.h>

// Подключаем правильный HAL под серию MCU
#if defined(STM32F103xB)
    #include "stm32f1xx_hal.h"   // для F103
#elif defined(STM32G431xx)
    #include "stm32g4xx_hal.h"   // для G431
#elif defined(STM32F411xE)
    #include "stm32f4xx_hal.h"   // для F411
#else
    #error "Unsupported STM32 series"
#endif

#if defined(STM32G431xx)
#include "configs/lpp_config_g431.h"
#elif defined(STM32F103xB)
#include "configs/lpp_config_f103.h"
#elif defined(STM32F411xE)
#include "configs/lpp_config_f411.h"
#endif

// ============================================================================
// Константы режимов работы пинов
// ============================================================================
#define PIN_MODE_INPUT 0   // Обычный цифровой вход
#define PIN_MODE_OUTPUT 1  // Цифровой выход
#define PIN_MODE_EXTI 2    // Вход с активацией внешнего прерывания

#define PIN_OUT_PP 0  // Выход: Push-Pull (двухтактный)
#define PIN_OUT_OD 1  // Выход: Open-Drain (открытый сток)

#define PIN_NOPULL 0    // Без подтяжки
#define PIN_PULLUP 1    // Внутренняя подтяжка к VCC
#define PIN_PULLDOWN 2  // Внутренняя подтяжка к GND

// ============================================================================
// Идентификаторы пинов для обращения из кода
// ============================================================================
typedef enum {
    // Драйвер оси X
    PIN_X_MO_R = 0,
    PIN_X_MO_L,
    PIN_X_MO_EN,
    // H-мост оси X
    PIN_X_MO_R_H,
    PIN_X_MO_L_H,
    // Выходы DB25    
    PIN_X_STEP_DB25,
    PIN_X_DIR_DB25,
    PIN_X_EN_DB25,
    // Ось Y
    PIN_Y_STEP,
    PIN_Y_DIR,
    PIN_Y_EN,
    // Ось Z
    PIN_Z_STEP,
    PIN_Z_DIR,
    PIN_Z_EN,
    // ШИМ устройства
    PIN_PWM_LASER,
    PIN_PWM_LED1,
    PIN_PWM_LED2,
    // Энкодер
    PIN_X_ENC_A,
    PIN_X_ENC_B,
    // Датчики
    PIN_PROBE,
    PIN_E_STOP,
		// Индикация 
		PIN_LED_STATUS,
    // Общее количество
    PIN_COUNT,
	// Системные индексы
    SYS_PIN_USB_EN,
		SYS_PIN_LED,
		TOTAL_PINS	
} PIN_ID_T;

// ============================================================================
// Структура конфигурации пина (оптимизирована для скорости)
// ============================================================================
typedef struct {
    volatile uint32_t* bsrr;  // Прямой адрес регистра установки/сброса
    volatile uint32_t* idr;   // Прямой адрес регистра чтения данных
    uint16_t pin;             // Битовая маска (например, GPIO_PIN_5)
    uint8_t mode;             // Режим (Input/Output/EXTI)
    uint8_t outcfg;           // Тип выхода (PP/OD)
    uint8_t pull;             // Подтяжка (No/Up/Down)
    uint8_t used;             // Флаг: 1 - активен, 0 - игнорируется
} PIN_CFG_T;

// Сделайте массив доступным для других файлов (.c)
extern PIN_CFG_T g_pins[TOTAL_PINS];

// ============================================================================
// Публичные функции (API)
// ============================================================================

/**
 * @brief Основная функция для внешней конфигурации (из Pascal/EEPROM).
 * * ПАРАМЕТРЫ:
 * W_PIN_ID:   ID из PIN_ID_T (какую функцию выполняет: X_STEP, PROBE...)
 * W_PIN_PORT: Номер порта (0=A, 1=B, 2=C, 3=D, 255=Disabled)
 * W_PIN_NUM:  Номер ножки в порту (0..15)
 * W_PIN_MODE: Режим работы (0=INPUT, 1=OUTPUT, 2=EXTI)
 * W_PIN_OUT:  Тип выхода (0=Push-Pull, 1=Open-Drain)
 * W_PIN_PULL: Подтяжка (0=NoPull, 1=PullUp, 2=PullDown)
 * W_PIN_USED: Активность (1=Используется, 0=Пропустить)
 */
void SetPinConfiguration(uint8_t id, uint8_t port, uint8_t num, uint8_t mode, uint8_t out, uint8_t pull,
                         uint8_t used);

/** Полная деактивация всех пинов, кроме реально используемых и системных (PA8) */
void Hardware_PurgeUnused(void);

/** * @brief Стандартная безопасная инициализация пина.
 * (Автоматически проверяет защиту системных пинов USB/SWD)
 */
void InitPin(PIN_CFG_T* p);

/** * @brief Расширенная инициализация пина.
 * @param check_protected Если true — включает защиту, если false — игнорирует её.
 */
void InitPinEx(PIN_CFG_T* p, bool check_protected);

/** Вспомогательная функция для получения базы порта из адреса BSRR */
GPIO_TypeDef* GetPortFromBSRR(volatile uint32_t* bsrr);

// ============================================================================
// Сверхбыстрые макросы доступа (без проверок, 1-2 инструкции процессора)
// ============================================================================
#define F_SET_PIN(p)   (*((p)->bsrr) = (uint32_t)((p)->pin))// Установка пина в LOGIC 1 
#define F_RESET_PIN(p) (*((p)->bsrr) = (uint32_t)((p)->pin) << 16)// Сброс пина в LOGIC 0 
// Инвертировать состояние пина (используем XOR для регистра ODR или просто считываем и меняем)
#define F_INV_PIN(p) (*((p)->bsrr) = ((uint32_t)((p)->pin) << (F_GET_PIN(p) ? 16 : 0)))
#define F_GET_PIN(p) ((*((p)->idr) & (p)->pin) ? 1 : 0)             // Считать 1/0


// Динамическая привязка DMA-каналов лазера и светодиодов к регистрам BSRR портов
extern void PWM_LaserLight_LinkHardware();
// Динамическая привязка DMA-каналов моста оси X к регистрам BSRR портов
//extern void XMotor_LinkHardware();

#endif  // LPP_CORE_GPIO_H
