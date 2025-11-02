// ============================================================================
// LPP Configuration — STM32F103
// ============================================================================
#ifndef LPP_CONFIG_F103_H
#define LPP_CONFIG_F103_H

#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"

// ============================================================================
// Память и адреса версий
// ============================================================================
#define BASE_BOOT_VER  0x0800FFECU   // Адрес версии BOOT-прошивки
#define BASE_APP_VER   0x0800BFECU   // Адрес версии основной APP-прошивки

// ============================================================================
// Уникальные сигнатуры (идентификаторы прошивок)
// ============================================================================
// --- Сигнатура BOOT ---
#define BOOT_SIG_KEY0  0x10300000U
#define BOOT_SIG_KEY1  0x7AE58357U
#define BOOT_SIG_KEY2  0x58D8422BU
#define BOOT_SIG_KEY3  0xF940ACB1U

// --- Сигнатура APP ---
#define APP_SIG_KEY0   0x10300000U
#define APP_SIG_KEY1   0x244F9766U
#define APP_SIG_KEY2   0x884016F2U
#define APP_SIG_KEY3   0x0C4F36FAU

// ============================================================================
// Адреса для секций (__attribute__)
// ============================================================================
// Эти строки используются в объявлении констант прошивки (main.c)
#define APP_RESETI_SECTION    ".ARM.__at_0x0800BFE8"
#define APP_KEY0_SECTION      ".ARM.__at_0x0800BFEC"
#define APP_KEY1_SECTION      ".ARM.__at_0x0800BFF0"
#define APP_KEY2_SECTION      ".ARM.__at_0x0800BFF4"
#define APP_KEY3_SECTION      ".ARM.__at_0x0800BFF8"
#define APP_VER_F_SECTION     ".ARM.__at_0x0800BFFC"

// ============================================================================
// Переход из APP в BOOT (и обратно)
// ============================================================================
// Адрес Флага перехода (хранится в последнем секторе перед BOOT)
#define BASE_BOOT_JUMP_FLAG_ADDR   0x0800BFE8U

#define BOOT_JUMP_FLAG_SET         0xFFFFFFF0U  // Устанавливается APP → переход в BOOT
#define BOOT_JUMP_FLAG_DEFAULT     0xFFFFFFFFU  // Сброшено — обычный запуск APP

// Точки входа
#define BASE_APP_START_ADDR        0x08000000U  // Адрес приложения
#define BASE_BOOT_START_ADDR       0x0800C000U  // Адрес загрузчика

#endif // LPP_CONFIG_F103_H
