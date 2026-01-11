/**
 ******************************************************************************
 * @file    lpp_config_f103.h
 * @brief   LPP hardware configuration for STM32F103 (Blue Pill)
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

#ifndef LPP_CONFIG_F103_H
#define LPP_CONFIG_F103_H

#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"
#include "counter.h"

// ============================================================================
// Пины и порт энкодера
// ============================================================================
#define X_ENCODER_PORT    GPIOB
#define X_ENCODER_CFG_PIN_A   GPIO_PIN_6   // PB6
#define X_ENCODER_CFG_PIN_B   GPIO_PIN_8   // PB8

// ============================================================================
// Память и адреса версий (НОВАЯ 32+32 КБ архитектура)
// ============================================================================
#define BASE_BOOT_VER  0x0800FFF8U   // версия бута — последние 4 байта
#define BASE_APP_VER   0x08007FFCU   // версия приложения — последние 4 байта

#define BOOT_SIG_BLOCK_ADDR  0x0800FFE8U  // BOOT_KEY0
#define APP_SIG_BLOCK_ADDR   0x08007FECU  // APP KEY0

// ============================================================================
// Уникальные сигнатуры 
// ============================================================================
#define BOOT_SIG_KEY0  0x10300000U
#define BOOT_SIG_KEY1  0x7AE58357U
#define BOOT_SIG_KEY2  0x58D8422BU
#define BOOT_SIG_KEY3  0xF940ACB1U

#define APP_SIG_KEY0   0x10300000U
#define APP_SIG_KEY1   0x244F9766U
#define APP_SIG_KEY2   0x884016F2U
#define APP_SIG_KEY3   0x0C4F36FAU

// Точки входа
#define BASE_APP_START_ADDR        0x08000000U  // приложение: 0–32 КБ
#define BASE_BOOT_START_ADDR       0x08008000U  // бутлоадер: 32–64 КБ

// ============================================================================
// Адреса для секций 
// ============================================================================
// --- Приложение (0–32 КБ) ---
#define APP_RESETI_SECTION    ".ARM.__at_0x08007FE8"
#define APP_KEY0_SECTION      ".ARM.__at_0x08007FEC"
#define APP_KEY1_SECTION      ".ARM.__at_0x08007FF0"
#define APP_KEY2_SECTION      ".ARM.__at_0x08007FF4"
#define APP_KEY3_SECTION      ".ARM.__at_0x08007FF8"
#define APP_VER_F_SECTION     ".ARM.__at_0x08007FFC"

// --- Бутлоадер (32–64 КБ) ---
#define BOOT_KEY0_SECTION     ".ARM.__at_0x0800FFE8"
#define BOOT_KEY1_SECTION     ".ARM.__at_0x0800FFEC"
#define BOOT_KEY2_SECTION     ".ARM.__at_0x0800FFF0"
#define BOOT_KEY3_SECTION     ".ARM.__at_0x0800FFF4"
#define BOOT_VER_F_SECTION    ".ARM.__at_0x0800FFF8"

#endif // LPP_CONFIG_F103_H