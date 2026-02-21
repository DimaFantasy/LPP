/**
 ******************************************************************************
 * @file    lpp_config_f411.h
 * @brief   LPP hardware configuration for STM32F411CEU6
 *
 * This file is part of the LPP (Laser Printer Platform) SDK —
 * a software development kit for embedded laser printer control,
 * designed for STM32 microcontrollers.
 *
 * Copyright (C) 2025  Dima
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * Official channel: https://t.me/LPP_Printer
 * Community chat:    https://t.me/LPP_Printer_Chat
 ******************************************************************************
 */

#ifndef LPP_CONFIG_F411_H
#define LPP_CONFIG_F411_H

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

// ============================================================================
// Защищённые GPIO-пины (не должны сбрасываться или переинициализироваться)
// ============================================================================
typedef struct {
    GPIO_TypeDef *port;
    uint16_t      pin;
} lpp_protected_pin_t;

static const lpp_protected_pin_t lpp_protected_pins[] = {
    // USB пины (критически важны для связи)
    { GPIOA, GPIO_PIN_11 },  // PA11 — USB DM (Data-)
    { GPIOA, GPIO_PIN_12 },  // PA12 — USB DP (Data+)
    
    // SWD пины для отладки (опционально, можно закомментировать если не используете)
    { GPIOA, GPIO_PIN_13 },  // PA13 — SWDIO
    { GPIOA, GPIO_PIN_14 },  // PA14 — SWCLK

    { NULL,  0 }             // Завершающий элемент массива
};

// ============================================================================
// Память и адреса версий
// STM32F411CEU6: 512KB Flash (0x08000000 - 0x0807FFFF)
// Разбивка:
//   APP:  0x08000000 - 0x08007FFF (32 KB, sectors 0-1)
//   BOOT: 0x08008000 - 0x0800FFFF (32 KB, sector 2)
// ============================================================================

// --- Адреса версий (в последних 8 байтах области) ---
#define BASE_APP_VER           0x08007FFCU  // Последние 4 байта APP
#define BASE_BOOT_VER          0x0800FFF8U  // Последние 8 байт BOOT (оставляем запас)

// --- Адреса сигнатур ---
#define APP_SIG_BLOCK_ADDR     0x08007FECU  // APP  KEY0 (16 байт до конца)
#define BOOT_SIG_BLOCK_ADDR    0x0800FFE8U  // BOOT KEY0 (24 байта до конца)

// ============================================================================
// Уникальные сигнатуры (STM32F411CEU6)
// Полное соответствие PC-проверке
// ============================================================================

// --- BOOT ---
#define BOOT_SIG_KEY0          0x41100000U
#define BOOT_SIG_KEY1          0x52AB83E1U
#define BOOT_SIG_KEY2          0x8C74D2F9U
#define BOOT_SIG_KEY3          0x1A36E4B7U

// --- APP ---
#define APP_SIG_KEY0           0x41100000U
#define APP_SIG_KEY1           0xF6D13925U
#define APP_SIG_KEY2           0x0B97AC8EU
#define APP_SIG_KEY3           0xCD42F5A3U

// ============================================================================
// Базовые адреса
// ============================================================================
#define BASE_APP_START_ADDR    0x08000000U  // Начало APP
#define BASE_BOOT_START_ADDR   0x08008000U  // Начало BOOT (бут: 32 КБ)

// ============================================================================
// Адреса метаданных приложения (последние 24 байта APP области)
// APP: 32KB = 0x8000, конец = 0x08007FFF
// Метаданные с 0x08007FE8 до 0x08007FFF (24 байта)
// ============================================================================
#define APP_RESETI_SECTION     ".ARM.__at_0x08007FE8"  // 4 байта: счетчик сбросов
#define APP_KEY0_SECTION       ".ARM.__at_0x08007FEC"  // 4 байта: ключ 0
#define APP_KEY1_SECTION       ".ARM.__at_0x08007FF0"  // 4 байта: ключ 1
#define APP_KEY2_SECTION       ".ARM.__at_0x08007FF4"  // 4 байта: ключ 2
#define APP_KEY3_SECTION       ".ARM.__at_0x08007FF8"  // 4 байта: ключ 3
#define APP_VER_F_SECTION      ".ARM.__at_0x08007FFC"  // 4 байта: версия

// ============================================================================
// Сигнатуры бутлоадера (в конце BOOT области)
// BOOT: 32KB начиная с 0x08008000, конец = 0x0800FFFF
// Метаданные с 0x0800FFE8 до 0x0800FFFF (24 байта)
// ============================================================================
#define BOOT_KEY0_SECTION      ".ARM.__at_0x0800FFE8"  // 4 байта: ключ 0
#define BOOT_KEY1_SECTION      ".ARM.__at_0x0800FFEC"  // 4 байта: ключ 1
#define BOOT_KEY2_SECTION      ".ARM.__at_0x0800FFF0"  // 4 байта: ключ 2
#define BOOT_KEY3_SECTION      ".ARM.__at_0x0800FFF4"  // 4 байта: ключ 3
#define BOOT_VER_F_SECTION     ".ARM.__at_0x0800FFF8"  // 4 байта: версия


#endif // LPP_CONFIG_F411_H
