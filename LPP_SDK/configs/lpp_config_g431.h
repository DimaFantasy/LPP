/**
 ******************************************************************************
 * @file    lpp_config_g431.h
 * @brief   LPP hardware configuration for STM32G431
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

#ifndef LPP_CONFIG_G431_H
#define LPP_CONFIG_G431_H

#include "stm32g4xx.h"
#include "stm32g4xx_hal.h"

// ============================================================================
// Пины и порт энкодера
// ============================================================================
#define X_ENCODER_PORT         GPIOB
#define X_ENCODER_CFG_PIN_A    GPIO_PIN_6   // PB6
#define X_ENCODER_CFG_PIN_B    GPIO_PIN_5   // PB5

// ============================================================================
// Память и адреса версий
// ============================================================================
#define BASE_BOOT_VER          0x0800FFF8U
#define BASE_APP_VER           0x08007FFCU

#define BOOT_SIG_BLOCK_ADDR    0x0800FFE8U  // BOOT KEY0
#define APP_SIG_BLOCK_ADDR     0x08007FECU  // APP  KEY0

// ============================================================================
// Уникальные сигнатуры (STM32G431CBTx)
// Полное соответствие PC-проверке
// ============================================================================

// --- BOOT ---
#define BOOT_SIG_KEY0          0x43100000U
#define BOOT_SIG_KEY1          0x5E6F7788U
#define BOOT_SIG_KEY2          0x99AABBCCU
#define BOOT_SIG_KEY3          0xDDEEFF01U

// --- APP ---
#define APP_SIG_KEY0           0x43100000U
#define APP_SIG_KEY1           0x9ABCDEF0U
#define APP_SIG_KEY2           0x0F1E2D3CU
#define APP_SIG_KEY3           0x4B5A6978U

// ============================================================================
// Базовые адреса
// ============================================================================
#define BASE_APP_START_ADDR    0x08000000U
#define BASE_BOOT_START_ADDR   0x08008000U   // бут: 32 КБ

// ============================================================================
// Адреса метаданных приложения (последние 24 байта)
// ============================================================================
#define APP_RESETI_SECTION     ".ARM.__at_0x08007FE8"
#define APP_KEY0_SECTION       ".ARM.__at_0x08007FEC"
#define APP_KEY1_SECTION       ".ARM.__at_0x08007FF0"
#define APP_KEY2_SECTION       ".ARM.__at_0x08007FF4"
#define APP_KEY3_SECTION       ".ARM.__at_0x08007FF8"
#define APP_VER_F_SECTION      ".ARM.__at_0x08007FFC"

// ============================================================================
// Сигнатуры бутлоадера (в конце бут-области)
// ============================================================================
#define BOOT_KEY0_SECTION      ".ARM.__at_0x0800FFE8"
#define BOOT_KEY1_SECTION      ".ARM.__at_0x0800FFEC"
#define BOOT_KEY2_SECTION      ".ARM.__at_0x0800FFF0"
#define BOOT_KEY3_SECTION      ".ARM.__at_0x0800FFF4"
#define BOOT_VER_F_SECTION     ".ARM.__at_0x0800FFF8"

#endif // LPP_CONFIG_G431_H
