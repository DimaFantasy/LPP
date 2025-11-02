/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/

/* USER CODE BEGIN Private defines */
////////////////////////////////////////////////////////////
#define IDX_JAMP_TO 25			// номер (IDX) 
typedef union {								// структура 
    struct {
			uint8_t  		ID; 				// Равняем по 32 бита
			uint8_t  		R_IDX; 		  // ID пакета	
			uint8_t     W_WRITE; 	  // 1 Записать данные, 0 Читаем данные			
			uint8_t     W_CURENT; 	// 0-Работает APP 1-Работает BOOT // Равняем по 32 бита						
			///
			uint8_t     W_ADRES; 	// 0-Работает APP 1-Работает BOOT // Равняем по 32 бита				
    } DAT; // всего 60 байт
    uint8_t BIN[64];		
} TYPE_APP_JAMP_TO;
extern TYPE_APP_JAMP_TO APP_JAMP_TO; // Прыгаем в адрес
////////////////////////////////////////////////////////////
#define IDX_APP_SPEED_TEST 24			// номер (IDX) 
typedef union {								// структура 
    struct {
			uint8_t  		ID; 				// Равняем по 32 бита
			uint8_t  		R_IDX; 		  // ID пакета	
			uint8_t     W_WRITE; 	  // 1 Записать данные, 0 Читаем данные			
			uint8_t     W_CURENT; 	// 0-Работает APP 1-Работает BOOT // Равняем по 32 бита						

			uint8_t     W_INFO[55]; // 12 слов по 4 байта = 48 байт
			
    } DAT; // всего 60 байт
    uint8_t BIN[64];		
} TYPE_APP_SPEED_TEST;
extern TYPE_APP_SPEED_TEST APP_SPEED_TEST;
////////////////////////////////////////////////////////////
#define IDX_WRITE 23			// номер (IDX) 
typedef union {								// структура 
    struct {
			uint8_t  		ID; 				// Равняем по 32 бита
			uint8_t  		R_IDX; 		  // ID пакета			
			uint8_t     W_CURENT; 	// 0-Работает APP 1-Работает BOOT // Равняем по 32 бита	
			uint8_t     W_COUNT;     // Число прошытых байт // 12 байт 
			// 
			uint32_t    W_ADRES;    // Адрес начала 						
			//uint32_t     W_INFO[12]; // 12 слов по 4 байта = 48 байт
			uint32_t     W_INFO[14]; // 14 слов по 4 байта = 56 байт
    } DAT; // всего 60 байт
    uint8_t BIN[64];		
} TYPE_APP_WRITE;
extern TYPE_APP_WRITE APP_WRITE; // Пишем байты в FLASH
////////////////////////////////////////////////////////////
#define IDX_ERASE 22			// номер (IDX) 
typedef union {								// структура 
    struct {
			uint8_t  		ID; 				// Равняем по 32 бита
			uint8_t  		R_IDX; 		  // ID пакета	
			uint8_t     W_WRITE; 	  // 1 Записать данные, 0 Читаем данные			
			uint8_t     W_CURENT; 	// 0-Работает APP 1-Работает BOOT // Равняем по 32 бита						
			// 
			uint32_t    W_START;        	// 			
			uint32_t    W_COUNT;         // 			 						
    } DAT;
    uint8_t BIN[64]; 
} TYPE_APP_ERASE;
extern TYPE_APP_ERASE APP_ERASE; // Стираем сектора
////////////////////////////////////////////////////////////
#define IDX_APP_ID 21			// номер (IDX) 
typedef union {
    struct {
        uint8_t   ID;           // 1 байт
        uint8_t   R_IDX;        // 1 байт
        uint8_t   W_WRITE;      // 1 байт
        uint8_t   W_CURENT;     // 1 байт

        uint32_t  W_ID[3];      // 12 байт
        uint32_t  W_A_VER;      // 4 байта
        uint32_t  W_B_VER;      // 4 байта
        uint32_t  W_A_NAME[4];  // 16 байт
        uint32_t  W_B_NAME[4];  // 16 байт
    } DAT; // всего 58 байт, но с выравниванием на 4 байта будет 60 или 64

    uint8_t BIN[64];           // выравниваем до 64 байт
} TYPE_APP_ID;
extern TYPE_APP_ID APP_ID; 	// нформация пошивки / чипа
///////////////////////////////////////////////////////////
#define BASE_BOOT_VER 0x0800FFEC // Начальный адресс версии BOOT
#define BASE_APP_VER  0x0800BFEC // Начальный адресс версии APP
//////////////////////////////////////////////////////////
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
