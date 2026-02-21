/**
 ******************************************************************************
 * @file    lpp_config_f103.h
 * @brief   LPP hardware configuration for STM32F103 (Blue Pill)
 ******************************************************************************
 */

#ifndef LPP_CONFIG_F103_H
#define LPP_CONFIG_F103_H

#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"
#include <stddef.h> // Для NULL

// ============================================================================
// Защищённые GPIO-пины (Blue Pill)
// ============================================================================
typedef struct {
    GPIO_TypeDef *port;
    uint16_t      pin;
} lpp_protected_pin_t;

static const lpp_protected_pin_t lpp_protected_pins[] = {
    // USB пины (F103: PA11/PA12)
    { GPIOA, GPIO_PIN_11 },  // USB_DM
    { GPIOA, GPIO_PIN_12 },  // USB_DP
    
    // SWD отладка
    { GPIOA, GPIO_PIN_13 },  // SWDIO
    { GPIOA, GPIO_PIN_14 },  // SWCLK

    { NULL,  0 }             // Стоп-маркер
};

extern volatile uint32_t GPIO_NULL_REG;

// ============================================================================
// Память и адреса (Архитектура 32КБ + 32КБ)
// На многих F103C8T6 на самом деле 128КБ Flash, но мы ориентируемся на 64КБ
// ============================================================================
#define BASE_BOOT_VER        0x0800FFF8U   
#define BASE_APP_VER         0x08007FFCU   

#define BOOT_SIG_BLOCK_ADDR  0x0800FFE8U  
#define APP_SIG_BLOCK_ADDR   0x08007FECU  

// ============================================================================
// Уникальные сигнатуры (F103)
// ============================================================================
#define BOOT_SIG_KEY0        0x10300000U
#define BOOT_SIG_KEY1        0x7AE58357U
#define BOOT_SIG_KEY2        0x58D8422BU
#define BOOT_SIG_KEY3        0xF940ACB1U

#define APP_SIG_KEY0         0x10300000U
#define APP_SIG_KEY1         0x244F9766U
#define APP_SIG_KEY2         0x884016F2U
#define APP_SIG_KEY3         0x0C4F36FAU

// Точки входа
#define BASE_APP_START_ADDR  0x08000000U  // Приложение: 0–32 КБ
#define BASE_BOOT_START_ADDR 0x08008000U  // Бутлоадер: 32–64 КБ

// ============================================================================
// Адреса для секций (Keil __at)
// ============================================================================
#define APP_RESETI_SECTION   ".ARM.__at_0x08007FE8"
#define APP_KEY0_SECTION     ".ARM.__at_0x08007FEC"
#define APP_KEY1_SECTION     ".ARM.__at_0x08007FF0"
#define APP_KEY2_SECTION     ".ARM.__at_0x08007FF4"
#define APP_KEY3_SECTION     ".ARM.__at_0x08007FF8"
#define APP_VER_F_SECTION    ".ARM.__at_0x08007FFC"

#define BOOT_KEY0_SECTION    ".ARM.__at_0x0800FFE8"
#define BOOT_KEY1_SECTION    ".ARM.__at_0x0800FFEC"
#define BOOT_KEY2_SECTION    ".ARM.__at_0x0800FFF0"
#define BOOT_KEY3_SECTION    ".ARM.__at_0x0800FFF4"
#define BOOT_VER_F_SECTION   ".ARM.__at_0x0800FFF8"

#endif // LPP_CONFIG_F103_H